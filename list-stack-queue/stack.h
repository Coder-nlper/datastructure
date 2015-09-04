#ifndef _STACK_H
#define _STACK_H 1
#include"questa.h"

template<class type> class stackc;
template <class type> ostream& operator<<(ostream&,const stackc<type>&);
template<class type> class stackcitem{
	type data;
	stackcitem *next;
	friend class stackc<type>;
	friend ostream& operator<< <type>(ostream&, const stackc<type>&);
	stackcitem(const type &t):data(t),next(0){}
};
template<class type> class stackc{
private:
	stackcitem<type> *top;
	stackcitem<type> *move;
	int count;
public:
	stackc():count(0),top(0){}
	void push(const type&);
	type pop();
	int stack_len();
	void cleanstack();
	friend ostream& operator<< <type>(ostream&, const stackc<type>&);
	inline bool isempty()
	{
		return top==0;
	}
	~stackc(){
		cleanstack();
	}
};
template<class type> void stackc<type>::push(const type &data)
{
	stackcitem<type> *node=new stackcitem<type>(data);
	if(isempty())
	{
		top=move=node;
		count=1;
	}
	else
	{
		move->next=node;
		move=node;
		++count;
	}
}
template<class type> type stackc<type>::pop()
{
	    stackcitem<type> *p=top;
		type  value=top->data;
		top=top->next;
		delete p;
		--count;
		return value;
}
template<class type> void stackc<type>::cleanstack(){
	while(!isempty())
		pop();
	count=0;
}
template<class type> int stackc<type>::stack_len(){
	return count;
}
template <class type> ostream& operator<< <type> (ostream &os, const stackc<type> &q) 
 {
	 os <<"{*";
      stackcitem<type> *p;
      for(p=q.top;p;p=p->next)
           os <<p->data<<" ";
	  os<<"*}";
      return os;
 }
#endif