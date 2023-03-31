/* 图_有向图_十字链表的实现 */

/*
	G(V,E)
	 - V(G)		顶点表
	 - E(G)		边表
	 - 十字链表（邻接表，逆向邻接表)
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdbool.h>
#include "40_图_有向图_十字链表的实现.h"




static void BFS(CLGraph* clgp, int vexInd, BVisited* breadthVisited);
static void depthFirstSearch(CLGraph* clgp, int vexInd);
static void breadthFirstSearch(CLGraph* clgp, int vexInd);
static int  vertexInedgeNumber(CLGraph* clgp, int vexInd);
static int  vertexOutedgeNumber(CLGraph* clgp, int vexInd);
static void MinimumSpanTree_Prim(CLGraph* clgp, int vexInd);
static void MinimumSpanTree_Kruskal(CLGraph* clgp);
static void printVexEdgeSet(CLGraph* clgp);


static void minHeapInsert(MinHeap* minHeap, KEdge* edge);
static KEdge* getWeightMinEdge(MinHeap* minHeap);
static void printMinHeapEdgeArr(MinHeap* minHeap);

static void shortPathDijkstra(CLGraph* clgp, int startVexInd, int endVexInd);
static void shortPathFloyd(int(*vexRelaArr)[VexRelaArrNum]);


static void numInDegree(CLGraph* clgp, TopologicalTool* topologicalTool);
static bool topological_sort(CLGraph* clgp);



static InEdge* createInEdge(EdgeType weight, int rearInd)
{
	InEdge* newInEdge = NULL;
	newInEdge = (InEdge*)malloc(sizeof(InEdge));
	assert(newInEdge != NULL);
	newInEdge->inWeight = weight;
	newInEdge->inVexInd = rearInd;
	newInEdge->next = NULL;
	return newInEdge;
}

static OutEdge* createOutEdge(EdgeType weight, int frontInd)
{
	OutEdge* newOutEdge = NULL;
	newOutEdge = (OutEdge*)malloc(sizeof(OutEdge));
	assert(newOutEdge != NULL);
	newOutEdge->outWeight = weight;
	newOutEdge->outToVexInd = frontInd;
	newOutEdge->next = NULL;
	return newOutEdge;
}

static EdgeNode* createEdgeNode()
{
	EdgeNode* newEdgeNode = NULL;
	newEdgeNode = (EdgeNode*)malloc(sizeof(EdgeNode));
	assert(newEdgeNode != NULL);
	newEdgeNode->inEdgeSet = NULL;
	newEdgeNode->outEdgeSet = NULL;
	return  newEdgeNode;
}

static VertexNode* createVertexNode(VertexType data)
{
	VertexNode* newVertexNode = NULL;
	newVertexNode = (VertexNode*)malloc(sizeof(VertexNode));
	assert(newVertexNode != NULL);
	newVertexNode->data = data;
	newVertexNode->vexEdgeSet = NULL;
	return newVertexNode;
}

static DVisited* createDepthVisited(int arrLen)
{
	int visitedSize;
	DVisited* newDepthVisited = NULL;

	newDepthVisited = (DVisited*)malloc(sizeof(DVisited));
	assert(newDepthVisited != NULL);

	visitedSize = arrLen * sizeof(bool);
	newDepthVisited->depthVisited = (bool*)malloc(visitedSize);
	assert(newDepthVisited->depthVisited != NULL);
	
	memset(newDepthVisited->depthVisited, false, visitedSize);
	newDepthVisited->length = 0;

	return newDepthVisited;
}

static BVisited* createBreadthVisited(int arrLen)
{
	int visitedSize;
	BVisited* newBreadthVisited = NULL;

	newBreadthVisited = (BVisited*)malloc(sizeof(BVisited));
	assert(newBreadthVisited != NULL);

	visitedSize = arrLen * sizeof(bool);
	newBreadthVisited->breadthVisited = (bool*)malloc(visitedSize);
	assert(newBreadthVisited->breadthVisited != NULL);

	memset(newBreadthVisited->breadthVisited, false, visitedSize);
	newBreadthVisited->length = 0;

	return newBreadthVisited;
}


static Stack* createStack(int stackLen)
{
	int stackSize;
	Stack* newStack = NULL;

	newStack = (Stack*)malloc(sizeof(Stack));
	assert(newStack != NULL);

	stackSize = stackLen * sizeof(int);
	newStack->stack = (int*)malloc(stackSize);
	assert(newStack->stack != NULL);

	memset(newStack->stack, -1, stackSize);
	newStack->length = 0;

	return newStack;
}


static PrimTool* createPrimtool(int initNum)
{
	PrimTool* newPrimtool = NULL;
	
	newPrimtool = (PrimTool*)malloc(sizeof(PrimTool));
	assert(newPrimtool != NULL);
	/*遍历记录列表*/
	newPrimtool->vexVisited = (bool*)malloc(initNum * sizeof(bool));
	assert(newPrimtool->vexVisited != NULL);

	memset(newPrimtool->vexVisited, false, initNum * sizeof(bool));
	newPrimtool->length = 0;

	return newPrimtool;
}

static KEdge* createKEdge(int startVexInd, int endVexInd, int weight)
{
	KEdge* newKEdge = NULL;
	
	newKEdge = (KEdge*)malloc(sizeof(KEdge));
	assert(newKEdge != NULL);

	newKEdge->startVexInd = startVexInd;
	newKEdge->endVexInd = endVexInd;
	newKEdge->weight = weight;

	return newKEdge;
}


static KruskalTool* createKruskalTool(int vexNum, int arcNum)
{
	KruskalTool* newKruskaltool = NULL;
	
	newKruskaltool = (KruskalTool*)malloc(sizeof(KruskalTool));
	assert(newKruskaltool != NULL);

	newKruskaltool->edgearr = (KEdgeArr)malloc(arcNum * sizeof(KEdge*));
	assert(newKruskaltool->edgearr != NULL);
	memset(newKruskaltool->edgearr, 0, arcNum * sizeof(KEdge*));

	newKruskaltool->parent = (int*)malloc(vexNum * sizeof(int));
	assert(newKruskaltool->parent != NULL);
	for (int i = 0; i < vexNum; i++) newKruskaltool->parent[i] = i;

	newKruskaltool->length = 0;
	newKruskaltool->edgeSize = 0;

	return newKruskaltool;
}



