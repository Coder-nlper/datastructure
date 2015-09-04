#ifndef QUEUE_H
#define QUEUE_H 1
#include"questa.h"

/**友元类与函数**/
template<class type> class Queue;
template <class type> ostream& operator<<(ostream&,const Queue<type>&);

/**队列元素类**/
template<class type> class Queueitem
{
	Queueitem(const type &t):item(t),next(0){}
	friend  class Queue<type>;
	friend ostream& operator<< <type>(ostream&, const Queue<type>&);
	type item;
	Queueitem *next;
};
/**队列结构类**/
template<class type> class Queue{
private:
    Queueitem<type> *head;
    Queueitem<type> *tail;
	int length;
	void destroy();
	void copy_elems(const Queue&);
	template <class Iter> void copy_elems(Iter,Iter);
public:
	Queue():head(0),tail(0),length(0){};
	Queue(const Queue &Q):head(0),tail(0),length(0)
	{
		copy_elems(Q);
	}
	Queue& operator=(const Queue&);
	friend ostream& operator<< <type>(ostream&,const Queue<type>&);
	~Queue(){
		destroy();
	}
	type &front();
	const type &front() const;
	void push(const type&);
	void pop();
	int Queue_len();
	template <class It> Queue(It begin,It end):head(0),tail(0),length(0)//模板成员初始化队列
	{
		copy_elems(begin,end);
	}
	template <class Iter> void assign(Iter,Iter);
	inline bool empty() const//判断队列是否为空
	{
		return head==0;
	}
};
template <class type> type& Queue<type>::front()//返回队首元素
{
	return head->item;
}
template <class type> const type& Queue<type>::front() const//返回队首元素，这个函数表明类参数不可更改
{
	return head->item;
}
template <class type> void Queue<type>::pop()//删除队首元素，依次删除直到队列为空
{
	Queueitem<type> *p=head;

	head=head->next;
	delete p;
	--length;
}
template <class type> void Queue<type>::push(const type &val)//利用链表的尾插法进行入队列
{
	Queueitem<type> *pt=new Queueitem<type>(val);
	if(empty())
	{
		head=tail=pt;
		length=1;
	}
	else
	{
		tail->next=pt;
		tail=pt;
		++length;
	}
}
template <class type> int Queue<type>::Queue_len()
{
	return length;
}
template <class type> void Queue<type>::copy_elems(const Queue &orig)
{
	for(Queeuitem<type> *pt=orig.head;pt;pt=pt->next)
		push(pt->item);
}
template <class type> Queue<type>& Queue<type>::operator=(const Queue& Que)//队列赋值运算符重载
{
	destroy();
	copy_elems(Que);
	return *this;
}
template <class type> void Queue<type>::destroy()//销毁队列
{
	while(!empty())
		pop();
}
template <class type> template <class It> void Queue<type>::copy_elems(It begin,It end)
{
	while(begin!=end){
		push(*begin);
		++begin;
	}
}
template <class type> template <class Iter> void Queue<type>::assign(Iter begin,Iter end)//拷贝其他类型容器元素到队列中，需要借助于成员模板
{
	destroy();
	copy_elems(begin,end);
}
template <class type> ostream& operator<< <type> (ostream &os, const Queue<type> &q) //重载<<运算符，输出Queue的元素
 {
      os <<"<**";
      Queueitem<type> *p;
      for(p=q.head;p;p=p->next)
           os << p->item <<"-";
      os <<"**>";
      return os;
 }
#endif