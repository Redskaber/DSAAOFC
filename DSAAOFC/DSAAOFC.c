/*
	本项目是有关与C的数据结构与算法的学习。
		- 数据结构
			- 数据结构基础
				- 线性表
					- 顺序表
					- 链表
					- 队列	先进先出
					- 栈	先进后出
				- 有根树的表示
			- 字符串
				- 暴力匹配	(一个一个的匹配)

			- 非线性
				- 树
					- 无序树（自由树）
					- 有序树
						- 二叉树
							- 完全二叉树
							- 非完全二叉树
							- 线索二叉树
			- 图
				- 实现方法
					- 邻接矩阵(二维数组)    密图
					- 邻接表(数组+链表)		疏图
					- 十字链表(邻接表+逆向邻接表)	有向图
					- 邻接多重表(左右双顶点next双邻接链重表)	无向图中用于解决无向图的线（删除操作）
					- 边集数组(顶点数组+边数组)
				- 实现类型
					- 无向图
					- 有向图
						- 有向图不带权重
						- 有向图带权重
			- c实现c++中class的功能
		- 算法
*/

#include <stdio.h>
#include <stdlib.h>
// #include "01_static_seqlist_case.h"
// #include "02_seq_dynamic_case.h"
// #include "03_single_linker_case.h"
// #include "04_双向链表的Case.h"
// #include "05_queue的case.h"
// #include "05_链式队列的Case.h"
// #include "06_stack的case.h"
// #include "07_stack的链式case.h"
// #include "cRealizeCase.h"
// #include "10_二叉树的Case.h"
// #include "11_二叉树的Case.h"
#include "20_图_无向图_邻接矩阵Case.h"
// #include "30_图_无向图_邻接表Case.h"
// #include "40_图_有向图_十字链表Case.h"
// #include "40_图_有向图_邻接多重表Case.h"
// #include "40_图_有向图_边集数组Case.h"

int main()
{
	// start_static_linker();
	// start_dynamic_linker();
	// start_single_linker();
	// start_bidirectional_linker();
	// start_queue();
	// start_LinkQueue();
	// start_stack();
	// start_stack_of_link();
	// start_class_realize();
	// start_binary_tree_case();
	// start_binaryTree_case();
	start_undirectedGraph_case();
	// start_adjacencyTable_Graph_case();	
	// start_CrossLinke_list_case();
	// start_adjacency_multiple_Graph_case();
	// start_edgeSet_array_Graph_case();


	return 0;
}