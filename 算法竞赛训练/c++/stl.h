//  @ 方泽宇2351610105
//  2024-12-13  stl.h



#ifndef STL_H
#define STL_H
#include<stdexcept>
#include<iostream>
namespace fzy
{
    template<typename T>
    struct queuenode
    {
        T v;
        queuenode<T>* next;
    };
    template<typename T>
    class queue
    {
    private:
        queuenode<T>* head;
        queuenode<T>* last;
        int size_;
    public:
        queue()
        {
            head=new queuenode<T>;
            head->next=nullptr;
            last=head;
            size_=0;
        }
        ~queue()
        {
            clear();
            delete head;
        }
        void clear()
        {
            while(!empty()) pop();
        }
        void push(T v)
        {
            queuenode<T>* newnode = new queuenode<T>;
            newnode->v = v;
            newnode->next = nullptr;
            last->next = newnode;
            last = newnode;
            ++size_;
        }
        void pop()
        {
            if (size_>0)
            {
                queuenode<T>* temp=head->next;
                head->next=temp->next;
                if (head->next==nullptr) last=head;
                delete temp;
                --size_;
            }
        }
        T front()
        {
            if(size_>0) return head->next->v;
            throw std::runtime_error("Queue is empty");
        }
        T back()
        {
            if(size_>0) return last->v;
            throw std::runtime_error("Queue is empty");
        }
        bool empty()
        {
            return size_==0;
        }
        int size()
        {
            return size_;
        }
        void print()
        //定义为按照队列的入(出)队顺序进行打印
        {
            queuenode<T> *i;
            int j;
            for(i=head->next,j=1;j<=size_;++j,i=i->next)
            {
                std::cout<<i->v<<" ";
            }
            std::cout<<std::endl;
        }
    };
    template<typename T>
    struct stacknode
    {
        T v;
        stacknode *next;
    };
    template<typename T>
    class stack
    {
        private:
        stacknode<T> *head;
        int size_;
        public:
        stack()
        {
            head=new stacknode<T>;
            head->next = nullptr;
            size_=0;
        }
        ~stack()
        {
            clear();
        }
        void clear()
        {
            while(size()) pop();
        }
        void pop()
        {
            if(size_==0) throw std::runtime_error("stack is empty");
            stacknode<T>* tmp=head->next;
            head->next=head->next->next;
            --size_;
            delete tmp;
        }
        int size()
        {
            return size_;
        }
        bool empty()
        {
            return size_==0;
        }
        T top()
        {
            if(size_==0) throw std::runtime_error("stack is empty");
            return head->next->v;
        }
        void push(T v)
        {
            stacknode<T> *newnode=new stacknode<T>;
            newnode->next=head->next;
            head->next=newnode;
            newnode->v=v;
            ++size_;
        }
        void print()
        //定义为按照栈的出栈顺序进行打印
        {
            int j=1;
            stacknode<T> *i;
            for(i=head->next;j<=size_;++j,i=i->next)
            {
                std::cout<<i->v<<" ";
            }
            std::cout<<std::endl;
        }
    };
}
#endif