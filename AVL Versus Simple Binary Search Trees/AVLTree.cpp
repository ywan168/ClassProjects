/**
 * Models an AVL tree.
 * @param <E> data type of elements of the tree
 * @since 02-22-2019
 * @see AVLTree.h
 */

#include "AVLTree.h"
#include <cstdlib>
#include <iostream>
#include <queue>
#include <cmath>
#include<algorithm>
using namespace std;

/* Nested Node class definitions */

template <typename E>
AVLTree<E>::Node::Node(E s)
{
   data = s;
   left = NULL;
   right = NULL;
   bal = EH;
}

/* Outer AVLTree class definitions */

template <typename E>
AVLTree<E>::AVLTree()
{
   root = NULL;
   count = 0;
   cmp = [](E a, E b) -> int{return a < b? -1 : (a == b? 0 : 1);};
}

template <typename E>
AVLTree<E>::AVLTree(std::function<int(E,E)> fn)
{
    root = NULL;
    count = 0;
    if (cmp == nullptr) 
        cmp = fn;
}

template <typename E>
AVLTree<E>::~AVLTree()
{
   recDestroy(root);
}


template <typename E>
bool AVLTree<E>::isEmpty() const
{
   return root == NULL;
}

template<typename E>
void AVLTree<E>::insert(const E& obj)
{
   bool forTaller;
   Node* newNode = new Node(obj);
   /* If it is the first node in the tree */
   if (!inTree(obj))
      count++;
   root = insert(root, newNode, forTaller);
}

template<typename E>
bool AVLTree<E>::inTree(const E& item) const
{
   Node *tmp;
   if (isEmpty())
      return false;
   /*find where it is */
   tmp = root;
   while (1)
   {
      if (cmp(tmp->data,item) == 0)
         return true;
      if (cmp(tmp->data, item) > 0)
      {
         if (!(tmp->left))
            return false;
         /* continue searching */
         tmp = tmp->left;
      }
      else
      {
         if (!(tmp->right))
            return false;
         /* continue searching for insertion pt. */
         tmp = tmp->right;
      }
   }
}

template<typename T>
void AVLTree<T>::remove(const T& item)
{
   bool shorter;
   bool success;
   Node* newRoot;
   if (!inTree(item))
      return;
   newRoot = remove(root, item, shorter, success);
   if (success)
   {
      root = newRoot;
      count--;
   }
}

template<typename T>
const T& AVLTree<T>::retrieve(const T& key) const throw (AVLTreeException)
{
   Node* tmp;
   if (isEmpty())
      throw AVLTreeException("AVL Tree Exception: tree empty on retrieve()");
   tmp = root;
   while(true)
   {
      if (cmp(tmp->data,key) == 0)
         return tmp->data;
      if (cmp(tmp->data, key) > 0)
      {
         if (tmp->left == NULL)
            throw new AVLTreeException("AVL Tree Exception: key not in tree call to retrieve()");
         tmp = tmp->left;
      }
      else
      {
         if (tmp->right ==  NULL)
            throw new AVLTreeException("AVL Tree Exception: key not in tree call to retrieve()");
         tmp = tmp->right;
      }
   }
   //never reached
   return tmp->data;
}

template<typename T>
void AVLTree<T>::traverse(FuncType func)
{
   traverse(root,func);
}

template<typename E>
int AVLTree<E>::size() const
{
   return count;
}


template<typename E>
int AVLTree<E>::depth(const E& item) const
{
    //Implement this function, almost done!
     Node *tmp;
     if (isEmpty())
         return 0;
     tmp = root;
     int depth = 0;
     while (1)
   {
      if (cmp(tmp->data,item) == 0)
         return (depth);
      if (cmp(tmp->data, item) > 0)
      {
        /* continue searching */
         if (tmp->left)
         tmp = tmp->left;
         depth++;
      }
      else
      {
        /* continue searching for item. */
         if (tmp->right)
         tmp = tmp->right;
         depth++;
      }
   }
     return depth;
}

template<typename T>
int AVLTree<T>::height() const
{
    //Implement this method, done!
    vector<int> levels;
    levels = leavesLevels();
    int height;
    //for (std::vector<int>::iterator it = levels.begin() ; it != levels.end(); ++it)
    //std::cout << ' ' << *it;
    //std::cout << '\n';
    if(levels.size()==0){
       height=0;
    } else {
       height =*max_element(levels.begin(), levels.end());
    }
    return height;
}

template<typename T>
vector<int> AVLTree<T>::leavesLevels() const
{
    vector<int> levels;
    if (root != NULL)
    {
        leavesLevels(root,0,levels);
    }
    return levels;
}

template<typename E>
bool AVLTree<E>::isFull() const
{
    if (root == NULL)
        return true;
    if (count % 2 == 0)
        return false;    
    return isFull(root);
}


template<typename T>
bool AVLTree<T>::isComplete() const
{
    //implement this function, done!
    return (isComplete(root,0));
}


/* Private functions */

