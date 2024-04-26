#include"stdio.h"
#include"stdlib.h"
#include"iostream"
#include"string.h"

using namespace std;


#define _CRT_SECURE_NO_WARNINGS

#define MAXINT 100

typedef struct ArcNode {//�����ߵĽṹ��
	int data;
	struct ArcNode* next;
}ArcNode;

typedef struct VNode {//��������Ľṹ��
	int  ind, outd,data;
	char n;
	struct ArcNode* first;
	bool visit;
}VNode;

typedef struct Graph {//����ͼ�Ľṹ�壬�����ڽӱ�ʽ�洢
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
bool push(Stack &s,VNode x) {//��ջ
	if (s.top == MAXINT - 1)
	{
		return false;
	}
	else
	{
		s.data[++s.top] = x;
	}
}
VNode pop(Stack& s) {//��ջ
	return s.data[s.top--];
}

int locat(Graph* G, int data) {//��λ�±�
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
	printf("�������������е���������:");
	scanf("%d", &G->vnum);
	for (i = 0; i < G->vnum; i++) {
		G->list[i].first = NULL;
		int a = 0;
	}
	printf("������ȴ���������:");
	scanf("%d", &G->anum);
	for (i = 0; i < G->vnum; i++) {
		printf("�������%d������:",i+1);
		cin>>G->list[i].n;
		G->list[i].data = i + 1;
	}
	for (i = 0; i < G->anum; i++) {
		printf("������ȴ��е�������:");
		cin>>start;
		for (j = 0; j < G->vnum; j++) {
			if (G->list[j].data == start) {
				p = (ArcNode*)malloc(sizeof(ArcNode));
				p->next = NULL;
				printf("�����뱻�ȴ���������:");
				cin>>p->data;
				p->next = G->list[j].first;
				G->list[j].first = p;
			}
		}
	}
	return G;
}	
void GetInDegree(Graph *G) {//д�붥������
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
void GetOutDegree(Graph* G) {//д�붥��ĳ���
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
		printf("����Ŀ��������\n");
		printf("��������������Ϊ��");
		for (int i = 0; i < G->vnum; i++) {
			if (G->list[i].visit == false)
				printf("%c  ", G->list[i].n);
		}
	}
	else
		printf("����Ŀδ����\n");
	system("pause");
}