static MinHeap* createMinHeap(int initNemNum)
{
	MinHeap* newminHeap = NULL;

	newminHeap = (MinHeap*)malloc(sizeof(MinHeap));
	assert(newminHeap != NULL);

	newminHeap->edgeArr = (KEdge**)malloc(initNemNum * sizeof(KEdge*));
	assert(newminHeap->edgeArr != NULL);

	memset(newminHeap->edgeArr, 0, initNemNum * sizeof(KEdge*));
	newminHeap->capacity = initNemNum;
	newminHeap->length = 0;

	newminHeap->getWeightMinEdge = getWeightMinEdge;
	newminHeap->minHeapInsert = minHeapInsert;
	newminHeap->printMinHeapEdgeArr = printMinHeapEdgeArr;

	return newminHeap;
}


static DijkstraTool* createDijkstraTool(int vexNum, int startVexInd, int endVexInd)
{
	DijkstraTool* newDijkstraTool = NULL;

	newDijkstraTool = (DijkstraTool*)malloc(sizeof(DijkstraTool));
	assert(newDijkstraTool != NULL);

	newDijkstraTool->distic = (int*)malloc(vexNum * sizeof(int));
	assert(newDijkstraTool->distic != NULL);

	newDijkstraTool->visited = (bool*)malloc(vexNum * sizeof(bool));
	assert(newDijkstraTool->visited != NULL);

	for (int i = 0; i < vexNum; i++)
	{
		newDijkstraTool->distic[i] = VexMaxDistance;
		newDijkstraTool->visited[i] = false;
	}

	newDijkstraTool->startVexInd = startVexInd;
	newDijkstraTool->endVexInd = endVexInd;
	newDijkstraTool->vlength = 0;

	return newDijkstraTool;

}



static TopologicalTool* createTopologicalTool(CLGraph* clgp)
{

	TopologicalTool* newTopologicalTool = NULL;

	newTopologicalTool = (TopologicalTool*)malloc(sizeof(TopologicalTool));
	assert(newTopologicalTool != NULL);

	newTopologicalTool->stack = (Stack*)createStack(clgp->vexNum);
	assert(newTopologicalTool->stack != NULL);

	newTopologicalTool->indgree = (int*)malloc(clgp->vexNum * sizeof(int));
	assert(newTopologicalTool->indgree != NULL);

	memset(newTopologicalTool->indgree, 0, clgp->vexNum * sizeof(int));
	newTopologicalTool->count = 0;

	/*初始化入度数据*/
	numInDegree(clgp, newTopologicalTool);

	return newTopologicalTool;
}



static void destroyDijkstraTool(DijkstraTool* dijkstraTool)
{
	if (dijkstraTool)
	{
		free(dijkstraTool->distic);
		free(dijkstraTool->visited);
		free(dijkstraTool);
		dijkstraTool = NULL;
	}
}

static void destroyKEdge(KEdge* kedge)
{
	if (kedge)
	{
		free(kedge);
		kedge = NULL;
	}
}

static void destroyMinHeap(MinHeap* minHeap)
{
	if (minHeap)
	{
		for (int i = 0; i < minHeap->length; i++) destroyKEdge(minHeap->edgeArr[i]);
		free(minHeap);
		minHeap = NULL;
	}

}

static void destroyKruskalTool(KruskalTool* kruskaltool)
{
	if (kruskaltool)
	{
		for (int i = 0; i < kruskaltool->edgeSize; i++) destroyKEdge(kruskaltool->edgearr[i]);
		free(kruskaltool->edgearr);
		free(kruskaltool->parent);
		free(kruskaltool);
		kruskaltool = NULL;
	}
}

static void destroyPrimtool(PrimTool* primTool)
{
	if (primTool)
	{
		free(primTool->vexVisited);
		free(primTool);
		primTool = NULL;
	}
}


static void destroyInEdge(InEdge* inedge)
{
	if (inedge)
	{
		destroyInEdge(inedge->next);
		free(inedge);
		inedge = NULL;
	}
}


static void destroyOutEdge(OutEdge* outedge)
{
	if (outedge)
	{
		destroyOutEdge(outedge->next);
		free(outedge);
		outedge = NULL;
	}
}


static void destroyEdgeNode(EdgeNode* destEdgeNode)
{
	if (destEdgeNode)
	{
		destroyInEdge(destEdgeNode->inEdgeSet);
		destroyOutEdge(destEdgeNode->outEdgeSet);
		free(destEdgeNode);
		destEdgeNode = NULL;
	}
}


static void destroyVertexNode(VertexNode* destVertexNode)
{
	if (destVertexNode)
	{
		destroyEdgeNode(destVertexNode->vexEdgeSet);
		free(destVertexNode);
		destVertexNode = NULL;
	}
}


static void destroyDepthVisited(DVisited* depthVisited)
{
	if (depthVisited)
	{
		free(depthVisited->depthVisited);
		free(depthVisited);
		depthVisited = NULL;
	}
}


static void destroyBreadthVisited(BVisited* breadthVisited)
{
	if (breadthVisited)
	{
		free(breadthVisited->breadthVisited);
		free(breadthVisited);
		breadthVisited = NULL;
	}
}


static void destroyStack(Stack* stack)
{
	if (stack)
	{
		free(stack->stack);
		free(stack);
		stack = NULL;
	}
}



static void destroyTopologicalTool(TopologicalTool* topologicalTool)
{
	if (topologicalTool)
	{
		destroyStack(topologicalTool->stack);
		free(topologicalTool->indgree);
		free(topologicalTool);

		topologicalTool = NULL;
	}
}



