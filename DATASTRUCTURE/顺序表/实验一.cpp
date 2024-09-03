#include <stdio.h>
#include <Windows.h>
#include <string.h>

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


typedef struct {  //顺序表（顺序结构）的定义
	ElemType* elem;
	int length;
	int listsize;
}SqList;

typedef struct {  //线性表的管理表定义
    struct {
        char name[30];
        SqList L;
    } elem[10];
    int length;
    int listsize;
}LISTS;




void sort_list(SqList L);

int cmp(const void* a, const void* b);

status InitList(SqList& L);

status DestroyList(SqList& L);

status ClearList(SqList& L);
 
status ListEmpty(SqList L);

int ListLength(SqList L);

status GetElem(SqList L,int i,ElemType& e);

status LocateElem(SqList L,ElemType e);

status PriorElem(SqList L,ElemType cur,ElemType& pre_e);

status NextElem(SqList L,ElemType cur,ElemType& next_e);

status ListInsert(SqList& L,int i,ElemType e);

status ListDelete(SqList& L, int i, ElemType& e);
status ListTrabverse(SqList L);

bool is_same(char* str1, char* str2);

status  SaveList(SqList L, const char FileName[]);

status  LoadList(SqList& L, const char FileName[]);

status AddList(LISTS& Lists, const char ListName[]);

status RemoveList(LISTS& Lists, char ListName[]);

int LocateList(LISTS Lists, const char ListName[]);
#include <stdint.h>

int max(int a,int b){
	return a>b? a:b;
}
int cmp(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}

int max_sub_array(SqList L)
{
	if (L.length == 0)
	{
		return INT64_MIN;
	}
	int result = 0;
	int* dp = (int*)malloc(sizeof(int) * L.length);
	dp[0] = L.elem[0];
	for (int i = 1; i < L.length; i++)
	{
		dp[i] = max(dp[i - 1] + L.elem[i], L.elem[i]);
		result = max(result, dp[i]);
	}
	free(dp);
	return result;
}
void sort_list(SqList L)
{
	qsort(L.elem, L.length, sizeof(int), cmp);
	return;
}



status InitList(SqList& L)
{
	
		// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
	
		// 请在这里补充代码，完成本关任务
		/********** Begin *********/
		//如果线性表不存在
		if (L.elem == NULL)
		{
			L.elem = (ElemType*)malloc(sizeof(int) * LIST_INIT_SIZE);    //为elem数组开辟空间
			L.length = 0;    //线性表的初始长度设置为0
			L.listsize = LIST_INIT_SIZE;    //线性表的最大长度
			return OK;
		}
		//如果线性表存在，返回INFEASIBLE
		return INFEASIBLE;
		/********** End **********/
	
}



status DestroyList(SqList& L)
{
	if (L.elem != NULL)
	{
		L.elem = NULL;
		free(L.elem);
		return OK;
	}

	return INFEASIBLE;
}


status ClearList(SqList& L)
{
	if (L.elem != NULL)
	{
		//删除线性表中的元素
		L.length = 0;

		return OK;
	}
	//如果线性表不存在，返回INFEASIBLE
	return INFEASIBLE;
}



status ListEmpty(SqList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	//如果线性表不存在
	if (L.elem == NULL)
	{
		return INFEASIBLE;
	}
	else
	{

		if (L.length == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	/********** End **********/
}


status ListLength(SqList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L.elem == NULL)
	{
		return INFEASIBLE;
	}
	return L.length;

	/********** End **********/
}

status GetElem(SqList L, int i, ElemType& e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L.elem == NULL)
	{
		return INFEASIBLE;
	}
	if (i > L.length || i < 1)
	{
        return ERROR;
	}
	e = L.elem[i - 1];
	return OK;
	/********** End **********/
}

int LocateElem(SqList L, ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE（即-1）。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L.elem == NULL)
	{
		return INFEASIBLE;
	}
	for (int i = 0; i < L.length; i++)
	{
		if (L.elem[i] == e)
		{
			return i + 1;
		}
	}
	return 0;

	/********** End **********/
}

