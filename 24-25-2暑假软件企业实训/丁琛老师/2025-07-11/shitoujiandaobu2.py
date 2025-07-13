import os
import random

shenlicnt = 0
pinju = 0
jisuanjiwin = 0  # 增加计算机胜场计数

def randnum(): # 生成随机数
    return random.randint(0, 2)

# 0表示石头，1表示剪刀，2表示布
def get_pai(x):
    if x == 0:
        return "石头"
    if x == 1:
        return "剪刀"
    if x == 2:
        return "布"

def get_sl(x, y): # x是选手出牌，y是电脑出牌，返回1表示选手胜利，返回0表示电脑胜利
    if (x - y + 3) % 3 == 1:
        return 1
    else:
        return 0

def ask():
    global pinju
    print("请\"出牌\"  0表示石头，1表示剪刀，2表示布")
    num = 100
    while num < 0 or num > 2:
        ch = input()[0]
        num = int(ch)
        if num < 0 or num > 2:
            print("输入数据非法")
    jisuanjipai = randnum()
    print("计算机出的牌为", get_pai(jisuanjipai), "你出的牌是", get_pai(num))
    if num == jisuanjipai:
        print("你和计算机本局打了平手")
        pinju = pinju + 1
        return -1  # 平局标记
    elif get_sl(num, jisuanjipai) == 1:
        print("你本局胜利了！")
        return 1
    else:
        print("你本局失败了！")
        return 0

if __name__ == '__main__':
    jucnt = 0  # 有效局数（平局不计）
    while jucnt < 3 and shenlicnt < 2 and jisuanjiwin < 2:
        res = ask()
        if res == -1:
            continue
        elif res == 1:
            shenlicnt = shenlicnt + 1
        else:
            jisuanjiwin = jisuanjiwin + 1
        jucnt = jucnt + 1

    print("=== 比赛结束 ===")
    print("你的胜场数为：", shenlicnt)
    print("计算机胜场数为：", jisuanjiwin)
    print("平局次数为：", pinju)
    if shenlicnt == 2:
        print("你战胜了计算机！")
    elif jisuanjiwin == 2:
        print("你输给了计算机")
    else:
        print("比赛平局")