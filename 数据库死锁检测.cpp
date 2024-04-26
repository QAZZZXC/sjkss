#include"stdio.h"
#include"stdlib.h"
#include"iostream"
#include"string.h"

using namespace std;


#define _CRT_SECURE_NO_WARNINGS

#define MAXINT 100

typedef struct ArcNode {//创建边的结构体
	int data;
	struct ArcNode* next;
}ArcNode;

typedef struct VNode {//创建顶点的结构体
	int  ind, outd,data;
	char n;
	struct ArcNode* first;
	bool visit;
}VNode;

typedef struct Graph {//创建图的结构体，采用邻接表方式存储
	VNode list[MAXINT];
	int vnum, anum;
}Graph;


typedef struct {
	VNode data[MAXINT];
	int top;
}Stack;


void initstack(Stack &s) {
	s.top = -1;
	return;
}

bool stackempty(Stack s) {
	if (s.top == -1)
		return true;
	else
		return false;
}
bool push(Stack &s,VNode x) {//入栈
	if (s.top == MAXINT - 1)
	{
		return false;
	}
	else
	{
		s.data[++s.top] = x;
	}
}
VNode pop(Stack& s) {//出栈
	return s.data[s.top--];
}

int locat(Graph* G, int data) {//定位下标
	int i;
	for (i = 0; i < G->vnum; i++) {
		if (G->list[i].data== data)
			return i;
	}
	return -1;
}

Graph* creatGraph() {
	int i, j;
	int start;
	Graph* G = (Graph*)malloc(sizeof(Graph));
	ArcNode* p;
	printf("请输入正在运行的事务数量:");
	scanf("%d", &G->vnum);
	for (i = 0; i < G->vnum; i++) {
		G->list[i].first = NULL;
		int a = 0;
	}
	printf("请输入等待事项数量:");
	scanf("%d", &G->anum);
	for (i = 0; i < G->vnum; i++) {
		printf("请输入第%d项事务:",i+1);
		cin>>G->list[i].n;
		G->list[i].data = i + 1;
	}
	for (i = 0; i < G->anum; i++) {
		printf("请输入等待中的事务编号:");
		cin>>start;
		for (j = 0; j < G->vnum; j++) {
			if (G->list[j].data == start) {
				p = (ArcNode*)malloc(sizeof(ArcNode));
				p->next = NULL;
				printf("请输入被等待的事务编号:");
				cin>>p->data;
				p->next = G->list[j].first;
				G->list[j].first = p;
			}
		}
	}
	return G;
}	
void GetInDegree(Graph *G) {//写入顶点的入度
	ArcNode* p;
	for (int i = 0; i < G->vnum; i++) {
		G->list[i].ind = 0;
	}
	for (int i = 0; i < G->vnum; i++) {
		p = G->list[i].first;
		while (p) {
			G->list[locat(G, p->data)].ind++;
			p = p->next;
		}
	}
}
void GetOutDegree(Graph* G) {//写入顶点的出度
	ArcNode* p;
	for (int i = 0; i < G->vnum; i++) {
		G->list[i].outd = 0;
	}
	for (int i = 0; i < G->vnum; i++) {
		p = G->list[i].first;
		while (p) {
			G->list[i].outd++;
			p = p->next;
		}
	}
}
void main() {
	int i = 0;
	int num=0;
	Stack s;
	VNode v;
	ArcNode* e;
	Graph* G = creatGraph();
	for (i = 0; i < G->vnum; i++) {
		G->list[i].visit = false;
	}
	initstack(s);
	GetInDegree(G);
	GetOutDegree(G);
	for (i = 0; i < G->vnum; i++) {
		if (G->list[i].ind == 0 || G->list[i].outd == 0) {
			push(s, G->list[i]);
			G->list[i].visit = true;
		}
	}
	while (!stackempty(s)) {
		v = pop(s);
		num++;
		for (e = v.first; e; e = e->next) {
			G->list[locat(G, e->data)].ind--;
		}
		for (i = 0; i < G->vnum; i++) {
			for (e = G->list[i].first; e; e = e->next) {
				if (e->data == v.data) {
					G->list[i].outd--;
				}
			}
		}
		for (int x = 0; x < G->vnum; x++) {
			if ((G->list[x].ind == 0 || G->list[x].outd == 0) && G->list[x].visit == false) {
				push(s, G->list[x]);
				G->list[x].visit = true;
			}
		}
	}
	if (num < G->vnum) {
		printf("该项目存在死锁\n");
		printf("存在死锁的事务为：");
		for (int i = 0; i < G->vnum; i++) {
			if (G->list[i].visit == false)
				printf("%c  ", G->list[i].n);
		}
	}
	else
		printf("该项目未死锁\n");
	system("pause");
}
