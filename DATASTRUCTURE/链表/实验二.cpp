#include "stdio.h"
#include "stdlib.h"
#include<windows.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int ElemType;
typedef struct LNode{  //单链表（链式结构）结点的定义
      ElemType data;
      struct LNode *next;
    }LNode,*LinkList;

typedef struct {  //多个线性表管理
    struct {
        char name[30];
        LinkList L;
    } elem[10];
    int length;
    int listsize;
}LISTS;
//函数一
status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L){
        L=(LinkList)malloc(sizeof(LNode));
        L->next=NULL;
        return OK;
    }
    return INFEASIBLE;
    /********** End **********/
}
//函数二
status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L)return INFEASIBLE;
    while(L->next!=NULL){
        LNode *p =L->next;
        L->next=L->next->next;
        free(p);
    }
    free(L);
    L=NULL;
    return OK;
    /********** End **********/
}
//函数三
status ClearList(LinkList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L)return INFEASIBLE;
    while(L->next!=NULL){
        LNode *p =L->next;
        L->next=L->next->next;
        free(p);
    }
    return OK;
    /********** End **********/
}
//函数四
status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L)return INFEASIBLE;
    if(L->next==NULL)return OK;
    else return FALSE;
    /********** End **********/
}
//函数五
int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L)return INFEASIBLE;
    int length=0;
    LinkList current=L->next;
    while(current!=NULL){
        current=current->next;
        length++;
    }
    return length;
    /********** End **********/
}
//函数六
status GetElem(LinkList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L)return INFEASIBLE;
    int cur_pos=1;
    LinkList cur = L->next;
    while(cur!=NULL){
        if(cur_pos==i){
            e=cur->data;
            return OK;
        }
        cur_pos++;
        cur=cur->next;
    }
    return ERROR;
    /********** End **********/
}
//函数七
status LocateElem(LinkList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L)return INFEASIBLE;
    LinkList cur;
    if(L->next)
    cur=L->next;
    else return ERROR;
    int postion = 1;
    while(cur!=NULL){
        if(cur->data==e){
            return postion;
        }
        cur=cur->next;
        postion++;
    }
    return ERROR;
    /********** End **********/
}
//函数八
status PriorElem(LinkList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L)return INFEASIBLE;
    if(L->next)
        L=L->next;
    else return ERROR;
    while(L->next!=NULL){
        if(L->next->data==e){
            pre = L->data;
            return OK;
        }
        L=L->next;
    }
    return ERROR;
    /********** End **********/
}
//函数九
status NextElem(LinkList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L)return INFEASIBLE;
    if(L->next)
        L=L->next;
    else return ERROR;
    while(L->next!=NULL){
        if(L->data==e){
            next = L->next->data;
            return OK;
        }
        L=L->next;
    }
    return ERROR;
    /********** End **********/
}
//函数十
status ListInsert(LinkList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L)return INFEASIBLE;
    LinkList cur=L->next;
    int postion=1;
    if(i==1){
        LinkList NewNode = (LinkList)malloc(sizeof(LNode));
        NewNode->data=e;
        NewNode->next=L->next;
        L->next=NewNode;
        return OK;
    }
    while(cur!=NULL){
        if(postion==i-1){
            LinkList NewNode = (LinkList)malloc(sizeof(LNode));
            NewNode->data=e;
            NewNode->next=cur->next;
            cur->next=NewNode;
            return OK;
        }
        postion++;
        cur=cur->next;
    }
    return ERROR;
    /********** End **********/
}
//函数十一
status ListDelete(LinkList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L)return INFEASIBLE;
    LinkList cur=L->next;
    LinkList pre=L;
    int postion=1;
    if(i==1){
        e=L->next->data;
        LinkList node = L->next;
        L->next=L->next->next;
        free(node);
        return OK;
    }
    while(cur!=NULL){
        if(postion==i-1&&cur->next!=NULL){
            e=cur->next->data;
            LinkList node = cur->next;
            cur->next=cur->next->next;
            free(node);
            return OK;
        }
        postion++;
        cur=cur->next;
    }
    return ERROR;
    /********** End **********/
}
//函数十二
status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L)return INFEASIBLE;
    LinkList cur = L->next;
    while(cur!=NULL){
        printf("%d ",cur->data);
        cur=cur->next;
    }
    return OK;
    /********** End **********/
}
//函数十三
status reverseList(LinkList &L){
    if(!L)return INFEASIBLE;
    LinkList pre=NULL,cur=L->next;
    while(cur!=NULL){
        LinkList next=cur->next;
        cur->next=pre;
        pre=cur;
        cur=next;
    }
    L->next=pre;
    return OK;
}
//函数十四
status RemoveNthFromEnd(LinkList &L,int i){
    int length=ListLength(L);
    int postion=1;
    i=length-i+1;
    if(!L)return INFEASIBLE;
    LinkList cur=L->next;
    if(i==1){
        LinkList node = L->next;
        L->next=L->next->next;
        free(node);
        return OK;
    }
    while(cur!=NULL){
        if(postion==i-1&&cur->next!=NULL){
            LinkList node = cur->next;
            cur->next=cur->next->next;
            free(node);
            return OK;
        }
        postion++;
        cur=cur->next;
    }
    return ERROR;
}
//函数十五
//排序
status sortList(LinkList &L){
    if(!L)return INFEASIBLE;
    LNode *cur = L->next;
    while (cur != NULL) {
        LNode *minNode=cur;
        LNode *temp=cur->next;
        // 交换当前节点和最小节点的值
        while(temp!=NULL){
            if(temp->data<minNode->data){
                minNode=temp;
            }
            temp=temp->next;
        }
        int tmp=minNode->data;
        cur->data=minNode->data;
        minNode->data=tmp;
    }
    return OK;
}