template<typename E>
void AVLTree<E>::recDestroy(Node* root)
{
   if (root)
   {
      if (root->left) recDestroy(root->left);
      if (root->right) recDestroy(root->right);
      delete root;
   }
   return;
}

template<typename E>
typename AVLTree<E>::Node* AVLTree<E>::insert(Node* curRoot, Node* newNode, bool& taller)
{
   if (curRoot == NULL)
   {
      curRoot = newNode;
      taller = true;
      return curRoot;
   }
   if (cmp(newNode->data,curRoot->data) < 0)
   {
      curRoot->left = insert(curRoot->left,newNode, taller);
      if (taller)
         switch(curRoot->bal)
         {
            case LH: // was left-high -- rotate
               curRoot = leftBalance(curRoot, taller);
               break;
            case EH: //was balanced -- now LH
               curRoot->bal = LH;
               break;  
            case RH: //was right-high -- now EH
               curRoot->bal = EH;
               taller = false;
               break;
         }
      return curRoot;
   }
   if (cmp(newNode->data,curRoot->data) > 0)
   {
      curRoot->right = insert(curRoot->right,newNode,taller);
      if (taller)
         switch(curRoot->bal)
         {
            case LH: // was left-high -- now EH
               curRoot->bal = EH;
               taller=false;
               break;
           case EH: // was balance -- now RH
              curRoot->bal = RH;
              break;
           case RH: //was right high -- rotate
              curRoot = rightBalance(curRoot,taller);
              break;
         }
      return curRoot;
   }
   else
   {
      curRoot->data = newNode->data;
      delete newNode;
      taller = false;
      return curRoot;
   }
}

template<typename E>
typename AVLTree<E>::Node* AVLTree<E>::leftBalance(Node* curRoot, bool& taller)
{
   Node* rightTree;
   Node* leftTree;   
   leftTree = curRoot->left;
   switch(leftTree->bal)
   {
      case LH: //left-high -- rotate right
         curRoot->bal = EH;
         leftTree->bal = EH;
         // Rotate right
         curRoot = rotateRight(curRoot);
         taller = false;
         break;
      case EH: // This is an error
         cerr<<"AVL Tree Error: error in balance tree in call to leftBalance()"<<endl;
         exit(-5);
         break;   
      case RH: // right-high - requires double rotation: first left, then right
         rightTree = leftTree->right;
         switch(rightTree->bal)
         {
            case LH:
               curRoot->bal = RH;
               leftTree->bal = EH;
               break;   
            case EH:
               curRoot->bal = EH;
               leftTree->bal = EH;   
               break;
            case RH:
               curRoot->bal = EH;
               leftTree->bal = LH;
               break;
         }
         rightTree->bal = EH;
         // rotate left
         curRoot->left = rotateLeft(leftTree);
         //rotate right
         curRoot = rotateRight(curRoot);
         taller= false;
   }
   return curRoot;
}

template<typename E>
typename AVLTree<E>::Node* AVLTree<E>::rightBalance(Node* curRoot, bool& taller)
{
   Node* rightTree;
   Node* leftTree;
   rightTree = curRoot->right;
   switch(rightTree->bal)
   {
      case RH: //right-high -- rotate left   
         curRoot->bal = EH;
         rightTree->bal = EH;
         // Rotate left
         curRoot = rotateLeft(curRoot);
         taller = false;
         break;
      case EH: // This is an error
         cerr<<"AVL Tree Error: error in balance tree in call to rightBalance()"<<endl;
         exit(1);
         break;
      case LH: // left-high - requires double rotation: first right, then left
         leftTree = rightTree->left;
         switch(leftTree->bal)
         {
            case RH:
               curRoot->bal = LH;
               rightTree->bal = EH;
               break;
            case EH:   
               curRoot->bal = EH;
               rightTree->bal = EH;    
               break;
            case LH:
               curRoot->bal = EH;
               rightTree->bal = RH;
               break;
         }
         leftTree->bal = EH;
         // rotate right
         curRoot->right = rotateRight(rightTree);
         //rotate left
         curRoot = rotateLeft(curRoot);
         taller = false;
   }
   return curRoot;
}

template<typename E>
typename AVLTree<E>::Node* AVLTree<E>::rotateLeft(Node* node)
{
   Node* tmp;
   tmp = node->right; 
   node->right = tmp->left;
   tmp->left = node;
   return tmp;
}

template<typename E>
typename AVLTree<E>::Node* AVLTree<E>::rotateRight(Node* node)
{
   Node* tmp;
   tmp = node->left;
   node->left = tmp->right;
   tmp->right = node;
   return tmp;
}   


template<typename E>
void AVLTree<E>::traverse(Node* node, FuncType func)
{
   if (node)
   {
      traverse(node->left,func);
      func(node->data);
      traverse(node->right,func);
   }
}


