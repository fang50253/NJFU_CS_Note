# 代码5-1
import numpy as np
import matplotlib.pyplot as plt
# %matplotlib inline表示在行中显示图片，在命令行运行报错
data = np.arange(0, 1.1, 0.01)
plt.title('lines')  # 添加标题
plt.xlabel('x')  # 添加x轴的名称
plt.ylabel('y')  # 添加y轴的名称
plt.xlim((0, 1))  # 确定x轴范围
plt.ylim((0, 1))  # 确定y轴范围
plt.xticks([0, 0.2, 0.4, 0.6, 0.8, 1])  # 规定x轴刻度
plt.yticks([0, 0.2, 0.4, 0.6, 0.8, 1])  # 确定y轴刻度
plt.plot(data, data ** 2)  # 添加y=x^2曲线
plt.plot(data, data ** 4)  # 添加y=x^4曲线
plt.legend(['y=x^2', 'y=x^4'])
plt.savefig('../tmp/y=x^2.jpg')
plt.show()


# 代码5-2
x = np.arange(0, np.pi * 2, 0.01)
# 第一幅子图
p1 = plt.figure(figsize=(8, 6), dpi=80)  # 确定画布大小
# 创建一个2行1列的子图，并开始绘制第一幅
ax1 = p1.add_subplot(2, 1, 1)
plt.title('lines')  # 添加标题
plt.xlabel('x')  # 添加x轴的名称
plt.ylabel('y')  # 添加y轴的名称
plt.xlim((0, 1))  # 确定x轴范围
plt.ylim((0, 1))  # 确定y轴范围
plt.xticks([0, 0.2, 0.4, 0.6, 0.8, 1])  # 规定x轴刻度
plt.yticks([0, 0.2, 0.4, 0.6, 0.8, 1])  # 确定y轴刻度
plt.plot(x, x ** 2)  # 添加y=x^2曲线
plt.plot(x, x ** 4)  # 添加y=x^4曲线
plt.legend(['y=x^2', 'y=x^4'])
# 第二幅子图
ax2 = p1.add_subplot(2, 1, 2)  # 开始绘制第二幅
plt.title('sin/cos(x)')  # 添加标题
plt.xlabel('x')  # 添加x轴的名称
plt.ylabel('y')  # 添加y轴的名称
plt.xlim((0, np.pi * 2))  # 确定x轴范围
plt.ylim((-1, 1))  # 确定y轴范围
plt.xticks([0, np.pi / 2, np.pi, np.pi * 1.5, np.pi * 2])  # 规定x轴刻度
plt.yticks([-1, -0.5, 0, 0.5, 1])  # 确定y轴刻度
plt.plot(x, np.sin(x))  # 添加sin(x)曲线
plt.plot(x, np.cos(x))  # 添加cos(x)曲线
plt.legend(['y=sin(x)', 'y=cos(x)'])
plt.tight_layout()  # 调整两个子图间距
plt.savefig('../tmp/sincos(x).jpg')
plt.show()


# 代码5-3
# 原图
x = np.linspace(0, 4 * np.pi)  # 生成x轴数据
y = np.sin(x)  # 生成y轴数据
plt.plot(x, y, label='$sin(x)$')  # 绘制sin曲线图
plt.title('sin(x)')
plt.xlabel('x')
plt.ylabel('y')
plt.show()

# 修改rc参数后的图
plt.rcParams['lines.linestyle'] = '-.'
plt.rcParams['lines.linewidth'] = 3
plt.plot(x, y, label='$sin(x)$')  # 绘制三角函数
plt.title('sin(x)')
plt.xlabel('x')
plt.ylabel('y')
plt.show()


# 代码5-4
# 无法显示中文标题
plt.plot(x, y, label='$sin(x)$')  # 绘制三角函数
plt.title('sin(x)曲线')
plt.xlabel('x')
plt.ylabel('y')
plt.show()

# 设置rc参数显示中文标题
# 设置字体为SimHei显示中文
plt.rcParams['font.sans-serif'] = 'SimHei' 
plt.rcParams['axes.unicode_minus'] = False  # 设置正常显示符号
plt.plot(x, y, label='$sin(x)$')  # 绘制三角函数
plt.title('sin(x)曲线')
plt.xlabel('x')
plt.ylabel('y')
plt.show()


