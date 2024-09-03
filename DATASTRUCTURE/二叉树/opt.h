#ifndef OPT_H_INCLUDED
#define OPT_H_INCLUDED

#include <cstring>
#include <set>
#include <queue>
#include<stdio.h>
#include<string.h>
#include"def.h"
#define INF 0x3f3f3f3f

using namespace std;

set<int> s;

int n = 0, k = 0;

void visit(BiTree T)
{
    printf(" %d,%s",T->data.key,T->data.others);
}

bool isDulplicate(TElemType definition[]){
    int Hash[1000]={0};
    for(int i=0;definition[i].key!=-1;++i){
        Hash[definition[i].key]++;
    }
    for(int j=1;j<10;++j){
        if(Hash[j]>1) return TRUE;//表示有重复的
    }
    return FALSE;
}

status CreateBiTree(BiTree &T,TElemType definition[])
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/ 
    if(isDulplicate(definition))return ERROR;//重复元素
    static int index=0;
    if(definition==nullptr||definition[index].key==0){
        T=nullptr;
        return OK;
    }
    T=(BiTree)malloc(sizeof(BiTNode));
    T->data.key=definition[index].key;
    strcpy(T->data.others,definition[index].others);
    //左
    index++;
    CreateBiTree(T->lchild,definition);
    //右
    index++;
    CreateBiTree(T->rchild,definition);
    return OK;
    /********** End **********/
}
//不太确定的功能
status DestroyBiTree(BiTree &T){
    if(!T)return ERROR;
    free(T);
    return OK;
}

status ClearBiTree(BiTree &T){
    //将二叉树设置成空，并删除所有结点，释放结点空间
    if(T==nullptr)return OK;
    ClearBiTree(T->lchild);
    ClearBiTree(T->rchild);
    free(T);
    T=nullptr;
    return OK;
}

int BiTreeDepth(BiTree T){
    //求二叉树的深度
    if(T==nullptr)return 0;
    int dep1=0,dep2=0;
    dep1=BiTreeDepth(T->lchild);
    dep2=BiTreeDepth(T->rchild);
    return dep1>dep2? dep1+1: dep2+1;
}

BiTNode* LocateNode(BiTree T,KeyType e)
//查找结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T==nullptr||T->data.key==e)return T;
    BiTNode *lnode = LocateNode(T->lchild,e);
    if(lnode)return lnode;
    BiTNode *rnode =LocateNode(T->rchild,e);
    return rnode;
}
    /********** End **********/

status Assign(BiTree &T,KeyType e,TElemType value)
//实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTNode* node=LocateNode(T, e);
    if (node!= NULL) {
        if (LocateNode(T,value.key)!=NULL&&LocateNode(T,value.key)!=node) {
            return ERROR;
        }
        node->data = value;
        return OK;
    }
    return ERROR;
    /********** End **********/
}

BiTNode* GetSibling(BiTree T,KeyType e)
//实现获得兄弟结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
   if (T==nullptr) {
        return nullptr; // 如果当前节点为空，直接返回nullptr
    }
    if (T->lchild!=nullptr&&T->lchild->data.key==e&&T->rchild != nullptr) {
        return T->rchild; // 如果目标节点是左子树节点且右子树存在，则返回右子树节点
    }
    if (T->rchild!=nullptr&&T->rchild->data.key==e&&T->lchild != nullptr) {
        return T->lchild; // 如果目标节点是右子树节点且左子树存在，则返回左子树节点
    }
    BiTNode* leftSibling=GetSibling(T->lchild, e);
    if (leftSibling != nullptr) {
        return leftSibling; //如果在左子树中找到兄弟节点，直接返回结果
    }
    BiTNode* rightSibling=GetSibling(T->rchild, e);
    if (rightSibling!=nullptr) {
        return rightSibling; // 如果在右子树中找到兄弟节点，直接返回结果
    }
    return nullptr; 
    /********** End **********/
}

bool BiTreeEmpty(BiTree T){
    if(T==nullptr)return true;
    return false;
}

