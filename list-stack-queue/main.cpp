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
	s.push("Lin ChenChen");
	cout<<s.stack_len()<<":"<<s<<endl;
	s.insert_back("Liebe","world!");
	s.insert_front("Cai yunlong","Liebe");
	s.insert_back("is cute","Lin ChenChen");
	s.insert_front("C++ primer","hello");
	//s.delete_elem("Liebe");
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
	link<int> linklist;
	for(int i=0;i<10;i++)
		linklist.head_insert(i);
	cout<<linklist.link_len()<<":"<<linklist<<endl;
}