template<typename E>
typename AVLTree<E>::Node* AVLTree<E>::remove(Node* node,const E& key, bool& shorter, bool& success)
{
   Node* delPtr;   
   Node* exchPtr;
   Node* newRoot;
   if (node == NULL) 
   {
      shorter = false;
      success = false;
      return NULL;
   }
   if (cmp(key,node->data) < 0)
   {
      node->left = remove(node->left,key,shorter,success);
      if (shorter)
         node = deleteRightBalance(node,shorter);
   }
   else if (cmp(key,node->data) > 0)
   {
      node->right = remove(node->right,key,shorter,success);
      if (shorter)
         node = deleteLeftBalance(node,shorter);
   }
   else
   {
      delPtr = node;
      if (node->right == NULL)
      {
         newRoot = node->left;
         success = true;
         shorter = true;
         delete delPtr;
         return newRoot;
      }
      if(node->left == NULL)
      {
         newRoot = node->right;
         success = true;
         shorter = true;
         delete delPtr;
         return newRoot;
      }
      else
      {
         exchPtr = node->left;
         while(exchPtr->right != NULL)
            exchPtr = exchPtr->right;
         node->data = exchPtr->data;
         node->left = remove(node->left,exchPtr->data,shorter,success);
         if (shorter)
            node = deleteRightBalance(node,shorter);
      }
   }
   return node;
}


template<typename E>
typename AVLTree<E>::Node* AVLTree<E>::deleteRightBalance(Node* node,bool& shorter)
{
   Node* rightTree;
   Node* leftTree;
   switch(node->bal)
   {
      case LH: //deleted left -- now balanced  
         node->bal = EH;
         break;
         case EH: //now right high
         node->bal = RH;
         shorter = false;
         break;
      case RH: // right high -- rotate left
         rightTree = node->right;
         if (rightTree->bal == LH)
         {
            leftTree = rightTree->left;
            switch(leftTree->bal)
            {
               case LH:
                  rightTree->bal = RH;
                  node->bal = EH;
                  break;
               case EH:
                  node->bal = EH;
                  rightTree->bal = EH;
                  break;
               case RH:
                  node->bal = LH;
                  rightTree->bal = EH;
                  break;
            }
            leftTree->bal = EH;
            //rotate right, then left
            node->right = rotateRight(rightTree);
            node = rotateLeft(node);
         }
         else
         {
            switch(rightTree->bal)
            {
               case LH: 
               case RH:
                  node->bal = EH;
                  rightTree->bal = EH;
                  break;
               case EH:
                  node->bal = RH;
                  rightTree->bal = LH;
                  shorter = false;
                  break;
            }
            node = rotateLeft(node);
         }
      }
   return node;
}

template<typename E>
typename AVLTree<E>::Node* AVLTree<E>::deleteLeftBalance(Node* node,bool& shorter)
{
   Node* rightTree;
   Node* leftTree;
   switch(node->bal)
   {
      case RH: //deleted right -- now balanced  
         node->bal = EH;
         break;
      case EH: //now left high
         node->bal = LH;
         shorter = false;
         break;
      case LH: // left high -- rotate left
         leftTree = node->left;
         if (leftTree->bal == RH)
         {
            rightTree = leftTree->right;
            switch(rightTree->bal)
            {
               case RH:
                  leftTree->bal = LH;
                  node->bal = EH;
                  break;
               case EH:
                  node->bal = EH;
                  leftTree->bal = EH;
                  break;
               case LH:
                  node->bal = RH;
                  leftTree->bal = EH;
                  break;
            }
            rightTree->bal = EH;
            //rotate left, then right
            node->left = rotateLeft(leftTree);
            node = rotateRight(node);
         }
         else
         {
            switch(leftTree->bal)
            {
               case RH: 
               case LH:
                  node->bal = EH;
                  leftTree->bal = EH;
                  break;
               case EH:
                  node->bal = LH;
                  leftTree->bal = RH;
                  shorter = false;
                  break;
            }
            node = rotateRight(node);
         }
      }
   return node;
}

template<typename E>
void AVLTree<E>::leavesLevels(Node* node, int level, vector<int>& levels) const
{
    //Implement this method, done!
    /*if an empty*/
    if (node == NULL)
        return;
    /*if has no children*/
    if (node->left == NULL && node->right == NULL)
    {
        //cout << node->data << " ";
	levels.push_back(level);
        return;
    }
    /*if has left child*/
    if (node->left)
        leavesLevels(node->left,level+1, levels);
    /*if has right child*/
    if (node->right)
        leavesLevels(node->right,level+1, levels);
}

template<typename E>
bool AVLTree<E>::isFull(Node* node) const
{
   //Implement this method, done!
    /*empty*/
    if (node == NULL)
        return true;
    /*leaf node*/
    if (node->left == NULL && node->right == NULL)
        return true;
    /*both left and right node are not null, and left & right subT are full*/
    if (node->left && node->right)
        return (isFull(node->left) && isFull(node->right));
    /*if none of above conditions work*/            
    else return false;
}


template<typename E>
bool AVLTree<E>::isComplete(Node* node, int index) const
{
    //Implement this method, done!
    if (node == NULL)
        return true;
    if (index >= count)
        return false;
    return (isComplete(node->left, 2*index+1) && isComplete(node->right, 2*index+2));
}
