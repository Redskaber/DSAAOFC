#pragma once

#ifndef __40_图_有向图_边集数组实现_H__
	#define __40_图_有向图_边集数组实现_H__

	/*
		有向图_边集数组
		G(V,E)
			- V(G)	顶点表
			- E(G)	边表
		- G(V,E) 
			顶点数组
			边数组
	*/

	typedef int EdgeType;
	typedef int VertexType;
	
	/*边集数组：边表*/
	typedef struct EdgeNode
	{
		EdgeType weight;		// 边的权重
		int begin;				// 边的起始
		int end;				// 边的终端
	}EdgeNode, *EdgeArr;

	/*边集数组：顶点表*/
	typedef struct VertexNode
	{
		VertexType data;		// 顶点的值
	}VertexNode, *VertexArr;

	/*边集数组：边集数组*/
	typedef struct EdgeSetGraph
	{
		EdgeArr edgearr;		// 边集
		VertexArr vertexarr;	// 顶点集
		int arcNum, vexNum;
	}ESGraph;

#endif // !__40_图_有向图_边集数组实现_H__

