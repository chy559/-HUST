#ifndef OPT_H_INCLUDED
#define OPT_H_INCLUDED


#include <queue>
#include <cstring>
#include"def.h"

using namespace std;

bool CheckDuplicateKeys(VertexType V[],int vernum){
    for (int i = 0; i < vernum - 1; i++) {
        for (int j = i + 1; j < vernum; j++) {
            if (V[i].key == V[j].key) {
                return true;
            }
        }
    }
    return false;
}
status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    G.vexnum=0;
    G.arcnum=0;
    G.kind=UDG;
    //初始化头部节点
    for (int i = 0; i<MAX_VERTEX_NUM; i++){
        G.vertices[i].data.key = -1;
        G.vertices[i].firstarc = NULL;
    }
    // 遍历顶点序列和关系对序列，创建图的头结点
    while(V[G.vexnum].key != -1){
        G.vertices[G.vexnum].data = V[G.vexnum];
        G.vertices[G.vexnum].firstarc=NULL;
        G.vexnum++;
        if(G.vexnum>MAX_VERTEX_NUM)return ERROR;
    }
    if(G.vexnum==0)return ERROR;//判断是否有顶点

    if(CheckDuplicateKeys(V, G.vexnum))return ERROR;//检查是否有重复节点
    // 遍历关系对序列，构建邻接表
    for(int i = 0; VR[i][0]!=-1 && VR[i][1] != -1; i++){
        KeyType v1=VR[i][0];
        KeyType v2=VR[i][1];

        // 找到 v1 和 v2 对应的顶点位置
        int pos_v1 = -1, pos_v2 = -1;
        for(int j=0;j<G.vexnum; j++){
            if(G.vertices[j].data.key == v1)
                pos_v1 = j;
            else if(G.vertices[j].data.key == v2)
                pos_v2 =j;
        }
        // 无效顶点
        if(pos_v1 == -1||pos_v2 == -1){
            return ERROR;
        }
        // 创建表结点并插入邻接表中
        ArcNode *arc1=(ArcNode*)malloc(sizeof(ArcNode));
        arc1->adjvex=pos_v2;
        arc1->nextarc=G.vertices[pos_v1].firstarc;
        G.vertices[pos_v1].firstarc=arc1;

        ArcNode *arc2 = (ArcNode*)malloc(sizeof(ArcNode));
        arc2->adjvex = pos_v1;
        arc2->nextarc = G.vertices[pos_v2].firstarc;
        G.vertices[pos_v2].firstarc = arc2;

        G.arcnum++;
    }
    return OK;
}
    /********** End **********/

status DestroyGraph(ALGraph &G)
/*销毁无向图G,删除G的全部顶点和边*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    //删除边
    for(int i=0;i<G.vexnum;++i){
        ArcNode *p= G.vertices[i].firstarc;
        while(p!=NULL){
            ArcNode *current=p;
            p=p->nextarc;
            free(current);
            current=NULL;
        }
    }
    G.vexnum=0;
    G.arcnum=0;
    return OK;
    /********** End **********/
}

int LocateVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for(int i=0;i<G.vexnum;++i){
        if(G.vertices[i].data.key==u)return i;
    }
    return -1;
    /********** End **********/
}

status PutVex(ALGraph &G,KeyType u,VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for(int i=0;i<G.vexnum-1;++i){
        if(G.vertices[i].data.key==value.key)
            return ERROR;
    } //检查是否有重复的节点
    for(int i=0;i<G.vexnum;++i){
        if(G.vertices[i].data.key==u){
            G.vertices[i].data=value;
            return OK;
        }
    }   
    return ERROR;
    /********** End **********/
}

int FirstAdjVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int pos_1=LocateVex(G,u);
    if(pos_1==-1)return -1;
    ArcNode *p=G.vertices[pos_1].firstarc;
    return p->adjvex;
    /********** End **********/
}

int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//v对应G的一个顶点,w对应v的邻接顶点；操作结果是返回v的（相对于w）下一个邻接顶点的位序；
//如果w是最后一个邻接顶点，或v、w对应顶点不存在，则返回-1。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int pos_1=LocateVex(G,v);
    int pos_2=LocateVex(G,w);
    if(pos_1==-1||pos_2==-1)return -1;
    
    ArcNode* p=G.vertices[pos_1].firstarc;
    while(p&&p->nextarc){
        if(p->adjvex==pos_2)return p->nextarc->adjvex;
        p=p->nextarc;
    }
    return -1;
    /********** End **********/
}

