/**
 * Performs insertions and searches, using the same data set,on a binary search
 * tree and an AVL tree to compare the empirically compare the performance of
 * these operations on the trees.
 * @author YOUR NAME
 * @SEE AVLTree.cpp,BSTree.cpp, WordStat.h
 * @since DATE LAST MODIFIED
 */
#include <iostream>
#include <cstdlib>  
#include <stdexcept>
#include <iomanip>
#include <fstream> 
#include<algorithm>
#include "AVLTree.h"
#include "BSTree.h"
#include "AVLTree.cpp"
#include "BSTree.cpp"

using namespace std;

/**
 * Converts the specified string to uppercase
 * @param w a string
 * @return the uppercase version of the specified string
 */
string toUpper(string w)
{
   transform(w.begin(), w.end(),w.begin(),::toupper);
   return w;
}

//[](const string& item)->void {printf("%\n", data);};
//FuncType print = &printNode;

int main(int argc, char** argv) 
{
    //Implement this function
   std::string input_file = "default";
   if (argc == 2) { 
     input_file = argv[1]; 
   } else {
     cout << "Please check your arguments." << endl;
     cout << "The first argument should be input file name" << endl; 
     return 0;   
   }
   AVLTree<std::string> avl_tree;
   BSTree<std::string> bs_tree;
   
   std::ifstream infile;
   infile.open(input_file);
   std::string op,content;
   vector<int> leavesLevels;
   if(!infile.fail() & !cout.fail()){
        while(true)
        {
	   infile>> op;
	   if( infile.eof() ) break;
	   if(op == "insert"){
	      infile>>content;
              avl_tree.insert(content);

	      cout << "inserted:  " << toUpper(content) << " in the AVL" <<endl;
	      bs_tree.insert(content);
	      cout << "inserted:  " << toUpper(content) << " in the BST"<<endl;
              cout << "Type:" << std::setw(8) << "size" << std::setw(8) << "height" << std::setw(8) << "full?" << std::setw(8) \
		      << "  complete?" << endl;
              cout << "AVL:" << std::setw(8) << avl_tree.size() << std::setw(8) << avl_tree.height() << std::setw(8) << \
		      (avl_tree.isFull()? "true":"false") << std::setw(8) << (avl_tree.isComplete()?"true": "false") <<endl;
              cout << "BST:" << std::setw(8) << bs_tree.size() << std::setw(8) << bs_tree.height() << std::setw(8)<< \
		      (bs_tree.isFull()? "true":"false") << std::setw(8) << (bs_tree.isComplete()?"true": "false") <<endl;
	      cout << "               " << endl;

	      cout << "AVL:" <<endl;
	      leavesLevels.clear();
	      leavesLevels = avl_tree.leavesLevels();
	      cout << "Number of Leaf Nodes: " << leavesLevels.size() <<endl;
	      cout << "Levels of Leaf Nodes:";
	      for(auto it = leavesLevels.begin();it != leavesLevels.end(); ++it){
	         cout << " " << *it;
	      }  
	      cout << endl;
	      cout << "BST:" <<endl;
              leavesLevels.clear();
	      leavesLevels = bs_tree.leavesLevels();
	      cout << "Number of Leaf Nodes: " << leavesLevels.size() <<endl;
	      cout << "Levels of Leaf Nodes:";
	      for(auto it = leavesLevels.begin();it != leavesLevels.end(); ++it){
	         cout << " " << *it;
	      }  
	      cout << endl;
	      cout << "      " <<endl;

	   } else if (op == "remove"){
              // conduct remove operation
	      infile>>content;

	      cout << "removed: " << toUpper(content) << " from a depth of " << avl_tree.depth(content) << " in the AVL" <<endl;
	      avl_tree.remove(content);
	      cout << "removed: " << toUpper(content) << " from a depth of " << bs_tree.depth(content) << " in the BST" <<endl;
              bs_tree.remove(content);
              cout << "Type:" << std::setw(8) << "size" << std::setw(8) << "height" << std::setw(8) << "full?" << std::setw(8) \
		     << "  complete?" << endl;
	      cout << "AVL:" << std::setw(8) << avl_tree.size()<< std::setw(8) << avl_tree.height() << std::setw(8) \
		      <<(avl_tree.isFull()? "true":"false") << std::setw(8) << (avl_tree.isComplete()?"true": "false") <<endl;
              cout << "BST:" << std::setw(8) << bs_tree.size() << std::setw(8) << bs_tree.height() << std::setw(8) \
		      << (bs_tree.isFull()? "true":"false") << std::setw(8) << (bs_tree.isComplete()?"true": "false") <<endl;
	      cout << "     " <<endl;

              cout << "AVL:" <<endl;
	      leavesLevels.clear();
	      leavesLevels = avl_tree.leavesLevels();
	      cout << "Number of Leaf Nodes: " << leavesLevels.size() <<endl;
	      cout << "Levels of Leaf Nodes:";
	      for(auto it = leavesLevels.begin();it != leavesLevels.end(); ++it){
	         cout << " " << *it;
	      }  
	      cout << endl;
	      cout << "BST:" <<endl;
              leavesLevels.clear();
	      leavesLevels = bs_tree.leavesLevels();
	      cout << "Number of Leaf Nodes: " << leavesLevels.size() <<endl;
	      cout << "Levels of Leaf Nodes:";
	      for(auto it = leavesLevels.begin();it != leavesLevels.end(); ++it){
	         cout << " " << *it;
	      }  
	      cout << endl;
	      cout << "         " <<endl;

	   } else if (op == "traverse"){
	      // conduct traverse operation
	      cout << "AVL  (in-order): " << endl;
              avl_tree.traverse([](const string& item)->void {string strUpper = toUpper(item); cout << strUpper <<endl;});
	      cout << "------------------------------" << endl;
	      cout << "word count: " << avl_tree.size() << endl;
	      cout << endl;
	      cout << "BST  (in-order): " << endl;
	      bs_tree.traverse([](const string& item)->void {string strUpper = toUpper(item); cout<< strUpper <<endl;});
	      cout << "------------------------------" << endl;
	      cout << "word count: " << bs_tree.size() << endl;
	      cout << "      " << endl;
	   }	   
       }
   }   
   else{
       cerr<< "Error opening" <<endl;
       exit(1); 
   }
   infile.close();
   return 0;
}

