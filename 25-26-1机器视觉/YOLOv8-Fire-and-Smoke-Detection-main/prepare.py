"""
数据集准备脚本 - prepare_dataset.py
"""

import os
import shutil
from pathlib import Path
import yaml

def create_dataset_structure(base_path):
    """创建数据集目录结构"""
    directories = [
        base_path / "train" / "images",
        base_path / "train" / "labels", 
        base_path / "val" / "images",
        base_path / "val" / "labels",
        base_path / "test" / "images",
        base_path / "test" / "labels"
    ]
    
    for directory in directories:
        directory.mkdir(parents=True, exist_ok=True)
        print(f"✅ 创建目录: {directory}")
    
    return base_path

def create_data_yaml(dataset_path, class_names):
    """创建数据配置文件"""
    data_config = {
        'path': str(dataset_path),
        'train': 'train/images',
        'val': 'val/images', 
        'test': 'test/images',
        'nc': len(class_names),
        'names': class_names
    }
    
    yaml_path = dataset_path / "data.yaml"
    with open(yaml_path, 'w') as f:
        yaml.dump(data_config, f, default_flow_style=False)
    
    print(f"✅ 创建数据配置: {yaml_path}")
    return yaml_path

def split_dataset(image_dir, label_dir, train_ratio=0.7, val_ratio=0.2, test_ratio=0.1):
    """分割数据集"""
    # 获取所有图像文件
    image_files = list(Path(image_dir).glob("*.*"))
    image_files = [f for f in image_files if f.suffix.lower() in ['.jpg', '.jpeg', '.png', '.bmp']]
    
    # 随机打乱
    import random
    random.shuffle(image_files)
    
    # 计算分割点
    total = len(image_files)
    train_end = int(total * train_ratio)
    val_end = train_end + int(total * val_ratio)
    
    # 分割数据集
    train_files = image_files[:train_end]
    val_files = image_files[train_end:val_end]
    test_files = image_files[val_end:]
    
    print(f"📊 数据集分割:")
    print(f"  训练集: {len(train_files)} 图像")
    print(f"  验证集: {len(val_files)} 图像") 
    print(f"  测试集: {len(test_files)} 图像")
    
    return train_files, val_files, test_files

def prepare_fire_dataset():
    """准备林火数据集"""
    base_dir = Path.home() / "ForestFireDetection" / "datasets" / "fire_dataset"
    
    print("🔥 准备林火检测数据集...")
    
    # 创建目录结构
    dataset_path = create_dataset_structure(base_dir)
    
    # 创建数据配置 (林火检测通常有2个类别)
    class_names = {
        0: 'fire',    # 火焰
        1: 'smoke'    # 烟雾
    }
    
    create_data_yaml(dataset_path, class_names)
    
    print(f"""
    🎯 数据集结构已创建!
    
    请将您的数据按以下方式组织:
    
    {base_dir}/
    ├── data.yaml
    ├── train/
    │   ├── images/     # 放置训练图像
    │   └── labels/     # 放置YOLO格式的标注文件
    ├── val/
    │   ├── images/     # 放置验证图像  
    │   └── labels/     # 放置YOLO格式的标注文件
    └── test/
        ├── images/     # 放置测试图像
        └── labels/     # 放置YOLO格式的标注文件
    
    📝 标注文件格式 (YOLO):
      每行: <class_id> <x_center> <y_center> <width> <height>
      坐标需要归一化到 [0, 1]
    """)

if __name__ == "__main__":
    prepare_fire_dataset()