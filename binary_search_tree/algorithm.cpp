#include"header.h"

int searchBST(Bitree T,int key,Bitree f,Bitree *p)
{
	if(!T){
		*p=f;
		return 0;
	}
	else if(key == T->data){
		*p=T;
		return 1;
	}
	else if(key<T->data)
         return searchBST(T->lchild,key,T,p);
	else 
		 return searchBST(T->rchild,key,T,p);
}
int insertBST(Bitree *T,int key)
{
	Bitree p,s;
	if(!searchBST(*T,key,NULL,&p)){
		s=(Bitree)malloc(sizeof(BiTNode));
		s->data=key;
		s->lchild=s->rchild=NULL;
		if(!p)
			*T=s;
		else if(key<p->data)
			p->lchild=s;
		else 
			p->rchild=s;
		return 1;
	}
	else
		return 0;
}
/*looking up binary tree*/
void preordertraverse(Bitree T)
{
	if(T==NULL)
		return ;
	printf("%d\t",T->data);
	preordertraverse(T->lchild);
	preordertraverse(T->rchild);
}
void midordertraverse(Bitree T)
{
	if(T==NULL)
		return ;
	midordertraverse(T->lchild);
    printf("%d\t",T->data);
	midordertraverse(T->rchild);
}
void postordertraverse(Bitree T)
{
	if(T==NULL)
		return ;
	postordertraverse(T->lchild);
	postordertraverse(T->rchild);
	printf("%d\t",T->data);
}

/*delete Binary Sort Tree*/
int Delete(Bitree *p)
{
	Bitree q,s;

	if((*p)->rchild==NULL){
		q=*p;
		*p=(*p)->lchild;
		free(q);
	}
	else if((*p)->lchild==NULL){
		q=*p;
		*p=(*p)->rchild;
		free(q);
	}
	else{
		q=*p;
		s=(*p)->lchild;
		while(s->rchild){
			q=s;
			s=s->rchild;
		}
		(*p)->data=s->data;
		if(q!=*p)
			q->rchild=s->lchild;
		else
			q->lchild=s->lchild;
		free(s);
	}
	return 1;
}
int DeleteBST(Bitree *T,int key)
{
	if(!*T)
		return 0;
	else{
		if(key==(*T)->data)
			return Delete(T);
		else if(key<(*T)->data)
			return DeleteBST(&(*T)->lchild,key);
		else
			return DeleteBST(&(*T)->rchild,key);
	}
}


/*average binary tree*/
void R_Rotate(Bitree *P)
{
	Bitree L;
	L=(*P)->lchild;
	(*P)->lchild=L->rchild;
	L->rchild=(*P);
	*P=L;
}
void L_Rotate(Bitree *P)
{
	Bitree R;
	R=(*P)->rchild;
	(*P)->rchild=R->lchild;
	R->lchild=(*P);
	*P=R;
}
void LeftBalance(Bitree *P)
{
	Bitree L,Lr;
	L=(*P)->lchild;
	switch(L->bf)
	{
	case LH:
		(*P)->bf=L->bf=EH;
		R_Rotate(P);
		break;
	case RH:
		Lr=L->rchild;
		switch(Lr->bf){
	       case LH:
			   (*P)->bf=RH;
			    L->bf=EH;
				break;
		   case EH:
			   (*P)->bf=L->bf=EH;
			   break;
		   case RH:
			   (*P)->bf=EH;
			   L->bf=LH;
			   break;
		}
		Lr->bf=EH;
		L_Rotate(&(*P)->lchild);
		R_Rotate(P);
	}
}

void RightBalance(Bitree* T)  
{  
    Bitree lc,rd;  
    lc= (*T)->rchild;  
    switch (lc->bf)  
    {  
    case RH:  
        (*T)->bf = lc->bf = EH;  
        L_Rotate(T);  
        break;  
    case LH:  
        rd = lc->lchild;  
        switch(rd->bf)  
        {  
        case LH:  
            (*T)->bf = EH;  
            lc->bf = RH;  
            break;  
        case EH:  
            (*T)->bf = lc->bf = EH;  
            break;  
        case RH:  
            (*T)->bf = EH;  
            lc->bf = LH;  
            break;  
        }  
        rd->bf = EH;  
        R_Rotate(&(*T)->rchild);  
        L_Rotate(T);  
        break;  
    }  
}  

