"""
林火识别模型训练脚本 - YOLOv8 Custom Training
Forest Fire Detection Model Training Script
"""

import os
import yaml
import torch
import argparse
from pathlib import Path
from ultralytics import YOLO
import matplotlib.pyplot as plt
import numpy as np

# ==================== 训练配置 ====================
class TrainingConfig:
    # 模型配置
    MODEL_SIZE = "s"  # 可选: "n", "s", "m", "l", "x"
    PRETRAINED_MODEL = True  # 是否使用预训练权重
    
    # 训练参数
    EPOCHS = 150
    IMAGE_SIZE = 640
    BATCH_SIZE = 16
    LEARNING_RATE = 0.01
    PATIENCE = 25  # 早停耐心值
    
    # 数据增强
    AUGMENT = True
    HSV_H = 0.015  # 色调增强
    HSV_S = 0.7    # 饱和度增强  
    HSV_V = 0.4    # 亮度增强
    FLIP_LR = 0.5  # 左右翻转概率
    
    # 优化器
    OPTIMIZER = "AdamW"  # SGD, Adam, AdamW, RMSprop
    WEIGHT_DECAY = 0.0005
    MOMENTUM = 0.937
    
    # 路径配置
    PROJECT_NAME = "ForestFireDetection"
    DATASET_DIR = "datasets/fire_dataset"  # 数据集路径
    
    # 设备配置
    DEVICE = "auto"  # "auto", "cpu", "cuda", "mps" 或 0,1,2,3

