#pragma once


#ifndef __05_QUEUE_H__

	/*
		
		顺序队列
		-------------------------
		[]	[]	[]	[]	[]	[]	    队列
		-------------------------
		进 ->	队列	->出		（先进先出）

		维护:
			front*
			rear*
			maxSize

			[NULL] [NULL] [NULL] [NULL]

			push:
				front*  rear*
				[data] [NULL] [NULL] [NULL]

				front*		   rear*
				[data] [data] [NULL] [NULL]

			pop:
				front*		   rear*
				[data] [data] [NULL] [NULL]
					   front*  rear*
				[NULL] [data] [NULL] [NULL]

			rear* - front* = queue_size;

			if queue_size < maxsize;
	*/
	#define MaxSize 10
	#define InitMark 0
	typedef int Rstatus;
	typedef int ELemType;

	typedef struct STATICQUEUE
	{
		ELemType queue[MaxSize];	// 维护的队列
		int front;		// 前指针(由于使用的是数组构建)，所以直接使用数组下标作为记录反而封方便
		int rear;		// 后指针
		size_t length;	// 解决当队列front == rear 时，判断是空队列还是满队列时检测使用，方便处理， push +1， pop -1
	}SQueue;
	
	
	extern Rstatus staticQueueInit(SQueue* sq);
	extern Rstatus staticQueueRearPush(SQueue* sq, ELemType data);
	extern Rstatus staticQueueFrontPop(SQueue* sq);

	extern Rstatus staticQueuePrint(SQueue* sq);



#endif // !__05_QUEUE_H__
