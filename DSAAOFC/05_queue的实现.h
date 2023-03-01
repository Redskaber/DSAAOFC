#pragma once


#ifndef __05_QUEUE_H__

	/*
		
		˳�����
		-------------------------
		[]	[]	[]	[]	[]	[]	    ����
		-------------------------
		�� ->	����	->��		���Ƚ��ȳ���

		ά��:
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
		ELemType queue[MaxSize];	// ά���Ķ���
		int front;		// ǰָ��(����ʹ�õ������鹹��)������ֱ��ʹ�������±���Ϊ��¼�����ⷽ��
		int rear;		// ��ָ��
		size_t length;	// ���������front == rear ʱ���ж��ǿն��л���������ʱ���ʹ�ã����㴦�� push +1�� pop -1
	}SQueue;
	
	
	extern Rstatus staticQueueInit(SQueue* sq);
	extern Rstatus staticQueueRearPush(SQueue* sq, ELemType data);
	extern Rstatus staticQueueFrontPop(SQueue* sq);

	extern Rstatus staticQueuePrint(SQueue* sq);



#endif // !__05_QUEUE_H__
