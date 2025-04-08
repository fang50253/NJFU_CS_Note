# 代码5-40
import pandas as pd
import numpy as np
from pyecharts import options as opts
from pyecharts.charts import Scatter3D

# 最大携氧能力、体重和运动后心率的三维散点图
player_data = pd.read_excel('../data/运动员的最大携氧能力、体重和运动后心率数据.xlsx')
player_data = [player_data['体重（kg）'], player_data['运动后心率（次/分钟）'], 
               player_data['最大携氧能力（ml/min）']]
player_data = np.array(player_data).T.tolist()
s = (Scatter3D()
  .add('', player_data, xaxis3d_opts=opts.Axis3DOpts(name='体重（kg）'), 
       yaxis3d_opts=opts.Axis3DOpts(name='运动后心率（次/分钟）'), 
       zaxis3d_opts=opts.Axis3DOpts(name='最大携氧能力（ml/min）')
      )
  .set_global_opts(title_opts=opts.TitleOpts(
      title='最大携氧能力、体重和运动后心率3D散点图'), 
                   visualmap_opts=opts.VisualMapOpts(range_color=[
                       '#1710c0', '#0b9df0', '#00fea8', '#00ff0d', '#f5f811', '#f09a09', 
                       '#fe0300'])))
s.render_notebook()


# 代码5-41
from pyecharts.charts import Funnel
data = pd.read_excel('../data/某淘宝店铺的订单转化率统计数据.xlsx')
x_data = data['网购环节'].tolist()
y_data = data['人数'].tolist()
data = [[x_data[i], y_data[i]] for i in range(len(x_data))]
funnel = (Funnel()
    .add('', data_pair=data,label_opts=opts. LabelOpts(
        position='inside', formatter='{b}:{d}%'), gap=2, 
        tooltip_opts=opts.TooltipOpts(trigger='item'), 
        itemstyle_opts=opts.ItemStyleOpts(border_color='#fff', border_width=1))
    .set_global_opts(title_opts=opts.TitleOpts(title='某淘宝店铺的订单转化率漏斗图'), 
                     legend_opts=opts.LegendOpts(pos_left='40%')))
funnel.render_notebook()



# 代码5-42
from pyecharts.charts import WordCloud
data_read = pd.read_csv('../data/worldcloud.csv', encoding='gbk')
words = list(data_read['词语'].values)
num = list(data_read['频数'].values)
data = [k for k in zip(words, num)]
data = [(i,str(j)) for i, j in data]
wordcloud = (WordCloud()
           .add('', data_pair=data, word_size_range=[10, 100])
           .set_global_opts(title_opts=opts.TitleOpts(
               title='部分宋词词频词云图', title_textstyle_opts=
               opts.TextStyleOpts(font_size=23)), 
                            tooltip_opts=opts.TooltipOpts(is_show=True))
      )
wordcloud.render_notebook()

