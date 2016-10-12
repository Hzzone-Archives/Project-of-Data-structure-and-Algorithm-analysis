#include <iostream>
#include "DataStructure.h"
#include <string>
#include <fstream>
using namespace std;
typedef struct {
    char name[20];
    int sum;
}Student;
int main(){
    int n, chinese, math, en;
    cin>>n;
    Link<Student> head;
    Link<Student>* node = &head;
    for(int i=0;i<n;i++){
        Student stu;
        cin>>stu.name>>chinese>>math>>en;
        stu.sum = chinese + math + en;
        node = node->next = new Link<Student>(stu);
    }
    node->next = NULL;
    for(node=head.next;node!=NULL;node=node->next) {
        for (Link<Student>* li = node->next; li != NULL; li = li->next) {
            if (node->element.sum < li->element.sum) {
                char temp1[20];
                strcpy(temp1, node->element.name);
                strcpy(node->element.name, li->element.name);
                strcpy(li->element.name, temp1);
                int temp2 = node->element.sum;
                node->element.sum = li->element.sum;
                li->element.sum = temp2;
            }
        }
    }
    ofstream out("student.txt");
    if(!out.is_open()){
        cout<<"open error"<<endl;
        exit(1);
    }
    for(node=head.next;node!=NULL;node=node->next)
        out<<node->element.name<<" "<<node->element.sum<<endl;
    out.close();
    ifstream in("student.txt");
    if(!in.is_open()){
        cout<<"open error"<<endl;
        exit(1);
    }
    string name;
    int num;
    int i = 0;
    while(i<n){
        in>>name>>num;
        cout<<name<<" "<<num<<endl;
        i++;
    }
    return 0;
}
