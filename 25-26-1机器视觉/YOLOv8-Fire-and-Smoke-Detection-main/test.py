import os
import cv2
import torch
import glob
import platform
from pathlib import Path
from ultralytics import YOLO
import matplotlib.pyplot as plt
import numpy as np

# ==================== 全局配置变量 ====================
# 神经网络配置
MODEL_SIZE = "s"  # 可选: "n", "s", "m", "l", "x" - 控制模型大小和层数
MODEL_TYPE = "detect"  # 任务类型: "detect", "segment", "classify"

# 训练配置
TRAIN_EPOCHS = 100
TRAIN_IMGSZ = 640
TRAIN_BATCH = 8
TRAIN_LEARNING_RATE = 0.01

# 推理配置
INFERENCE_CONF = 0.25  # 置信度阈值
INFERENCE_IOU = 0.45   # IOU阈值

# 路径配置
PROJECT_NAME = "FireDetection"

# 设备配置
AUTO_DEVICE = True  # 自动选择设备
FORCE_CPU = False   # 强制使用CPU

# ==================== 模型层数映射 ====================
MODEL_ARCHITECTURE = {
    "n": {
        "name": "YOLOv8n",
        "layers": 168,
        "parameters": "3.2M",
        "description": "轻量级 - 最快速度"
    },
    "s": {
        "name": "YOLOv8s", 
        "layers": 168,
        "parameters": "11.2M",
        "description": "小模型 - 平衡速度精度"
    },
    "m": {
        "name": "YOLOv8m",
        "layers": 218,
        "parameters": "25.9M",
        "description": "中模型 - 推荐使用"
    },
    "l": {
        "name": "YOLOv8l",
        "layers": 268,
        "parameters": "43.7M",
        "description": "大模型 - 高精度"
    },
    "x": {
        "name": "YOLOv8x",
        "layers": 268,
        "parameters": "68.2M",
        "description": "超大模型 - 最高精度"
    }
}

