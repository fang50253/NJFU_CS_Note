# 代码5-13
# 导库
from matplotlib import pyplot as plt
import pandas as pd
import seaborn as sns

# 设置中文字体
plt.rcParams['font.sans-serif'] = ['SimHei']
sns.set_style({'font.sans-serif':['simhei', 'Arial']})

# 加载数据
hr = pd.read_csv('../data/hr.csv', encoding='gbk')

data = hr.head(100)
# 使用Matplotlib库绘图
color_map = dict(zip(data['薪资'].unique(), ['b', 'y', 'r']))
for species, group in data.groupby('薪资'):
    plt.scatter(group['每月平均工作小时数（小时）'],
                group['满意度'],
                color=color_map[species], alpha=0.4,
                edgecolors=None, label=species)
plt.legend(frameon=True, title='薪资')
plt.xlabel('平均每个月工作时长（小时）')
plt.ylabel('满意度水平')
plt.title('满意度水平与平均每个月工作小时')
plt.show()

# 使用seaborn库绘图
sns.lmplot('每月平均工作小时数（小时）', '满意度', data, hue='薪资', fit_reg=False, height=4)
plt.xlabel('平均每个月工作时长（小时）')
plt.ylabel('满意度水平')
plt.title('满意度水平与平均每个月工作小时')
plt.show()



# 代码5-14
import numpy as np
plt.rcParams['axes.unicode_minus'] = False
x = np.arange(1, 10, 2)
y1 = x + 1
y2 = x + 3
y3 = x + 5
# 绘制3条不同的直线
# 使用Matplotlib库绘图
plt.title('Matplotlib库的绘图风格')
plt.plot(x, y1)
plt.plot(x, y2)
plt.plot(x, y3)
plt.show()

# 使用seaborn库绘图
# 第1部分
sns.set_style('darkgrid')  # 全黑风格
sns.set_style({'font.sans-serif':['simhei', 'Arial']})
plt.title('seaborn库的绘图风格')
# 第2部分
sns.lineplot(x, y1)
sns.lineplot(x, y2)
sns.lineplot(x, y3)
plt.show()



# 代码5-15
x = np.arange(1, 10, 2)
y1 = x + 1
y2 = x + 3
y3 = x + 5
def showLine(flip=1):
    sns.lineplot(x, y1)
    sns.lineplot(x, y2)
    sns.lineplot(x, y3)
pic = plt.figure(figsize=(12, 8))
with sns.axes_style('darkgrid'):  # 使用darkgrid主题
    pic.add_subplot(2, 3, 1)
    showLine()
    plt.title('darkgrid')
with sns.axes_style('whitegrid'):  # 使用whitegrid主题
    pic.add_subplot(2, 3, 2)
    showLine()
    plt.title('whitegrid')
with sns.axes_style('dark'):  # 使用dark主题
    pic.add_subplot(2, 3, 3)
    showLine()
    plt.title('dark')
with sns.axes_style('white'):  # 使用white主题
    pic.add_subplot(2, 3, 4)
    showLine()
    plt.title('white')
with sns.axes_style('ticks'):  # 使用ticks主题
    pic.add_subplot(2, 3, 5)
    showLine()
    plt.title('ticks')
sns.set_style(style='darkgrid', rc={'font.sans-serif': ['MicrosoftYaHei', 'SimHei'],
                            'grid.color': 'black'})  # 修改主题中参数
pic.add_subplot(2, 3, 6)
showLine()
plt.title('修改参数')
plt.show()



# 代码5-16
sns.set()
x = np.arange(1, 10, 2)
y1 = x + 1
y2 = x + 3
y3 = x + 5
def showLine(flip=1):
    sns.lineplot(x, y1)
    sns.lineplot(x, y2)
    sns.lineplot(x, y3)
# 恢复默认参数
pic = plt.figure(figsize=(8, 8), dpi=100)
with sns.plotting_context('paper'):  # 选择paper类型
    pic.add_subplot(2, 2, 1)
    showLine()
    plt.title('paper')
