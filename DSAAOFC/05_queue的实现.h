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
	#define MaxSize 20
	typedef int ELemType;

	typedef struct QUEUE
	{
		ELemType queue[MaxSize];
		ELemType* front;
		ELemType* rear;
		size_t length;
	}Queue;
	




#endif // !__05_QUEUE_H__