class CrossPlatformForestFireDetector:
    def __init__(self, model_path=None):
        """
        初始化跨平台森林火灾检测器
        """
        self.conf_threshold = INFERENCE_CONF
        self.model = None
        self.system_info = self.get_system_info()
        self.setup_environment()
        self.load_model(model_path)
    
    def get_system_info(self):
        """获取系统信息"""
        system = platform.system()
        info = {
            "system": system,
            "is_windows": system == "Windows",
            "is_mac": system == "Darwin",
            "is_linux": system == "Linux",
            "architecture": platform.architecture()[0],
            "processor": platform.processor()
        }
        return info
    
    def setup_environment(self):
        """设置跨平台环境"""
        print("=" * 60)
        print("🌲 森林火灾识别系统 - 跨平台版")
        print("=" * 60)
        
        # 显示系统信息
        print(f"💻 操作系统: {self.system_info['system']}")
        print(f"🔧 处理器: {self.system_info['processor']}")
        print(f"📊 架构: {self.system_info['architecture']}")
        
        # 显示模型配置
        model_config = MODEL_ARCHITECTURE.get(MODEL_SIZE, MODEL_ARCHITECTURE["s"])
        print(f"🤖 模型配置: {model_config['name']}")
        print(f"📈 网络层数: {model_config['layers']}层")
        print(f"💾 参数量: {model_config['parameters']}")
        print(f"🎯 特点: {model_config['description']}")
        
        # 设备检测和选择
        self.device = self.select_device()
        
        # 设置跨平台工作目录
        self.setup_cross_platform_paths()
        
        print("✅ 环境初始化完成")
    
    def select_device(self):
        """选择计算设备"""
        if FORCE_CPU:
            print("⚠️ 强制使用CPU模式")
            return "cpu"
        
        if not AUTO_DEVICE:
            print("⚠️ 手动设备选择模式")
            return 0  # 默认
        
        # 自动设备选择
        if torch.cuda.is_available():
            gpu_name = torch.cuda.get_device_name(0)
            print(f"🎯 检测到CUDA GPU: {gpu_name}")
            return 0
        elif hasattr(torch.backends, 'mps') and torch.backends.mps.is_available():
            print("🍎 检测到Apple Silicon MPS")
            return "mps"
        else:
            print("⚠️ 使用CPU进行推理")
            return "cpu"
    
    def setup_cross_platform_paths(self):
        """设置跨平台路径"""
        # 使用平台特定的路径
        if self.system_info['is_windows']:
            # Windows: 使用用户文档目录
            self.home_dir = str(Path.home() / "Documents" / PROJECT_NAME)
        elif self.system_info['is_mac']:
            # Mac: 使用用户主目录
            self.home_dir = str(Path.home() / PROJECT_NAME)
        else:
            # Linux和其他系统
            self.home_dir = str(Path.home() / PROJECT_NAME)
        
        # 创建必要的目录
        directories = [
            self.home_dir,
            f"{self.home_dir}/results",
            f"{self.home_dir}/datasets",
            f"{self.home_dir}/models",
            f"{self.home_dir}/exports"
        ]
        
        for directory in directories:
            os.makedirs(directory, exist_ok=True)
        
        print(f"📁 工作目录: {self.home_dir}")
    
    def get_model_path(self, model_path=None):
        """获取模型路径（跨平台兼容）"""
        if model_path and os.path.exists(model_path):
            return model_path
        
        # 检查工作目录中的模型
        local_model_path = f"{self.home_dir}/models/best.pt"
        if os.path.exists(local_model_path):
            return local_model_path
        
        # 使用全局配置的模型
        model_name = f"yolov8{MODEL_SIZE}.pt"
        return model_name
    
    def load_model(self, model_path=None):
        """
        加载YOLOv8模型
        """
        try:
            final_model_path = self.get_model_path(model_path)
            
            if final_model_path.endswith('.pt') and os.path.exists(final_model_path):
                print(f"🔧 加载自定义模型: {final_model_path}")
                self.model = YOLO(final_model_path)
            else:
                print(f"🔧 加载预训练模型: yolov8{MODEL_SIZE}.pt")
                self.model = YOLO(f'yolov8{MODEL_SIZE}.pt')
            
            print("✅ 模型加载成功!")
            
            # 显示模型信息
            if hasattr(self.model, 'model'):
                if hasattr(self.model.model, 'nc'):
                    print(f"🎯 模型类别数: {self.model.model.nc}")
            
        except Exception as e:
            print(f"❌ 模型加载失败: {e}")
            # 尝试加载基础模型作为备用
            try:
                print("🔄 尝试加载基础YOLOv8n模型...")
                self.model = YOLO('yolov8n.pt')
                print("✅ 备用模型加载成功!")
            except Exception as e2:
                print(f"❌ 所有模型加载尝试都失败: {e2}")
    
    def detect_image(self, image_path, save=True, show=True):
        """
        对单张图像进行火灾检测
        """
        print(f"🖼️ 处理图像: {image_path}")
        
        # 跨平台路径处理
        image_path = self.normalize_path(image_path)
        
        if not os.path.exists(image_path):
            print(f"❌ 图像文件不存在: {image_path}")
            return None
        
        try:
            # 执行推理
            results = self.model.predict(
                source=image_path,
                conf=self.conf_threshold,
                iou=INFERENCE_IOU,
                save=save,
                save_txt=True,
                save_conf=True,
                device=self.device
            )
            
            # 显示结果
            if show and len(results) > 0:
                result = results[0]
                self.display_detection_result(result, image_path)
            
            return results
            
        except Exception as e:
            print(f"❌ 图像检测失败: {e}")
            return None
    
    def detect_video(self, video_path, output_path=None):
        """
        对视频进行火灾检测
        """
        print(f"🎥 处理视频: {video_path}")
        
        video_path = self.normalize_path(video_path)
        
        if not os.path.exists(video_path):
            print(f"❌ 视频文件不存在: {video_path}")
            return None
        
        if output_path is None:
            video_name = Path(video_path).stem
            output_path = f"{self.home_dir}/results/{video_name}_detected.mp4"
        
        try:
            # 执行视频推理
            results = self.model.predict(
                source=video_path,
                conf=self.conf_threshold,
                save=True,
                project=f"{self.home_dir}/results",
                name="video_detection",
                device=self.device
            )
            
            print(f"✅ 视频处理完成: {output_path}")
            return results
            
        except Exception as e:
            print(f"❌ 视频检测失败: {e}")
            return None
    
    def detect_webcam(self, camera_id=0):
        """
        使用摄像头进行实时火灾检测
        """
        print("📹 启动摄像头实时检测...")
        
        # 在Windows上可能需要不同的后端
        if self.system_info['is_windows']:
            cap = cv2.VideoCapture(camera_id, cv2.CAP_DSHOW)
        else:
            cap = cv2.VideoCapture(camera_id)
        
        if not cap.isOpened():
            print("❌ 无法打开摄像头")
            # 尝试其他摄像头ID
            for i in range(1, 5):
                cap = cv2.VideoCapture(i)
                if cap.isOpened():
                    print(f"✅ 找到摄像头 ID: {i}")
                    break
            else:
                print("❌ 未找到可用的摄像头")
                return
        
        print("🎯 按 'q' 键退出实时检测")
        print("🎯 按 's' 键保存当前帧")
        
        frame_count = 0
        try:
            while True:
                ret, frame = cap.read()
                if not ret:
                    print("❌ 无法读取摄像头画面")
                    break
                
                # 执行推理
                results = self.model(frame, conf=self.conf_threshold, device=self.device)
                
                # 绘制检测结果
                annotated_frame = results[0].plot()
                
                # 显示系统信息
                fps = cap.get(cv2.CAP_PROP_FPS)
                status_text = [
                    f"FPS: {fps:.1f}",
                    f"Device: {self.device}",
                    f"Model: YOLOv8{MODEL_SIZE}",
                    "Press 'q' to quit, 's' to save"
                ]
                
                for i, text in enumerate(status_text):
                    y_position = 30 + i * 25
                    cv2.putText(annotated_frame, text, (10, y_position), 
                               cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2)
                
                # 显示结果
                cv2.imshow('森林火灾实时检测 - Cross Platform', annotated_frame)
                
                # 按键处理
                key = cv2.waitKey(1) & 0xFF
                if key == ord('q'):
                    break
                elif key == ord('s'):
                    # 保存当前帧
                    save_path = f"{self.home_dir}/results/capture_{frame_count:04d}.jpg"
                    cv2.imwrite(save_path, annotated_frame)
                    print(f"💾 保存截图: {save_path}")
                    frame_count += 1
        
        finally:
            cap.release()
            cv2.destroyAllWindows()
    
    def normalize_path(self, path):
        """标准化路径（跨平台兼容）"""
        return str(Path(path))
    
    def display_detection_result(self, result, image_path):
        """
        显示检测结果
        """
        boxes = result.boxes
        if boxes is not None and len(boxes) > 0:
            print(f"🔥 检测到 {len(boxes)} 个火灾区域:")
            
            for i, box in enumerate(boxes):
                cls = int(box.cls[0])
                conf = float(box.conf[0])
                coords = box.xyxy[0].cpu().numpy()
                
                class_name = "火灾" if cls == 0 else f"类别{cls}"
                print(f"  区域 {i+1}: {class_name}, 置信度={conf:.4f}")
        else:
            print("✅ 未检测到火灾")
        
        # 显示结果文件路径
        if hasattr(result, 'save_dir'):
            result_image_path = f"{result.save_dir}/{os.path.basename(image_path)}"
            if os.path.exists(result_image_path):
                print(f"💾 结果图像已保存: {result_image_path}")
                
                # 在不同平台上尝试打开图像
                if self.system_info['is_windows']:
                    os.system(f'start "" "{result_image_path}"')
                elif self.system_info['is_mac']:
                    os.system(f'open "{result_image_path}"')
                elif self.system_info['is_linux']:
                    os.system(f'xdg-open "{result_image_path}"')
    
    def batch_detect(self, images_dir, output_dir=None):
        """
        批量检测图像
        """
        print(f"📁 批量处理目录: {images_dir}")
        
        images_dir = self.normalize_path(images_dir)
        
        if not os.path.exists(images_dir):
            print(f"❌ 图像目录不存在: {images_dir}")
            return []
        
        if output_dir is None:
            output_dir = f"{self.home_dir}/results/batch_detection"
        os.makedirs(output_dir, exist_ok=True)
        
        # 跨平台图像格式支持
        image_extensions = ['*.jpg', '*.jpeg', '*.png', '*.bmp', '*.tiff', '*.webp']
        image_paths = []
        
        for extension in image_extensions:
            image_paths.extend(glob.glob(f"{images_dir}/{extension}"))
            # 处理大写扩展名
            image_paths.extend(glob.glob(f"{images_dir}/{extension.upper()}"))
        
        print(f"📊 找到 {len(image_paths)} 张图像")
        
        all_results = []
        for i, image_path in enumerate(image_paths):
            print(f"🔍 处理图像 {i+1}/{len(image_paths)}: {os.path.basename(image_path)}")
            results = self.detect_image(image_path, save=True, show=False)
            all_results.append((image_path, results))
        
        self.generate_report(all_results)
        return all_results
    
    def generate_report(self, results):
        """
        生成检测报告
        """
        print("\n" + "="*60)
        print("📊 森林火灾检测报告 - 跨平台版")
        print("="*60)
        
        total_images = len(results)
        fire_detected = 0
        total_fires = 0
        
        for image_path, result in results:
            if result and len(result) > 0 and result[0].boxes is not None:
                fire_count = len(result[0].boxes)
                if fire_count > 0:
                    fire_detected += 1
                    total_fires += fire_count
        
        # 显示报告
        model_info = MODEL_ARCHITECTURE.get(MODEL_SIZE, MODEL_ARCHITECTURE["s"])
        
        print(f"🤖 模型信息: {model_info['name']}")
        print(f"💻 运行平台: {self.system_info['system']}")
        print(f"⚡ 计算设备: {self.device}")
        print(f"📁 处理图像总数: {total_images}")
        print(f"🔥 检测到火灾的图像: {fire_detected}")
        print(f"🔥 总火灾区域数: {total_fires}")
        
        if total_images > 0:
            detection_rate = (fire_detected / total_images) * 100
            print(f"📈 火灾检测率: {detection_rate:.2f}%")
        
        print("="*60)