with sns.plotting_context('notebook'):  # 选择notebook类型
    pic.add_subplot(2, 2, 2)
    showLine()
    plt.title('notebook')
with sns.plotting_context('talk'):  # 选择talk类型
    pic.add_subplot(2, 2, 3)
    showLine()
    plt.title('talk')
with sns.plotting_context('poster'):  # 选择poster类型
    pic.add_subplot(2, 2, 4)
    showLine()
    plt.title('poster')
plt.show()



# 代码5-17
with sns.axes_style('white'):
    showLine()
    sns.despine()  # 默认无参数状态，就是删除上方和右方的边框
    plt.title('控制图形边框')
plt.show()


with sns.axes_style('white'):
    data = np.random.normal(size=(20, 6)) + np.arange(6) / 2
    sns.boxplot(data=data)
    sns.despine(offset=10, left=False, bottom=False)
    plt.title('控制图形边框')
plt.show()




# 代码5-18
sns.palplot(sns.color_palette())



# 代码5-19
palette = sns.color_palette('muted')
sns.palplot(palette)



# 代码5-20
sns.palplot(sns.color_palette('hls', 8))



# 代码5-21
sns.palplot(sns.hls_palette(8, l=.3, s=.8))  # l控制亮度，s控制饱和度


#代码5-22
sns.palplot(sns.color_palette('husl', 8))



# 代码5-23
plt.plot(x, y1, sns.xkcd_rgb['pale red'], lw=3)
plt.plot(x, y2, sns.xkcd_rgb['medium green'], lw=3)
plt.plot(x, y3, sns.xkcd_rgb['denim blue'], lw=3)
plt.title('线条颜色示例')
plt.show()

# 自定义定性调色板
colors = ['windows blue', 'amber', 'greyish', 'faded green', 'dusty purple']
sns.palplot(sns.xkcd_palette(colors))



# 代码5-24
sns.palplot(sns.color_palette('Greens'))
sns.palplot(sns.color_palette('YlOrRd_r'))
sns.palplot(sns.color_palette('YlOrRd_d'))



# 代码5-25
sns.palplot(sns.cubehelix_palette(8, start=1, rot=0))

x, y = np.random.multivariate_normal([0, 0], [[1, -.5], [-.5, 1]], size=300).T
cmap = sns.cubehelix_palette(as_cmap=True)  # 生产调色板对象
sns.kdeplot(x, y, cmap=cmap, shade=True)
plt.title('连续调色板')
plt.show()



# 代码5-26
sns.palplot(sns.light_palette('blue'))
sns.palplot(sns.dark_palette('yellow'))
# 使用husl颜色空间作为种子
pal = sns.dark_palette((200, 80, 60), input='husl', reverse=True, as_cmap=True)
sns.kdeplot(x, y, cmap=pal)
plt.title('自定义连续调色板')
plt.show()



# 代码5-27
sns.palplot(sns.color_palette('BrBG', 7))
sns.palplot(sns.color_palette('RdBu_r', 7))



# 代码5-28
sns.palplot(sns.color_palette('coolwarm', 7))



# 代码5-29
sns.palplot(sns.diverging_palette(240, 10, n=7))
sns.palplot(sns.diverging_palette(150, 275, s=80, l=55, n=7))
# 创建中间是暗色的调色板
sns.palplot(sns.diverging_palette(250, 15, s=75, l=40, n=7, center='dark'))
# 通过sep参数控制中间区域渐变宽度
sns.palplot(sns.diverging_palette(150, 275, s=80, l=55, n=7, sep=80))



# 代码5-30
x = np.arange(1, 10, 2)
y1 = x + 1
y2 = x + 3
y3 = x + 5
def showLine(flip=1):
    sns.lineplot(x, y1)
    sns.lineplot(x, y2)
    sns.lineplot(x, y3)
