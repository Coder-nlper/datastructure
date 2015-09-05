#ifndef _STACK_H
#define _STACK_H 1
#include"questa.h"

template<class type> class stackc;
template <class type> ostream& operator<<(ostream&,const stackc<type>&);
template<class type> class stackcitem{
	type data;
	stackcitem *prev;
	stackcitem *next;
	friend class stackc<type>;
	friend ostream& operator<< <type>(ostream&, const stackc<type>&);
	stackcitem():data(type()),prev(0),next(0){}
	stackcitem(const type &t):data(t),prev(0),next(0){}
};
template<class type> class stackc{
private:
	stackcitem<type> *headnode;//首位节点负责移动插入删除节点
	stackcitem<type> *tailnode;//末尾节点标志位
    stackcitem<type> *resetnode;//复位到首位节点
	int count;
public:
	stackc():count(0){
		cout<<"construct stack..."<<endl;
	    initstack();
	}
	void initstack();
	void push(const type&);
	bool insert_front(const type& elem,type target);
	bool insert_back(const type& elem,type target);
	bool delete_elem(const type& elem);
	type pop();
	int stack_len();
	void cleanstack();
	friend ostream& operator<< <type>(ostream&, const stackc<type>&);
	inline bool isempty()
	{
		return tailnode==0;
	}
	~stackc(){
		cleanstack();
	}
};
template<class type> void stackc<type>::initstack()
{
	cout<<"init stack..."<<endl;
	stackcitem<type> *node;
	node=new stackcitem<type>;
	cout<<"build stack node ok..."<<endl;
	if(NULL==node)
	{
		cerr<<"no memory..."<<endl;
		exit(1);
	}
	headnode=tailnode=resetnode=node;
}
template<class type> void stackc<type>::push(const type &data)
{
	stackcitem<type> *node;
	try{
	      node=new stackcitem<type>(data);
	}catch(bad_alloc& node){
		cout<<"catch alloc memory error exception"<<endl;
	}

	tailnode->next=node;
	node->prev=tailnode;
	tailnode=node;
	++count;
}
template<class type> bool stackc<type>::insert_front(const type& elem,type target)
{
    stackcitem<type> *node;
	try{
	      node=new stackcitem<type>(elem);
	}catch(bad_alloc& node){
		cout<<"catch alloc memory error exception"<<endl;
	}
	while(headnode)
	{
		if(headnode->data == target)
		{
			if(headnode->prev!=NULL)
			{
			     node->prev=headnode->prev;
				 node->next=headnode;
				 headnode->prev=node;
				 headnode->prev->next=node;
			}
			else
			{
				node->next=headnode;
				headnode->prev=node;
				resetnode=node;//链表向前增长，复位跟踪节点
			}
			++count;
            headnode=resetnode;//回到首位节点
			return true;
		}
		headnode=headnode->next;
	}
	return false;
}
template<class type> bool stackc<type>::insert_back(const type& elem,type target)
{
    stackcitem<type> *node;
	try{
	      node=new stackcitem<type>(elem);
	}catch(bad_alloc& node){
		cout<<"catch alloc memory error exception"<<endl;
	}
	while(headnode)
	{
		if(headnode->data == target)
		{
			if(headnode->next!=NULL)
			{
			     node->prev=headnode;
				 node->next=headnode->next;
				 headnode->next->prev=node;
				 headnode->next=node;
			}
			else
			{
				headnode->next=node;
				node->prev=headnode;
				headnode=node;//headnode移动到末尾
				tailnode=headnode;//末尾节点发生变化
			}
			++count;
			headnode=resetnode;//回到首位节点
			return true;
		}
		headnode=headnode->next;
	}
	return false;
}
template<class type> bool stackc<type>::delete_elem(const type& elem){
	stackcitem<type> *node;
	while(headnode)
	{
		if(headnode->data==elem)
		{
			 if(headnode->prev==NULL)
			{
				node=headnode;
				headnode=headnode->next;
				headnode->prev=NULL;
				delete node;
			}
			else if(headnode->next==NULL){
				node=headnode;
				headnode=headnode->prev;
				headnode->next=NULL;
				delete node;
			}
			else if(headnode->next!=NULL && headnode->prev!=NULL)
			{
				node=headnode;
				headnode->prev->next=headnode->next;
				headnode->next->prev=headnode->prev;
				delete node;
			}
			headnode=resetnode;//回到首位节点
			--count;
			return true;
		}
		headnode=headnode->next;
	}
	return false;
}
template<class type> type stackc<type>::pop()
{
	    stackcitem<type> *p=tailnode;
		type  value=p->data;
		p=p->prev;
		delete tailnode;
		tailnode=p;
		--count;
		return value;
}
template<class type> void stackc<type>::cleanstack(){
	while(!isempty())
		pop();
}
template<class type> int stackc<type>::stack_len(){
	return count;
}
template <class type> ostream& operator<< <type> (ostream &os, const stackc<type> &q) 
 {
	 os <<"{*";
      stackcitem<type> *p;
      for(p=q.headnode->next;p;p=p->next)
           os <<p->data<<",";
	  os<<"*}";
      return os;
 }
#endif