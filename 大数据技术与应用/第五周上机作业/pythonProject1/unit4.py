import numpy as np
import pandas as pd
health_care_dataset_stroke=pd.read_csv("../healthcare-dataset-stroke-data.csv")
health_care_dataset_age_abs=pd.read_csv("../stroke-data.csv")

print(f"health_care_dataset_stroke 数据量: {len(health_care_dataset_stroke)} 行")
print(f"health_care_dataset_age_abs 数据量: {len(health_care_dataset_age_abs)} 行")

merged_data = pd.merge(
    health_care_dataset_stroke,
    health_care_dataset_age_abs,
    on="avg_glucose_level",
    how="outer",
    indicator=True
)

print(merged_data)