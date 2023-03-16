#pragma once 


#ifndef __CREALIZECLASS_H__
	#define __CREALIZECLASS_H__


	typedef int ElemType;

	typedef void* inClass;


	typedef struct CLASS
	{
		inClass self;
		ElemType classSize;
		void (*printVal)(int val);
		int(*init)(inClass self,int number, ...);
	}class;

	extern int classInit(class* _class);


#endif // !__CREALIZECLASS_H__
