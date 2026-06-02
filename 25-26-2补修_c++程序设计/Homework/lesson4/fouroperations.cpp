#include<bits/stdc++.h>
using namespace std;
char getRandomOperations(){
    int n = rand()%4;
    const char operations[4] = {'+', '-', '*', '/'};
    return operations[n];
}
int getRandomNumber(int l,int r){
    return l + rand()%(r-l+1);
}
int main()
{
     srand(time(NULL));
     int questions,correct=0;
     cout<<"Enter number of questions: ";
     cin>>questions;
     auto starttime=chrono::high_resolution_clock::now();
     int leftbound,rightbound;
     cout<<"Enter left bound: ";
     cin>>leftbound;
     cout<<"Enter right bound: ";
     cin>>rightbound;
     for(int i=0;i<questions;i++){
        int a = getRandomNumber(leftbound,rightbound);
        int b = getRandomNumber(leftbound,rightbound);
        char operation = getRandomOperations();
        if(operation == '/'){
            while(a<b||a%b!=0){
                a = getRandomNumber(leftbound,rightbound);
                b = getRandomNumber(leftbound,rightbound);
            }
        }
        cout<<a<<" "<<operation<<" "<<b<<" = ";
        int ans;
        cin>>ans;
        int correct_ans;
        switch(operation){
            case '+':
                correct_ans = a+b;
                break;
            case '-':
                correct_ans = a-b;
                break;
            case '*':
                correct_ans = a*b;
                break;
            case '/':
                correct_ans = a/b;
                break;
        }
        if(ans==correct_ans){
            cout<<"Correct\n";
            correct++;
        }
        else{
            cout<<"Wrong\n";
        }
     }
     auto endtime=chrono::high_resolution_clock::now();
     cout<<"Questions completed\n";
     cout<<"Time taken: "<<chrono::duration_cast<chrono::milliseconds>(endtime-starttime).count()/1000.0<<" s\n";
     cout<<"Average time taken: "<<chrono::duration_cast<chrono::milliseconds>(endtime-starttime).count()/questions/1000.0<<" s\n";
     cout<<"Correct: "<<correct<<" out of "<<questions<<" questions\n";
     cout<<"Accuracy: "<<(double)correct/questions*100<<" %\n";
     return 0;
}