status InsertVex(ALGraph &G,VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    //先判断是否重复
    for(int i=0;i<G.vexnum;++i){
        if(G.vertices[i].data.key==v.key)return ERROR; 
    }
    //判断是否已满
    if(G.vexnum==20)return ERROR;
    VNode newNode;
    newNode.data=v;
    newNode.firstarc=NULL;
    G.vertices[G.vexnum++]=newNode;
    return OK;
    /********** End **********/
}

void DeleteVex_A_Node(ALGraph &G,VNode &Node,int index)
{
    ArcNode * p =Node.firstarc;
    while(Node.firstarc!=NULL && Node.firstarc->adjvex==index)
    {
        G.arcnum--;
        Node.firstarc=Node.firstarc->nextarc;
        free(p);
        p=Node.firstarc;
    }
    if(Node.firstarc==NULL)return;
    ArcNode * q =Node.firstarc->nextarc;
    for(;q!=NULL;)
    {
        if(q->adjvex==index)
        {
            G.arcnum--;
            p->nextarc=q->nextarc;
            free(q);
            q=p->nextarc;
        }
        else
        {
            p=p->nextarc;
            q=q->nextarc;
        }
    }
}
status DestroyList(ArcNode * f)
{
    if(f==NULL)return INFEASIBLE;
    ArcNode * p=f;
    while(p)
    {
        f=f->nextarc;
        free(p);
        p=f;
    }
    return OK;
}
status DeleteVex(ALGraph &G,KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int loc=LocateVex(G,v);
    if (loc==-1||G.vexnum==1) return ERROR;
    for(int i=0;i<G.vexnum;i++)
    {
        DeleteVex_A_Node(G,G.vertices[i],loc);
    }
    for(int i=0;i<G.vexnum;i++)
    {
        ArcNode * f=G.vertices[i].firstarc;
        for(;f!=NULL;f=f->nextarc)
        {
            if(f->adjvex>loc)
            {
                (f->adjvex)--;
            }
        }
    }
    DestroyList(G.vertices[loc].firstarc);
    for (int i=loc;i<G.vexnum-1;++i)
        G.vertices[i] = G.vertices[i+1];
    --G.vexnum;
    return OK;
    /********** End **********/
}
status InsertArc(ALGraph &G,KeyType v,KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int pos_1=LocateVex(G,v);
    int pos_2=LocateVex(G,w);   
    if(pos_1==-1||pos_2==-1)return ERROR;
    //检查是否加入了重复的边
    ArcNode *p=G.vertices[pos_1].firstarc;
    while(p){
        if(p->adjvex==pos_2)return ERROR;
        p=p->nextarc;
    }

    ArcNode *v1=(ArcNode*)malloc(sizeof(ArcNode));
    v1->adjvex=pos_2;
    v1->nextarc=G.vertices[pos_1].firstarc;
    G.vertices[pos_1].firstarc=v1;

    ArcNode *v2=(ArcNode*)malloc(sizeof(ArcNode));
    v2->adjvex=pos_1;
    v2->nextarc=G.vertices[pos_2].firstarc;
    G.vertices[pos_2].firstarc=v2;
    ++G.arcnum;
    return OK;
    /********** End **********/
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int pos_1=LocateVex(G,v);
    int pos_2=LocateVex(G,w);
    if(pos_1==-1||pos_2==-1)return ERROR;

    ArcNode *p1 = G.vertices[pos_1].firstarc;
    ArcNode *prev_p1 = nullptr;
    while (p1) {
        if (p1->adjvex == pos_2) {
            if (prev_p1) {
                prev_p1->nextarc = p1->nextarc;
            } else {
                G.vertices[pos_1].firstarc = p1->nextarc;
            }
            free(p1);
            //p1=(prev_p1? prev_p1->nextarc:G.vertices[pos_1].firstarc);
            break;
        }
        prev_p1 = p1;
        p1 = p1->nextarc;
    }
    if (!p1)
       return ERROR;

    ArcNode *p2 = G.vertices[pos_2].firstarc;
    ArcNode *prev_p2 = nullptr;
    while (p2) {
        if (p2->adjvex == pos_1) {
            if (prev_p2) {
                prev_p2->nextarc = p2->nextarc;
            } else {
                G.vertices[pos_2].firstarc = p2->nextarc;
            }
            free(p2);
            //p2=(prev_p2? prev_p2->nextarc:G.vertices[pos_2].firstarc);
            break;
        }
        prev_p2 = p2;
        p2 = p2->nextarc;
    }
    G.arcnum--;
    return OK;
    /********** End **********/
}

