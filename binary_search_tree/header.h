#ifndef _BTREE_
#define _BTREE_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<time.h>


typedef unsigned int UINT;

typedef struct BiTNode{
	int data;
	int bf;
	struct BiTNode *lchild,*rchild;
}BiTNode,*Bitree;

#define max(a,b)  a>b?a:b

#define LH 1
#define EH 0
#define RH -1

#endif