# 代码5-5
import numpy as np
import matplotlib.pyplot as plt
plt.rcParams['font.sans-serif'] = 'SimHei'  # 设置中文显示
plt.rcParams['axes.unicode_minus'] = False
data = np.load('../data/2001-2019年劳动力与就业人员数据.npz',
    encoding='ASCII', allow_pickle=True)
columns = data['arr_0']  # 提取其中的columns数组，视为数据的标签
values = data['arr_1']  # 提取其中的values数组，视为数据的存在位置
plt.figure(figsize=(12, 6), dpi=1080)  # 设置画布
plt.scatter(values[:, 0], values[:, 1], marker='o')  # 绘制散点图
plt.xlabel('年份（年）')
plt.ylabel('劳动力人数（万人）')
plt.ylim(70000, 85000)  # 设置y轴范围
plt.xticks(range(2001, 2020, 1), labels=values[:, 0])
plt.title('2001～2019年劳动力人数散点图')  # 添加图表标题
plt.show()


# 代码5-6
p = plt.figure(figsize=(12, 6), dpi=1080)  # 设置画布
# 绘制散点图1
plt.scatter(values[:, 0], values[:, 3], marker='o', c='b')
# 绘制散点图2
plt.scatter(values[:, 0], values[:, 4], marker='o', c='r')
plt.xlabel('年份（年）')
plt.ylabel('人数（万人）')
plt.ylim(20000, 60000)  # 设置y轴范围
plt.xticks(range(2001, 2020, 1), labels=values[:, 0])
plt.legend(['城镇就业人员', '乡村就业人员'])  # 设置图例
plt.title('2001～2019年城乡就业人数散点图')  # 添加图表标题
plt.show()



# 代码5-7
p = plt.figure(figsize=(12, 6), dpi=1080)  #设置画布
plt.plot(values[:, 0], values[:, 2], color='r', linestyle='-')
plt.xlabel('年份（年）')
plt.ylabel('人数（万人）')
plt.ylim(70000, 80000)  # 设置y轴范围
plt.xticks(range(2001, 2020, 1), labels=values[:, 0])
plt.title('2001～2019年就业人数折线图')
plt.show()


# 代码5-8
p = plt.figure(figsize=(12, 6), dpi=1080)  #设置画布
plt.plot(values[:, 0], values[:, 2], c='b', linestyle = '-', 
         marker = 'o')  # 绘制点线图
plt.xlabel('年份（年）')
plt.ylabel('人数（万人）')
plt.ylim(70000, 80000)  # 设置y轴范围
plt.xticks(range(2001, 2020, 1), labels=values[:, 0])
plt.title('2001～2019年就业人数点线图')
plt.show()



# 代码5-9
p = plt.figure(figsize=(12, 6), dpi=1080) #设置画布
plt.plot(values[:, 0], values[:, 3], 'bs-',
          values[:, 0], values[:, 4], 'ro-.')
plt.xlabel('年份（年）')
plt.ylabel('人数（万人）')
plt.ylim(20000, 60000)  # 设置y轴范围
plt.xticks(range(2001, 2020, 1), labels=values[:, 0])
plt.legend(['城镇就业人员', '乡村就业人员'])
plt.title('2001～2019年城乡就业人数点线图')
plt.show()


# 代码5-10
columns = data['arr_0']  # 提取其中的columns数组，视为数据的标签
values = data['arr_1']  # 提取其中的values数组，视为数据的存在位置
# 绘制柱形图
labels = ['城镇就业人员', '乡村就业人员']
p = plt.figure(figsize=(6, 6), dpi=1080)
plt.bar(range(2), values[-1, 3:5], width=0.5)
plt.xlabel('类别')
plt.ylabel('就业人数（万人）')
plt.xticks(range(2), labels)
plt.title('2019年城乡就业人数柱形图')
plt.show()



# 代码5-11
label = ['城镇就业人员', '乡村就业人员']
explode = [0.01, 0.01]  # 设定各项距离圆心n个半径
p = plt.figure(figsize=(6, 6), dpi=1080)  # 设置画布
plt.pie(values[-1, 3:5], explode=explode, 
    labels=label, autopct='%1.1f%%')
plt.title('2019年城乡就业人数分布饼图')
plt.show()



# 代码5-12
label= ['城镇就业人员', '乡村就业人员']
gdp = (list(values[:, 3]),list(values[:, 4]))
p = plt.figure(figsize=(6, 6), dpi=1080)
plt.boxplot(gdp, notch=True, labels=label, meanline=True)
plt.title('2001～2019年城乡就业人数分布箱线图')
plt.show()