void destroyCrossGraph(CLGraph* clgp)
{
	if (clgp)
	{
		for (int i = 0; i < clgp->vexNum; i++) destroyVertexNode(clgp->crossList[i]);
	
		clgp->vexNum = 0;
		clgp->arcNum = 0;

		clgp->breadthFirstSearch = NULL;
		clgp->depthFirstSearch = NULL;

		clgp->printVexEdgeSet = NULL;
		clgp->MinimumSpanTree_Kruskal = NULL;
		clgp->MinimumSpanTree_Prim = NULL;

		clgp->shortPathDijkstra = NULL;
		clgp->shortPathFloyd = NULL;

		clgp->topological_sort = NULL;
		clgp->vertexInedgeNumber = NULL;
		clgp->vertexOutedgeNumber = NULL;
		clgp = NULL;
	}
}






static void swap(KEdge** edgearr, int parent, int child)
{
	KEdge* temp = edgearr[parent];
	edgearr[parent] = edgearr[child];
	edgearr[child] = temp;
}


static void minHeapUpSize(MinHeap* minHeap)
{
	int newSize;
	KEdge** temp;
	newSize = 2 * sizeof(minHeap->capacity* sizeof(KEdge*));

	temp = realloc(minHeap->edgeArr, newSize);
	assert(temp != NULL);
	minHeap->edgeArr = temp;
}


static void minHeapInsert(MinHeap* minHeap, KEdge* edge)
{
	if (minHeap->capacity == minHeap->length) minHeapUpSize(minHeap);

	minHeap->edgeArr[minHeap->length++] = edge;
	int arrInd = minHeap->length - 1;

	// 只有当minHeap维护的数组除了0以外的索引，子结点小于父节点时需要父子互换
	while (arrInd > 0 && minHeap->edgeArr[arrInd]->weight < minHeap->edgeArr[(arrInd - 1)/2]->weight)			
	{
		swap(minHeap->edgeArr, (arrInd - 1) / 2, arrInd);
		arrInd = (arrInd - 1) / 2;		// 可能新添加的元素比祖辈更小
	}
}


static void heapOrder(MinHeap* minHeap, int arrInd)
{
	/*由于本质上在初次加入堆中，已经将数组中的权重大致分好，再这里将最末尾的添加到首部，
	好处是，可以通过最少的判读获取数组中最小的值，并对其进行swap操作，第二此获取时同样的处理，
	会导致，第二小的会顺利的获取并以此类推
	*/
	int smallInd = arrInd;
	int leftChildInd = 2 * smallInd + 1;
	int rightChildInd = 2 * smallInd + 2;

	if (leftChildInd < minHeap->length && minHeap->edgeArr[leftChildInd]->weight < minHeap->edgeArr[smallInd]->weight) 
	{
		smallInd = leftChildInd;		// 打标记
	}
	if (rightChildInd < minHeap->length && minHeap->edgeArr[rightChildInd]->weight < minHeap->edgeArr[smallInd]->weight)
	{
		smallInd = rightChildInd;
	}
	if (smallInd != arrInd)		// 说明发生里变化，头部的不是最小值,移动一个结点，需要遍历
	{
		swap(minHeap->edgeArr, arrInd, smallInd);
		heapOrder(minHeap, smallInd);	// 继续
	}
}


static KEdge* getWeightMinEdge(MinHeap* minHeap)
{
	KEdge* temp;
	if (!minHeap->length) return NULL;

	temp = minHeap->edgeArr[0];
	minHeap->edgeArr[0] = minHeap->edgeArr[--minHeap->length];
	heapOrder(minHeap, 0);
	return temp;
}


static void printMinHeapEdgeArr(MinHeap* minHeap)
{
	for (int i = 0; i < minHeap->length; i++)
	{
		printf("%d (%d,%d,%d)\n", i, 
			minHeap->edgeArr[i]->startVexInd, 
			minHeap->edgeArr[i]->endVexInd, 
			minHeap->edgeArr[i]->weight
		);
	}

}


static int stackpush(Stack* stack, int vexInd)
{
	stack->stack[stack->length++] = vexInd;
	return vexInd;
}


static int stackpop(Stack* stack)
{
	int popInd;
	popInd = stack->stack[stack->length - 1];
	stack->stack[stack->length--] = -1;
	return popInd;
}


static bool stackIsEmtry(Stack* stack)
{
	return stack->length == 0;
}


static void initCrossLinkGraph(CLGraph* clgp, int vexNum)
{
	assert(vexNum > 0 && vexNum <= VexMaxNum);
	memset(clgp->crossList, 0, sizeof(clgp->crossList));
	clgp->vexNum = vexNum;
	clgp->arcNum = 0;
}


static void initCrossGraphCrossList(CLGraph* clgp, int *vexArr)
{
	VertexNode* vexNodeTemp;
	VertexType vexNodeData;
	for (int corsInd = 0; corsInd < clgp->vexNum; corsInd++)
	{
		vexNodeData = vexArr[corsInd];
		vexNodeTemp = createVertexNode(vexNodeData);
		/*将新建的顶点添加入corsslist中*/
		clgp->crossList[corsInd] = vexNodeTemp;
	}
}