status PriorElem(SqList L, ElemType e, ElemType& pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L.elem == NULL)
	{
		return INFEASIBLE;
	}

	for (int i = 0; i < L.length; i++)
	{
		if (L.elem[i] == e)
		{
			if (i == 0)
			{
				return ERROR;
			}
			pre = L.elem[i - 1];
			return OK;
		}
	}
	return ERROR;
	/********** End **********/
}

status NextElem(SqList L, ElemType e, ElemType& next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L.elem == NULL)
	{
		return INFEASIBLE;
	}

	for (int i = 0; i < L.length; i++)
	{
		if (L.elem[i] == e)
		{
			if (i == L.length - 1)
			{
				return ERROR;
			}
			next = L.elem[i + 1];
			return OK;
		}
	}
	return ERROR;
	/********** End **********/
}

status ListInsert(SqList& L, int i, ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L.elem == NULL)
	{
		return INFEASIBLE;
	}

	if (i <= 0 || i > L.length + 1)
	{
		return ERROR;
	}
	L.length++;
	L.listsize++;
	int index = L.length - 1;
	for (index; index >= i; index--)
	{
		L.elem[index] = L.elem[index - 1];
	}
	L.elem[index] = e;
	return OK;
	/********** End **********/
}

status ListDelete(SqList& L, int i, ElemType& e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L.elem == NULL)
	{
		return INFEASIBLE;
	}
	if (i <= 0 || i > L.length)
	{
		return ERROR;
	}
	e = L.elem[i - 1];
	for (int j = i - 1; j < L.length; j++)
	{
		L.elem[j] = L.elem[j + 1];
	}
	L.length--;
	return OK;
	/********** End **********/
}

status ListTrabverse(SqList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L.elem == NULL)
	{
		return INFEASIBLE;
	}
	for (int i = 0; i < L.length; i++)
	{
		if (i == L.length - 1)
		{
			printf("%d", L.elem[i]);
		}
		else
		{
			printf("%d ", L.elem[i]);
		}

	}
	return OK;
	/********** End **********/
}



status  SaveList(SqList L, const char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L.elem == NULL)
	{
		return INFEASIBLE;
	}
	FILE* stream;
	stream = fopen(FileName, "w");
	for (int i = 0; i < L.length; i++)
	{
		fprintf(stream, "%d ", L.elem[i]);
	}
	fclose(stream);
	return OK;
	/********** End **********/
}
status  LoadList(SqList& L, const char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L.elem != NULL)
	{
		return INFEASIBLE;
	}
	L.elem = (ElemType*)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
	if (L.elem == NULL)
	{
		return INFEASIBLE;
	}
	L.length = 0;
	FILE* stream;
	stream = fopen(FileName, "r");
	while (fscanf(stream, "%d", &L.elem[L.length++]) != EOF);
	L.length--;
	fclose(stream);
	return OK;
	/********** End **********/
}

status AddList(LISTS& Lists, const char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	int i = 0;
	for (i; ListName[i] != '\0'; i++)
	{
		Lists.elem[Lists.length].name[i] = ListName[i];
	}
	Lists.elem[Lists.length].L.elem = (ElemType*)malloc(sizeof(ElemType) * 10);
	Lists.elem[Lists.length].L.listsize = 10;
	Lists.elem[Lists.length].L.length = 0;
	Lists.elem[Lists.length].name[i]  = '\0';
	Lists.length++;
	return OK;
	/********** End **********/
}




status RemoveList(LISTS& Lists, char ListName[])
// Lists中删除一个名称为ListName的线性表
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	for (int i = 0; i < Lists.length; i++)
	{
		if (is_same(Lists.elem[i].name, ListName))
		{
			for (int j = i; j < Lists.length - 1; j++)
			{
				Lists.elem[i] = Lists.elem[i + 1];
			}
			Lists.length--;
			return OK;
		}
	}
	return false;

	/********** End **********/
}


bool is_same(char* str1, char* str2)
{
	if (strlen(str1) != strlen(str2))
	{
		return false;
	}
	int n = strlen(str1);
	for (int i = 0; i < n; i++)
	{
		if (str1[i] != str2[i])
		{
			return false;
		}
	}
	return true;
}

