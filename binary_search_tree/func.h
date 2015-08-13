#ifndef AVL_FUNC_
#define AVL_FUNC_
/*Average Binary Tree*/
#define LH +1
#define EH 0
#define RH -1

void R_Rotate(Bitree *P);
void L_Rotate(Bitree *P);
void LeftBalance(Bitree *P);
void RightBalance(Bitree* T);
int insertAVL(Bitree *T,int e,int *taller);
int DeleteAVL(Bitree *T, int key, int &shorter);
int search(Bitree *P,int e);



int searchBST(Bitree T,int key,Bitree f,Bitree *p);  
int insertBST(Bitree *T,int key);  
void preordertraverse(Bitree T);  
void midordertraverse(Bitree T);  
void postordertraverse(Bitree T);  
  
/*delete tree*/  
int Delete(Bitree *p);  
int DeleteBST(Bitree *T,int key);

/*operate tree*/
int getwidth(Bitree T);
int getHeight(Bitree P);
#endif