static void initCrossGraphVexRela(CLGraph* clgp, int(*vexRelaArr)[VexRelaArrNum])
{
	VertexNode* cLvexTemp;
	VertexNode* cLvexADJ;
	EdgeNode* cLvexEdge;
	EdgeType weightIn;
	EdgeType weightOut;
	InEdge* inEdge;
	OutEdge* outEdge;
	/*
		{65535, 1,        3, 65535},	(in Number)
		{3,     65535,    3,	 2},
		{4,     1,    65535,	 4},
		{65535, 1,    65535, 65535},

		(Out Numver)
	*/

	for (int rearInd = 0; rearInd < clgp->vexNum; rearInd++)			// [0,1,2,3]
	{
		cLvexTemp = clgp->crossList[rearInd];
		for (int frontInd = 0; frontInd < clgp->vexNum; frontInd++)		// [0,1,2,3]
		{
			if (rearInd == frontInd) continue;
			weightIn = vexRelaArr[rearInd][frontInd];		// InEdge Weight(本身)
			weightOut = vexRelaArr[frontInd][rearInd];		// OutEdge Weight(邻接）

			cLvexADJ = clgp->crossList[rearInd];
			

			if ((weightIn < VexMaxDistance && weightIn >= VexMinDistance) && (weightOut < VexMaxDistance && weightOut >= VexMinDistance))
			{
				// 本身顶点与邻接顶点之间都存在相互联通的边时
				// cLvexTemp <-> cLvexADJ

				inEdge = createInEdge(weightIn, frontInd); 
				outEdge = createOutEdge(weightOut, frontInd); 

				if (cLvexTemp->vexEdgeSet)
				{
					inEdge->next = cLvexTemp->vexEdgeSet->inEdgeSet;		// 进边
					outEdge->next = cLvexTemp->vexEdgeSet->outEdgeSet;		// 出边
					cLvexTemp->vexEdgeSet->inEdgeSet = inEdge;
					cLvexTemp->vexEdgeSet->outEdgeSet = outEdge;

				}
				if (!cLvexTemp->vexEdgeSet)
				{
					cLvexEdge = createEdgeNode();
					cLvexEdge->inEdgeSet = inEdge;
					cLvexEdge->outEdgeSet = outEdge;
					cLvexTemp->vexEdgeSet = cLvexEdge;
				}

				clgp->arcNum++;
				clgp->arcNum++;
			}

			else if (weightIn < VexMaxDistance && weightIn >= VexMinDistance)
			{
				// cLvexTemp <- cLvexADJ
				inEdge = createInEdge(weightIn, frontInd); 
				if (cLvexTemp->vexEdgeSet) {
					inEdge->next = cLvexTemp->vexEdgeSet->inEdgeSet;		// 进边
					cLvexTemp->vexEdgeSet->inEdgeSet = inEdge;
				}

				if (!cLvexTemp->vexEdgeSet)
				{
					cLvexEdge = createEdgeNode();
					cLvexEdge->inEdgeSet = inEdge;
					cLvexTemp->vexEdgeSet = cLvexEdge;
				}

				clgp->arcNum++;
			}

			else if (weightOut < VexMaxDistance && weightOut >= VexMinDistance)
			{
				// cLvexTemp -> cLvexADJ
				outEdge = createOutEdge(weightOut, frontInd);
				if (cLvexTemp->vexEdgeSet) {
					outEdge->next = cLvexTemp->vexEdgeSet->outEdgeSet;		// 进边
					cLvexTemp->vexEdgeSet->outEdgeSet = outEdge;
				}

				if (!cLvexTemp->vexEdgeSet)
				{
					cLvexEdge = createEdgeNode();
					cLvexEdge->outEdgeSet = outEdge;
					cLvexTemp->vexEdgeSet = cLvexEdge;
				}

				clgp->arcNum++;
			}
		}
	}

	clgp->arcNum = clgp->arcNum / 2;
}


void CrossLinkGraphInit(CLGraph* clgp, int vexNum, VertexType vexArr[], VertexType (*vexRelaArr)[VexRelaArrNum])
{
	/*
		CLGraph* clgp：初始化的图
		int vexNum：初始化顶点数
		int (*vexArr)：初始化顶点列表
		int (*vexRelaArr)[VexRelaArrNum]：初始化顶点关系
	*/
	VertexType* vexArrTemp = vexArr;
	VertexType (*vexRelaArrTemp)[VexRelaArrNum] = vexRelaArr;

	/*初始化顶点数*/
	initCrossLinkGraph(clgp, vexNum);
	/*初始化顶点列表：将顶点创建并添加入crossList中*/
	initCrossGraphCrossList(clgp, vexArrTemp);
	/*初始化顶点之间的关系表*/
	initCrossGraphVexRela(clgp, vexRelaArrTemp);
	printf("clgp->vexNum:%d, clgp->arcNum:%d\n", clgp->vexNum, clgp->arcNum);


	clgp->depthFirstSearch		= depthFirstSearch;
	clgp->breadthFirstSearch	= breadthFirstSearch;
	clgp->vertexInedgeNumber	= vertexInedgeNumber;
	clgp->vertexOutedgeNumber	= vertexOutedgeNumber;
	clgp->printVexEdgeSet		= printVexEdgeSet;
	clgp->MinimumSpanTree_Prim  = MinimumSpanTree_Prim;
	clgp->MinimumSpanTree_Kruskal = MinimumSpanTree_Kruskal;
	clgp->shortPathDijkstra		= shortPathDijkstra;
	clgp->shortPathFloyd		= shortPathFloyd;
	clgp->topological_sort		= topological_sort;
}


static void printVexEdgeSet(CLGraph* clgp)
{
	VertexNode* tempVex;
	InEdge* inEdgeset;
	OutEdge* outEdgeset;
	for (int corsind = 0; corsind < clgp->vexNum; corsind++)
	{
		tempVex = clgp->crossList[corsind];
		if (!tempVex->vexEdgeSet) continue;
		inEdgeset = tempVex->vexEdgeSet->inEdgeSet;
		outEdgeset = tempVex->vexEdgeSet->outEdgeSet;
		printf("\n\n***************************************\n");
		while (inEdgeset)
		{
			printf("inVexInd:%d inWeight:%d\t", inEdgeset->inVexInd, inEdgeset->inWeight);
			inEdgeset = inEdgeset->next;
		}
		printf("\n");
		printf("\n");
		while (outEdgeset)
		{
			printf("outVexInd:%d outWeight:%d\t", outEdgeset->outToVexInd, outEdgeset->outWeight);
			outEdgeset = outEdgeset->next;
		}
		printf("\n***************************************\n\n");
	}
}



