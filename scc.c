#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define WHITE 0
#define GRAY 1
#define BLACK 2

int node; 
int edge; 
struct edge {
	int tail, head, type;
};
typedef struct edge edgeType;
edgeType *edgeTab;
int *firstEdge; 

int *vertexStatus, *secondDFSrestarts;

int tailThenHead(const void* xin, const void* yin)

{
	int result;
	edgeType *x, *y;

	x = (edgeType*)xin;
	y = (edgeType*)yin;
	result = x->tail - y->tail;
	if (result != 0)
		return result;
	else
		return x->head - y->head;
}

void read_input_file()
{
	int a, b, i, j;

	printf("vertices, edges의 수를 입력하세요.:");
	scanf("%d, %d", &node, &edge);
	edgeTab = (edgeType*)malloc(edge*sizeof(edgeType));
	if (!edgeTab)
	{
		printf("edgeTab malloc failed %d\n", __LINE__);
		exit(0);
	}

	for (i = 0; i<edge; i++)
	{
		printf("a->b 면 a, b를 입력하세요.: ");
		scanf("%d, %d", &a, &b);
		if (a<0 || a >= node || b<0 || b >= node)
		{
			printf("Invalid input %d, %d at %d\n", a, b, __LINE__);
			exit(0);
		}
		edgeTab[i].tail = a;
		edgeTab[i].head = b;
	}

	qsort(edgeTab, edge, sizeof(edgeType), tailThenHead);

	j = 0;
	for (i = 1; i<edge; i++)
		if (edgeTab[j].tail == edgeTab[i].tail
			&& edgeTab[j].head == edgeTab[i].head)
			;
		else
		{
			j++;
			edgeTab[j].tail = edgeTab[i].tail;
			edgeTab[j].head = edgeTab[i].head;
		}
	edge = j + 1;

	firstEdge = (int*)malloc((node + 1)*sizeof(int));
	if (!firstEdge)
	{
		printf("malloc failed %dn", __LINE__);
		exit(0);
	}
	j = 0;
	for (i = 0; i<node; i++)
	{
		firstEdge[i] = j;
		for (;
		j<edge && edgeTab[j].tail == i;
			j++)
			;
	}
	firstEdge[node] = edge;
}

int finishIndex;

void DFSvisit(int u)
{
	int i, v;

	vertexStatus[u] = GRAY;

	for (i = firstEdge[u]; i<firstEdge[u + 1]; i++)
	{
		v = edgeTab[i].head;
		if (vertexStatus[v] == WHITE)
			DFSvisit(v);
	}
	vertexStatus[u] = BLACK;
	secondDFSrestarts[-finishIndex] = u;
}

void reverseEdges()
{
	int a, b, i, j;

	for (i = 0; i<edge; i++)
	{
		a = edgeTab[i].tail;
		b = edgeTab[i].head;
		edgeTab[i].tail = b;
		edgeTab[i].head = a;
	}

	
	qsort(edgeTab, edge, sizeof(edgeType), tailThenHead);

	
	if (!firstEdge)
	{
		printf("malloc failed %dn", __LINE__);
		exit(0);
	}
	j = 0;
	for (i = 0; i<node; i++)
	{
		firstEdge[i] = j;
		for (;
		j<edge && edgeTab[j].tail == i;
			j++)
			;
	}
	firstEdge[node] = edge;
}

void DFSvisit2(int u)
{
	int i, v;

	printf("%dn", u);
	vertexStatus[u] = GRAY;

	for (i = firstEdge[u]; i<firstEdge[u + 1]; i++)
	{
		v = edgeTab[i].head;
		if (vertexStatus[v] == WHITE)
			DFSvisit2(v);
	}
	vertexStatus[u] = BLACK;
}

int main()
{
	int u, i;
	int SCCcount = 0;

	read_input_file();

	vertexStatus = (int*)malloc(node*sizeof(int));
	secondDFSrestarts = (int*)malloc(node*sizeof(int));
	if (!vertexStatus || !secondDFSrestarts)
	{
		printf("malloc failed\n");
		exit(0);
	}
	
	for (u = 0; u<node; u++)
		vertexStatus[u] = WHITE;
	finishIndex = node;
	for (u = 0; u<node; u++)
		if (vertexStatus[u] == WHITE)
			DFSvisit(u);

	reverseEdges();


	for (u = 0; u<node; u++)
		vertexStatus[u] = WHITE;
	for (i = 0; i<node; i++)
		if (vertexStatus[secondDFSrestarts[i]] == WHITE)
		{
			SCCcount++;
			printf("Strongly Connected Component %d\n", SCCcount);
			DFSvisit2(secondDFSrestarts[i]);
		}

	free(edgeTab);
	free(firstEdge);
	free(vertexStatus);
	free(secondDFSrestarts);
	return 0;
}