class ForestFireTrainer:
    def __init__(self, config):
        self.config = config
        self.model = None
        self.setup_environment()
        
    def setup_environment(self):
        """设置训练环境"""
        print("=" * 60)
        print("🔥 林火识别模型训练系统")
        print("=" * 60)
        
        # 显示训练配置
        self.print_training_config()
        
        # 设置设备
        self.device = self.setup_device()
        
        # 创建目录结构
        self.setup_directories()
        
        # 检查数据集
        self.check_dataset()
        
    def print_training_config(self):
        """打印训练配置"""
        print("📋 训练配置:")
        print(f"  🤖 模型: YOLOv8{self.config.MODEL_SIZE.upper()}")
        print(f"  📊 训练轮数: {self.config.EPOCHS}")
        print(f"  🖼️ 图像尺寸: {self.config.IMAGE_SIZE}")
        print(f"  📦 批大小: {self.config.BATCH_SIZE}")
        print(f"  📈 学习率: {self.config.LEARNING_RATE}")
        print(f"  🔄 数据增强: {self.config.AUGMENT}")
        print(f"  ⚡ 优化器: {self.config.OPTIMIZER}")
        
    def setup_device(self):
        """设置训练设备"""
        if self.config.DEVICE == "auto":
            if torch.cuda.is_available():
                device = 0
                print(f"🎯 使用GPU: {torch.cuda.get_device_name(0)}")
            elif hasattr(torch.backends, 'mps') and torch.backends.mps.is_available():
                device = "mps"
                print("🍎 使用Apple Silicon MPS")
            else:
                device = "cpu"
                print("⚠️ 使用CPU训练，速度较慢")
        else:
            device = self.config.DEVICE
            print(f"🔧 使用指定设备: {device}")
            
        return device
    
    def setup_directories(self):
        """创建目录结构"""
        # 项目根目录
        self.project_dir = Path.home() / self.config.PROJECT_NAME
        self.project_dir.mkdir(exist_ok=True)
        
        # 子目录
        directories = [
            self.project_dir / "datasets",
            self.project_dir / "models",
            self.project_dir / "results",
            self.project_dir / "exports"
        ]
        
        for dir_path in directories:
            dir_path.mkdir(exist_ok=True)
            
        print(f"📁 项目目录: {self.project_dir}")
    
    def check_dataset(self):
        """检查数据集完整性"""
        dataset_path = self.project_dir / self.config.DATASET_DIR
        
        if not dataset_path.exists():
            print(f"❌ 数据集路径不存在: {dataset_path}")
            print("请将数据集放置在以下目录结构:")
            print(f"""
            {dataset_path}/
            ├── train/
            │   ├── images/
            │   └── labels/
            ├── val/
            │   ├── images/
            │   └── labels/
            ├── test/
            │   ├── images/
            │   └── labels/
            └── data.yaml
            """)
            return False
        
        # 检查必要的文件和目录
        required_paths = [
            dataset_path / "data.yaml",
            dataset_path / "train/images",
            dataset_path / "train/labels", 
            dataset_path / "val/images",
            dataset_path / "val/labels"
        ]
        
        for path in required_paths:
            if not path.exists():
                print(f"❌ 缺失必要文件/目录: {path}")
                return False
        
        # 检查数据YAML文件
        try:
            with open(dataset_path / "data.yaml", 'r') as f:
                data_cfg = yaml.safe_load(f)
            
            print("✅ 数据集配置:")
            print(f"  类别数: {data_cfg.get('nc', '未知')}")
            print(f"  类别名称: {data_cfg.get('names', '未知')}")
            print(f"  训练图像: {len(list((dataset_path / 'train/images').glob('*')))}")
            print(f"  验证图像: {len(list((dataset_path / 'val/images').glob('*')))}")
            
            if (dataset_path / "test/images").exists():
                print(f"  测试图像: {len(list((dataset_path / 'test/images').glob('*')))}")
                
        except Exception as e:
            print(f"❌ 数据配置文件错误: {e}")
            return False
            
        self.dataset_path = dataset_path
        return True
    
    def analyze_dataset(self):
        """分析数据集统计信息"""
        print("\n📊 数据集分析:")
        
        # 分析训练集标注
        train_labels_dir = self.dataset_path / "train/labels"
        if train_labels_dir.exists():
            label_files = list(train_labels_dir.glob("*.txt"))
            
            if label_files:
                class_counts = {}
                total_objects = 0
                
                for label_file in label_files:
                    with open(label_file, 'r') as f:
                        for line in f:
                            if line.strip():
                                class_id = int(line.strip().split()[0])
                                class_counts[class_id] = class_counts.get(class_id, 0) + 1
                                total_objects += 1
                
                print(f"  总标注对象: {total_objects}")
                print(f"  类别分布: {class_counts}")
                
                # 读取类别名称
                with open(self.dataset_path / "data.yaml", 'r') as f:
                    data_cfg = yaml.safe_load(f)
                
                if 'names' in data_cfg:
                    for class_id, count in class_counts.items():
                        class_name = data_cfg['names'].get(class_id, f'class_{class_id}')
                        print(f"    {class_name}: {count} 个实例")
    
    def create_model(self):
        """创建模型"""
        print("\n🤖 创建模型...")
        
        if self.config.PRETRAINED_MODEL:
            # 使用预训练权重
            model_name = f"yolov8{self.config.MODEL_SIZE}.pt"
            print(f"  加载预训练模型: {model_name}")
            self.model = YOLO(model_name)
        else:
            # 从零开始训练
            model_name = f"yolov8{self.config.MODEL_SIZE}.yaml"
            print(f"  从零开始训练: {model_name}")
            self.model = YOLO(model_name)
        
        print("✅ 模型创建完成")
    
    def setup_training_arguments(self):
        """设置训练参数"""
        args = {
            # 基础配置
            'data': str(self.dataset_path / "data.yaml"),
            'epochs': self.config.EPOCHS,
            'imgsz': self.config.IMAGE_SIZE,
            'batch': self.config.BATCH_SIZE,
            'patience': self.config.PATIENCE,
            
            # 优化器配置
            'lr0': self.config.LEARNING_RATE,
            'lrf': 0.01,  # 最终学习率倍数
            'momentum': self.config.MOMENTUM,
            'weight_decay': self.config.WEIGHT_DECAY,
            'optimizer': self.config.OPTIMIZER,
            
            # 数据增强
            'hsv_h': self.config.HSV_H,
            'hsv_s': self.config.HSV_S,
            'hsv_v': self.config.HSV_V,
            'fliplr': self.config.FLIP_LR,
            'mosaic': 1.0,  # mosaic数据增强
            
            # 训练策略
            'cos_lr': True,  # 余弦学习率衰减
            'warmup_epochs': 3.0,  # 热身轮数
            'warmup_momentum': 0.8,
            'close_mosaic': 10,  # 最后10轮关闭mosaic
            
            # 设备配置
            'device': self.device,
            'workers': 8,  # 数据加载线程
            
            # 保存配置
            'save': True,
            'save_period': 10,  # 每10轮保存一次
            'exist_ok': True,  # 覆盖现有运行
            'project': str(self.project_dir / "results"),
            'name': f"yolov8{self.config.MODEL_SIZE}_fire_detection",
            
            # 验证配置
            'val': True,  # 训练期间验证
            'cache': False,  # 数据缓存 (True可加速但需要更多内存)
        }
        
        return args
    
    def train(self):
        """开始训练"""
        print("\n🚀 开始模型训练...")
        
        # 创建模型
        self.create_model()
        
        # 设置训练参数
        train_args = self.setup_training_arguments()
        
        try:
            # 开始训练
            results = self.model.train(**train_args)
            
            print("✅ 训练完成!")
            return results
            
        except Exception as e:
            print(f"❌ 训练失败: {e}")
            return None
    
    def validate_model(self, model_path=None):
        """验证模型性能"""
        print("\n🔍 验证模型性能...")
        
        if model_path is None:
            # 自动找到最佳模型
            model_path = self.project_dir / "results" / f"yolov8{self.config.MODEL_SIZE}_fire_detection" / "weights" / "best.pt"
        
        if not os.path.exists(model_path):
            print(f"❌ 模型文件不存在: {model_path}")
            return None
        
        try:
            # 加载最佳模型
            best_model = YOLO(str(model_path))
            
            # 在验证集上验证
            metrics = best_model.val(
                data=str(self.dataset_path / "data.yaml"),
                split='val',
                device=self.device
            )
            
            print("📊 验证结果:")
            print(f"  mAP50: {metrics.box.map50:.4f}")
            print(f"  mAP50-95: {metrics.box.map:.4f}")
            print(f"  精确度: {metrics.box.mp:.4f}")
            print(f"  召回率: {metrics.box.mr:.4f}")
            
            return metrics
            
        except Exception as e:
            print(f"❌ 验证失败: {e}")
            return None
    
    def export_model(self, model_path=None, format='onnx'):
        """导出模型"""
        print(f"\n📤 导出模型为 {format.upper()} 格式...")
        
        if model_path is None:
            model_path = self.project_dir / "results" / f"yolov8{self.config.MODEL_SIZE}_fire_detection" / "weights" / "best.pt"
        
        if not os.path.exists(model_path):
            print(f"❌ 模型文件不存在: {model_path}")
            return None
        
        try:
            model = YOLO(str(model_path))
            
            # 导出模型
            export_path = model.export(format=format, dynamic=True)
            
            print(f"✅ 模型导出成功: {export_path}")
            return export_path
            
        except Exception as e:
            print(f"❌ 模型导出失败: {e}")
            return None
    
    def run_complete_pipeline(self):
        """运行完整的训练流程"""
        # 1. 环境检查
        if not self.check_dataset():
            return False
        
        # 2. 数据分析
        self.analyze_dataset()
        
        # 3. 开始训练
        results = self.train()
        if results is None:
            return False
        
        # 4. 验证模型
        metrics = self.validate_model()
        if metrics is None:
            return False
        
        # 5. 导出模型
        export_path = self.export_model()
        
        print("\n🎉 训练流程完成!")
        print(f"📁 最佳模型: {self.project_dir}/results/yolov8{self.config.MODEL_SIZE}_fire_detection/weights/best.pt")
        if export_path:
            print(f"📤 导出模型: {export_path}")
        
        return True

