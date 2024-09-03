#include"def.h"
#include"opt.h"
#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<queue>

void visit(VertexType v)
{
    printf(" %d,%s",v.key,v.others);
}

int g[40][40];

void MatrixTransformer(ALGraph G){
    for(int i=0;i<40;++i)
        for(int j=0;j<40;++j)
            g[i][j]=0;
    for(int i=0;i<G.vexnum;++i){
        ArcNode *p=G.vertices[i].firstarc;
        while(p){
            g[i][p->adjvex]=1;
            p=p->nextarc;
        }
    }
    
}

int ans[20],anss[20];
status VerticesSetLessThanK(ALGraph G,KeyType v,int k){
    MatrixTransformer(G);//矩阵化
    int p = LocateVex(G,v);
    for(int i=0;i<20;++i)ans[i]=0;
    if(p==-1)return ERROR;//节点不存在
    ans[p]=1;
    for(int i=1;i<k;++i){
        for(int h=0;h<20;++h)anss[h]=ans[h];
        for(int j=0;j<20;++j){
            if(anss[j]==1){
                for(int k=0;k<G.vexnum;++k)
                    if(g[j][k]==1)ans[k]=1;//利用邻接矩阵，两点之间有边即可以标记
            }
        }
    }
    return OK;
}

int tm[40][40];
void MatrixMul(){
    for(int i=0;i<20;++i){
        for(int j=0;j<20;++j){
            tm[i][j]=0;
        }
    }
    for(int i=0;i<20;++i){
        for(int j=0;j<20;++j){
            for(int k=0;k<20;++k){
                tm[i][j]+=g[i][k]*g[k][j];
            }
        }
    }
    for(int i=0;i<20;++i){
        for(int j=0;j<20;++j){
            g[i][j]=tm[i][j];
        }
    }
}//利用矩阵的乘法判断可达性

int ShortestPathLength(ALGraph G,KeyType v,KeyType w){
    int s1=LocateVex(G,v),s2=LocateVex(G,w);
    if(s1==-1||s2==-1)return -1;
    MatrixTransformer(G);
    if(g[s1][s2])return 1;
    for(int i=0;i<G.vexnum;++i){ 
        MatrixMul();
        if(g[s1][s2])return i+2;
    }
    return -1;
    /******************/
}

int shortest2(ALGraph G,KeyType v,KeyType w){
    int i=0,j=0,pos_1=-1,pos_2=-1,minid=0,min=1;
    int inf=1<<30;
    int dist[G.vexnum]={0};//距离数组
    int book[G.vexnum]={0};//标记数组
    pos_1=LocateVex(G,v);
    pos_2=LocateVex(G,w);
    if(pos_1==-1||pos_2==-1)return -1;
    book[pos_1]++;
    for(int i=0;i<G.vexnum;++i)dist[i]=inf;
    ArcNode *p=G.vertices[pos_1].firstarc;
    dist[pos_1]=0;
    while(p!=NULL){
        dist[p->adjvex]=1;
        p=p->nextarc;
    }//首节点
    for(int i=0;i<G.vexnum-1;++i){
        min=inf;
        for(int j=0;j<G.vexnum;++j){
            if(book[j]==0&&min>dist[j]){
                minid=j;
                min=dist[j];
            }
        }//找到距离最近的节点
        book[minid]++;
        p=G.vertices[minid].firstarc;
        while(p!=NULL){
            if(dist[p->adjvex]>1+dist[minid]){
                dist[p->adjvex]=1+dist[minid];
            }
            p=p->nextarc;
        }
    }
    if(dist[pos_2]==inf)return -1;
    return dist[pos_2];
}
int book[100];
void bfs(ALGraph G,int startnode){
    std::queue<int>Q;
    Q.push(startnode);
    while(!Q.empty()){
        int p=Q.front();
        Q.pop();
        book[p]=1;
        ArcNode *pp=G.vertices[p].firstarc;
        while(pp!=NULL){
            if(book[pp->adjvex]==0){
                Q.push(pp->adjvex);
            }
            pp=pp->nextarc;
        }
    }
}
int ConnectedComponentsNums(ALGraph &G){//连通分支
    for(int i=0;i<100;++i)book[i]=0;
    int cnt=0;
    if(G.vertices==NULL)return 0;
    for(int i=0;i<G.vexnum;++i){
        if(book[i]==0){
            cnt++;
            book[i]++;
            bfs(G,i);
        }
    }
    return cnt;
}

