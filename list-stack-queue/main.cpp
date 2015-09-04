#include"questa.h"
#include"queue.h"
#include"stack.h"
#include"linklist.h"

int main()
{
	int test[]={0,1,2,3,4,5,2,1};
	stackc<string> s;
	s.push("hello");
	s.push("world!");
	s.push("Lin Chen");
	s.push("Lin Chen Chen");
	cout<<s<<endl;
	while(!s.isempty())
		cout<<s.pop()<<endl;
	Queue<int> q;
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);
	q.assign(test,test+5);
	cout<<q.front()<<endl; 
	cout<<q<<":"<<q.Queue_len()<<endl;
	linklist<int> link;
	for(int i=0;i<10;i++)
		link.tail_insert(i);
	cout<<link<<endl;
}