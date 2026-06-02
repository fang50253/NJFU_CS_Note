// 设计一个日期类CDate，其结构如下：
// 	私有数据成员Year（年份）、Month（月份）、Day（日号）；
// 	构造函数对数据成员初始化；
// 	友元函数Leap(CDate& d);判断当前日期d是否为闰年；
// 	友元函数Sub (CDate& d1, CDate& d2);计算两个日期d1和d2之间的天数；
// 	友元函数Count_Day(CDate& d,int  flag);当参数flag=1时，计算年头到当前日期d的天数；当参数flag=0时，计算当前日期d到年尾的天数；

#include<bits/stdc++.h>
class CDate{
private:
    int Year,Month,Day;
public:
    CDate(int year,int month,int day){
        Year=year;
        Month=month;
        Day=day;
    }
    friend bool Leap(CDate& d);
    friend int Sub(CDate& d1, CDate& d2);
    friend int Count_Day(CDate& d,int flag);//年头包含当天，年尾不含当天
};
bool Leap(CDate& d){
    if(d.Year%400==0) return 1;
    else if(d.Year%100==0) return 0;
    else if(d.Year%4==0) return 1;
    else return 0;
}
int Count_Day(CDate& d,int flag){
    const int unlunarlen[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    const int lunarlen[]={0,31,29,31,30,31,30,31,31,30,31,30,31};
    int sttime=0;
    if(Leap(d)){
        for(int i=1;i<d.Month;++i){
            sttime+=lunarlen[i];
        }
        sttime+=d.Day;
        if(flag==1) return sttime;
        else return 366-sttime;
    }
    else{
        for(int i=1;i<d.Month;++i){
            sttime+=unlunarlen[i];
        }
        sttime+=d.Day;
        if(flag==1) return sttime;
        else return 365-sttime;
    }
}
int Sub(CDate& d1, CDate& d2){
    int cnt=0;
    for(int i=d1.Year+1;i<=d2.Year-1;++i){
        if((i%400==0)||(i%4==0&&i%100!=0)){
            cnt+=366;
        }
        else {
            cnt+=365;
        }
    }
    cnt+=Count_Day(d1,0);
    cnt+=Count_Day(d2,1);
    return cnt;
}
int main(){
    CDate d1(2005,2,5);
    CDate d2(2026,4,19);
    CDate d3(2008,2,9);
    std::cout<<(Leap(d1)?"闰年":"平年")<<std::endl;
    std::cout<<(Leap(d2)?"闰年":"平年")<<std::endl;
    std::cout<<(Leap(d3)?"闰年":"平年")<<std::endl;
    std::cout<<Count_Day(d2,0)<<std::endl;
    std::cout<<Count_Day(d2,1)<<std::endl;
    std::cout<<Sub(d1,d2)<<std::endl;
    return 0;
}
