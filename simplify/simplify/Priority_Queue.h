//基于binary min-heap和ELF-Hash的优先队列
#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#include <vector>
#include <set>
#include <list>
#include <utility>
#include <iterator>
#include <stack>

using namespace std;

template <typename Key, typename Type, int Size> class Priority_Queue
{
public:							//按key排序
	Priority_Queue();
	~Priority_Queue();
public:
	typename typedef struct _QUEUEITEM					//函数的返回类型
	{
		Key key;
		Type c;
		int heapPos;
		list<int>::iterator hashIter;
	} QueueItem;
	typename typedef vector<QueueItem>::iterator Iter;
	bool push(const Key&, const Type&);					//返回插入是否成功
	bool push(const QueueItem&);						
	bool push(const Iter);								
	bool isEmpty();										
	int size();											
	pair<Key,Type> pop();								
	Iter getMin();										
	Iter query(const Key&, const Type&);				
	Iter query(const QueueItem&);						
	Iter query(const Iter);								
	bool deleteItem(Iter);								
	void clear();
	Iter getNull();

	list<int> *hashSet;
	vector<int> minHeap;
	vector<QueueItem> dataVec;
	stack<int> freeStack;
	

	void Swap(int a,int b);
	int HashFunc(const Key&);
	bool Insert(const QueueItem&);
	Iter Query(const QueueItem&);
	bool Delete(Iter);
};
//模板类不能分开写函数

template<typename Key, typename Type, int Size>
Priority_Queue<Key,Type,Size>::Priority_Queue()
{
	hashSet=NULL;
	clear();
	hashSet=new list<int>[Size];
}

template<typename Key, typename Type, int Size>
Priority_Queue<Key,Type,Size>::~Priority_Queue()
{
	clear();
}

template<typename Key,typename Type, int Size>
void Priority_Queue<Key,Type,Size>::clear() //全部清空
{
	if(hashSet!=NULL){
		delete []hashSet;
		hashSet=NULL;
	} 
	minHeap.clear();
	dataVec.clear();
	while(!freeStack.empty()) freeStack.pop();
}

template<typename Key, typename Type,int Size>
int Priority_Queue<Key,Type,Size>::HashFunc(const Key &k)  //返回它的哈希值
{
	double tmpk=static_cast<double>(k);
	if(tmpk<1e-8) tmpk=1;
	while(tmpk<1000000) tmpk*=91;
	int key=(int)tmpk;
	return key%Size;
}

template<typename Key, typename Type, int Size>
void Priority_Queue<Key, Type, Size>::Swap(int a, int b)  
{
	swap(dataVec[minHeap[a]].heapPos,dataVec[minHeap[b]].heapPos);
	swap(minHeap[a],minHeap[b]);
}

template<typename Key, typename Type, int Size>
bool Priority_Queue<Key,Type,Size>::Insert(const QueueItem &q)  //插入
{
	int storePos=-1;
	if(freeStack.empty())
	{
		dataVec.push_back(q);
		storePos=dataVec.size()-1;
	}
	else
	{
		storePos=freeStack.top();
		freeStack.pop();
		dataVec[storePos]=q;
	}
	minHeap.push_back(storePos);
	int now=(int)minHeap.size()-1;
	dataVec[storePos].heapPos=now;

	int key=HashFunc(q.key);
	hashSet[key].push_front(storePos);
	dataVec[storePos].hashIter=hashSet[key].begin();

	while(now!=0 && dataVec[minHeap[now]].key<dataVec[minHeap[(now-1)/2]].key)
	{
		Swap(now,(now-1)/2);
		now=(now-1)/2;
	}
	return true;
}

template<typename Key, typename Type, int Size>
typename Priority_Queue<Key,Type,Size>::Iter Priority_Queue<Key,Type,Size>::Query(const QueueItem &q)   //查询
{
	int key=HashFunc(q.key);
	for(list<int>::iterator it=hashSet[key].begin();
		it!=hashSet[key].end();++it){
			if(dataVec[*it].key==q.key && dataVec[*it].c==q.c)
			{
				return dataVec.begin()+(*it);
			}
	}
	Iter ans=dataVec.end();
	return ans;
}

