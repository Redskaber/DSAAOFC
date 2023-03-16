#include <stdio.h>
#include <stdlib.h>
#include "10_二叉树的实现.h"


int start_binary_tree_case()
{
	arrBinTree abtree;
	binaryTreeInit(&abtree);

	abtree.printBTree(&abtree,pro);
	printBTreeInfo(&abtree);
	
	abtree.push(&abtree, 10);
	printBTreeInfo(&abtree);

	abtree.push(&abtree, 20);
	abtree.printBTree(&abtree, pro);
	printBTreeInfo(&abtree);


	abtree.push(&abtree, 30);
	abtree.printBTree(&abtree, pro);
	printBTreeInfo(&abtree);


	abtree.push(&abtree, 40);
	abtree.printBTree(&abtree, pro);
	printBTreeInfo(&abtree);

	abtree.push(&abtree, 50);
	abtree.push(&abtree, 60);
	abtree.push(&abtree, 70);
	abtree.push(&abtree, 80);
	abtree.push(&abtree, 90);
	abtree.push(&abtree, 100);
	abtree.push(&abtree, 110);
	abtree.push(&abtree, 120);
	abtree.push(&abtree, 130);
	abtree.push(&abtree, 140);
	abtree.push(&abtree, 150);
	abtree.push(&abtree, 160);
	abtree.push(&abtree, 170);
	abtree.push(&abtree, 180);
	abtree.printBTree(&abtree, pro);
	printBTreeInfo(&abtree);


	abtree.proPrintBTree(&abtree);


	abtree.destroyBinaryTree(&abtree);
	abtree.printBTree(&abtree, pro);
	printBTreeInfo(&abtree);


	return 0;
}

