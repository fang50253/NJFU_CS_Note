import os
import random
shenlicnt=0
pinju=0
def randnum(): # 生成随机数
    return random.randint(0, 2)
# 0表示石头，1表示剪刀，2表示布
def get_pai(x):
    if x==0:
        return "石头"
    if x==1:
        return "剪刀"
    if x==2:
        return "布"
def get_sl(x,y):#x是选手出牌，y是电脑出牌，返回1表示选手胜利，返回0表示电脑胜利
    if (x-y+3)%3==1:
        return 1
    else:
        return 0
def ask():
    print("请\"出牌\"  0表示石头，1表示剪刀，2表示布")
    num=100
    while num<0 or num>2:
        ch=input()[0]
        num = int(ch) 
        if num<0 or num>2:
            print("输入数据非法")
    jisuanjipai=randnum()
    print("计算机出的牌为",get_pai(jisuanjipai),"你出的牌是",get_pai(num))
    if num==jisuanjipai:
        print("你和计算机本局打了平手")
        global pinju
        pinju=pinju+1
        return 0
    elif get_sl(num,jisuanjipai)==1:
        print("你本局胜利了！")
        return 1
    else:
        print("你本局失败了！")
        return 0
if __name__=='__main__':
    for i in range(0,3):
        if ask()==1 :
            shenlicnt=shenlicnt+1
        if shenlicnt==2:
            print("你战胜了计算机！")
            exit(0)
    if (shenlicnt == 1 and pinju == 1) or pinju==3 :
        print("你和计算机打了平手")
    elif shenlicnt == 1 and pinju==2 :
        print("你战胜了计算机")
    else:
        print("你输给了计算机")