void insert(BiTNode*T,int LR,BiTNode*newNode){
    if(LR==0){
        if(T->lchild==NULL){
            T->lchild=newNode;
        }
        else{
            newNode->rchild=T->lchild;
            T->lchild=newNode;
        }
    }
    if(LR==1){
        if(T->rchild==NULL){
            T->rchild=newNode;
        }
        else{
            newNode->rchild=T->rchild;
            T->rchild=newNode;
        }
    }
}
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
//插入结点。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTree newNode = (BiTree)malloc(sizeof(BiTNode));
    newNode->data=c;
    newNode->lchild=NULL;
    newNode->rchild=NULL;
    if(LR==-1){
        newNode->rchild=T;
        T=newNode;
        return OK;
    }
    BiTNode* node=LocateNode(T,e);//找到目标的节点
    if(node==NULL)return ERROR;//没有目标的节点
    if(LocateNode(T,c.key)!=NULL)return ERROR;//关键词重复
    insert(node,LR,newNode);
    return OK;  
    /********** End **********/
}

status DeleteNode(BiTree &T,KeyType e){
    //删除结点。此题允许通过增加其它函数辅助实现本关任务
    if(!T)return ERROR;

    int flag=0;        
    if(T->data.key==e)flag=1;
    if(flag){
        int deg=0;
        if(T->lchild)deg+=1;
        if(T->rchild)deg+=2;
        if(deg==0){
            free(T);
            T=nullptr;
        }
        if(deg==1){
            BiTNode*tmp=T;
            T=T->lchild;
            free(tmp);
            tmp=nullptr;
        }
        if(deg==2){
            BiTree tmp=T;
            T=T->rchild;
            free(tmp);
            tmp=nullptr;
        }
        if(deg==3){
            BiTree tmp=T;
            BiTree LC=T->lchild;
            BiTree RC=T->rchild;
            T=LC;
            while(LC->rchild){
                LC=LC->rchild;
            }
            LC->rchild=RC;
            free(tmp);
            tmp=nullptr;
        }
        return OK;
    }
    else{
        status state1,state2;
        state1=DeleteNode(T->lchild,e);
        state2=DeleteNode(T->rchild,e);
        if(state1==OK||state2==OK)return OK;
        return ERROR;
    }
}

typedef struct _stack{
    BiTNode* stack[100];
    int top;
}Stack;
int isEmpty(Stack s){
    return s.top==0? 1:0;
}
BiTNode* Pop(Stack *s){
    return s->stack[--(s->top)];
}
void push(Stack *s,BiTNode* node){
    s->stack[s->top++]=node;
}
status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
//先序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    Stack nodes;
    nodes.top=0;
    push(&nodes,T);
    while(!isEmpty(nodes)){
        BiTNode* current=Pop(&nodes);
        if(current!=NULL){
            visit(current);
            push(&nodes,current->rchild);
            push(&nodes,current->lchild);
        }
    }
    return OK;
    /********** End **********/
}

status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//中序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    Stack nodes;
    nodes.top=0;
    BiTNode *node=T;
    while(!isEmpty(nodes)||node!=NULL){
        while(node!=NULL){
            push(&nodes,node);
            node=node->lchild;
        }
        node=Pop(&nodes);
        visit(node);
        node=node->rchild;
    }
    return OK;
    /********** End **********/
}

status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//后序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T==nullptr)return OK;
    PostOrderTraverse(T->lchild,visit);
    PostOrderTraverse(T->rchild,visit);
    visit(T);
    /********** End **********/
}

status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//按层遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTNode* Queue[100];
    int rear,front;
    rear=front=0;
    Queue[rear++]=T;
    while(front<rear){
        BiTNode* node=Queue[front++];
        visit(node);
        if(node->lchild!=NULL){
            Queue[rear++]=node->lchild;
        }if(node->rchild!=NULL){
            Queue[rear++]=node->rchild;
        }
    }
    return OK;
    /********** End **********/
}

typedef struct {
    int pos;
    TElemType data;
} HE;

int get_index(BiTree T,BiTree child,int idx)
{
    if(T==NULL)return 0;
    if(T->data.key==child->data.key){
        return idx;
    }
    int gll = get_index(T->lchild,child,idx*2);
    int grr = get_index(T->rchild,child,idx*2+1);
    if(grr>gll)return grr;
    return gll;
}

status CreateBiTree1(BiTree &T,HE definition[])
{
    int i=0,j;
    static BiTNode *st[100];
    while (j=definition[i].pos)
    {
        st[j]=(BiTNode *)malloc(sizeof(BiTNode));
       st[j]->data=definition[i].data;
       st[j]->lchild=NULL;
       st[j]->rchild=NULL;
       if (j!=1)
               if (j%2)   st[j/2]->rchild=st[j];
              else      st[j/2]->lchild=st[j];
       i++;
    }
    T=st[1];
    return OK;
}