static int vertexInedgeNumber(CLGraph* clgp, int vexInd)
{
	EdgeNode* tempEdge;
	InEdge* tempIn;
	int inNumber = 0;

	assert(vexInd < clgp->vexNum && vexInd >= 0);
	tempEdge = clgp->crossList[vexInd]->vexEdgeSet;
	if (tempEdge == NULL) return inNumber;

	tempIn = tempEdge->inEdgeSet;
	while (tempIn)
	{
		tempIn = tempIn->next;
		inNumber++;
	}

	return inNumber;
}


static int vertexOutedgeNumber(CLGraph* clgp, int vexInd)
{
	EdgeNode* tempEdge;
	OutEdge* tempOut;
	int outNumber = 0;

	assert(vexInd < clgp->vexNum && vexInd >= 0);
	tempEdge = clgp->crossList[vexInd]->vexEdgeSet;
	if (tempEdge == NULL) return outNumber;

	tempOut = tempEdge->outEdgeSet;
	while (tempOut)
	{
		tempOut = tempOut->next;
		outNumber++;
	}

	return outNumber;
}


static void depthvisit(CLGraph* clgp, int vexInd, DVisited* depthvisited)
{
	printf("%d ", clgp->crossList[vexInd]->data);
	depthvisited->depthVisited[vexInd] = true;
	depthvisited->length++;
}


static void breadthvisit(CLGraph* clgp, int vexInd, BVisited* breadthvisited)
{
	printf("%d ", clgp->crossList[vexInd]->data);
	breadthvisited->breadthVisited[vexInd] = true;
	breadthvisited->length++;
}


static int depthNextNeighbor(CLGraph* clgp, int vexInd, DVisited* depthvisited, Stack* stack)
{
	EdgeNode* tempEdge;
	OutEdge*  tempOut;

	tempEdge = clgp->crossList[vexInd]->vexEdgeSet;
	tempOut = tempEdge->outEdgeSet;
	while (tempOut)
	{
		if (!depthvisited->depthVisited[tempOut->outToVexInd])
		{
			return stackpush(stack, tempOut->outToVexInd);
		}
		else
		{
			if (stack->length == clgp->vexNum -1) return -1;
			tempOut = tempOut->next;
		}
	}
	
	if (!tempOut && stack->length) depthNextNeighbor(clgp, stackpop(stack), depthvisited, stack);
	return -1;
}


static void DFS(CLGraph* clgp, int vexInd, DVisited* depthvisited, Stack* stack)
{
	int nextVexInd;

	if (vexInd == -1) return;
	if (!depthvisited->depthVisited[vexInd])
	{
		depthvisit(clgp, vexInd, depthvisited);
		nextVexInd = depthNextNeighbor(clgp, vexInd, depthvisited, stack);
		DFS(clgp, nextVexInd, depthvisited, stack);
	}
}


/*深度优先遍历算法（有向图，存在权重）十字链表*/
static void depthFirstSearch(CLGraph* clgp, int vexInd)
{
	/*
		{65535, 1,        3, 65535},	(in Number)
		{3,     65535,    3,	 2},
		{4,     1,    65535,	 4},
		{65535, 1,    65535, 65535},

		(Out Numver)

		1. 创建一个临时标记的队列对顶点访问进行统计
		2.创建一个类栈的功能体，对访问的顺序进行存储
		3.通过获取顶点的邻接顶点，反复获取，如果顶点的所有出边的顶点都被访问，则退回上一个顶点类此。
	*/

	DVisited* depthVisited =  createDepthVisited(clgp->vexNum);
	Stack* stack = createStack(clgp->vexNum);

	DFS(clgp, vexInd, depthVisited, stack);

	destroyDepthVisited(depthVisited);
	destroyStack(stack);
	printf("\n");

}


static void breadthNextNeighbor(CLGraph* clgp, int vexInd, BVisited* breadthVisited)
{
	/*访问vexInd顶点的下一层再次遍历层级*/
	EdgeNode* tempEdge;
	OutEdge*  tempOut;

	tempEdge = clgp->crossList[vexInd]->vexEdgeSet;
	tempOut = tempEdge->outEdgeSet;
	while (tempOut)
	{
		BFS(clgp, tempOut->outToVexInd, breadthVisited);
		tempOut = tempOut->next;
	}
	BFS(clgp, -1, breadthVisited);
}


static void BFS(CLGraph* clgp, int vexInd, BVisited* breadthVisited)
{
	if (vexInd == -1) return;	
	if (!breadthVisited->breadthVisited[vexInd])
	{
		breadthvisit(clgp, vexInd, breadthVisited);
		breadthNextNeighbor(clgp, vexInd, breadthVisited);		
	}
}


static void breadthFirstSearch(CLGraph* clgp, int vexInd)
{
	/*
		{65535, 1,        3, 65535},	(in Number)
		{3,     65535,    3,	 2},
		{4,     1,    65535,	 4},
		{65535, 1,    65535, 65535},

		(Out Numver)
	*/
	
	BVisited* breadthVisited = createBreadthVisited(clgp->vexNum);
	BFS(clgp, vexInd, breadthVisited);
	destroyBreadthVisited(breadthVisited);
	printf("\n");
}



static void mstPrimvisit(CLGraph* clgp, int* startVexInd, int* endVexInd, int* weight, PrimTool* primTool)
{
	primTool->length++;
	primTool->vexVisited[*endVexInd] = true;
	printf("(startVexInd:%d, endVexInd:%d, weight:%d)\n", *startVexInd, *endVexInd, *weight);
}


static void recordVexEdge(CLGraph* clgp, int* startVexInd, int* endVexInd, PrimTool* primTool, MinHeap* minHeap)
{
	OutEdge* tempOut;
	KEdge* newKedge = NULL;
	
	tempOut = clgp->crossList[*endVexInd]->vexEdgeSet->outEdgeSet;

	while (tempOut)
	{
		if (!primTool->vexVisited[tempOut->outToVexInd])
		{
			newKedge = createKEdge(*endVexInd, tempOut->outToVexInd, tempOut->outWeight);
			minHeap->minHeapInsert(minHeap, newKedge);
			newKedge = NULL;
		}
		tempOut = tempOut->next;
	}
}


