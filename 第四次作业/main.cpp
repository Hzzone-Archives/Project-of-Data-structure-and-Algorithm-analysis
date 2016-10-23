#include <iostream>
#include "DataStructure.h"
#include <string>
#include <fstream>
#include <queue>
#include <cmath>

using namespace std;
////二叉树抽象数据类型
//template <typename E> class BinNode {
//public:
//    virtual ~BinNode(){}
//    //二叉树节点中的元素
//    virtual E& element() = 0;
//    //设置元素值
//    virtual void  setElement(const E&) = 0;
//
//    virtual BinNode* left() const = 0;
//    virtual BinNode* right() const = 0;
//    virtual void setLeft(BinNode*) = 0;
//    virtual void setRight(BinNode*) = 0;
//    //是否是叶子节点
//    virtual bool isLeaf() = 0;
//};

////二叉树指针实现
//template <typename Key, typename E>
//class BSTNode: public BinNode<E> {
//private:
//    Key k;
//    E it;
//    BSTNode* lc;
//    BSTNode* rc;
//public:
//    BSTNode(){lc = rc = NULL;}
//    BSTNode(Key K, E e, BSTNode* l=NULL, BSTNode* r=NULL){
//        k = K; it = e; lc = l; rc = r;
//    }
//    ~BSTNode(){}
//
//    E& element(){return it;}
//    void setElement(const E& e){it=e;}
//    Key& key(){ return k;}
//    void setKey(const Key& K){ k= K;}
//    inline BSTNode* left() const{ return lc;}
//    inline BSTNode* right() const{ return rc;}
//    void setLeft(BinNode<E>* b){ lc=(BSTNode*)b;}
//    void setRight(BinNode<E>* b){ rc=(BSTNode*)b;}
//
//    bool isLeaf(){
//        return (lc==NULL)&&(rc==NULL);
//    }
//};

//二叉树实现
template <typename E> class Tree{
private:
    E it;
    Tree* lc;
    Tree* rc;
public:
    Tree(){lc = rc = NULL;}
    Tree(E e, Tree* l=NULL, Tree* r=NULL){
        it = e; lc = l; rc = r;
    }
    ~Tree(){}

    E& element(){return it;}
    void setElement(const E& e){it=e;}
    Tree* left() const{ return lc;}
    Tree* right() const{ return rc;}
    void setLeft(Tree<E>* b){ lc=b;}
    void setRight(Tree<E>* b){ rc=b;}

    bool isLeaf(){
        return (lc==NULL)&&(rc==NULL);
    }
};;
//按层次打印二叉树
template <typename E>
void printByLevel(Tree<E>* root){
    queue<Tree<E>*> q1;
    queue<Tree<E>*> q2;
    q1.push(root);
    while(!q1.empty()){
        while(!q1.empty()){
            Tree<E>* temp = q1.front();
            q1.pop();
            cout<<temp->element()<<" ";
            if(temp->left())
                q2.push(temp->left());
            if(temp->right())
                q2.push(temp->right());
        }
        cout<<endl;
        q1.swap(q2);
    }
}
//得到二叉树的深度
template <typename E>
int getHeight(Tree<E>* root){
    if(root==NULL){
        return 0;
    }
    return max(getHeight(root->left()), getHeight(root->right()))+1;
}

//按照中序遍历的顺序打印min到max范围内的节点
template <typename E>
void printRange(Tree<E>* root,const E& min, const E& max){
    if(root==NULL)
        return;
    printRange(root->left(), min, max);
    E ele = root->element();
    if(ele>min && ele<max)
        cout<<ele<<" ";
    printRange(root->right(), min, max);
}
int main(){
    Tree<int> t1(1);
    Tree<int> t3(3);
    Tree<int> t2(2,&t1,&t3);
    Tree<int> t5(5);
    Tree<int> t4(4,&t2,&t5);
    Tree<int> t7(7);
    Tree<int> t9(9);
    Tree<int> t11(11);
    Tree<int> t13(13);
    Tree<int> t8(8,&t7,&t9);
    Tree<int> t12(12,&t11,&t13);
    Tree<int> t10(10,&t8,&t12);
    Tree<int> t6(6,&t4,&t10);
    printRange(&t6, 2, 12);
    return 0;
}