int MaxPathSum(BiTree T){
    if(!T)return ERROR;
    if(!T->lchild&&!T->rchild)return T->data.key;
    int ll,rr;
    ll=(T->lchild?MaxPathSum(T->lchild):-INF);
    rr=(T->rchild?MaxPathSum(T->rchild):-INF);
    return std::max(ll,rr)+T->data.key;
}

BiTree LowestCommonAncestor(BiTree T,KeyType e1,KeyType e2){
    if(T->data.key==e1||T->data.key==e2||T==nullptr)return T;
    BiTree left=LowestCommonAncestor(T->lchild, e1, e2);
    BiTree right=LowestCommonAncestor(T->rchild,e1,e2);
    if (left && right) return T;
    else if (!left) return right;
    else if (!right) return left;
    else return T;
}

void InvertTree(BiTree &T){
    if(T->lchild)InvertTree(T->lchild);
    if(T->rchild)InvertTree(T->rchild);
    BiTree tmp=T->lchild;
    T->lchild=T->rchild;
    T->rchild=tmp;
}

status SaveBiTree(BiTree T, char FileName[])
//将二叉树的结点数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    if(T!=NULL)
    {
        FILE *fp;
        int index=1;
        fp=fopen(FileName,"w");
        queue<BiTree> Q;
        Q.push(T);
        BiTree cur;
        while(Q.size()){
            cur=Q.front();
            Q.pop();
            if(cur!=NULL){
                fprintf(fp,"%d %d %s ",get_index(T,cur,1),cur->data.key,cur->data.others);
            }
            index++;
            if(cur->lchild!=NULL) Q.push(cur->lchild);
            if(cur->rchild!=NULL) Q.push(cur->rchild);
        }
        fprintf(fp,"0 0 null");
        fclose(fp);
    }
    return OK;
}

status LoadBiTree(BiTree &T,  char FileName[])
//读入文件FileName的结点数据，创建二叉树
{
    int i=0;
    HE definition[100];
    FILE *fp;
    fp=fopen(FileName,"r");
    do {
    fscanf(fp,"%d %d %s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
} while (definition[i++].pos);

    CreateBiTree1(T,definition);
    fclose(fp);
    return OK;
}

status AddTree(Trees &trees,char ListName[]){
    for(int i=0;i<trees.length;i++)
        if (strcmp(trees.elem[i].name, ListName) == 0)
        {
            printf("多线性表中已存在名称为 %s 的线性表！\n", ListName);
            return ERROR;
        }
    strcpy(trees.elem[trees.length].name,ListName);
    trees.elem[trees.length].T=nullptr;
    trees.elem[trees.length].T=(BiTNode*)malloc(sizeof(BiTNode));
    trees.length++;
    return OK;
}

status LocateTree(Trees &trees,char ListName[]){
    for(int i=0;i<trees.length;++i){
        if(strcmp(trees.elem[i].name,ListName)==0){
            return 1+i;
        }
    }
    return 0;
}

status RemoveTree(Trees &trees,char ListName[]){
    for(int i = 0; i < trees.length; ++i){
        if(!strcmp(ListName, trees.elem[i].name)){
            for(int j = i; j < trees.length - 1; ++j){
                trees.elem[j] = trees.elem[j + 1];
            }
            trees.length--;
            return OK;
        }
    }
    return ERROR;
}

BiTree SwitchTree(Trees &trees,int i){
    if (i > trees.length || i < 1)
        return NULL;
    else
    {   
        return trees.elem[i-1].T;
    }
}

BiTNode *findLCA(BiTNode *root,int n1,int n2){
    if (root == nullptr) return nullptr;

    if (root->data.key == n1 || root->data.key == n2)
        return root;

    BiTNode* leftLCA = findLCA(root->lchild, n1, n2);
    BiTNode* rightLCA = findLCA(root->rchild, n1, n2);

    // 如果在左子树和右子树中分别找到了n1和n2
    if (leftLCA && rightLCA) return root;

    // 只有左子树或只有右子树中有n1和n2
    return (leftLCA != nullptr) ? leftLCA : rightLCA;
}

#endif