int LocateList(LISTS Lists, const char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	for (int i = 0; i < Lists.length; i++)
	{
		if (strcmp(Lists.elem[i].name, ListName) == 0)
		{
			return i + 1;
		}
	}
	return 0;

	/********** End **********/
}
int SubarrayK(int K,SqList L){
	int count=0;
	for(int i=0;i<L.length;++i){
		int sum=0;
		for(int j=i;j<L.length;++j){
			sum+=L.elem[j];
			if(sum==K)count++;
		}
	}
	return count;
}
ElemType SubArrayNum(SqList L, int k) {  
    if (L.length == 0&&L.elem) return ERROR; // 空表直接返回0  
    else if(L.elem==NULL){
        return INFEASIBLE;
	}
    int count = 0;  
    int prefixSum = 0;  
    int prefixSumCounts[20001] = {0}; 
    prefixSumCounts[0] = 1; // 初始化前缀和为0的次数为1  
  
    for (int i = 0; i < L.length; i++) {  
        prefixSum += L.elem[i];  
        // 如果prefixSum-k在之前出现过，则找到了一个和为k的子数组  
        if (prefixSum - k >= 0 && prefixSumCounts[prefixSum - k] > 0) {  
            count += prefixSumCounts[prefixSum - k];  
        }  
        // 更新当前前缀和出现的次数  
        if (prefixSum >= 0 && prefixSum < 20001) { // 确保不会越界  
            prefixSumCounts[prefixSum]++;  
        }  
    }  
    return count;  
}
int main(void)
{
	SqList L;  
	LISTS lists;
	lists.length = 0;
	lists.listsize = 10;
	L.elem = NULL;
	L.listsize = LIST_INIT_SIZE;
	L.length = 0;
	int op = 1;
	int i;
	int e;
	int x;
	int state;
	char name[100];
	while (op)
	{
		system("cls");
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. InitList       10. ListInsert\n");
		printf("    	  2. DestroyList    11. ListDelete\n");
		printf("    	  3. ClearList      12. ListTrabverse\n");
		printf("    	  4. ListEmpty      13.SaveList\n");
		printf("    	  5. ListLength     14.LoadList\n");
		printf("    	  6. GetElem        15.AddList\n");
		printf("          7. LocateElem     16.RemoveList\n");
		printf("          8. PriorElem      17.LocateList\n");
		printf("          9. NextElem       18.SortList\n");
		printf("    	  19.MaxSubarray    20.SubarrayK\n");
		printf("          0.exit");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~20]:\n");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			state = InitList(L);
			if (state == INFEASIBLE)
			{
				printf("线性表创建失败。");
			}
			else
			{
				printf("线性表创建成功。");
			}
			break;
		case 2:
			state = DestroyList(L);
			if (state == OK)
			{
				printf("销毁成功");
			}
			else
			{
				printf("线性表不存在。");
			}
			break;
		case 3:
			state = ClearList(L);
			if (state == -1)
			{
				printf("线性表不存在。\n");
			}
			else
			{
				printf("删除成功。\n");
			}
			break;
		case 4:
			if (ListEmpty(L) == TRUE)
			{
				printf("线性表是空的。\n");
			}
			else if (ListEmpty(L) == INFEASIBLE)
			{
				printf("线性表不存在。\n");
			}
			else
			{
				printf("线性表不是空的。\n");
			}
			break;
		case 5:
			state = ListLength(L);
			if (state == INFEASIBLE)
			{
				printf("线性表不存在。\n");
			}
			else
			{
				printf("线性表的长度为:%d\n", state);
			}
			break;
		case 6:
			if (L.elem == NULL)
			{
				printf("线性表不存在。\n");
				break;
			}
			printf("请输入你想获取元素的序号：");
			scanf("%d", &i);
			state = GetElem(L, i, e);
			if (state == -1)
			{
				printf("线性表不存在。\n");
			}
			else if (state == 0)
			{
				
				printf("%d不合法。\n", i);
			}
			else
			{
				printf("序号为%d的元素为：%d。\n", i, e);
			}

			break;
		case 7:
			if (L.elem == NULL)
			{
				printf("线性表不存在。\n");
				break;
			}
			printf("请输入你想查找的元素：\n");
			scanf("%d", &e);
			state = LocateElem(L, e);
			if (state == -1)
			{
				printf("线性表不存在。\n");
			}
			if (state == 0)
			{
				printf("元素%d不存在。\n", e);
			}
			if (state != 0 && state != -1)
			{
				printf("%d的序号为%d。\n", e, state);
			}
			break;
		case 8:
			if (L.elem == NULL)
			{
				printf("线性表不存在。\n");
				break;
			}
			printf("请输入目标元素：\n");
			scanf("%d", &e);
			state = PriorElem(L, e, x);
			if (state == INFEASIBLE)
			{
				printf("线性表不存在。\n");
			}
			else if (state)
			{
				
				printf("%d的前驱元素为%d。\n", e, x);
			}
			else
			{
				if (LocateElem(L, e) == 0)
				{
					printf("%d不存在。", e);
					break;
				}
				printf("%d无前驱元素\n", e);
			}
			break;
		case 9:
			if (L.elem == NULL)
			{
				printf("线性表不存在。\n");
				break;
			}
			printf("请输入你想获得后继元素的元素：");
			scanf("%d", &e);
			state = NextElem(L, e, x);
			if (state == INFEASIBLE)
			{
				printf("线性表不存在。\n");
			}
			else if (state)
			{
				printf("%d的后继元素为：%d\n", e, x);
			}
			else
			{
				if (LocateElem(L, e) == 0)
				{
					printf("%d不存在。\n", e);
					break;
				}
				printf("%d无后继元素。 \n", e);
			}
			break;
		case 10:
			if (L.elem == NULL)
			{
				printf("线性表不存在。\n");
				break;
			}
			printf("请输入你想插入的序号和元素：\n");
			scanf("%d %d", &i, &e);
			state = ListInsert(L, i, e);
			if (state == -1)
			{
				printf("线性表不存在。\n");
			}
			else if (state)
			{
				printf("插入成功。\n");
			}
			else
			{
				printf("输入的序号无效。\n");
			}
			break;
		case 11:
			if (L.elem == NULL)
			{
				printf("线性表不存在。\n");
				break;
			}
			printf("请输入你想删除元素的序号：");
			scanf("%d", &i);
			state = ListDelete(L, i, e);
			if (state == INFEASIBLE)
			{
				printf("线性表不存在。\n");
			}
			else if (state)
			{
				printf("已成功删除元素%d。\n", e);
			}
			else
			{
				printf("输入的序号无效。\n");
			}
			break;
		case 12:
			if (L.elem == NULL)
			{
				printf("线性表不存在。\n");
				break;
			}
			ListTrabverse(L);
			break;
		case 13:
			state = SaveList(L, "C:\\Users\\LENOVO\\Desktop\\edcoder.txt");
			if (state == -1)
			{
				printf("线性表不存在。\n");
			}
			else
			{
				printf("保存完成。\n");
			}
			break;
		case 14:
			state = LoadList(L, "C:\\Users\\LENOVO\\Desktop\\edcoder.txt");
			if (state == -1)
			{
				printf("线性表已存在，无法读入。\n");
			}
			else
			{
				printf("已成功读入。\n");
			}
			break;
		case 15:
			printf("请输入要添加线性表的名称：");
			scanf("%s", name, 100);
			state = AddList(lists, name);
			if (state == 1)
			{
				printf("线性表添加成功.");
			}
			else
			{
				printf("添加失败。");
			}
			break;
		case 16:
			printf("请输入要移除线性表的名称：");
			scanf("%s", name, 100);
			state = RemoveList(lists, name);
			if (state == 1)
			{
				printf("移除成功。");
			}
			else
			{
				printf("移除失败");
			}
			break;
		case 17:
			printf("请输入要查找线性表的名称：");
			scanf("%s", name);
			state = LocateList(lists, name);
			if (state == 0)
			{
				printf("该线性表不存在。");
			}
			else
			{
				printf("该线性表的序号为：%d", state);
			}
			break;
		case 18:
			sort_list(L);
			printf("排序成功");
			break;
		case 19:
			state=max_sub_array(L);
			printf("最大的连续子数组和为%d",state);
			break;
		case 20:
			int K;
			printf("请输入K的值:");
			scanf("%d",&K);
		    printf("连续子数组和为%d的个数为%d",K,SubarrayK(K,L));
			break;
		case 0:
			break;

		}
		Sleep(1000);
	}
	return 0;
}