int insertAVL(Bitree *T,int e,int *taller)
{
	if(!*T)
	{
		*T=(Bitree)malloc(sizeof(BiTNode));
		(*T)->data=e;
		(*T)->lchild=(*T)->rchild=NULL;
		(*T)->bf=EH;
		*taller=1;
	}
	else
	{
		if(e==(*T)->data)
		{
			*taller=0;
			return 0;
		}
		if(e<(*T)->data)
		{
			if(!insertAVL(&(*T)->lchild,e,taller))
				return 0;
			if(*taller)
			{
				switch((*T)->bf)
				{
				case LH:
					LeftBalance(T);
					*taller=0;
					break;
				case EH:
					(*T)->bf=LH;
					*taller=1;
					break;
				case RH:
					(*T)->bf=EH;
					*taller=0;
					break;
				}
			}
		}
		else
		{
			if(!insertAVL(&(*T)->rchild,e,taller))
				return 0;
			if(*taller)
			{
				switch((*T)->bf){
				case LH:
					(*T)->bf=EH;
					*taller=0;
					break;
				case EH:
					(*T)->bf=RH;
					*taller=1;
					break;
				case RH:
					RightBalance(T);
					*taller=0;
					break;
				}
			}
		}
	}
	return 1;
}
int search(Bitree *P,int e)
{
	if(!*P)
		return 0;
	if((*P)->data==e)
		return 1;
	else if((*P)->data<e)
		return search(&(*P)->lchild,e);
	else
		return search(&(*P)->rchild,e);
}

int DeleteAVL(Bitree *T, int key, int &shorter){  
    if (!T)  
    { 
        shorter = false;  
        return 0;  
    }  
    else  
    {  
        if(key == (*T)->data)  
        {  
           Bitree q = *T;  
            if (!(*T)->lchild)  
            {  
                q = *T;  
                *T = (*T)->rchild;  
                free(q);  
                shorter = 1;  
                return 1;  
            }  
            else if (!(*T)->rchild){
                q = *T;  
                *T= (*T)->lchild;
                free(q);  
                shorter = 1;  
                return 1;  
            }  
            else {    
                Bitree s = (*T)->lchild;  
                while(s->rchild)  
                   s = s->rchild;

                (*T)->data = s->data;  
                key = s->data; 
            }  
        }  
        if (key < (*T)->data){  
            if (!DeleteAVL(&(*T)->lchild, key, shorter)) 
				return 0;  
            if (shorter){  
                switch((*T)->bf){  
                case LH:
					(*T)->bf = EH; 
					shorter = 1;
					break;  
                case EH:
					(*T)->bf = RH;
					shorter = 0;
					break;  
                case RH:
					RightBalance(T);   
                    if ((*T)->rchild->bf == EH)  
                        shorter = 0;  
                    else   
                        shorter = 1;
					break;  
                }  
            }  
        }  
        else{  
            if (!DeleteAVL(&(*T)->rchild, key, shorter)) 
				return 0;  
            if (shorter){  
                switch((*T)->bf){  
                case LH:
					LeftBalance(T);  
                    if ((*T)->lchild->bf == EH)  
                        shorter = 0;  
                    else   
                        shorter = 1;
					break;  
                case EH:
					(*T)->bf = LH; 
					shorter = 0;
					break;  
                case RH:
					(*T)->bf = EH;
					shorter = 1;
					break;  
                }  
            }  
        }  
    }  
    return 1;  
}
/*Get the depth of the tree*/
int getHeight(Bitree T){  
	int leftheight=1;
	int rightheight=1;

    if(T==NULL)
		return 0;
	   leftheight=leftheight+getHeight(T->lchild);
	   rightheight=rightheight+getHeight(T->rchild); 

	return max(leftheight,rightheight);
}  

/*Get the width of the tree*/
int getwidth(Bitree T){  
	int leftheight=1;
	int rightheight=1;

    if(T==NULL)
		return 0;
	   leftheight=leftheight+getHeight(T->lchild);
	   rightheight=rightheight+getHeight(T->rchild); 

	return  leftheight+rightheight;
}  