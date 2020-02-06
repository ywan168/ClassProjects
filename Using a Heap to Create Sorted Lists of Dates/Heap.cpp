
/**
   file Heap.cpp
   @date 2019-02-12
   Description: implementation for the max Heap class
*/

#include "Heap.h"
#include<iostream> 
#include<algorithm> //  heap  
#include<vector> 
using namespace std;

template <typename E>
Heap<E>::Heap()                  
{
    //implement this function
    cmp = [](E a, E b) -> bool {return (a < b? true : false);};
}

template <typename E>
Heap<E>::Heap(std::function<bool(E,E)> fn)
{
    //implement this function
    cmp=fn;
}

template <typename E>
bool Heap<E>::isEmpty() const
{
   // implement this function
    return (tree.size() == 0);

}

template<typename E>
void Heap<E>::insert(E item)
{
  //implement this function
    tree.push_back(item);
    int place = tree.size()-1;
    int parent = (place - 1)/2;
    //while ((parent >= 0) && tree[place] > tree[parent])
    while(parent >=0 && cmp(tree[parent], tree[place]))
    { 
	swap(place, parent);
        place = parent;
        parent = (place - 1)/2;
    }
    //tree.resize(tree.size()+1);
}

template<typename E>
E Heap<E>::remove() throw (HeapException)
{
   // implement this function
    if (isEmpty())
        throw HeapException("Heap is empty.");
    E root = tree[0];
    tree[0] = tree[tree.size() - 1];
    tree.resize(tree.size() - 1);
    rebuild(0, tree.size());
    return root;
}

template<typename E>
const E& Heap<E>::peek() const throw (HeapException)
{
   //implement this function
    if (isEmpty())
        throw HeapException("Heap is empty.");
    return tree[0];
}

template<typename E>
int Heap<E>::size()const
{
   //implement this function
    return tree.size();
}


template<typename E>
void Heap<E>::swap(int place, int parent)
{
   //implement this function
    E temp;
    temp = tree[place];
    tree[place] = tree[parent];
    tree[parent] = temp;

}

template<typename E>
void Heap<E>::rebuild(int root, int eSize)   
{
   //implement this function
   int child = 2*root +1;
   if (child < eSize)
   { 
	   int rightchild = child +1;
           //if ((rightchild < eSize) && (tree[rightchild]> tree[child]))
           if((rightchild < eSize) && cmp(tree[child],tree[rightchild]))
                child = rightchild;
           //if (tree[root] < tree[child])
	   if(cmp(tree[root],tree[child]))
           {
		   swap(child, root);
                   rebuild(child, eSize);
           }
   }
}