template<typename Key, typename Type, int Size>
bool Priority_Queue<Key,Type,Size>::Delete(Iter iter)   //删除
{
	
	if(iter==dataVec.end())
	{
		return false;
	}
	
	int key=HashFunc(iter->key);
	list<int>::iterator it=iter->hashIter;
	if(it==hashSet[key].end())
	{
		return false;
	}

	hashSet[key].erase(iter->hashIter);

	int now=iter->heapPos;
	Swap(now, minHeap.size()-1);
	freeStack.push(minHeap[minHeap.size()-1]);
	minHeap.pop_back();

	if(now<(int)minHeap.size()){
		while(now!=0 && dataVec[minHeap[now]].key<dataVec[minHeap[(now-1)/2]].key)
		{
			Swap(now,(now-1)/2);
			now=(now-1)/2;
		}

		while((2*now+1<(int)minHeap.size() && dataVec[minHeap[now]].key>dataVec[minHeap[2*now+1]].key) ||
			  (2*now+2<(int)minHeap.size() && dataVec[minHeap[now]].key>dataVec[minHeap[2*now+2]].key))
		{
				if(2*now+2==(int)minHeap.size() || dataVec[minHeap[2*now+1]].key<dataVec[minHeap[2*now+2]].key)
				{
					Swap(2*now+1, now);
					now=2*now+1;
				}
				else
				{
					Swap(2*now+2, now);
					now=2*now+2;
				}
		}
	}
	return true;
}

template<typename Key, typename Type,int Size>
bool Priority_Queue<Key,Type,Size>::push(const Key &k, const Type &t)   
{
	QueueItem q;
	q.key=k;
	q.c=t;
	return Insert(q);
}

template<typename Key, typename Type,int Size>
bool Priority_Queue<Key,Type,Size>::push(const Iter iter)
{
	return Insert(&iter);
}

template<typename Key, typename Type,int Size>
bool Priority_Queue<Key,Type,Size>::push(const QueueItem &q)
{
	return Insert(q);
}

template<typename Key, typename Type, int Size>
bool Priority_Queue<Key,Type,Size>::isEmpty()
{
	return (minHeap.size()==0);
}

template<typename Key, typename Type, int Size>
int Priority_Queue<Key,Type,Size>::size()
{
	return (int)(minHeap.size());
}

template<typename Key, typename Type, int Size>
typename pair<Key,Type> Priority_Queue<Key,Type,Size>::pop()
{
	Iter iter=getMin();
	QueueItem tmpItem=*iter;
	Delete(iter);
	pair<Key,Type> tmpPair(tmpItem.key, tmpItem.c);
	return tmpPair;
}

template<typename Key, typename Type, int Size>
typename Priority_Queue<Key,Type,Size>::Iter Priority_Queue<Key,Type,Size>::getMin()
{
	return dataVec.begin()+minHeap[0];
}

template<typename Key, typename Type, int Size>
typename Priority_Queue<Key,Type,Size>::Iter Priority_Queue<Key,Type,Size>::query(const Key &k, const Type &t)
{
	QueueItem tmpItem;
	tmpItem.key=k;
	tmpItem.c=t;
	return Query(tmpItem);
}

template<typename Key, typename Type, int Size>
typename Priority_Queue<Key,Type,Size>::Iter Priority_Queue<Key,Type,Size>::query(const Iter iter)
{
	QueueItem tmpItem=*iter;
	return Query(tmpItem);
}

template<typename Key, typename Type,int Size>
typename Priority_Queue<Key,Type,Size>::Iter Priority_Queue<Key,Type,Size>::query(const QueueItem &q)
{
	return Query(q);
}

template<typename Key, typename Type, int Size>
bool Priority_Queue<Key,Type,Size>::deleteItem(Iter iter)
{
	return Delete(iter);
}

template<typename Key, typename Type, int Size>
typename Priority_Queue<Key,Type,Size>::Iter Priority_Queue<Key,Type,Size>::getNull()
{
	return dataVec.end();
}

#endif