static void getNextEdge(CLGraph* clgp, int* startVexInd, int* endVexInd, int *weight, PrimTool* primTool, MinHeap* minHeap)
{
	/*找到已经遍历过的顶点中未遍历的边中的权重最小的边的对应邻接顶点： endVexInd*/
	KEdge*	newKedge = NULL;
	newKedge = minHeap->getWeightMinEdge(minHeap);
	*startVexInd = newKedge->startVexInd;
	*endVexInd = newKedge->endVexInd;
	*weight = newKedge->weight;	
}


static void MSTPrim(CLGraph* clgp, int* startVexInd, int* endVexInd, int* weight, PrimTool* primTool, MinHeap* minHeap)
{
	if (primTool->length == clgp->vexNum) return;
	mstPrimvisit(clgp, startVexInd, endVexInd, weight, primTool);
	recordVexEdge(clgp, startVexInd, endVexInd, primTool, minHeap);
	getNextEdge(clgp, startVexInd, endVexInd, weight, primTool, minHeap);
	MSTPrim(clgp, startVexInd, endVexInd, weight, primTool, minHeap);
}



static void MinimumSpanTree_Prim(CLGraph* clgp, int vexInd)
{
	/*
		Prim 算法是基于贪心算法，将图的顶点作为一个集合（vexArr），将访问过的顶点从集合中移动到另一个集合中(visit vexArr)，
		每次获取下一条边时，是通过找已经遍历过的顶点的所有临边（排除已经访问过的）剩下的中挑选权重最小的边，添加到minTree中，并更新（visit vexArr）
		
		总顶点数：clgp->vexNum
			- 使用 createPrimtool 创建：
				- 总集： vexvist[clgp->vexNum]	
				- 遍历过的集： vexvisit[...] = true 的集合
			- 判断 是否遍历完成：
				- 使用： clgp->vexNum =?= Primtool->length ;
	*/

	int endVexInd = 0, weight = 0;
	PrimTool* primTool = createPrimtool(clgp->vexNum);
	MinHeap* minHeap = createMinHeap(clgp->arcNum);

	MSTPrim(clgp, &vexInd, &endVexInd, &weight, primTool, minHeap);
	destroyPrimtool(primTool);
	destroyMinHeap(minHeap);
}





static bool hasKEdge(KruskalTool* kruskalTool, int startVexInd, int endVexInd, int weight)
{
	if (!kruskalTool->edgearr[0]) return false;
	for (int i = 0; i < kruskalTool->edgeSize; i++)
	{
		if (
			kruskalTool->edgearr[i]->startVexInd == startVexInd && 
			kruskalTool->edgearr[i]->endVexInd == endVexInd && 
			kruskalTool->edgearr[i]->weight == weight
			) return true;
	}
	return false;
}


static void createEdgeArr(CLGraph* clgp, KruskalTool* kruskalTool)
{
	EdgeNode* tempEdge;
	InEdge*		tempIn;
	OutEdge*   tempOut;
	KEdge*   tempkedge;

	for (int vexInd = 0; vexInd < clgp->vexNum; vexInd++)
	{
		tempEdge = clgp->crossList[vexInd]->vexEdgeSet;
		if (tempEdge)
		{
			tempIn = tempEdge->inEdgeSet;
			tempOut = tempEdge->outEdgeSet;

			while (tempIn)
			{
				if (!hasKEdge(kruskalTool, tempIn->inVexInd, vexInd, tempIn->inWeight))
				{
					tempkedge = createKEdge(tempIn->inVexInd, vexInd, tempIn->inWeight);
					kruskalTool->edgearr[kruskalTool->edgeSize++] = tempkedge;
				}
				tempIn = tempIn->next;
			}
			while (tempOut)
			{
				if (!hasKEdge(kruskalTool, vexInd, tempOut->outToVexInd, tempOut->outWeight))
				{
					tempkedge = createKEdge(vexInd, tempOut->outToVexInd, tempOut->outWeight);
					kruskalTool->edgearr[kruskalTool->edgeSize++] = tempkedge;
				}
				tempOut = tempOut->next;
			}
		}
	}
}



static int cmp(const void* ea, const void* eb)
{
	return (*(KEdge**)ea)->weight - (*(KEdge**)eb)->weight;
}


static int find(int parent[], int vexInd)
{
	if (parent[vexInd] != vexInd)							// 相等表示顶点没有被访问过
	{
		parent[vexInd] = find(parent, parent[vexInd]);		// 被访问过测试是否成环
	}
	return parent[vexInd];
}


static void merge(int startVexInd, int endVexInd, int parent[]) 
{
	parent[find(parent, startVexInd)] = find(parent, endVexInd);		// 更新标记，将尾顶点的下标更新到对应的下标
}


static void printsort(KruskalTool* kruskaltool)
{
	for (int i = 0; i < kruskaltool->edgeSize; i++)
	{
		printf(
			"%d (%d %d %d)\n", i, 
			kruskaltool->edgearr[i]->startVexInd, 
			kruskaltool->edgearr[i]->endVexInd, 
			kruskaltool->edgearr[i]->weight
		);
	}
}


static void MSTKruskal(CLGraph* clgp, KruskalTool* kruskaltool)
{
	int startVexInd;
	int endVexInd;
	int weight;

	for (int arcInd = 0; arcInd < kruskaltool->edgeSize; arcInd++)
	{
		startVexInd = kruskaltool->edgearr[arcInd]->startVexInd;
		endVexInd = kruskaltool->edgearr[arcInd]->endVexInd;
		weight = kruskaltool->edgearr[arcInd]->weight;

		if (find(kruskaltool->parent, startVexInd) != find(kruskaltool->parent, endVexInd))
		{
			merge(startVexInd, endVexInd, kruskaltool->parent);
			printf("%d (%d %d %d)\n", arcInd, startVexInd, endVexInd, weight);
			kruskaltool->length++;

		}
		if (kruskaltool->length == kruskaltool->edgeSize - 1) break;
	}
}


