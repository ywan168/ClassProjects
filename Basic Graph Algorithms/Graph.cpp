/**
 * Implementation of an extensible pointer-based adjacency
 * list representation of a weighted digraph whose vertices
 * hold objects that override the relational operators.
 * @Instructor: Duncan
 * @author Yanfang Wang
 * Course: CS3102.01
 * Programming Project #: 3
 * @since 03-27-2019
 * @see Graph.h, City.h, Graph.cpp
*/

#include "Graph.h"
#include <queue>
#include <stack>
#include <cstdlib>

using namespace std;

/* nested Vertex class definitions */

template<typename E>
Graph<E>::Vertex::Vertex(E s)
{
   pNextVertex = NULL;
   data = s;
   inDeg = 0;
   outDeg = 0;
   pEdge = NULL;
   processed = 0;
}

/* nested Edge class definitions */
template<typename E>
Graph<E>::Edge::Edge(double wt)
{
   destination = NULL;
   weight = wt;
   pNextEdge = NULL;
}

/* Outer Graph class definitions */
template <typename E>
Graph<E>::Graph()
{
   first = NULL;
   order = 0;
   cmp = [](E a, E b) -> int{return a < b? -1 : (a == b? 0 : 1);};      
}

template <typename E>
Graph<E>::Graph(std::function<int(E,E)> fn)
{
   first = NULL;
   order = 0;
   if (cmp == nullptr) 
        cmp = fn;
}

template <typename E> 
Graph<E>::~Graph() noexcept
{
   Edge* edgePtr;
   Vertex* vertexPtr;
   vertexPtr = first;
   while (first)
   {
      vertexPtr = first;
      while(vertexPtr->pEdge)
      {
         edgePtr = vertexPtr->pEdge;
         vertexPtr->pEdge = edgePtr->pNextEdge;
         delete edgePtr;
      }
      first = vertexPtr->pNextVertex;
      delete vertexPtr;
   }
}

template <typename E>
Graph<E>::Graph(const Graph<E>& other)
{
    first = NULL;
    order = 0;
    cmp = other.cmp;
    Vertex* tmp = other.first;
    Edge* edgPtr = NULL;
    while (tmp)
    {
        insertVertex(tmp->data);
        edgPtr = tmp->pEdge;
        while (edgPtr)
        {
            insertEdge(tmp->data,edgPtr->destination->data, edgPtr->weight);
            edgPtr = edgPtr->pNextEdge;
        }
    }        
}

template <typename E>
Graph<E>::Graph(Graph<E>&& other) noexcept
{
    first = other.first;
    order = other.order;
    cmp = other.cmp;
    other.first = nullptr;
    other.order = 0;   
    other.cmp = nullptr;
}

template <typename E>
Graph<E>& Graph<E>::operator=(const Graph<E>& other)
{
    if (this != &other)
    {
        first = NULL;
        order = 0;
        cmp = other.cmp;
        Vertex* tmp = other.first;
        Edge* edgPtr = NULL;
        while (tmp)
        {
            insertVertex(tmp->data);
            edgPtr = tmp->pEdge;
            while (edgPtr)
            {
                insertEdge(tmp->data,edgPtr->destination->data,edgPtr->weight);
                edgPtr = edgPtr->pNextEdge;
            }
        }  
    }
    return *this;
}

template <typename E>
Graph<E>& Graph<E>::operator =(Graph<E>&& other) noexcept
{
    if (this != &other)
    {
        Edge* edgePtr;
        Vertex* vertexPtr;
        vertexPtr = first;
        while (first)
        {
            vertexPtr = first;
            while(vertexPtr->pEdge)
            {
                edgePtr = vertexPtr->pEdge;
                vertexPtr->pEdge = edgePtr->pNextEdge;
                delete edgePtr;
            }
            first = vertexPtr->pNextVertex;
            delete vertexPtr;
        }
        first = other.first;
        order = other.order;
        cmp = other.cmp;
        other.first = nullptr;
    }
    return *this;
}

