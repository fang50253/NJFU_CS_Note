# 代码 4-1
import pandas as pd
user_all_info = pd.read_csv('../data/user_all_info.csv')
df1 = user_all_info.iloc[:, :3]  # 取出user_all_info的前3列数据
df2 = user_all_info.iloc[:, 3:]  # 取出user_all_info的后1列数据
print('合并df1的大小为%s，df2的大小为%s' % (df1.shape, df2.shape))
print('外连接合并后的数据框大小为：', pd.concat([df1, df2], axis=1,
                                 join='outer').shape) 
print('内连接合并后的数据框大小为：', pd.concat([df1, df2], axis=1,
                                  join='inner').shape)

# 代码 4-2
# 取出user_all_info前500行数据
df3 = user_all_info.iloc[:500, :] 
# 取出user_all_info的500后的数据
df4 = user_all_info.iloc[500:, :] 
print('合并df3的大小为%s，df4的大小为%s' % (df3.shape, df4.shape))
print('内连接纵向合并后的数据框大小为：', pd.concat([df3, df4],
       axis=0, join='outer').shape) 
print('外连接纵向合并后的数据框大小为：', pd.concat([df3, df4],
       axis=0, join='inner').shape)



# 代码 4-3
print('堆叠前df3的大小为%s，df4的大小为%s' % (df3.shape, df4.shape))
print('append纵向堆叠后的数据框大小为：', df3.append(df4).shape)




# 代码 4-4
pay_info = pd.read_csv('../data/user_pay_info.csv', encoding='gbk')
download_info = pd.read_csv('../data/user_download.csv', encoding='gbk')
# 用户信息表和用户每月支出信息表中都有'用户编号'
download_and_pay = pd.merge(download_info, pay_info, 
                            left_on='用户编号', right_on='编号')
print('pay_info用户每月支出信息表的原始形状为：', pay_info.shape)
print('download_info用户下载意愿表的原始形状为：', 
      download_info.shape)
print('用户下载意愿表和用户每月支出信息表主键合并后的形状为：', 
      download_and_pay.shape)



# 代码 4-5
pay_info.rename({'编号': '用户编号'}, inplace=True)
download_and_pay1 = download_info.join(pay_info, on='用户编号', 
                                       rsuffix='1')
print('用户下载意愿表和用户每月支出信息表主键合并后的形状为：',
      download_and_pay1.shape)



# 代码 4-6
import numpy as np
#建立两个字典，除了ID外，别的特征互补
dict1 = {'ID': [1, 2, 3, 4, 5, 6, 7, 8, 9],
         'System': ['win10', 'win10', np.nan, 'win10',
                np.nan, np.nan, 'win7', 'win7', 'win8'], 
      'cpu': ['i7', 'i5', np.nan, 'i7', np.nan, np.nan, 
             'i5', 'i5', 'i3']}
dict2 = {'ID': [1, 2, 3, 4, 5, 6, 7, 8, 9], 
         'System': [np.nan, np.nan, 'win7', np.nan, 
                'win8', 'win7', np.nan, np.nan, np.nan], 
        'cpu': [np.nan, np.nan, 'i3', np.nan, 'i7', 
                'i5', np.nan, np.nan, np.nan]}
# 变换两个字典为DataFrame
df1 = pd.DataFrame(dict1)
df2 = pd.DataFrame(dict2)
print('经过重叠合并后的数据为：\n', df1.combine_first(df2))