static void MinimumSpanTree_Kruskal(CLGraph* clgp)
{
	/*
		Kruskal算法是一种用于解决最小生成树问题的贪心算法。
		其基本思想是将图中的所有边按照权值从小到大排序，然后依次加入到生成树中，直到生成树中包含了所有的节点为止。
		具体来说，Kruskal算法的步骤如下：
		将图中的所有边按照权值从小到大排序。
		依次遍历所有的边，如果当前边的两个端点在生成树中不在同一个连通分量中，那么将这条边加入到生成树中。
		重复步骤2，直到生成树中包含了所有的节点。
		Kruskal算法的时间复杂度为O(ElogE)，其中E为边的数量。该算法的主要优点是简单、易于实现，并且能够保证得到最小生成树。
		需要注意的是，Kruskal算法并不适用于存在负权边的图，因为在这种情况下，
		排序后的边集合可能存在环路，导致算法无法正确地得到最小生成树。
	*/

	KruskalTool* kruskalTool = createKruskalTool(clgp->vexNum, clgp->arcNum);
	createEdgeArr(clgp, kruskalTool);
	qsort(kruskalTool->edgearr, kruskalTool->edgeSize, sizeof(KEdge*), cmp);
	// printsort(kruskalTool);
	printf("startKruskal:\n");
	MSTKruskal(clgp, kruskalTool);
}



static void printDistic(CLGraph* clgp, DijkstraTool* dijkstraTool)
{
	for (int i = 0; i < clgp->vexNum; i++)
	{
		printf("%d (%d)\n", i, dijkstraTool->distic[i]);
	}
}


static void updateVisited(DijkstraTool* dijkstraTool, int visitedInd)
{
	dijkstraTool->visited[visitedInd] = true;
	dijkstraTool->vlength++;
}


static void updateDistic(DijkstraTool* dijkstraTool, int disticInd, int minWeight)
{
	dijkstraTool->distic[disticInd] = minWeight;
}


static void initDijkstraTool(CLGraph* clgp, DijkstraTool* dijkstraTool, int* MinInd)
{
	EdgeNode* tempEdge;
	OutEdge* tempOut;
	int minInd = -1, minWeight = VexMaxDistance;

	updateVisited(dijkstraTool, 0);
	updateDistic(dijkstraTool, 0, 0);
	tempEdge = clgp->crossList[dijkstraTool->startVexInd]->vexEdgeSet;
	tempOut = tempEdge->outEdgeSet;

	while (tempOut)
	{
		if (!dijkstraTool->visited[tempOut->outToVexInd])
		{
			if (tempOut->outWeight < minWeight)
			{
				minWeight = tempOut->outWeight;
				minInd = tempOut->outToVexInd;
			}
			dijkstraTool->distic[tempOut->outToVexInd] = tempOut->outWeight;
		}
		tempOut = tempOut->next;
	}

	updateVisited(dijkstraTool, minInd);
	updateDistic(dijkstraTool, minInd, minWeight);

	*MinInd = minInd;
}


static int getNextMinVex(CLGraph* clgp, DijkstraTool* dijkstraTool, int minInd, int minWeight)
{
	bool tempBool;

	for (int i = 0; i < clgp->vexNum; i++)
	{
		tempBool = dijkstraTool->visited[i];
		if (!tempBool && dijkstraTool->distic[i] < minWeight) minInd = i;
	}

	return minInd;
}


static void SPD(CLGraph* clgp, DijkstraTool* dijkstraTool, int* MinInd)
{
	EdgeNode* tempEdge;
	OutEdge* tempOut;
	int disticWeight, newDistWeight;
	bool hasVisit;
	int minInd = -1, minWeight = VexMaxDistance;

	tempEdge = clgp->crossList[*MinInd]->vexEdgeSet;
	tempOut = tempEdge->outEdgeSet;

	while (tempOut)
	{
		hasVisit = dijkstraTool->visited[tempOut->outToVexInd];
		disticWeight = dijkstraTool->distic[tempOut->outToVexInd];
		newDistWeight = dijkstraTool->distic[*MinInd] + tempOut->outWeight;

		if (!hasVisit && newDistWeight < disticWeight)
		{
			dijkstraTool->distic[tempOut->outToVexInd] = newDistWeight;
		}
		tempOut = tempOut->next;
	}

	updateVisited(dijkstraTool, minInd);
	updateDistic(dijkstraTool, minInd, minWeight);
	*MinInd = getNextMinVex(clgp, dijkstraTool, minInd, minWeight);

	printDistic(clgp, dijkstraTool);
	printf("MinInd:%d, weight:%d\n", *MinInd, dijkstraTool->distic[*MinInd]);
}


static void shortPathDijkstra(CLGraph* clgp, int startVexInd, int endVexInd)
{

	/*
	Dijkstra算法是一种用于计算带权图中单源最短路径的算法，
	其基本思想是从给定的起始点开始，依次计算该点到所有其他点的最短路径，并将结果保存在一个距离数组中。
	
	具体实现过程如下：
		初始化：将起始点的距离设为0，将其他点的距离设为无穷大。
		选择当前距离最小的点作为下一个处理点，并将其标记为已访问。
		对于当前处理点，遍历所有与其相邻的点，更新它们的距离值，如果发现新的最短距离，则将其加入到一个优先队列中。
		重复步骤2和3，直到所有点都被访问或者所有距离都已经被计算出来。
		最终得到的距离数组即为从起始点到每个点的最短路径长度。
	Dijkstra算法的时间复杂度为O(E+VlogV)，其中E为边数，V为顶点数。它使用了贪心策略，
	每次都选择当前距离最小的点进行扩展，因此可以保证得到的路径是最短的。
	*/


	int MinInd = -1;
	DijkstraTool* dijkstraTool = createDijkstraTool(clgp->vexNum, startVexInd, endVexInd);
	initDijkstraTool(clgp, dijkstraTool, &MinInd);

	printDistic(clgp, dijkstraTool);
	printf("MinInd:%d, weight:%d\n", MinInd, dijkstraTool->distic[MinInd]);
	SPD(clgp, dijkstraTool, &MinInd);
	// destroyDijkstraTool(dijkstraTool);
}