template <typename E> 
void Graph<E>::insertVertex(E obj)
{
   assert(isVertex(obj) == false);
   Vertex* locPtr = first;
   Vertex* predPtr = NULL;
   while (locPtr != NULL && cmp(obj,locPtr->data) > 0)
   {
      predPtr = locPtr;
      locPtr = locPtr->pNextVertex;
   }
   /*key already exist. */
   if (locPtr != NULL && cmp(obj,locPtr->data)==0)
   {
      locPtr->data = obj;
      return;
   }
   /* insert before first vertex */
   Vertex* newPtr = new Vertex(obj);
   newPtr->pNextVertex = NULL;
   newPtr->data = obj;
   newPtr->inDeg = 0;
   newPtr->outDeg = 0;
   newPtr->processed = 0;
   newPtr->pEdge = NULL;   
   if (predPtr == NULL)
      first = newPtr;
   else
      predPtr->pNextVertex = newPtr;
   newPtr->pNextVertex = locPtr;
   order++;
}

template <typename E> 
void Graph<E>::deleteVertex(E key)
{
   if (isEmpty())
      return;
   Vertex* predPtr = NULL;
   Vertex* walkPtr = first;  
   Vertex* tmp;
   /* does vertex exist */
   while (walkPtr != NULL && cmp(key,walkPtr->data) > 0)
   {  
      predPtr = walkPtr;
      walkPtr = walkPtr->pNextVertex;
   }
   if (walkPtr == NULL || cmp(key,walkPtr->data) != 0)
      return;
   /* vertex found. Test degree */
   if ((walkPtr->inDeg > 0) || (walkPtr->outDeg > 0))
      return;
   /* OK to delete */
   if (predPtr == NULL)
   {
      tmp = first;
      first = walkPtr->pNextVertex;
      delete tmp;
   }
   else
   {
      tmp = predPtr->pNextVertex;
      predPtr->pNextVertex = walkPtr->pNextVertex;
      delete tmp;
   }
   order--;
}

template <typename E> 
void Graph<E>::insertEdge(E fromKey, E toKey, double weight)
{

   if (isEmpty())
      return;
   /* check whether originating vertex exists */
   Vertex* tmpFrom = first;
   while (tmpFrom != NULL && cmp(fromKey,tmpFrom->data) > 0)
      tmpFrom = tmpFrom->pNextVertex;
   if (tmpFrom == NULL || cmp(fromKey,tmpFrom->data) != 0)
      return; 
   /* locate destination vertex */
   Vertex* tmpTo = first;
   while (tmpTo != NULL && cmp(toKey,tmpTo->data) > 0)
      tmpTo = tmpTo->pNextVertex;
   if (tmpTo == NULL || cmp(toKey,tmpTo->data) != 0)
      return;
   /*check if edge already exists */
   Edge* tmpEdge = tmpFrom->pEdge;
   while (tmpEdge != NULL && tmpEdge->destination != tmpTo)
      tmpEdge = tmpEdge->pNextEdge;
   if (tmpEdge != NULL && tmpEdge->destination != NULL)
      return;
   tmpFrom->outDeg++;
   tmpTo->inDeg++;
   Edge* newEdge = new Edge(weight);
   newEdge->destination = tmpTo;
   newEdge->weight = weight;
   newEdge->pNextEdge = NULL;
   if (tmpFrom->pEdge == NULL)
   {
      tmpFrom->pEdge = newEdge;
      return;
   }
   Edge* pred = NULL;
   tmpEdge = tmpFrom->pEdge;
   while (tmpEdge != NULL && tmpEdge->destination != tmpTo)
   {
      pred = tmpEdge;
      tmpEdge = tmpEdge->pNextEdge;
   }
   if (pred == NULL)
      tmpFrom->pEdge = newEdge;
   else
     pred->pNextEdge = newEdge;
   newEdge->pNextEdge = tmpEdge;
}

template <typename E> 
void Graph<E>::deleteEdge(E fromKey, E toKey)
{
   /* find source vertex */
   Vertex* tmpFrom = first;
   while (tmpFrom != NULL && cmp(fromKey,tmpFrom->data) > 0)
      tmpFrom = tmpFrom->pNextVertex;
   if (tmpFrom == NULL || cmp(fromKey,tmpFrom->data) != 0)
      return;
   /* locate destination vertex */
   Vertex* tmpTo = first; 
   while (tmpTo != NULL && cmp(toKey,tmpTo->data) > 0)
      tmpTo = tmpTo->pNextVertex;
   if (tmpTo == NULL || cmp(toKey,tmpTo->data) != 0)
      return;
   /*check if edge does not exist */
   Edge* tmpEdge = tmpFrom->pEdge;
   Edge* pred = NULL;
   while (tmpEdge != NULL && tmpEdge->destination != tmpTo)
   {
      pred = tmpEdge;
      tmpEdge = tmpEdge->pNextEdge;
   }
   /* if edge does not exist */
   if (tmpEdge == NULL)
      return;
   /* update degrees */
   pred->pNextEdge = tmpEdge->pNextEdge;
   tmpFrom->outDeg--;
   tmpTo->inDeg--;
   delete tmpEdge;
}

