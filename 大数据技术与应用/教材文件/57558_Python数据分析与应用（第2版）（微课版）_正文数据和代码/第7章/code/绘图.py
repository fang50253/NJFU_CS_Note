

a = sum(tipdm_data['userid'].isnull())
b = len(tipdm_data)-sum(tipdm_data['userid'].isnull())

import matplotlib.pyplot as plt
plt.rcParams['font.sans-serif']='SimHei'#设置中文显示
plt.figure(figsize=(4,4))#将画布设定为正方形，则绘制的饼图是正圆
label=['空值','非空值']#定义饼图的标签，标签是列表
explode=[0,0]#设定各项距离圆心n个半径
#plt.pie(values[-1,3:6],explode=explode,labels=label,autopct='%1.1f%%')#绘制饼图
values=[a,b]
plt.pie(values,explode=explode,labels=label,autopct='%1.1f%%')#绘制饼图
plt.title('userid空值与非空值占比')#绘制标题
plt.show()
plt.savefig('./饼图')
#############################



a = sum(tipdm_data['uniqueVisitorId'].isnull())
b = len(tipdm_data)-sum(tipdm_data['uniqueVisitorId'].isnull())

plt.figure(figsize=(4,4))#将画布设定为正方形，则绘制的饼图是正圆
label=['空值','非空值']#定义饼图的标签，标签是列表
explode=[0,0]#设定各项距离圆心n个半径
#plt.pie(values[-1,3:6],explode=explode,labels=label,autopct='%1.1f%%')#绘制饼图
values=[a,b]
plt.pie(values,explode=explode,labels=label,autopct='%1.1f%%')#绘制饼图
plt.title('uniqueVisitorId空值与非空值占比')#绘制标题
plt.show()


plt.savefig('./饼图2')#保存图片

#############


con_data['reallID'].value_counts().values

a = pd.DataFrame(con_data['reallID'].value_counts())
a.columns=['count']

# a.reset_index(inplace=True)
b = pd.DataFrame(a['count'].value_counts())


super_35 = list(b['count'])[34:]
sum_35 = 0
for i in super_35:
    sum_35 += int(i)

dianji = list(b['count'])[:34]
dianji.append(sum_35)

tick_label = ["1", "5", "10", "15", "20",'25','30','35']

plt.bar(range(len(dianji)), dianji)
plt.xticks([0,4,9,14,19,24,29,34], tick_label)
plt.title('用户点击网页柱形图')
plt.xlabel('点击网页数（次）')
plt.ylabel('用户数（人）')
plt.show()
plt.savefig('./饼图3')#保存图片
#######################################


mode_data['page_path'].value_counts()
ind_1 = a[a['count'] == 1].index
ind_1_1 = [i in ind_1 for i in con_data['reallID']]
c = pd.DataFrame(con_data[ind_1_1]['page_path'].value_counts())

#########################################################
data = con_data
data = data.fillna('1')
indx = [i[:4] != '2021'  for i in  data['date_time']]
data.loc[indx,'date_time'] = data.loc[indx, 'sessionid']
data['date_time'] = pd.to_datetime(data['date_time'])

o=[]
for k in range(3,35):
    li = reallid_count[reallid_count['count']==k]['reallID'].to_list()
    s=0
    for i in li:
        a=data[data['reallID']==i][['date_time','reallID']]['date_time']
        for j in range(0,k-2):
            num = (a.iloc[j+1]-a.iloc[j]).total_seconds()
            s+= num
    s=s/(k*len(li))
    o.append(s)

y=o
plt.plot(range(3,35),y)
plt.title('平均点击间隔')
plt.xlabel('点击网页次数（次）')
plt.ylabel('平均点击间隔（秒）')
plt.xticks(range(3,35))
plt.savefig('./饼图4')#保存图片
#############################################################

data[data['reallID']==109664.0]['date_time'].shape





