# 使用默认调色板
showLine()
plt.title('默认调色板')
plt.show()

# sns.set_palette函数设置调色板
sns.set_palette('YlOrRd_d')
showLine()
plt.title('使用set_palette设置调色板')
plt.show()

sns.set()  # 恢复所有默认设置
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False
pic = plt.figure(figsize=(8, 4))
with sns.color_palette('PuBuGn_d'):  # 临时配置调色板
    pic.add_subplot(1, 2, 1)
    showLine()
    plt.title('使用color_palette设置调色板')
pic.add_subplot(1, 2, 2)  # 使用默认调色板
showLine()
plt.title('默认调色板')
plt.show()


# 代码5-31
boston = pd.read_csv('../data/boston_house_prices.csv', encoding='gbk')
plt.rcParams['axes.unicode_minus'] = False
corr = boston.corr()  # 特征的相关系数矩阵
sns.heatmap(corr)
plt.title('特征矩阵热力图')
plt.show()


# 代码5-32
plt.figure(figsize=(10, 10))
sns.heatmap(corr, annot=True, fmt='.2f')
plt.title('特征矩阵热力图')
plt.show()


# 代码5-33
# 提取部门为销售部、离职为1的数据
sale = hr.iloc[(hr['部门'].values=='销售部') & (hr['离职'].values==1), :]
sns.stripplot(x=sale['每月平均工作小时数（小时）'])
plt.title('简单水平分布散点图')
plt.show()


# 代码5-34
# 提取离职为1的数据
hr1 = hr.iloc[hr['离职'].values==1, :]
plt.figure(figsize=(10, 5))
plt.subplot(121)
plt.xticks(rotation=70)
sns.stripplot(x='部门', y='每月平均工作小时数（小时）', data=hr1)  # 默认添加随机噪声
plt.title('默认随机噪声抖动')
plt.subplot(122)
plt.xticks(rotation=70)
sns.stripplot(x='部门', y='每月平均工作小时数（小时）',
                 data=hr1, jitter=False)  # 不添加随机噪声
plt.title('无随机噪声抖动')
plt.show()



# 代码5-35
# 提取高薪在职的数据
hr2 = hr.iloc[(hr['薪资'].values=='高') & (hr['离职'].values==0), :]
sns.stripplot(x='5年内升职', y='每月平均工作小时数（小时）',
              hue='部门', data=hr2, jitter=True)
plt.title('前5年是否晋升与平均每月工作时长')
plt.show()



# 代码5-36
plt.figure(figsize=(10, 13))
plt.subplot(211)
plt.xticks(rotation=70)
plt.title('不同部门的平均每月工作时长')
sns.stripplot(x='部门', y='每月平均工作小时数（小时）', hue='5年内升职', data=hr2)
plt.subplot(212)
plt.xticks(rotation=70)
sns.stripplot(x='部门', y='每月平均工作小时数（小时）', hue='5年内升职',
              data=hr2, dodge=True)
plt.show()



# 代码5-37
sns.swarmplot(x='部门', y='每月平均工作小时数（小时）', data=hr2)
plt.xticks(rotation=70)
plt.title('不同部门的平均每月工作时长')
plt.show()



# 代码5-38
sns.swarmplot(x='部门', y='每月平均工作小时数（小时）',
                 hue='5年内升职', data=hr2)
plt.xticks(rotation=30)
plt.title('不同部门的平均每月工作时长')
plt.show()


# 代码5-39
fig, axes = plt.subplots(1, 2, figsize=(8, 4))
axes[0].set_title('修改前的线性回归拟合图')
axes[1].set_title('修改后的线性回归拟合图')
sns.regplot(x='房间数（间）', y='房屋价格（美元）', data=boston, ax=axes[0])
sns.regplot(x='房间数（间）', y='房屋价格（美元）', data=boston, ci=50, ax=axes[1])
plt.show()