int visited[25];
void dfs(ALGraph G,int n,void (*visit)(VertexType)){
    visited[n]=1;
    visit(G.vertices[n].data);
    ArcNode *p=G.vertices[n].firstarc;
    while(p){
        if(visited[p->adjvex]==0)dfs(G,p->adjvex,visit);
        p=p->nextarc;
    }
}
status DFSTraverse(ALGraph &G,void (*visit)(VertexType)){
    for(int i=0;i<25;++i)visited[i]=0;
    for(int i=0;i<G.vexnum;++i){
        if(visited[i]==0)dfs(G,i,visit);
    }
}

status BFSTraverse(ALGraph &G,void(*visit)(VertexType)){
    for(int i=0;i<25;++i)visited[i]=0;
    queue<int>Queue;
    for(int i=0;i<G.vexnum;++i){
        if(visited[i]==0){
            Queue.push(i);
            visited[i]=1;
        }
        while(!Queue.empty()){
            int cur = Queue.front();
            Queue.pop();
            visit(G.vertices[cur].data);
            ArcNode*p=G.vertices[cur].firstarc;
            while(p){
                if(visited[p->adjvex]==0){Queue.push(p->adjvex);
                visited[p->adjvex]=1;}
                p=p->nextarc;
            }
        }
    }
    return OK;
}

status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    FILE*fp1;
    fp1=fopen(FileName,"w");
    int i,j,tt=-1;
    int nnn[30][2];
    i=0;
    while(i<G.vexnum)
    {
        fprintf(fp1,"%d %s ",G.vertices[i].data.key,G.vertices[i].data.others);
        ++i;
    }
    i=0;
    fprintf(fp1,"%d null ",tt);
    while(i<G.vexnum)
    {
        for(j=0;j<30;++j)
        {
            nnn[j][0]=-1;
            nnn[j][1]=-1;
        }
        j=0;
        if(G.vertices[i].firstarc!=NULL)
        {
            // if(G.vertices[i].data.key<G.vertices[G.vertices[i].firstarc->adjvex].data.key)
            // {
            //     nnn[j][0]=G.vertices[i].data.key;
            //     nnn[j][1]=G.vertices[G.vertices[i].firstarc->adjvex].data.key;
            //     ++j;
            // }
            ArcNode*p=G.vertices[i].firstarc;
            while(p!=NULL)
            {
                if(G.vertices[i].data.key<G.vertices[p->adjvex].data.key)
                {
                    nnn[j][0]=G.vertices[i].data.key;
                    nnn[j][1]=G.vertices[p->adjvex].data.key;
                    ++j;
                }
                p=p->nextarc;
            }
        }
        --j;
        while(j>=0)
        {
           fprintf(fp1,"%d %d ",nnn[j][0],nnn[j][1]);
            --j;
        }
        ++i;
    }
    fprintf(fp1,"%d %d ",tt,tt);
    fclose(fp1);
    return OK;

}

status LoadGraph(ALGraph &G,char FileName[]){
    FILE *fp=fopen(FileName,"r+");
    VertexType V[30];
    int VR[100][2];
    int i=0;
    do{
        fscanf(fp,"%d %s ",&V[i].key,V[i].others);
    }while(V[i++].key!=-1);//将点的数据取出
    i=0;
    do{
        fscanf(fp,"%d %d ",&VR[i][0],&VR[i][1]);
    }while(VR[i++][0]!=-1);
    fclose(fp);
    CreateGraph(G,V,VR);
}   

status AddALGraph(ALGraphs &GS,char ListName[]){
    for(int i=0;i<GS.length;i++)
        if (strcmp(GS.elem[i].name, ListName) == 0)
        {
            printf("多表中已存在名称为 %s 的图！\n", ListName);
            return ERROR;
        }
    strcpy(GS.elem[GS.length].name,ListName);
    GS.elem[GS.length].G.vexnum=0;
    GS.elem[GS.length].G.arcnum=0;
    GS.length++;
    return OK;
}

status LocateALGraph(ALGraphs &GS,char ListName[]){
    for(int i=0;i<GS.length;++i){
        if(strcmp(GS.elem[i].name,ListName)==0)
            return i+1;
    }
    return 0;
}

status RemoveALGraph(ALGraphs &GS,char ListName[]){
    for(int i=0;i<GS.length;++i){
        if(strcmp(GS.elem[i].name,ListName)==0){
            for(int j=i;j<GS.length-1;++j){
                GS.elem[j]=GS.elem[j+1];
            }
            GS.length--;
            return OK;
        }
    }
    return ERROR;
}

void ALGraphTraverse(ALGraph &G){
    for(int i=0;i<G.vexnum;++i){
        printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
        ArcNode *p=G.vertices[i].firstarc;
        while(p!=nullptr){
            printf(" %d",p->adjvex);
            p=p->nextarc;
        }
        printf("\n");
    }
}
#endif