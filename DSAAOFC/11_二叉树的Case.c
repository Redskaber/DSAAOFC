#include<stdio.h>
#include<stdlib.h>
#include "11_二叉树的实现.h"


int start_binaryTree_case() 
{
	LBinTree lbtree;
	BinTreeInit(&lbtree);
	lbtree.printBinTreeInfo(&lbtree);
	lbtree.push(&lbtree, 10); lbtree.printNodeInfo(&lbtree);
	lbtree.push(&lbtree, 20); lbtree.printNodeInfo(&lbtree);
	lbtree.push(&lbtree, 30); lbtree.printNodeInfo(&lbtree);
	lbtree.push(&lbtree, 40); lbtree.printNodeInfo(&lbtree);
	lbtree.push(&lbtree, 50); lbtree.printNodeInfo(&lbtree);
	lbtree.push(&lbtree, 60); lbtree.printNodeInfo(&lbtree);
	lbtree.push(&lbtree, 70); lbtree.printNodeInfo(&lbtree);
	lbtree.push(&lbtree, 80); lbtree.printNodeInfo(&lbtree);
	lbtree.push(&lbtree, 90); lbtree.printNodeInfo(&lbtree);
	lbtree.push(&lbtree, 100); lbtree.printNodeInfo(&lbtree);
	lbtree.push(&lbtree, 110); lbtree.printNodeInfo(&lbtree);
	lbtree.push(&lbtree, 120); lbtree.printNodeInfo(&lbtree);
	lbtree.push(&lbtree, 130); lbtree.printNodeInfo(&lbtree);
	lbtree.push(&lbtree, 140); lbtree.printNodeInfo(&lbtree);
	lbtree.push(&lbtree, 150); lbtree.printNodeInfo(&lbtree);
	lbtree.push(&lbtree, 160); lbtree.printNodeInfo(&lbtree);
	lbtree.push(&lbtree, 170); lbtree.printNodeInfo(&lbtree);
	lbtree.push(&lbtree, 180); lbtree.printNodeInfo(&lbtree);
	lbtree.push(&lbtree, 190); lbtree.printNodeInfo(&lbtree);
	lbtree.push(&lbtree, 200); lbtree.printNodeInfo(&lbtree);
	lbtree.printBinTreeInfo(&lbtree);

	lbtree.preorderTraversal(&lbtree); printf("\n");
	lbtree.midorderTraversal(&lbtree); printf("\n");
	lbtree.postorderTraversal(&lbtree); printf("\n");

	BinTreeDestroy(&lbtree);
	lbtree.printBinTreeInfo(&lbtree);
	return 0;
}
