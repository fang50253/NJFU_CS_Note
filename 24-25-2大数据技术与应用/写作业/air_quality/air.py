import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.linear_model import LinearRegression
from sklearn.metrics import r2_score

# 1. 读取数据
df = pd.read_csv("./AirQualityData.csv",encoding="gbk")  # 替换为你的文件路径

# 2. 保证时间字段为 datetime 格式
df['DateTime'] = pd.to_datetime(df['Date'] + ' ' + df['Time'])

# 3. 选择每天中午11点的数据
df_11am = df[df['Hour'] == 11].copy()

# 4. 选择我们要分析的字段：Temperature vs AirQualityIndex（或 PM2.5）
x = df_11am[['Temperature']]
y = df_11am['AirQualityIndex']  # 可替换为 'PM2.5' 等字段

# 5. 可视化关系
plt.figure(figsize=(10,6))
sns.scatterplot(x='Temperature', y='AirQualityIndex', data=df_11am)
plt.title("Temperature vs Air Quality Index (11AM)")
plt.xlabel("Temperature (°C)")
plt.ylabel("Air Quality Index")
plt.grid(True)
plt.show()

# 6. 拟合线性回归模型
model = LinearRegression()
model.fit(x, y)

# 7. 预测 & 评估
y_pred = model.predict(x)
r2 = r2_score(y, y_pred)

print(f"线性回归方程: AQI = {model.coef_[0]:.2f} * Temperature + {model.intercept_:.2f}")
print(f"R² 分数: {r2:.4f}")

# 8. 可视化拟合结果
plt.figure(figsize=(10,6))
sns.scatterplot(x='Temperature', y='AirQualityIndex', data=df_11am, label='Actual')
plt.plot(df_11am['Temperature'], y_pred, color='red', label='Linear Fit')
plt.title("Temperature vs Air Quality Index (11AM) with Regression Line")
plt.xlabel("Temperature (°C)")
plt.ylabel("Air Quality Index")
plt.legend()
plt.grid(True)
plt.show()




# 补充代码
# 按小时统计平均空气质量（例如用 AirQualityIndex，也可以替换为 PM2.5 等）
hourly_aqi = df.groupby('Hour')['AirQualityIndex'].mean().reset_index()

# 可视化每小时平均空气质量
plt.figure(figsize=(10,6))
sns.lineplot(x='Hour', y='AirQualityIndex', data=hourly_aqi, marker='o')
plt.title("Average Air Quality Index by Hour")
plt.xlabel("Hour of Day")
plt.ylabel("Average Air Quality Index")
plt.xticks(range(0, 24))
plt.grid(True)
plt.show()






# 日起
from sklearn.preprocessing import MinMaxScaler

# 按日期计算平均值
daily_data = df.groupby('Date')[['AirQualityIndex', 'PM2.5', 'PM10']].mean().reset_index()

# 归一化处理
scaler = MinMaxScaler()
scaled_values = scaler.fit_transform(daily_data[['AirQualityIndex', 'PM2.5', 'PM10']])
normalized_df = pd.DataFrame(scaled_values, columns=['AirQualityIndex', 'PM2.5', 'PM10'])
normalized_df['Date'] = daily_data['Date']

# 绘图
plt.figure(figsize=(14, 6))
sns.lineplot(data=normalized_df, x='Date', y='AirQualityIndex', label='Air Quality Index (Normalized)')
sns.lineplot(data=normalized_df, x='Date', y='PM2.5', label='PM2.5 (Normalized)')
sns.lineplot(data=normalized_df, x='Date', y='PM10', label='PM10 (Normalized)')
plt.title("Daily Air Quality Index, PM2.5, and PM10 Trends (Normalized)")
plt.xlabel("Date")
plt.ylabel("Normalized Value")
plt.xticks(rotation=45)
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()



import seaborn as sns
import matplotlib.pyplot as plt

# 选择数值型变量列（可根据你的实际数据微调）
numeric_cols = ['AirQualityIndex', 'PM2.5', 'PM10', 'CO(GT)', 'NOx(GT)', 'NO2(GT)', 'O3(GT)', 'SO2(GT)',
                'Temperature', 'Humidity', 'Pressure', 'WindSpeed', 
                'CO_NOx_Ratio', 'NOx_NO2_Ratio', 'Temp_Humidity_Index']

# 去除缺失值（防止相关性计算报错）
df_corr = df[numeric_cols].dropna()

# 计算皮尔逊相关系数矩阵
corr_matrix = df_corr.corr()

# 可视化热力图
plt.figure(figsize=(12, 10))
sns.heatmap(corr_matrix, annot=True, fmt=".2f", cmap="coolwarm", linewidths=0.5, square=True)
plt.title("Correlation Matrix of Air Quality and Environmental Factors")
plt.xticks(rotation=45)
plt.yticks(rotation=0)
plt.tight_layout()
plt.show()