template <typename E> 
double Graph<E>::retrieveEdge(E fromKey, E toKey) const throw (GraphException)
{
   Edge* tmpEdge;
   Edge* pred;
   Vertex* tmpFrom;
   Vertex* tmpTo;
   /* find source vertex */
   tmpFrom = first;
   while (tmpFrom != NULL && cmp(fromKey,tmpFrom->data) > 0)
      tmpFrom = tmpFrom->pNextVertex;
   if (tmpFrom == NULL || cmp(fromKey,tmpFrom->data) != 0)
      throw GraphException("Non-existent edge - retrieveEdge().");
   /* locate destination vertex */
   tmpTo = first; 
   while (tmpTo != NULL && cmp(toKey,tmpTo->data) > 0)
      tmpTo = tmpTo->pNextVertex;
   if (tmpTo == NULL || cmp(toKey,tmpTo->data) != 0)
      throw GraphException("Non-existent edge - retrieveEdge().");
   /*check if edge does not exist */
   tmpEdge = tmpFrom->pEdge;
   while (tmpEdge != NULL && tmpEdge->destination != tmpTo)
      tmpEdge = tmpEdge->pNextEdge;
   /* if edge does not exist */
   if (tmpEdge == NULL)
      throw  GraphException("Non-existent edge - retrieveEdge().");
   return tmpEdge->weight; 
}

template <typename E> 
const E& Graph<E>::retrieveVertex(const E& key) const throw (GraphException)
{
   Vertex* tmp;
   if (isEmpty())
      throw GraphException("Non-existent vertex in call to retrieveVertex().");
   tmp = first;
   while (tmp != NULL && cmp(key,tmp->data) != 0)
      tmp = tmp->pNextVertex;
   if (tmp == NULL)
      throw GraphException("Non-existent vertex - retrieveVertex().");
   return tmp->data;
}

template <typename E> 
void Graph<E>::bfsTraverse(std::function<void(const E&)> func)
{
   Vertex* walkPtr;
   Vertex* toPtr;
   queue<Vertex*> q;
   Edge* edgeWalk;  
   Vertex* tmp;
   if (isEmpty())
      return;
   walkPtr = first;
   while (walkPtr != NULL)
   {
      walkPtr->processed = 0;
      walkPtr = walkPtr->pNextVertex;
   }
   walkPtr = first;
   while (walkPtr != NULL)
   {
      if (walkPtr->processed < 2)
      {
         if (walkPtr->processed < 1)
         {
            q.push(walkPtr); 
            walkPtr->processed = 1;
         }
      }
      while (!q.empty())
      {
          tmp = q.front();
          q.pop();
          func(tmp->data);
          tmp->processed = 2;
          edgeWalk = tmp->pEdge; 
          while (edgeWalk != NULL)           
          {
              toPtr = edgeWalk->destination;
              if (toPtr->processed == 0)
              {
                  toPtr->processed = 1;
                  q.push(toPtr);
              }
              edgeWalk = edgeWalk->pNextEdge;
          }
      }
      walkPtr = walkPtr->pNextVertex;
   }
}

