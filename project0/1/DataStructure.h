//
// Created by Hzzone on 2016/10/8.
//

#ifndef LEARNINGC_DATASTRUCTURE_H
#define LEARNINGC_DATASTRUCTURE_H
#include <iostream>
using namespace std;
template<typename E> class Link{
public:
    E element;
    Link* next;
    Link(const E& elemval, Link* nextval=NULL){
        element = elemval;
        next = nextval;
    }
    Link(Link* nextval=NULL){
        next = nextval;
    }
};
template<typename E> class LList{
private:
    Link<E>* head;
    Link<E>* tail;
    Link<E>* curr;
    int cnt;
    void init(){
        curr = tail = head = new Link<E>;
        cnt = 0;
    }
public:
    LList(int size=0){
        init();
    }
    int length(){
        return cnt;
    }
    void moveToPos(int pos){
        curr = head;
        for(int i=0;i<pos;i++) curr = curr->next;
    }
    void append(const E& it){
        tail = tail->next = new Link<E>(it, NULL);
        cnt++;
    }
    void reverse(){
        Link<E>* temp1;
        Link<E>* temp2;
        temp1 = head->next;
        while(temp1->next!=NULL){
            temp2 = temp1->next;
            temp1->next = temp2->next;
            temp2->next = head->next;
            head->next = temp2;
        }
    }
    const E& getValue(){
        return curr->element;
    }
    void print(){
        Link<E>* it = head->next;
        while(it!=NULL){
            cout<<it->element<<endl;
            it = it->next;
        }
    }
};
//this function merge two sorted-growing link and return a new growing link
template <typename E>
Link<E>* merge_two_link(Link<E>* prev_link, Link<E>* next_link) {
    //compare the two head node and as the end condition
    if(prev_link==NULL){
        return next_link;
    }else if(next_link == NULL){
        return prev_link;
    }

    Link<E>* new_head = NULL; //it's used to point new Link whose previous node is smaller
    if(prev_link->element < next_link->element)
    {
        new_head = prev_link;
        new_head->next = merge_two_link(prev_link->next, next_link);
    }
    else
    {
        new_head = next_link;
        new_head->next = merge_two_link(prev_link, next_link->next);
    }
    //return the small link
    return new_head;
}
template<typename E> class Stack{
private:
    void operator=(const Stack&){}
    Stack(const Stack&){}
public:
    Stack(){}
    virtual ~Stack(){}
    virtual void clear() = 0;
    virtual void push(const E&) = 0;
    virtual E pop() = 0;
    virtual const E& topValue() const = 0;
    virtual int length() const = 0;
};
template<typename E> class LStack: public Stack<E>
{
private:
    Link<E>* top;
    int size;
public:
    LStack(int sz=0){top = NULL; size = 0;}
    ~LStack(){clear();}
    void clear(){
        while(top!=NULL){
            Link<E>* temp = top;
            top = top->next;
            delete temp;
        }
        size = 0;
    }
    void push(const E& it)	{
        top = new Link<E>(it, top);
        size++;
    }
    E pop(){
        if(top == NULL){
            cout<<"Stack is empty"<<endl;
            cin.get();
            exit(1);
        }
        E it = top->element;
        Link<E>* ltemp = top->next;
        delete top;
        top = ltemp;
        size--;
        return it;
    }
    const E& topValue() const {
        if(top == NULL){
            cout<<"Stack is empty"<<endl;
            cin.get();
            exit(1);
        }
        return top->element;
    }
    int length() const{
        return size;
    }
};

#endif //LEARNINGC_DATASTRUCTURE_H
