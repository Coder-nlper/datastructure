#ifndef LINKLIST_H
#define LINKLIST_H 1

#include"questa.h"
template<class type> class linklist;
template<class type> ostream& operator<<(ostream&,const linklist<type>&);

template<class type> class linkdata{
	type data;
	linkdata *next;
	friend class linklist<type>;
    friend ostream& operator<< <type> (ostream&,const linklist<type>&);
	linkdata():data(0),next(0){}
	linkdata(const type& d):data(d),next(0){}
};
template<class type> class linklist
{
private:
	linkdata<type> *Link;
	int count;
	void clean();
public:
	linklist():Link(0),count(0){}
	void initlist();
	void head_insert(const type &d);
	void tail_insert(const type &d);
	void elem_del(const type &d);
	friend ostream& operator<< <type> (ostream&,const linklist<type>&);
	int link_len();
	bool empty()
	{
		return Link==0;
	}
	~linklist()
	{
		clean();
	}
};
template<class type> void linklist<type>::head_insert(const type &d)
{
	linkdata<type> *node=new linkdata<type>(d);
	if(NULL==node)
	{
		cerr<<"no memory..."<<endl;
		exit(1);
	}
	if(empty())
	{
		Link=node;
		count=1;
	}
	else
	{
	    node->next=Link->next;
	    Link->next=node;
		++count;
	}
}
template<class type> void linklist<type>::tail_insert(const type &d)
{
	linkdata<type> *node=new linkdata<type>(d);
    if(NULL==node)
	{
		cerr<<"no memory..."<<endl;
		exit(1);
	}
	if(empty())
	{
		Link=node;
		count=1;
	}
	else
	{
	    Link->next=node;
	    Link=node;
		++count;
	}
}
template<class type> void linklist<type>::clean()
{
	linkdata<type> *node;
	while(Link)
	{
		Link=node;
	    Link=Link->next;
	    delete node;
	}
	    count=0;
}
template<class type> void linklist<type>::elem_del(const type &d)
{
	linkdata<type> *node;
	while(Link)
	{
	   if(Link->data==d)
	   {
		   node=Link;
		   Link=Link->next;
		   delete node;
		   --count;
	   }
	   else
		  Link=Link->next;
	}
}
template<class type> int linklist<type>::link_len(){
	return count;
}
template<class type> ostream& operator<< <type> (ostream &os, const linklist<type> &q) 
 { 
      os <<"<";
      linkdata<type> *p;
      for(p=q.Link;p;p=p->next)
           os << p->data<<"-";
      os <<">";
      return os;
 }
#endif	