template <typename E> 
void Graph<E>::dfsTraverse(std::function<void(const E&)> func)
{
   Vertex* walkPtr;
   Vertex* toPtr;
   stack<Vertex*> s;
   Edge* edgeWalk;  
   Vertex* tmp;
   if (isEmpty())
      return;
   walkPtr = first;
   while(walkPtr != NULL)
   {
      walkPtr->processed = 0;
      walkPtr = walkPtr->pNextVertex;
   }
   walkPtr = first;
   while (walkPtr != NULL)
   {
      if (walkPtr->processed < 2)
      {
         if (walkPtr->processed < 1)
         {
            walkPtr->processed = 1;  
            s.push(walkPtr);
         }
         while (!s.empty())
         {

            tmp = s.top();
            edgeWalk = tmp->pEdge;
            while(edgeWalk != NULL)
            {
               toPtr = edgeWalk->destination;
               if (toPtr->processed == 0)
               {
                  toPtr->processed = 1;
                  s.push(toPtr);
                  edgeWalk = toPtr->pEdge;
               }
               else
                  edgeWalk = edgeWalk->pNextEdge;
            }
            tmp = s.top();
            s.pop();
            func(tmp->data);
            tmp->processed = 2;
         }
      }
      walkPtr = walkPtr->pNextVertex;
   }
}

template <typename E> 
bool Graph<E>::isEmpty() const
{
   return first == NULL;  
}

template <typename E> 
int Graph<E>::size() const
{
   return order;  
}

template <typename E> 
bool Graph<E>::isVertex(E key) const
{
   Vertex* tmp;
   if (isEmpty()) 
      return false;
   tmp = first;
   while (tmp != NULL && cmp(key,tmp->data) != 0)
      tmp = tmp->pNextVertex;
   if (tmp == NULL)
      return false;
   return true;
}

template <typename E> 
bool Graph<E>::isEdge(E fromKey, E toKey) const
{
   //implement this function
   try {
       // protected code
       retrieveEdge(fromKey, toKey);
       return true;
   } catch( GraphException e ) {
       return false;
   }
}

template <typename E> 
bool Graph<E>::isPath(E fromKey, E toKey) const
{
   //Implement this function
   if (isEmpty())
	return false;
   if(fromKey == toKey)
        return true;
   Vertex* walkPtr = first;
   while (walkPtr != NULL)         //make all as not visited
   {
      walkPtr->processed = 0;
      walkPtr = walkPtr->pNextVertex;
   }

   Vertex* fromPtr;
   Vertex* toPtr;
   queue<Vertex*> q;
   Edge* edgeWalk;  
   Vertex* tmp;
   walkPtr=first;
   while(walkPtr!=NULL && walkPtr->data!=fromKey){
      walkPtr = walkPtr->pNextVertex;
   }
   while (walkPtr!= NULL)
   { 
      if (walkPtr->processed < 2)
      {
         if (walkPtr->processed < 1)
         {
            q.push(walkPtr); 
            walkPtr->processed = 1;
         }
      }
      while (!q.empty())
      {
          tmp = q.front();
          q.pop();
	  if (walkPtr->data==toKey)
	  {
	     return true;
	  }
          tmp->processed = 2;
          edgeWalk = tmp->pEdge; 
          while (edgeWalk != NULL)           
          {
              toPtr = edgeWalk->destination;
              if (toPtr->data == toKey)
	      { 
                  return true;
	      }
              if (toPtr->processed == 0)
              {
                  toPtr->processed = 1;
                  q.push(toPtr);
              }
              edgeWalk = edgeWalk->pNextEdge;
          }
      }
      return false;
   } 
   return false; 
}
   
template <typename E> 
int Graph<E>::countEdges() const
{
   //Implement this function
   Vertex* tmp;
   tmp = first;
   int sum=0;
   while (tmp != NULL) {
       sum += tmp->outDeg; 
       tmp = tmp->pNextVertex;
   }
   return sum;
}

template <typename E> 
int Graph<E>::outDegree(E key) const throw (GraphException)
{
   Vertex* tmp;
   if (isEmpty())
      throw  GraphException("Non-existent vertex - outDegree().");
   tmp = first;
   while (tmp != NULL && cmp(key,tmp->data) != 0)
      tmp = tmp->pNextVertex;
   if (tmp == NULL)
      throw GraphException("Non-existent vertex - outDegree().");
   return tmp->outDeg;
}

template <typename E> 
int Graph<E>::inDegree(E key) const throw (GraphException)
{
   Vertex* tmp;
   if (isEmpty())
      throw  GraphException("Non-existent vertex - inDegree().");
   tmp = first;
   while (tmp != NULL && cmp(key,tmp->data) != 0)
      tmp = tmp->pNextVertex;
   if (tmp == NULL)
      throw GraphException("Non-existent vertex - inDegree().");
   return tmp->inDeg;
}




