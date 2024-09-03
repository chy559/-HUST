#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include<windows.h>
#include "def.h"
#include "opt.h"

using namespace std;
BiTree T;
Trees trees;

int main(){
    int op=1;
    int state;
    trees.length=0,trees.listsize=10;
    T=NULL;
    TElemType value;
    BiTNode *node;
    int e,LR,i;
    char str[100];
    while(op){
        system("cls");
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. 创建二叉树       10. 删除节点\n");
		printf("    	  2. 销毁二叉树       11. 前序遍历\n");
		printf("    	  3. 清空二叉树       12. 中序遍历\n");
		printf("    	  4. 判空二叉树       13. 后序遍历\n");
		printf("    	  5. 二叉树深度       14. 按层遍历\n");
		printf("    	  6. 查找节点         15. 最大路径和\n");
		printf("          7. 节点赋值         16. 最近公共祖先\n");
		printf("          8. 兄弟节点         17. 翻转二叉树\n");
		printf("          9. 插入节点         18. 文件保存\n");
		printf("    	  19.文件读取         20. 添加树\n");
		printf("          21.查找树           23. 删除树\n");//1 a 2 b 0 null 0 null 3 c 4 d 0 null 0 null 5 e 0 null 0 null -1 null
        printf("          22.选中树           0.exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~20]:\n");
		scanf("%d", &op);
        switch (op)
        {
        case 1:
            i=0;
            printf("请依次输入关键词和名字(以-1结尾)\n");
            TElemType definitions[100];
            do{
                scanf("%d%s",&definitions[i].key,definitions[i].others);
            }while(definitions[i++].key!=-1);
            state=CreateBiTree(T,definitions);
            if(state==OK)printf("创建成功\n");
            else if(state==ERROR)printf("创建失败\n");
            break;

        case 2:
            state=DestroyBiTree(T);
            if(state==OK)printf("销毁成功\n");
            else if(state==ERROR)printf("销毁失败，树为空\n");
            break;
        
        case 3:
            state=ClearBiTree(T);
            if(state==OK)printf("清空成功!\n");
            else if(state==ERROR)printf("失败，树为空\n");
            break;

        case 4:
            state=BiTreeDepth(T);
            if(state==0)printf("树为空\n");
            else printf("树非空");
            break;

        case 5:
            state=BiTreeDepth(T);
            if(state==0)printf("树为空");
            else printf("该二叉树的深度为:%d\n",state);
            break; 

        case 6:
            printf("请输入该结点关键词：");
            scanf("%d",&e);
            node=LocateNode(T,e);
            if(node==NULL)printf("该节点不存在");
            else printf("节点名: %s\n节点数值: %d\n",node->data.others,node->data.key);
            break;
        
        case 7:
            printf("请输入该节点的关键词：");
            scanf("%d",&e);
            printf("请输入该节点之新关键词和新名称:");
            scanf("%d%s",&value.key,value.others);
            state=Assign(T,e,value);
            if(state==ERROR)printf("未找到该节点");
            if(state==OK)printf("更行成功");
            break;

        case 8:
            printf("请输入节点的关键词:");
            scanf("%d",&e);
            node=GetSibling(T,e);
            if(node==NULL)printf("不存在兄弟节点");
            else
                printf("兄弟节点的名：%s,兄弟节点数值: %d\n",node->data.others,node->data.key);
            break;
        
        case 9:
            printf("请输入节点的关键词：");
            scanf("%d",&e);
            printf("请输入LR值：");
            scanf("%d",&LR);
            printf("请输入插入节点的关键词和名字：");
            scanf("%d%s",&value.key,value.others);
            state=InsertNode(T,e,LR,value);
            if(state==ERROR)printf("更新失败(关键词重复或未找到该节点)");
            if(state==OK)printf("更新成功");
            break;

        case 10:
            printf("请输入节点的关键词：");
            scanf("%d",&e);
            state=DeleteNode(T,e);
            if(state==OK)printf("删除成功");
            else if(state==ERROR)printf("删除失败，节点不存在");
            break;
        
        case 11:
            printf("前序遍历结果如下：\n");
            PreOrderTraverse(T,visit);
            break;
        
        case 12:
            printf("中序遍历结果如下：\n");
            InOrderTraverse(T,visit);
            break;
        
        case 13:
            printf("后序遍历结果如下：\n");
            PostOrderTraverse(T,visit);
            break;

        case 14:
            printf("层序遍历结果如下：\n");
            LevelOrderTraverse(T,visit);
            break;

        case 15:
            state=MaxPathSum(T);
            printf("该二叉树的最大路径和为：%d",state);
            break;
        
        case 16:
            int e1,e2;
            printf("请输入节点一和二的关键字：");
            scanf("%d%d",&e1,&e2);
            node=findLCA(T,e1,e2);
            if(node==NULL)printf("找不到");
            else printf("节点名：%s\n节点关键字：%d",node->data.others,node->data.key);
            break;

        case 17:
            InvertTree(T);
            printf("更新成功");
            break;
        
        case 18:
            SaveBiTree(T,"D:\\touge.txt");
            printf("保存成功");
            break;

        case 19:
            LoadBiTree(T,"D:\\touge.txt");
            printf("读取成功");
            break;

        case 20:
            printf("请输入新表的名字：");
            scanf("%s",str);
            state=AddTree(trees,str);
            if(state==OK)printf("添加成功");
            else if(state==ERROR)printf("已经存在，无法添加");
            break;
    
        case 21:
            printf("请输入你要查找的表名：");
            scanf("%s",str);
            state=LocateTree(trees,str);
            if(state==0)printf("不存在");
            else printf("位置是:%d",state);
            break;

        case 22:
            if(trees.length){
                printf("\n---------------- All lists --------------------\n");
                for(int i=0;i<trees.length;++i){
                    printf("%d    %s\n",i+1,trees.elem[i].name);
                }
                printf("------------------ end ------------------------\n");
            }
            printf("请输入想要进行操作的树的序号（从1开始）：");
            scanf("%d", &i);
            T=SwitchTree(trees,i);
            if (T == NULL)
                printf("输入的序号不合法！单表已置空！\n");
            else
                printf("下面可对线性表集合中序号为%d的树进行操作！\n", i);
            break;

        case 23:
            printf("请输入你要删除的表名");
            scanf("%s",str);
            state=RemoveTree(trees,str);
            if(state==OK)printf("删除成功");
            break;

        case 0:
            op=0;
            break;
        
        default:
            break;
        }
        Sleep(2000);
    }
}