int main(){
    int op=1;
    int state;
    ALGraphs GS;
    GS.length=0;
    GS.listsize=10;
    ALGraph G;
    while(op){
        system("cls");
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. 创建图         10. 删除弧\n");
		printf("    	  2. 销毁图         11. 深度优先遍历\n");//5 xxb 8 jh 7 ecs 6 wxt -1 nil  5 6  5 7 6 7 7 8 -1 -1
		printf("    	  3. 查找节点       12. 广度优先遍历\n");//5 线性表 8 集合 7 二叉树 6 无向图 -1 nil 5 6 5 7 6 7 7 8 -1 -1
		printf("    	  4. 顶点赋值       13.距离小于k的顶点集合\n");
		printf("    	  5. 获得第一邻接点  14.最小路径\n");
		printf("    	  6. 获得下一邻接   15.图的连通分支\n");
		printf("          7. 插入顶点       16.文件保存\n");
		printf("          8. 删除顶点       17.文件读取\n");
		printf("          9. 插入弧         18.添加图\n");
		printf("    	  19.查找图         20.删除图\n");
		printf("          21.选择图         22.提交修改\n");
        printf("          23.遍历图         0.exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~20]:\n");
        scanf("%d",&op);
        if(op==1){
            printf("请输入数据：");
            VertexType V[30];
            KeyType VR[100][2];
            int i=0;
            do {
                scanf("%d%s",&V[i].key,V[i].others);
            } while(V[i++].key!=-1);
            i=0;
            do {
                scanf("%d%d",&VR[i][0],&VR[i][1]);
            } while(VR[i++][0]!=-1);
            if (CreateGraph(G,V,VR)==ERROR) printf("输入数据错，无法创建\n");
            else printf("创建成功！\n");
        }
        if(op==2){
            state=DestroyGraph(G);
            if(state==OK)printf("销毁成功");
        }
        if(op==3){
            printf("请输入关键词:");
            int key;
            scanf("%d",&key);
            state=LocateVex(G,key);
            if(state==-1)printf("不存在该节点");
            else printf("位序为%d\n",state);
        }
        if(op==4){
            printf("请输入关键词和所赋的新值：(所赋的新值包括两个)");
            int key;
            VertexType value;
            scanf("%d%d%s",&key,&value.key,value.others);
            state=PutVex(G,key,value);
            if(state==ERROR)printf("赋值失败");
            else printf("赋值成功");
        }
        if(op==5){
            printf("请输入关键词：");
            int key;
            scanf("%d",&key);
            state=FirstAdjVex(G,key);
            if(state==-1)printf("不存在");
            else printf("第一邻接点为%d,%s",G.vertices[state].data.key,G.vertices[state].data.others);
        }
        if(op==6){
            printf("请输入2个关键词：");
            int key1;
            int key2;
            scanf("%d%d",&key1,&key2);
            state=NextAdjVex(G,key1,key2);
            if(state==-1)printf("不存在");
            else printf("下一个邻接点为%d,%s",G.vertices[state].data.key,G.vertices[state].data.others);
        }
        if(op==7){
            printf("请输入关键词（包括字符串):");
            VertexType value;
            scanf("%d%s",&value.key,value.others);
            state=InsertVex(G,value);
            if(state==ERROR)printf("插入失败");
            else printf("插入成功");
        }
        if(op==8){
            printf("请输入关键词(不包括字符串)：");
            int key;
            scanf("%d",&key);
            state=DeleteVex(G,key);
            if(state==ERROR)printf("删除失败");
            else printf("删除成功");
        }
        if(op==9){
            printf("请输入你想加边的两个点:");
            int k1,k2;
            scanf("%d%d",&k1,&k2);
            state=InsertArc(G,k1,k2);
            if(state==ERROR)printf("插入失败");
            else printf("插入成功");
        }
        if(op==10){
            printf("请输入你想要删除的边的两个点：");
            int k1,k2;
            scanf("%d%d",&k1,&k2);
            state=DeleteArc(G,k1,k2);
            if(state==ERROR)printf("删除失败");
            else printf("删除成功");
        }
        if(op==11){
            printf("深度优先遍历结果如下：\n");
            DFSTraverse(G,visit);
        }
        if(op==12){
            printf("广度优先遍历结果如下：\n");
            BFSTraverse(G,visit);
        }
        if(op==13){
            printf("请输入关键词和距离：");
            int k1,k2;
            scanf("%d%d",&k1,&k2);
            state=VerticesSetLessThanK(G,k1,k2);
            if(state==ERROR)printf("失败");
            else {
                printf("节点如下\n");
                for(int i=0;i<G.vexnum;i++)if(ans[i])printf("%d %s\n",G.vertices[i].data.key,G.vertices[i].data.others);
            }
        }
        if(op==14){
            printf("请输入两个关键词：");
            int k1,k2;
            scanf("%d%d",&k1,&k2);
            state=ShortestPathLength(G,k1,k2);
            if(state==-1)printf("不连通");
            else{
                printf("最短距离为：%d",state);
            }
        }
        if(op==15){
            state=ConnectedComponentsNums(G);
            printf("分支数为：%d",state);
        }
        if(op==16){
            SaveGraph(G,"D:\\touge.txt");
            printf("保存成功");
        }
        if(op==17){
            LoadGraph(G,"D:\\touge.txt");
            printf("读取成功");
        }
        if(op==18){
            char ListName[20];
            printf("请输入你要添加的图的名字：");
            scanf("%s",ListName);
            state=AddALGraph(GS,ListName);
            printf("添加成功");
        }
        if(op==19){
            char ListName[20];
            printf("请输入你要查找的图的名字：");
            scanf("%s",ListName);
            state=LocateALGraph(GS,ListName);
            if(state==0)printf("没有该图");
            else printf("该图的位置是%d",state);
        }
        if(op==20){
            char ListName[20];
            printf("请输入你要删除的图的名字：");
            scanf("%s",ListName);
            state=RemoveALGraph(GS,ListName);
            if(state==ERROR)printf("没有该图");
            else printf("删除成功");
        }
        if(op==21){
            if(GS.length){
                printf("\n---------------- All lists --------------------\n");
                for(int i = 0; i < GS.length; i++)
                    printf("%d %s\n", i + 1, GS.elem[i].name);
                printf("------------------ end ------------------------\n");
                int key;
                printf("请选择上述的序号之一进行操作:");
                scanf("%d",&key);
                G=GS.elem[key-1].G;
                printf("现在你可以对该序号的图进行操作!");
            }
            else printf("为空，无法操作");
            printf("请选择其中之一进行操作:");
           
        }
        if(op==22){
            int key;
            printf("请输入你想要修改的图的序号(先前选择的图):");
            scanf("%d",&key);
            GS.elem[key-1].G=G;
            printf("修改成功");
        }
        if(op==23){
            if(G.vexnum==0)printf("图为空");
            else{
                printf("遍历的结果如下\n");
                ALGraphTraverse(G);
            }
            
        }
        Sleep(2000);
    }
}