def show_model_options():
    """显示模型选项"""
    print("\n🤖 可用的神经网络配置:")
    print("-" * 50)
    for size, info in MODEL_ARCHITECTURE.items():
        current = " ← 当前" if size == MODEL_SIZE else ""
        print(f"{size.upper()}: {info['name']} - {info['description']}{current}")
        print(f"    层数: {info['layers']}, 参数: {info['parameters']}")
    print("-" * 50)

def main():
    """主函数"""
    # 显示模型选项
    show_model_options()
    
    # 初始化检测器
    detector = CrossPlatformForestFireDetector()
    
    while True:
        print(f"\n当前模型: YOLOv8{MODEL_SIZE.upper()} - {MODEL_ARCHITECTURE[MODEL_SIZE]['description']}")
        print("\n请选择操作:")
        print("1. 🖼️ 图像检测")
        print("2. 🎥 视频检测") 
        print("3. 📹 实时摄像头检测")
        print("4. 📁 批量图像检测")
        print("5. ⚙️ 显示系统信息")
        print("6. 🤖 显示模型选项")
        print("0. ❌ 退出")
        
        choice = input("请输入选择 (0-6): ").strip()
        
        if choice == '1':
            image_path = input("请输入图像路径: ").strip()
            detector.detect_image(image_path)
        
        elif choice == '2':
            video_path = input("请输入视频路径: ").strip()
            detector.detect_video(video_path)
        
        elif choice == '3':
            detector.detect_webcam()
        
        elif choice == '4':
            images_dir = input("请输入图像目录路径: ").strip()
            detector.batch_detect(images_dir)
        
        elif choice == '5':
            print(f"\n💻 系统信息:")
            for key, value in detector.system_info.items():
                print(f"  {key}: {value}")
            print(f"  计算设备: {detector.device}")
        
        elif choice == '6':
            show_model_options()
        
        elif choice == '0':
            print("👋 感谢使用跨平台森林火灾识别系统!")
            break
        
        else:
            print("❌ 无效选择，请重新输入")

if __name__ == "__main__":
    main()