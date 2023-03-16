#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include "cRealizeClass.h"


void printVal( int val)
{
	printf("val:%d\n", val);
}


int init(inClass self,int number,...)
{
	va_list args;
	va_start(args, number);
	
	void* temp;
	int argsp[100] = {number,};

	for (int i=0; i< number;i++) 
	{
		temp = va_arg(args,void*);
		argsp[i + 1] = temp;
	}
	va_end(args);

	for (int i = 0; i < number; i++)
	{
		printf("%d\n", argsp[i+1]);
	}

	return 1;
}

int classInit(class* _class)
{
	_class->printVal = printVal;
	_class->classSize = sizeof(class);
	_class->self = _class;
	_class->init = init;
	return 1;
}