//函数十六          以文件的形式保存
status SaveList(LinkList L, const char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    if (L == NULL){
        return INFEASIBLE;
    }
    FILE* stream;
    stream = fopen(FileName, "w");
    LinkList temp = L->next;
    while (temp){
        fprintf(stream, "%d ", temp->data);
        temp = temp->next;
    }
    fprintf(stream,"%d",0);
    fclose(stream);
    return OK;

    /********** End 1 **********/
}

//函数十七  将文件的数据导出
status LoadList(LinkList &L,const char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    //if (L) return INFEASIBLE;
    L = (LinkList)malloc(sizeof(LNode));
    FILE *fp = fopen(FileName, "r");
    LinkList p = L;
    int e;
    fscanf(fp, "%d", &e);
    while (e) {
        p->next = (LinkList)malloc(sizeof(LNode));
        p = p->next;
        p->data = e;
        fscanf(fp, "%d", &e);
    }
    p->next = NULL;
    fclose(fp);
    return OK;
    /********** End 2 **********/
}

//函数十八 add
//附加功能18 多线性表管理：增加新线性表
status AddList(LISTS &Lists,char ListName[])
// 在Lists中增加一个名称为ListName的线性表。
{
   for(int i=0;i<Lists.length;i++)
        if (strcmp(Lists.elem[i].name, ListName) == 0)
        {
            printf("多线性表中已存在名称为 %s 的线性表！\n", ListName);
            return ERROR;
        }
    strcpy(Lists.elem[Lists.length].name,ListName);
    //接下来对新线性表初始化 
    Lists.elem[Lists.length].L=NULL;
    InitList(Lists.elem[Lists.length].L);
    Lists.length++;
	return OK;
}
//函数十九 remove
//附加功能19 多线性表管理：删除线性表
status RemoveList(LISTS &Lists,char ListName[])
// Lists中删除一个名称为ListName的线性表
{
	for(int i = 0; i < Lists.length; ++i){
        if(!strcmp(ListName, Lists.elem[i].name)){
            for(int j = i; j < Lists.length - 1; ++j){
                Lists.elem[j] = Lists.elem[j + 1];
            }
            Lists.length--;
            return OK;
        }
    }
    return ERROR;
}
//函数二十 Locate
//附加功能20 多线性表管理：查找线性表
int LocateList(LISTS Lists, char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
	 for(int i = 0; i < Lists.length; ++i){
        if(!strcmp(ListName, Lists.elem[i].name))
            return i + 1;
    }
    return 0;
}

