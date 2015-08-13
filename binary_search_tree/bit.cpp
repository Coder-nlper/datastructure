#include"header.h"
#include"func.h"

#define _TYPE_INT(type) #type
#define TYPE_INT(type) _TYPE_INT(type)


int main()
{
	Bitree T=NULL;
	Bitree AVL=NULL;
	int taller;
	int BST_height=0;
	int AVL_height=0;
	int BST_width=0;
	int AVL_width=0;
	srand(time(0));
	printf("please input treenode number:\n");
    int n,i;
	scanf("%d",&n);
	for(i=0;i<=n;i++)
	{
		insertBST(&T,rand()%1000);
	}
	for(i=0;i<=n;i++){
		insertAVL(&AVL,rand()%1000,&taller);
	}
	printf("average binary tree:\n");
	midordertraverse(AVL);
	printf("\n");
	printf("preordertraverse,root->lchild->rchild.:\n");
	preordertraverse(T);
	printf("\n");
	printf("midordertraverse,lchild->root->rchild.:\n");
	midordertraverse(T);
	printf("\n");
	printf("postordertraverse,visit leaves firstly.lchild->rchild.:\n");
	postordertraverse(T);
	printf("\n");
	printf("delete element of tree...\n");
	if(DeleteBST(&T,99)>0){
       midordertraverse(T);
	   printf("\n");
	}
	else 
		printf("element does not in this tree\n");
	BST_height=getHeight(T);
	AVL_height=getHeight(AVL);
	printf("BST_height:%d\nAVL_height:%d\n",BST_height,AVL_height);
	BST_width=getwidth(T);
	AVL_width=getwidth(AVL);
	printf("BST_height:%d\nAVL_height:%d\n",BST_width,AVL_width);

}