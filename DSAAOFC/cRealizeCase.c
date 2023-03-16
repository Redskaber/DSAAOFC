#include<stdio.h>
#include<stdlib.h>
#include "cRealizeClass.h"

int start_class_realize()
{
	class _class;
	classInit(&_class);
	_class.printVal(_class.self);
	_class.init(_class.self, 3, 100, 200, 300);


	return 0;
}
