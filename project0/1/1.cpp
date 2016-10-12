/*
 *compare模版函数传入三个参数
 *用来比较这三个数并返回最大和最小的两个参数
 *返回形式是以一个链表的形式
 *这个LList对象的第一个节点为最小值，第二个节点为最大值
 *需要用到datastructure头文件
 *测试结果在1文件夹下
 */
#include <iostream>
#include "DataStructure.h"
#include <string>
#include <fstream>
using namespace std;
template <typename E> LList<E>* compare(const E& member1, const E& member2, const E& member3){
    LList<E>* list = new LList<E>(2);
    if(memcmp(&member1, &member2, sizeof(E))<0){
        if(memcmp(&member2, &member3, sizeof(E))<0){
            list->append(member1);
            list->append(member3);
        } else{
            if(memcmp(&member1, &member3, sizeof(E))<0){
                list->append(member1);
                list->append(member2);
            } else{
                list->append(member3);
                list->append(member2);
            }
        }
    }else{
        if(memcmp(&member2, &member3, sizeof(E))<0){
            if(memcmp(&member1, &member3, sizeof(E))<0){
                list->append(member3);
            } else{
                list->append(member1);
            }
            list->append(member2);
        } else{
            list->append(member3);
            list->append(member1);
        }
    }
    return list;
}
typedef struct {
    int num;
}test;
int main() {
    //我这里如果用数组的话输出会更容易一点，但是我实现这个函数用的是线性表，所以只能选择这种办法
    //尤其是结构体和类这种参数
    //测试int类型
    int x=1,y=2,z=3;
    LList<int>* li1 = compare(x,y,z);
    li1->print();
    //测试string类型
    string str1 = "aaaa", str2 = "bbbb", str3="cccc";
    LList<string>* li2 = compare(str1,str2,str3);
    li2->print();
    //测试结构体类型
    test test1 = {1}, test2 = {2}, test3 = {3};
    LList<test> *li3 = compare(test1, test2, test3);
    li3->moveToPos(1);
    cout << li3->getValue().num << endl;
    li3->moveToPos(2);
    cout << li3->getValue().num << endl;
}