static void shortPathFloyd(int (*vexRelaArr)[VexRelaArrNum])
{
	/*
		Floyd算法，也称为插点法，是一种用于寻找图中所有最短路径的算法。
		它可以处理有向图或无向图，并且可以处理其中存在负权边的情况。
		Floyd算法的时间复杂度为O(n^3)，在处理小规模图时非常高效。

		Floyd算法的实现原理如下：
		初始化：构建一个n × n的矩阵D，其中D[i][j]表示从节点i到节点j的最短路径长度。
		对于任意一个节点i，D[i][i] = 0，如果i和j之间有一条边，则D[i][j] = 边的权值，否则D[i][j] = INF。
		迭代更新：对于每一对节点i和j，如果存在一个节点k，使得从i到k再到j的路径长度比从i到j的路径长度更短，
		那么就更新D[i][j]的值为D[i][k] + D[k][j]。
		输出结果：当所有节点对的最短路径长度都计算出来后，矩阵D中的值就是图中所有节点对的最短路径长度。
	*/

	int min, row, col;
	int dist[VexRelaArrNum][VexRelaArrNum];
	int path[VexRelaArrNum][VexRelaArrNum];

	/*初始化顶点关系*/
	for (row = 0; row < VexRelaArrNum; row++) 
		for (col = 0; col < VexRelaArrNum; col++) 
			dist[row][col] = vexRelaArr[row][col];


	/*当有：[row][min]+ [min][col] < [row][col]时，更新路径*/
	for (int min = 0; min < VexRelaArrNum; min++) 
		for (int row = 0; row < VexRelaArrNum; row++) 
			for (int col = 0; col < VexRelaArrNum; col++)
				if (dist[row][col] > dist[row][min] + dist[min][col]) 
					dist[row][col] = dist[row][min] + dist[min][col];

	/*打印顶点关系*/
	printf("所有节点对的最短路径长度为：\n");
	for (int row = 0; row < VexRelaArrNum; row++)
	{
		for (int col = 0; col < VexRelaArrNum; col++)
		{
			if (dist[row][col] == VexMaxDistance) printf("INF\t");
			else printf("%d\t", dist[row][col]);
		}
		printf("\n");
	}

}



static void numInDegree(CLGraph* clgp, TopologicalTool* topologicalTool)
{
	InEdge* tempIn = NULL;
	EdgeNode* tempEdge = NULL;

	printf("\n\n");
	for (int vexInd = 0; vexInd < clgp->vexNum; vexInd++)
	{
		printf("\nstart:%d\n", vexInd);
		tempEdge = clgp->crossList[vexInd]->vexEdgeSet;
		if (tempEdge)
		{
			tempIn = tempEdge->inEdgeSet;
			while (tempIn)
			{
				printf("%d ", tempIn->inVexInd);
				topologicalTool->indgree[vexInd]++;
				tempIn = tempIn->next;
			}
		}
		printf("\ninnum:%d\n", topologicalTool->indgree[vexInd]);
	}
	printf("\n\n");
}



static void initIndegreeofZreo(CLGraph* clgp, TopologicalTool* topologicalTool)
{
	for (int vexInd = 0; vexInd < clgp->vexNum; vexInd++)
	{
		if (topologicalTool->indgree[vexInd] == 0) stackpush(topologicalTool->stack, vexInd);
	}
}


static void indegreeReduce(CLGraph* clgp, TopologicalTool* topologicalTool)
{
	for (int vexInd = 0; vexInd < clgp->vexNum; vexInd++)
	{
		if (!--topologicalTool->indgree[vexInd]) stackpush(topologicalTool->stack, vexInd);
	}
}


static bool TPS(CLGraph* clgp, TopologicalTool* topologicalTool)
{
	int vexInd = -1;
	int vexData = -1;

	//栈不空，则存在入度为0的顶点
	printf("\n####<<topologicalTool start>>#####\n");
	while (!stackIsEmtry(topologicalTool->stack)) 
	{	
		vexInd = stackpop(topologicalTool->stack);
		vexData = clgp->crossList[vexInd]->data;
		topologicalTool->count++;
		printf("%d ", vexData);

		//将所有i指向的顶点的入度减1，并且将入度减为0的顶点压入栈S
		indegreeReduce(clgp, topologicalTool);
	}
	printf("\n#####<<topologicalTool end>>######\n");

	if (topologicalTool->count < clgp->vexNum) return false;
	else return true;
}


static bool topological_sort(CLGraph* clgp)
{
	/*
	拓扑排序是一种对有向无环图（DAG）进行排序的算法。
	该算法将图中所有节点按照一定的次序排列，使得任何一条边的起点在排列中都排在终点的前面。

		具体的实现方法是:使用一个队列(stack)和一个计数器(count)。
		- 首先，将所有入度为0的节点加入队列中。
		- 然后，每次从队列中取出一个节点，将其所有相邻节点的入度减1。
		- 如果某个节点的入度减到0，则将其加入队列中。当队列为空时，所有节点的顺序就确定了。

	拓扑排序可以用于解决诸如任务调度、依赖分析等问题。如果图中存在环，则无法进行拓扑排序。
	
	int relaArr[4][4] = {
		{inf,  1,   3, inf},	// OUT	row
		{3,  inf,   3,	 2},
		{4,    1, inf,   4},
		{inf,  1, inf, inf},
	};
		//IN  col
	*/

	TopologicalTool* topologicalTool = createTopologicalTool(clgp);
	initIndegreeofZreo(clgp, topologicalTool);
	bool flag = TPS(clgp, topologicalTool);
	destroyTopologicalTool(topologicalTool);
	return flag;
}



static void criticalPath(CLGraph* clgp)
{
	/*
		关键路径：

	*/



}