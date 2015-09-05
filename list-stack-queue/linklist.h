#ifndef _LINK_H
#define _LINK_H 1
#include"questa.h"

template<class type> class link;
template <class type> ostream& operator<<(ostream&,const link<type>&);
template<class type> class linkitem{
	type data;
	linkitem *next;
	friend class link<type>;
	friend ostream& operator<< <type>(ostream&, const link<type>&);
	linkitem(const type &t):data(t),next(0){}
};
template<class type> class link{
private:
	linkitem<type> *headnode;
	linkitem<type> *topnode;
	int count,flag;
public:
	link():count(0),flag(0){
	initlist();
	}
	void initlist();
	void tail_insert(const type&);
	void head_insert(const type&);
	type pop();
	int link_len();
	void cleanstack();
	friend ostream& operator<< <type>(ostream&, const link<type>&);
	inline bool isempty()
	{
		return headnode==0;
	}
	~link(){
		cleanstack();
	}
};
template<class type> void link<type>::initlist()
{
	linkitem<type> *node=new linkitem<type>(0);
	if(NULL==node)
	{
		cerr<<"no memory..."<<endl;
		exit(1);
	}
	headnode=topnode=node;
}
template<class type> void link<type>::head_insert(const type &data)
{
	flag=1;
	linkitem<type> *node=new linkitem<type>(data);
	if(NULL==node)
	{
		cerr<<"no memory..."<<endl;
		exit(1);
	}
	node->next=headnode->next;
	headnode->next=node;
	++count;
}
template<class type> void link<type>::tail_insert(const type &data)
{
	flag=2;
	linkitem<type> *node=new linkitem<type>(data);
	if(NULL==node)
	{
		cerr<<"no memory..."<<endl;
		exit(1);
	}
	headnode->next=node;
	headnode=node;//插入元素结束，headnode到达链表的最后
	++count;
}
template<class type> type link<type>::pop()
{
	    linkitem<type> *p=headnode;
		type  value=headnode->data;
		headnode=headnode->next;
		delete p;
		--count;
		return value;
}
template<class type> void link<type>::cleanstack(){
	while(!isempty())
		pop();
}
template<class type> int link<type>::link_len(){
	return count;
}
template <class type> ostream& operator<< <type> (ostream &os, const link<type> &q) 
 {
	 if(q.flag==1){//头插法
	 os <<"{*";
      linkitem<type> *p;
      for(p=q.headnode->next;p;p=p->next)//p=q.headnode->next,链表中首节点不存储元素。同理于下面的p=q.topnode->next
           os <<p->data<<" ";
	  os<<"*}";
      return os;
	 }
	 else if(q.flag==2)
	 {
		 os <<"{*";
      linkitem<type> *p;
      for(p=q.topnode->next;p;p=p->next)
           os <<p->data<<" ";
	  os<<"*}";
      return os;
	 }
 }
#endif