def create_sample_data_yaml(dataset_path):
    """创建示例数据配置文件"""
    data_config = {
        'path': str(dataset_path),  # 数据集根目录
        'train': 'train/images',    # 训练图像路径
        'val': 'val/images',        # 验证图像路径
        'test': 'test/images',      # 测试图像路径 (可选)
        
        'nc': 2,  # 类别数
        'names': {
            0: 'fire',     # 火焰
            1: 'smoke'     # 烟雾
        },
        
        # 可选: 下载链接
        'download': None
    }
    
    yaml_path = dataset_path / "data.yaml"
    with open(yaml_path, 'w') as f:
        yaml.dump(data_config, f, default_flow_style=False)
    
    print(f"✅ 创建示例数据配置: {yaml_path}")
    return yaml_path

def main():
    """主函数"""
    parser = argparse.ArgumentParser(description='林火识别模型训练脚本')
    parser.add_argument('--model', type=str, default='m', 
                       choices=['n', 's', 'm', 'l', 'x'],
                       help='模型大小 (n/s/m/l/x)')
    parser.add_argument('--epochs', type=int, default=150,
                       help='训练轮数')
    parser.add_argument('--batch-size', type=int, default=16,
                       help='批大小')
    parser.add_argument('--img-size', type=int, default=640,
                       help='图像尺寸')
    parser.add_argument('--dataset', type=str, 
                       default='datasets/fire_dataset',
                       help='数据集路径')
    parser.add_argument('--no-pretrained', action='store_true',
                       help='不从预训练模型开始')
    
    args = parser.parse_args()
    
    # 更新配置
    config = TrainingConfig()
    config.MODEL_SIZE = args.model
    config.EPOCHS = args.epochs
    config.BATCH_SIZE = args.batch_size
    config.IMAGE_SIZE = args.img_size
    config.DATASET_DIR = args.dataset
    config.PRETRAINED_MODEL = not args.no_pretrained
    
    # 创建训练器
    trainer = ForestFireTrainer(config)
    
    # 运行完整流程
    success = trainer.run_complete_pipeline()
    
    if not success:
        print("\n❌ 训练流程失败，请检查上述错误信息")
        return 1
    
    return 0

if __name__ == "__main__":
    # 直接运行训练
    config = TrainingConfig()
    trainer = ForestFireTrainer(config)
    trainer.run_complete_pipeline()
    
    # 或者使用命令行参数
    # main()