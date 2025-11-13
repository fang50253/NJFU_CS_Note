"""
林火识别模型训练脚本 - 10轮快速训练版
Forest Fire Detection Model Training Script - 10 Epochs Quick Version
"""

import os
import yaml
import torch
from pathlib import Path
from ultralytics import YOLO

# ==================== 快速训练配置 ====================
class QuickTrainingConfig:
    # 模型配置
    MODEL_SIZE = "n"  # 使用小模型快速训练
    PRETRAINED_MODEL = True
    
    # 训练参数 - 只训练10轮
    EPOCHS = 10
    IMAGE_SIZE = 640
    BATCH_SIZE = 8
    LEARNING_RATE = 0.01
    
    # 简化数据增强
    AUGMENT = True
    
    # 优化器
    OPTIMIZER = "Adam"
    
    # 路径配置
    PROJECT_NAME = "ForestFireDetection"
    DATASET_DIR = "datasets/fire_dataset"
    
    # 设备配置
    DEVICE = "cpu"  # 使用CPU避免MPS问题

class QuickForestFireTrainer:
    def __init__(self, config):
        self.config = config
        self.model = None
        self.setup_environment()
        
    def setup_environment(self):
        """设置训练环境"""
        print("=" * 60)
        print("🔥 林火识别模型快速训练系统 - 10轮训练")
        print("=" * 60)
        
        # 显示训练配置
        self.print_training_config()
        
        # 设置设备
        self.device = self.setup_device()
        
        # 创建目录结构
        self.setup_directories()
        
        # 检查数据集
        if not self.check_dataset():
            return
        
        # 修复数据集问题
        self.fix_dataset_issues()
    
    def print_training_config(self):
        """打印训练配置"""
        print("📋 快速训练配置:")
        print(f"  🤖 模型: YOLOv8{self.config.MODEL_SIZE.upper()}")
        print(f"  ⚡ 训练轮数: {self.config.EPOCHS} (快速训练)")
        print(f"  🖼️ 图像尺寸: {self.config.IMAGE_SIZE}")
        print(f"  📦 批大小: {self.config.BATCH_SIZE}")
        print(f"  💻 设备: {self.config.DEVICE}")
        
    def setup_device(self):
        """设置训练设备"""
        if self.config.DEVICE == "auto":
            if torch.cuda.is_available():
                device = 0
                print(f"🎯 使用GPU: {torch.cuda.get_device_name(0)}")
            else:
                device = "cpu"
                print("⚠️ 使用CPU训练")
        else:
            device = self.config.DEVICE
            print(f"🔧 使用指定设备: {device}")
            
        return device
    
    def setup_directories(self):
        """创建目录结构"""
        # 项目根目录
        self.project_dir = Path.home() / self.config.PROJECT_NAME
        self.project_dir.mkdir(exist_ok=True)
        
        print(f"📁 项目目录: {self.project_dir}")
    
    def check_dataset(self):
        """检查数据集完整性"""
        dataset_path = self.project_dir / self.config.DATASET_DIR
        
        if not dataset_path.exists():
            print(f"❌ 数据集路径不存在: {dataset_path}")
            return False
        
        # 检查必要的文件
        data_yaml_path = dataset_path / "data.yaml"
        if not data_yaml_path.exists():
            print(f"❌ 数据配置文件不存在: {data_yaml_path}")
            return False
        
        # 读取数据配置
        try:
            with open(data_yaml_path, 'r') as f:
                self.data_cfg = yaml.safe_load(f)
            
            print("✅ 数据集配置:")
            print(f"  类别数: {self.data_cfg.get('nc', '未知')}")
            print(f"  类别名称: {self.data_cfg.get('names', '未知')}")
                
        except Exception as e:
            print(f"❌ 数据配置文件错误: {e}")
            return False
            
        self.dataset_path = dataset_path
        return True
    
    def fix_dataset_issues(self):
        """修复数据集问题"""
        print("\n🔧 检查数据集问题...")
        
        # 检查类别编号问题
        if 'names' in self.data_cfg:
            if isinstance(self.data_cfg['names'], dict):
                names_dict = self.data_cfg['names']
                max_class = max(names_dict.keys()) if names_dict else 0
                
                if max_class >= 2:  # 我们只有2个类别 (0,1)
                    print(f"⚠️ 检测到类别编号问题: 最大类别ID {max_class}")
                    print("🔄 需要修复标注文件中的类别ID...")
        
        print("✅ 数据集检查完成")
    
    def create_model(self):
        """创建模型"""
        print("\n🤖 创建模型...")
        
        try:
            if self.config.PRETRAINED_MODEL:
                model_name = f"yolov8{self.config.MODEL_SIZE}.pt"
                print(f"  加载预训练模型: {model_name}")
                self.model = YOLO(model_name)
            else:
                model_name = f"yolov8{self.config.MODEL_SIZE}.yaml"
                print(f"  从零开始训练: {model_name}")
                self.model = YOLO(model_name)
            
            print("✅ 模型创建完成")
            
        except Exception as e:
            print(f"❌ 模型创建失败: {e}")
            raise
    
    def setup_training_arguments(self):
        """设置训练参数 - 简化版本"""
        args = {
            # 基础配置
            'data': str(self.dataset_path / "data.yaml"),
            'epochs': self.config.EPOCHS,  # 关键：使用10轮
            'imgsz': self.config.IMAGE_SIZE,
            'batch': self.config.BATCH_SIZE,
            'patience': 5,  # 减少早停耐心值
            
            # 优化器配置
            'lr0': self.config.LEARNING_RATE,
            'optimizer': self.config.OPTIMIZER,
            
            # 简化数据增强
            'hsv_h': 0.015,
            'hsv_s': 0.7,
            'hsv_v': 0.4,
            'fliplr': 0.5,
            
            # 设备配置
            'device': self.device,
            'workers': 2,  # 减少工作线程
            
            # 保存配置
            'save': True,
            'exist_ok': True,
            'project': str(self.project_dir / "results"),
            'name': f"yolov8{self.config.MODEL_SIZE}_fire_quick",
            
            # 验证配置
            'val': True,
        }
        
        return args
    
    def train(self):
        """开始训练"""
        print(f"\n🚀 开始快速训练 ({self.config.EPOCHS}轮)...")
        
        try:
            # 创建模型
            self.create_model()
            
            # 设置训练参数
            train_args = self.setup_training_arguments()
            
            # 开始训练
            results = self.model.train(**train_args)
            
            print("✅ 快速训练完成!")
            return results
            
        except Exception as e:
            print(f"❌ 训练失败: {e}")
            return None
    
    def validate_model(self):
        """快速验证模型"""
        print("\n🔍 快速验证模型性能...")
        
        model_path = self.project_dir / "results" / f"yolov8{self.config.MODEL_SIZE}_fire_quick" / "weights" / "best.pt"
        
        if not os.path.exists(model_path):
            print(f"❌ 模型文件不存在: {model_path}")
            return None
        
        try:
            # 加载最佳模型
            best_model = YOLO(str(model_path))
            
            # 快速验证
            metrics = best_model.val(
                data=str(self.dataset_path / "data.yaml"),
                split='val',
                device=self.device
            )
            
            print("📊 快速验证结果:")
            print(f"  mAP50: {metrics.box.map50:.4f}")
            print(f"  精确度: {metrics.box.mp:.4f}")
            print(f"  召回率: {metrics.box.mr:.4f}")
            
            return metrics
            
        except Exception as e:
            print(f"❌ 验证失败: {e}")
            return None
    
    def run_quick_training(self):
        """运行快速训练流程"""
        # 1. 环境检查
        if not self.check_dataset():
            return False
        
        # 2. 开始训练
        results = self.train()
        if results is None:
            return False
        
        # 3. 快速验证
        self.validate_model()
        
        print("\n🎉 快速训练完成!")
        best_model_path = self.project_dir / "results" / f"yolov8{self.config.MODEL_SIZE}_fire_quick" / "weights" / "best.pt"
        print(f"📁 最佳模型: {best_model_path}")
        
        return True

def main():
    """主函数 - 直接运行10轮训练"""
    # 使用快速配置
    config = QuickTrainingConfig()
    
    # 创建训练器
    trainer = QuickForestFireTrainer(config)
    
    # 运行快速训练
    success = trainer.run_quick_training()
    
    if not success:
        print("\n❌ 快速训练失败")
        return 1
    
    return 0

if __name__ == "__main__":
    main()