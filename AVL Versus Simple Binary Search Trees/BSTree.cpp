/**
 * Models an binary search tree.
 * @param <E> data type of elements of the tree
 * @since 03-03-2019
 * @see BSTree.h
*/

#include "BSTree.h"
#include <cstdlib>
#include <iostream>
#include <queue>

using namespace std;

/* Nested Node class definitions */

template <typename E>
BSTree<E>::Node::Node(E s)
{
   data = s;
   left = NULL;
   right = NULL;
}

/* Outer BSTree class definitions */

template <typename E>
BSTree<E>::BSTree()
{
   root = NULL;
   count = 0;
   cmp = [](E a, E b) -> int{return a < b? -1 : (a == b? 0 : 1);};   
}

template <typename E>
BSTree<E>::BSTree(std::function<int(E,E)> fn)
{
    root = NULL;
    count = 0;
    if (cmp == nullptr) 
        cmp = fn;
}

template <typename E>
BSTree<E>::~BSTree()
{
   recDestroy(root);
}

template <typename E>
bool BSTree<E>::isEmpty() const
{
   return root == NULL;
}

template<typename E>
void BSTree<E>::insert(E item)
{
   Node* tmp;
   Node* newnode = new Node(item);
   /* If it is the first node in the tree */
   if (isEmpty())
   {
      root = newnode;
      count++;
      return;
   }
   /*find where it should go */
   tmp = root;
   while (1)
   {
      if (cmp(tmp->data,item) == 0)
      { /* Key already exists. */
         tmp->data = item;
         delete newnode; /* don’t need it */
         return;
      }
      else if (cmp(tmp->data, item) > 0)
      {
         if (!(tmp->left))
         {
            /* If the key is less than tmp */
            tmp->left = newnode;
            count++;
            return;
         }
         else
         {
            /* continue searching for insertion pt. */
            tmp = tmp->left;
         }
      }
      else
      {
         if (!(tmp->right))
         {
            /* If the key is greater than tmp */
            tmp->right = newnode;
            count++;
            return;
         }
         else
         /* continue searching for insertion point*/
            tmp = tmp->right;
      }
   }
}

template<typename E>
bool BSTree<E>::inTree(E item) const
{
   Node* tmp;
   if (isEmpty())
      return false;
   /*find where it is */
   tmp = root;
   while (1)
   {
      if (cmp(tmp->data, item) == 0)
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

template<typename E>
void BSTree<E>::remove(const E& item)
{
   Node* nodeptr;
   nodeptr = search(item);
   if (nodeptr)
   {
      remove(nodeptr);
      count--;
   }
}

template<typename E>
const E& BSTree<E>::retrieve(const E& key) const throw (BSTreeException)
{
   Node* tmp;
   if (isEmpty())
      throw BSTreeException("Binary Search Tree Exception: tree empty on retrieve()");
   tmp = root;
   while(tmp)
   {
      if (cmp(tmp->data, key) == 0)
         return tmp->data;
      if (cmp(tmp->data, key) > 0)
         tmp = tmp->left;
      else
         tmp = tmp->right;
   }
   if (tmp == NULL)
      throw BSTreeException("Binary Search Tree Exception: key does not exist on retrieve()");
   return tmp->data;
}

template<typename E>
void BSTree<E>::traverse(FuncType func)
{
   traverse(root,func);
}

template<typename E>
int BSTree<E>::size() const
{
   return count;
}

template<typename E>
int BSTree<E>::depth(const E& item) const
{
    //Implement this function
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

template<typename E>
int BSTree<E>::height() const
{
   return height(root);
}

template<typename E>
vector<int> BSTree<E>::leavesLevels() const
{
    vector<int> levels;
    if (root != NULL)
    {
        leavesLevels(root,0,levels);
    }
    return levels;
}

template<typename E>
bool BSTree<E>::isFull() const
{
   if (root == NULL)
      return true;
   if (count % 2 == 0)
       return false;   
   return isFull(root);    
}

template<typename T>
bool BSTree<T>::isComplete() const
{
   //implement this function
   return (isComplete(root,0));

}

template<typename E>
void BSTree<E>::recDestroy(Node* root)
{
   if (root)
   {
      if (root->left) recDestroy(root->left);
      if (root->right) recDestroy(root->right);
      delete root;
   }
}

template<typename E>
typename BSTree<E>::Node* BSTree<E>::findParent(Node* node)
{
   Node* tmp;
   tmp = root;
   if (tmp == node)
      return NULL;
   while(1)
   {
      assert(cmp(tmp->data, node->data) != 0);
      if (cmp(tmp->data, node->data) > 0)
      {
         assert(tmp->left != NULL);
         if (tmp->left == node)
            return tmp;
         tmp = tmp->left;
      }
      else
      {
         assert(tmp->right != NULL);
         if (tmp->right == node)
            return tmp;
         tmp = tmp->right;
      }
   }
}

template<typename E>
void BSTree<E>::traverse(Node* node, FuncType func)
{
   if (node)
   {
      traverse(node->left,func);
      func(node->data);
      traverse(node->right,func);
   }
}

template<typename E>
bool BSTree<E>::remove(Node* node)
{
   E data;
   Node* parent;
   Node* replacement;
   parent = findParent(node);
   
   if (node->left && node->right)
   {
      replacement = node->right;
      while (replacement->left)
         replacement = replacement->left;
      data = replacement->data;
      remove(replacement);
      node->data = data;
      return true;
   }
   else
   {
       if (node->left)
          replacement = node->left;
       else if (node->right)
          replacement = node->right;
       else
          replacement = NULL;
       if (!parent)
          root = replacement;
       else if (parent->left == node)
          parent->left = replacement;
       else
          parent->right = replacement;
       delete node;
       return true;
   }
}

template<typename E>
typename BSTree<E>::Node* BSTree<E>::search(const E& item)
{
   Node* tmp;
   tmp = root;
   while(tmp)
   {
      if (cmp(tmp->data, item) == 0)
         return tmp;
      if (cmp(tmp->data, item) > 0)
         tmp = tmp->left;
      else
         tmp = tmp->right;
   }
   return tmp;
}

template<typename E>
int BSTree<E>::height(Node* node) const
{
    //Implement this function, done!
    //if(node==NULL)
    //   return 0;
    //else
    //{  int lb=height(node->left);
    //   int rb=height(node->right);
    //   return max(lb,rb)+1;
    //}
    if(node==NULL){
        return (-1);
    }
    else if (node->left==NULL && node->right==NULL)
        return (0);
    else {
        int lheight = height(node->left);
        int rheight = height(node->right);
        /*use the larger height*/
        if (lheight > rheight)
            return (lheight+1);
        else return (rheight+1);
    }
}

template<typename E>
void BSTree<E>::leavesLevels(Node* node, int level, vector<int>& levels) const
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
bool BSTree<E>::isFull(Node* node) const
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
bool BSTree<E>::isComplete(Node* node, int index) const
{
    //Implement this method, done!
    if (node == NULL)
        return true;
    if (index >= count)
        return false;
    return (isComplete(node->left, 2*index+1) && isComplete(node->right, 2*index+2));
	
}