//附加功能21 多线性表管理：遍历多线性表
status ListsTraverse(LISTS Lists)
{
    if (Lists.length == 0)
        return ERROR;
    for (int num = 0; num < Lists.length; num++)
    {
        printf("当前表名：%s ", Lists.elem[num].name);
        ListTraverse(Lists.elem[num].L);
        putchar('\n');
    }
    return OK;
}

//附加功能22 多线性表管理：选择一个线性表，输入其序号，后续可对其进行操作
LinkList switchList(LinkList L, LISTS &Lists, int i)
{
    if (i > Lists.length || i < 1)
        return NULL;
    else
    {
        L = Lists.elem[i - 1].L;  //传递地址以改动表    
        L->next = Lists.elem[i - 1].L->next;
        L->data = Lists.elem[i - 1].L->data;
        return L;
    }
}

int main(){
    int op=1;
    int state;
    int e,i;
    LISTS Lists;
    Lists.length=0,Lists.listsize=10;
    LinkList L=NULL;
    while (op)
    {
        system("cls");
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. InitList       10. ListInsert\n");
		printf("    	  2. DestroyList    11. ListDelete\n");
		printf("    	  3. ClearList      12. ListTrabverse\n");
		printf("    	  4. ListEmpty      13.reverseList\n");
		printf("    	  5. ListLength     14.RemoveNthFromEnd\n");
		printf("    	  6. GetElem        15.sortList\n");
		printf("          7. LocateElem     16.SaveList\n");
		printf("          8. PriorElem      17.LoadList\n");
		printf("          9. NextElem       18.AddList\n");
		printf("    	  19.RemoveList     20.LocateList\n");
		printf("          21.ListsTrabverse 22.SwitchList\n");
        printf("          0.exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~20]:\n");
		scanf("%d", &op);
        switch (op){
            case 1:
                state=InitList(L);
                if(state==OK){
                    printf("线性表创建成功");
                }else if(state==INFEASIBLE){
                    printf("线性表创建失败");
                }
                break;

            case 2:
                state=DestroyList(L);
                if(state==OK)printf("线性表销毁成功");
                else if(state==INFEASIBLE)printf("线性表不存在");
                break;

            case 3:
                state=ClearList(L);
                if(state==OK)printf("线性表清空成功");
                else if(state==INFEASIBLE)printf("线性表不存在");
                break;

            case 4:
                state=ListEmpty(L);
                if(state==OK)printf("线性表为空");
                else if(state==FALSE)printf("线性表不为空");
                else if(state==INFEASIBLE)printf("线性表不存在");
                break;

            case 5:
                state=ListLength(L);
                if(state==INFEASIBLE)printf("线性表不存在");
                else{
                    printf("线性表的长度是%d",state);
                }
                break;
            
            case 6:
                printf("请输入你想要获取的位置:");
                scanf("%d",&i);
                state=GetElem(L,i,e);
                if(state==INFEASIBLE)printf("线性表不存在");
                else if(state==ERROR)printf("i不合法");
                else if(state==OK){
                    printf("%d号位置的元素是%d",i,e);
                }
                break;

            case 7:
                printf("请输入你要查找的元素:");
                scanf("%d",&e);
                state=LocateElem(L,e);
                if(state==INFEASIBLE)printf("线性表不存在");
                else if(state==ERROR)printf("%d不存在",e);
                else printf("%d在表中的位置是%d",e,state);
                break;

            case 8:
                int pre;
                printf("请输入你要查找的元素的前驱结点:");
                scanf("%d",&e);
                state=PriorElem(L,e,pre);
                if(state==INFEASIBLE)printf("线性表不存在");
                else if(state==OK)printf("%d的前驱结点元素是%d",e,pre);
                else if(state==ERROR)printf("该节点没有前驱");
                break;

            case 9:
                int next;
                printf("请输入你要查找的元素的后驱结点:");
                scanf("%d",&e);
                state=NextElem(L,e,next);
                if(state==INFEASIBLE)printf("线性表不存在");
                else if(state==OK)printf("%d的后驱结点元素是%d",e,next);
                else if(state==ERROR)printf("该节点没有后驱");
                break;

            case 10:
                printf("请输入你想要插入的位置和元素：");
                scanf("%d%d",&i,&e);
                state=ListInsert(L,i,e);
                if(state==INFEASIBLE)printf("线性表不存在");
                else if(state==OK)printf("插入成功");
                else if(state==ERROR)printf("插入位置有问题");
                break;

            case 11:
                printf("请输入想删除的位置:");
                scanf("%d",&i);
                state=ListDelete(L,i,e);
                if(state==INFEASIBLE)printf("线性表不存在");
                else if(state==OK)printf("删除成功");
                else if(state==ERROR)printf("删除位置有问题");
                break;
            
            case 12:
                state=ListTraverse(L);
                if(state==INFEASIBLE)printf("线性表不存在");
                break;

            case 13:
                state=reverseList(L);
                if(state==INFEASIBLE)printf("线性表不存在");
                else if(state==OK)printf("翻转成功");
                break;

            case 14:
                printf("请输入倒数第几个: ");
                scanf("%d",&i);
                state=RemoveNthFromEnd(L,i);
                if(state==INFEASIBLE)printf("线性表不存在");
                else if(state ==OK)printf("删除成功");
                break;

            case 15:
                state=sortList(L);
                if(state==INFEASIBLE)printf("线性表不存在");
                else if(state ==OK)printf("排序成功");
                break;

            case 16:
                state = SaveList(L,"D:\\touge.txt");
                if (state == -1){
				    printf("线性表不存在。\n");
			    }
			    else{
				    printf("线性表已经成功复制在路径为%s的文件中。\n","D:\\touge.txt");
			    }
                break;

            case 17:
                state=LoadList(L, "D:\\touge.txt");
                printf("已成功读入。\n");
                break;

            case 18:
                char ListName[100];
                printf("请输入你要添加的线性表的名字：");
                scanf("%s",ListName);
                state = AddList(Lists, ListName);
                if (state == OK)
                    printf("成功新增名称为 %s 的线性表！\n", ListName);
                else
                    printf("新增失败！\n");
			    break;
            
            case 19:
                if(!Lists.length)
                {
                    printf("线性表的集合为空！无法进行此操作！\n");
                    break;
                }
                printf("请输入想要删除的线性表的名称：");
                scanf("%s", ListName);
                state = RemoveList(Lists, ListName);
                if (state == OK)
                    printf("成功删除名称为 %s 的线性表！\n", ListName);
                else if (state == ERROR)
                    printf("删除失败！\n");
                break;

            case 20:
                if(!Lists.length)
                {
                    printf("线性表的集合为空！无法进行此操作！\n");
                    break;
                }
                printf("请输入想要查找的线性表的名称：");
                scanf("%s", ListName);
                i = LocateList(Lists, ListName);
                if (i == 0)
                    printf("不存在名称为 %s 的线性表！\n", ListName);
                else printf("名称为 %s 的线性表的序号为 %d ！\n", ListName, i);
                break;

            case 21:
                state = ListsTraverse(Lists);
                if (state== ERROR)
                    printf("线性表的集合为空！\n");
                break;

            case 22:
                if(Lists.length)
                {
                    printf("\n---------------- All lists --------------------\n");
                    for(int i = 0; i < Lists.length; i++)
                        printf("%d %s\n", i + 1, Lists.elem[i].name);
                    printf("------------------ end ------------------------\n");
                }
                else
                {
                    printf("线性表的集合为空！无法进行此操作！\n");
                    getchar();getchar();
                    break;
                }
                printf("请输入想要进行操作的线性表的序号（从1开始）：");
                scanf("%d", &i);
                L = switchList(L, Lists, i);
                if (L == NULL)
                    printf("输入的序号不合法！单表已置空！\n");
                else
                    printf("下面可对线性表集合中序号为 %d 的线性表进行操作！\n", i);
                break;

            case 0:
                op=0;
                break;

        }
        Sleep(1000);
    }
}