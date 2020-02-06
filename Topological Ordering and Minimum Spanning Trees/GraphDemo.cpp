/**
 * A test bed for methods of a  weighted diagraph and implementations of 
 * basic WDAG algorithms.
 * Course: CS3102.01
 * Programming Project #: 4
 * @since 04-22-2019
 * @see Graph.cpp, Graph.h, City.h
 */

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <fstream>
#include <limits>
#include <iomanip>
#include <string>
#include <queue>
#include <functional>
#include <vector>
#include <algorithm>
#include "City.h"
#include "Graph.h"
#include "Graph.cpp"
#include <map>

using namespace std;

#define INFINITY numeric_limits<double>::max()

int int_max = std::numeric_limits<int>::max();
int int_min = std::numeric_limits<int>::min();

/* function prototypes */   
Graph<City> readGraph(string filename);
int menu();
void floyd(const Graph<City>& g, double**& dist, int**& path);
Graph<City> complement(const Graph<City>& g) throw (GraphException);
int* isBipartite(const Graph<City>& g, bool& bipartite) throw (GraphException);
void dfsOut(const Graph<City>& g, int v, bool seen[],const int linearOrder[], int& index);
int* topoSort(const Graph<City>& g);
double  primMST(const Graph<City>& g, int root, int* parent) throw (GraphException);
string trim(string text);

int main(int argc, char **argv)
{
   if (argc != 2)
   {
      cout<<"Usage: GraphDemo <filename>"<<endl;
      exit(1);
   }
   Graph<City> g;
   Graph<City> gPrime;
   City aCity1, aCity2;
   int menuReturnValue, i, j,k;   
   g= readGraph(argv[1]);
   cout << "Read Graph"; 
   gPrime = complement(g);
   cout << "Get Complement";
   long s = g.size();
   menuReturnValue = -1;
   // cout<<"   cout edges:" << g.countEdges()<<endl;
   while (menuReturnValue != 0)
   {
      menuReturnValue = menu();
      cout << menuReturnValue;
      switch(menuReturnValue)
      {
          case 1: //Incidence Matrix for G'
            {
              //write code to generate the incidence matrix of of G
              //set column width to 3
              cout<<endl;
              cout<<"Incidence Matrix of the Directed Graph In "<<argv[1]<<endl;
              cout<<endl;
              //Add code here
	      int Nedges = g.countEdges();
	      int Nvertex = g.size();
	      map<int, vector<int>> memo;
	      vector<vector<int>> incimatrix(Nvertex, vector<int>(Nedges,0));
	      int edgeNum = 0;
              for (int i = 0; i < Nvertex; i++){
                  for (int j = 0; j < Nvertex; j++){
                      if (i != j){
                          if (g.isEdge(City(i+1),City(j+1))){
                              memo[edgeNum] = vector<int>{i, j};
	     		      edgeNum++;
                          }
	     	      }
	     	  }
	      }
	      
              if (memo.size() != Nedges)
	     	      return 1;
	      // assign value to matrix
	      for (i = 0; i < Nedges; i++){

	     	      int from = memo[i][0];
	     	      int to = memo[i][1];
	     	      incimatrix[from][i] = 1;
	     	      incimatrix[to][i] = -1;
	      }
	      for (i = 0; i < Nvertex; i++){
	     	      for (j = 0; j < Nedges; j++){
	     		      cout<< setw(3)<<right<<incimatrix[i][j];
	     	      }
	     	     cout<<endl;
	      }
              //End add code here
              cout<<endl<<"The graph has "<<g.countEdges()<<" edges and its complement has "<<gPrime.countEdges()<<" edges.";
              cout<<endl<<endl<<endl;  
            } 
            break;
          case 2://All-pairs Shortest-path algorithm
	    {
              cout<<endl;
              cout<<"Enter the source vertex: ";
              cin>>i;
              cout<<"Enter the destination vertex: ";  
              cin>>j;
              double wt;

              if (g.isPath(City(i), City(j)) && g.isPath(City(j), City(i)))
              {
                double** cost = new double*[(int)g.size()];
                int** path = new int*[(int)g.size()];
                for (k=0; k<g.size(); k++)
                {
                  cost[k] = new double[(int)g.size()];
                  path[k] = new int[(int)g.size()];
                }		
                floyd(g,cost,path);

                int initial = i, dest;
                string srcCity = trim(g.retrieveVertex(City(i)).getLabel());             
                string destCity = trim(g.retrieveVertex(City(j)).getLabel());
                cout<<"Shortest round trip from "<<srcCity<<" to "<<destCity<<":"<<endl;               
                cout<<"========================================================================================="<<endl;
                //Add code here to print each leg of the trip from the source to the destination
                //using the format below, where the columns are left-aligned and the distances
                //are displayed to the nearest hundredths.
                //For example:
               //Baton Rouge -> New Orleans:
                //Baton Rouge            ->   Gonzales                  10.20 mi
                //Gonzales               ->   Metaire                   32.00 mi
               //Metaire                ->   New Orleans                7.25 mi
               //Distance: 49.75 mi
               //
               //New Orleans -> Baton Rouge:
               //New Orleans            ->   Metaire                    8.00 mi
               //Metaire                ->   Gonzales                  33.00 mi
               //Gonzalen               ->   Baton Rouge               10.00 mi
               //Distance: 51.00 mi
               //=================================================================
               //Round Trip Distance: 100.75 mi
               
                cout<<srcCity<<"  ->  "<<destCity<<": "<<endl;
		int tmp_i = i;
		int tmp_j = j;
	        	
		while(true){
		     int midpoint = path[tmp_i-1][tmp_j-1];
		     // We update the destination with the midpoint until the midpoint equals to the source.
		     // That means we find and print the subpath starting from source
		     if (midpoint == tmp_i && midpoint != -1 ){
		         cout<<setw(15)<<left<<trim(g.retrieveVertex(City(midpoint)).getLabel())
		            <<setw(15)<<left<<"->"
			    <<setw(15)<<left<<trim(g.retrieveVertex(City(tmp_j)).getLabel())
			    <<setw(2)<<left<<setprecision(2)<<fixed
			    <<cost[tmp_i-1][tmp_j-1]<<" miles"<<endl;
			 tmp_i = tmp_j; //the source is updated by the destination of previous subpath
			 tmp_j = j; //the destination is updated by the real destination
			 if( path[tmp_i-1][tmp_j-1] == tmp_i ) // when the midpoint equals to the source, teminate the loop.
		         {
                               cout<<setw(15)<<left<<trim(g.retrieveVertex(City(tmp_i)).getLabel())
		                 <<setw(15)<<left<<"->"
			         <<setw(15)<<left<<trim(g.retrieveVertex(City(j)).getLabel())
			         <<setw(2)<<left<<setprecision(2)<<fixed
				 <<cost[tmp_i-1][j-1]<<" miles"<<endl;
		               break;
		         }
                         if( path[tmp_i-1][tmp_j-1] == -1 ) // when the midpoint equals to -1, teminate the loop. source==destination
		         {
		               break;
		         }
		     }
		     else {
		         tmp_j=midpoint;
		     }
		}
		cout<<"Distance: "<<setprecision(2)<<cost[i-1][j-1]<<" miles."<<endl;
		cout<<endl;

                // the oposite way
		cout<<destCity<<"  ->  "<<srcCity<<": "<<endl;
                tmp_j = j;
		while (true){
			int midpoint = path[tmp_j-1][i-1];
                        if (midpoint == tmp_j){
                           cout<<setw(15)<<left<<trim(g.retrieveVertex(City(tmp_j)).getLabel())
		               <<setw(15)<<left<<"->"
			       <<setw(15)<<left<<trim(g.retrieveVertex(City(i)).getLabel())
			       <<setw(2)<<left<<setprecision(2)<<fixed
			       <<cost[tmp_j-1][i-1]<<" miles"<<endl;
			   break;
                        }
		        cout<<setw(15)<<left<<trim(g.retrieveVertex(City(tmp_j)).getLabel())
		        <<setw(15)<<left<<"->"
		        <<setw(15)<<left<<trim(g.retrieveVertex(City(midpoint)).getLabel())
		        <<setw(2)<<left<<setprecision(2)<<fixed
			<<cost[tmp_j-1][midpoint-1]<<" miles"<<endl;
		        tmp_j = midpoint; 
		}
                cout<<"Distance: "<<setprecision(2)<<cost[j-1][i-1]<<" miles."<<endl;
		cout<<endl;
                //End code                                        
                cout<<"========================================================================================="<<endl;
                cout<<"Round Trip Distance: "<<setprecision(2)<<cost[i-1][j-1]+cost[j-1][i-1]<<" miles."<<endl<<endl;
                for (i = 0; i < g.size(); i++) delete[] cost[i];
                for (i = 0; i < g.size(); i++) delete[] path[i];
                delete[] cost;
                delete[] path;
              }
              else
                cout<<"A round trip is not possible."<<endl<<endl;
              cin.ignore(numeric_limits<streamsize>::max(), '\n'); //flush the end-of-line character
	    }
            break;
         case 3: //post-order depth-first-search traversal of G complement
	    {
              cout<<endl;
              cout<<"PostOrder DFS Traversal of the Complement of the Graph In "<<argv[1]<<endl;
              cout<<"==============================================================="<<endl;
            //invoke the dfsTraverse function
            // Output should be aligned in two-column format as illustrated below:
            // 1     Charlottetown
            // 4     Halifax
            // 2     Edmonton   
              gPrime.dfsTraverse([](const City& item)->void {cout<<item.getKey() <<"    "<< item.getLabel() <<endl;});
            
              cout<<"==============================================================="<<endl;
              cout<<endl;
              cout<<endl;
	    }
            break;
         case 4: //breadth-first-search traversal
	    {
              cout<<endl;
              cout<<"BFS Traversal of the complement of theGraph In "<<argv[1]<<endl;
              cout<<"==============================================================="<<endl;
              //invoke the bfsTraverse function
              // Output should be aligned in two-column format as illustrated below:
              // 1     Charlottetown
              // 4     Halifax
              // 2     Edmonton  
              //gComp.bfsTraverse([](const string& item)->void {string strUpper=toUpper(item);
              //cout<<g.retrieveVertex(City.getLabel()) <<endl;});
              gPrime.bfsTraverse([](const City& item)->void {cout<<item.getKey() <<"    "<< item.getLabel() <<endl;});
          
              cout<<"==============================================================="<<endl;
              cout<<endl;
              cout<<endl;
	    }
            break;
         case 5: //Check whether g is Bipartite
	    {
              cout<<endl;
              bool bip;
              int* part;
              part = isBipartite(g,bip);
              if (bip)
              {
                if (g.size() == 0)
                    cout<<"An empty graph is vacuously bipartite."<<endl;
                else
                {
                    cout<<"The Graph is Bipartite."<<endl<<endl;
                    cout<<"First Partition: "<<endl;
                    for (i = 1; i <= g.size(); i++)
                    {
                        if (part[i] == 1)
                            cout<<i<<". "<<trim(g.retrieveVertex(City(i)).getLabel())<<endl;
                    }
                    cout<<endl;
                    cout<<"Second Partition: "<<endl;
                    k = 0;
                    for (i = 1; i <= g.size(); i++)
                    {
                        if (part[i] == 0)
                        {
                            cout<<i<<". "<<trim(g.retrieveVertex(City(i)).getLabel())<<endl;
                            k++;
                        }
                    }
                    if (k == 0)
                        cout<<"EMPTY"<<endl;
                }
              }
              else
                cout<<"The graph is not bipartite."<<endl;                        
              delete[] part;
              cout<<endl;
	    }
            break;
         case 6: //topoSort
	    {
              cout<<endl;
              int* top = topoSort(g);
              if (top)
              {
                cout<<"Topological Sorting of The Graph In "<<argv[1]<<endl;
                cout<<"==============================================================="<<endl;
                for (i=1; i<=g.size(); i++)
                {
                    aCity1 = g.retrieveVertex(City(top[i-1]));
                    cout<<left<<setw(3)<<aCity1.getKey()<<" "<<left<<setw(2)<<trim(aCity1.getLabel())<<endl;
                }
                cout<<"==============================================================="<<endl;
              }
              else
                cout<<"No topological ordering possible. The digraph in "<<argv[1]<<" contains a directed cycle."<<endl;
              //delete[] top;
              cout<<endl<<endl;
	    }
            break;
         case 7: //primlMST
	    {   
              cout<<"Enter the root of the MST: ";
              cin>>j;             
              int *mst = new int[(int)g.size()];
              double totalWeight = primMST(g,j,mst);
              string cityName1, cityName2;
              cout<<endl;
              for (i=1; i<=g.size(); i++)
              {
                if (mst[i-1] < 1)
                    cityName1 = "NONE";
                else
                    cityName1 = g.retrieveVertex(City(mst[i-1])).getLabel();
                cityName2 = g.retrieveVertex(City(i)).getLabel();
                //cityName1[cityName1.length()-1]='\0';cityName2[cityName2.length()-1]='\0';
                cout<<i<<"-("<<trim(cityName2)<<")"<<" parent["<<i<<"] <- "<<mst[i-1]<<" ("<<trim(cityName1)<<")"<<endl;
              }
              cout<<"The weight of the minimum spanning tree/forest is "<<fixed<<setprecision(2)<<totalWeight<<" miles."<<endl<<endl;
              delete[] mst;
              cin.ignore(numeric_limits<streamsize>::max(), '\n'); //flush the end-of-line character
	    }  
            break;
      }
   }
   return 0;
}   

/**
 * Removes leading and trailing whitespace characters from the specified string
 * @param text a string
 * @return the specified string without leading and trailing whitespace characters
 */
string trim(string text)
{
    const auto startIndex = text.find_first_not_of(" \t\r\n");
    if (startIndex == string::npos) text = "";
    const auto endIndex = text.find_last_not_of(" \t\r\n");
    text = text.substr(startIndex, endIndex - startIndex+1);
    return text;
}

/**
   This function reads a text file formatted as described in the project 
   description.
   @param filename the name of the DIMACS formatted graph file.
   @return an instance of a graph.
*/
Graph<City> readGraph(string filename)
{
   fstream inFile;
   char temp;
   string tmp;
   int key,v1, v2, size=0, nEdges=0;
   double weight;
   inFile.open(filename.c_str());
   if (inFile.fail())
   {
      cerr<<"Error opening "<<filename<<endl;
      exit(1);
   }
   Graph<City> newGraph;
   while (inFile >> temp)
   {
      if (temp == 'p')
      {
         inFile>>size;
         inFile>>nEdges;
      }
      if (temp == 'c')
      {
         getline(inFile,tmp);
      }
      if (temp == 'n')
      {
         inFile>>key;
         getline(inFile,tmp);
         newGraph.insertVertex(City(key,tmp.c_str()));
      }

      if (temp == 'e')
      {
         inFile>>v1;
         inFile>>v2;
         inFile>>weight;
         newGraph.insertEdge(City(v1),City(v2),weight);
      }
   }
   inFile.close();
   return newGraph;
}

/**
   This function displays the menu interface for the weighted
   digraph application.
   @return an integer representing the menu option selected.
*/
int menu()
{
   string option; 
   do
   {
      cout<<"  BASIC WEIGHTED GRAPH APPLICATION   "<<endl;
      cout<<"====================================="<<endl;
      cout<<"[1] Incidence Matrix of G"<<endl;
      cout<<"[2] Floyd's Shortest Round Trip in G"<<endl;
      cout<<"[3] Postorder DFS Traversal of G Complement"<<endl;
      cout<<"[4] BFS Traversal of G Complement"<<endl;
      cout<<"[5] Check whether G is Bipartite"<<endl;
      cout<<"[6] Topological Ordering of V(G)"<<endl;
      cout<<"[7] Prim's Minimum Spanning Tree in G"<<endl;
      cout<<"[0] Quit"<<endl;
      cout<<"====================================="<<endl;
      cout<<"Select an option: ";
      getline(cin,option);
      option = trim(option);
      if (option < "0" || option > "7")
         cout<<"Invalid option...Try again"<<endl<<endl;
      else
         return atoi(option.c_str());      
   }while(true);
}

/**
 * This method creates the complement graph of the specified digraph,
 * that is a digraph whose vertices are the same but has edge (i,j)
 * if and only if (i,j) is not an edge in g, vice versa; this method should preserve
 * the specified graph and not mutate it while creating its complement.
 * @param g a directed graph (without loops)
 * @return an instance of a graph representing the complement of the 
 * specified graph with the weights set to 1
 * @throws GraphException
 */
Graph<City> complement(const Graph<City>& g) throw (GraphException)
{   
    //implement this method
   Graph<City> complementGraph;
    int i, j;
    if(!g.isEmpty()){
      for (i = 1; i <= g.size(); i++){
        complementGraph.insertVertex(g.retrieveVertex(i));
      }
      for (i = 1; i <= g.size(); i++){
        for (j = 1; j <= g.size(); j++){
            if (i != j){
                if (!g.isEdge(City(i),City(j))){
                    complementGraph.insertEdge(City(i),City(j),1);
                } else if (g.isEdge(i,j) && g.isEdge(j,i)){
                    complementGraph.deleteEdge(i,j);
                } else { 
	            complementGraph.insertEdge(City(j),City(i),1);
		}
            }
        }
      }
      return complementGraph;
    } else {
      throw  GraphException("Graph cannot be empty!");
    }
    //return NULL; 
    
}

/**
 * Determines whether an undirected graph is bipartite
 * @param g an undirected graph
 * @param bipartite is true if g is bipartite, otherwise false
 * @return an array of size |G|+1. The first entry is |G| and the remaining 
 * entries are in {0,1} when g is bipartite where [i] = 0 if vertex i
 * is in the first partition and 1 if it is in the second partition;
 * if g is not bipartite NULL returned.
 */
int* isBipartite(const Graph<City>& g, bool& bipartite) throw (GraphException)
{
    
     ///implement this method (Project # 4)
    //vector<int> colorArr(g.size()+1, -1);
    int *colorArr = new int[(int)g.size() + 1];
    vector<int> visited(g.size(), 0);
    //cout<< colorArr <<endl;
    
     for (int i = 0; i <= g.size(); i++)
    {
	    colorArr[i] = -1;
    }
    
    colorArr[0] = g.size();
    colorArr[1] = 1;
    //cout << colorArr <<endl;
    queue <int> q;
    q.push(1);
    while (!q.empty())
    {
	    // Dequeue a vertxt from queue
	    int u = q.front();
	    q.pop();

	    //return false if there is a self loop
	    if (g.isEdge(u,u) == 1)
		    return NULL;
	    for (int v = 1; v <= g.size(); v++)
	    {
		    // is Edge is true from u to v; and destination is not colored
		    if (g.isEdge(u,v) || g.isEdge(v,u) && colorArr[v] == -1)
		    {
			    // assign alternate color to this adjacent v of u
			    colorArr[v] = 1 - colorArr[u];
			    q.push(v);
		    }
		    else if (g.isEdge(u,v) || g.isEdge(v,u) && colorArr[v] == colorArr[u])
		    {
                            bipartite = false;
			    return NULL;

		    }
	    }
    }
    //bipartite = true;
    // return colorArr if bipartite is true
    if (bipartite == true)
    {
	    return colorArr;
    }
    else
	    return NULL;    
}

/**
   This method computes the cost and path matrices using the
   Floyd all-pairs shortest path algorithm.
   @param g an instance of a weighted directed graph.
   @param dist a matrix containing distances between pairs of vertices.
   @param path a matrix of intermediate vertices along the path between a pair
   of vertices. 0 indicates that the two vertices are adjacent.
   @return none.
*/
void floyd(const Graph<City>& g, double**& dist, int**& path)
{
   //Implement this method
      for (int i = 1; i <= g.size(); i++)
      {
	      for (int j = 1; j <= g.size(); j++)
	      {
		      try
		      {
			  dist[i-1][j-1] = g.retrieveEdge(i,j);
		          path[i-1][j-1] = i;
			   
		      }
     	              catch (GraphException& e)
	              {   
    		          path[i-1][j-1] = -1;
			  dist[i-1][j-1] = INFINITY;
                      }
	      }
      }
      for (int i = 1; i <= g.size(); i++){
	//cout << "i " << i;
	dist[i-1][i-1] = 0;
      }
      for (int k = 1; k <= g.size(); k++)
      {
	      for (int i = 1; i <= g.size(); i++)
	      {
		      for (int j = 1; j <= g.size(); j++)
		      {
			      if (dist[i-1][k-1] != INFINITY && dist[k-1][j-1] != INFINITY && dist[i-1][k-1] + dist[k-1][j-1] < dist[i-1][j-1])
			      {
				      dist[i-1][j-1] = dist[i-1][k-1] + dist[k-1][j-1];
				      path[i-1][j-1] = k;
			      }
			      //cout << path[i-1][j-1];
		      }
		      //cout << endl;
	      }
      }      
} 

/**
 *  an auxiliary function for the topoSort method.
 * @param g a weighted directed graph
 * @param v current vertex
 * @param seen a 1-D boolean matrix of vertices that
 * have been marked.
 * @param linearOrder a 1-D array containing the
 * topologically sorted list.
 * @param index current index.
 */
void dfsOut(const Graph<City>& g, int v, bool seen[],int linearOrder[], int& index)
{
    //Implement this function (Project # 4)
    seen[v] = true;
    for (int w = 1; w <= g.size(); w++)
    {
	    if (g.isEdge(City(v), City(w)) && v != w)
	    {
		    if (seen[w] == false)
		    {
			    dfsOut(g, w, seen, linearOrder, index);
		    }
	    }
    }
    linearOrder[index-1] = v;
    index = index - 1;
    
}

/**
 *  This method generates a listing of the vertices of a weighted
 * directed graph using the reverse dfs topological sorting.
 * @param g a weighted directed graph
 * @return an array containing a topological ordering of the vertices
 *        of g in reverse DFS order; Null is returned if the g
 *        contains a directed cycle
*/ 
int* topoSort(const Graph<City>& g)
{
   //implement this function (Project # 4)
   
   //vector<int> lin(g.size());
   int *lin = new int[(int)g.size()-1];
   //int* results(g.size()) = &lin(g.size());
   //vector<bool> seen(g.size());
   bool *seen = new bool[(int)g.size()];
   int count = g.size();
   //int* index = new int(count);
   int index = count;

   for (int i = 1; i <= g.size(); i++)
   {
	   seen[i] = false;
   }
   /**
    *******With out detecting the cycle***********
    *
   for (int v = 1; v <= g.size(); v++)
   {
	  if (seen[v] == false)
	  {
		   dfsOut(g, v, seen, lin, index);
	  }
   }
   return lin;
   **/

   /*******With the detection of cycle**************/
   
   // check if there is a cycle
   // create a vector to store in-degrees of all vertices. 
   // Initialize all in-degrees as 0, and calculate 
   // in-degrees of all vertices
   vector<int> in_degree(g.size(),0);
   for (int i = 1; i <= g.size(); i++)
   {
	   in_degree[i] = g.inDegree(i);
   }

   // create an queue and enqueue all vertices with in-degree 0
   std::queue<int> q;
   for (int i = 1; i <= g.size(); i++)
   {
	   if (in_degree[i] == 0)
	   {
		   q.push(i);
	   }
   }
   // initialize count of visited vertices
   int cnt = 0;

   // one by one dequeue vertices from queue and enqueue neighbors 
   // if in-degree of neighbors becomes 0
   while(!q.empty())
   {
	   // extract front of queue
	   int u = q.front();
	   q.pop();
	   // iterate through all its neighbouring nodes of dequeued 
	   // node and decrease their in-degree by 1
           for (int v = 1; v <= g.size(); v++){
		   if(in_degree[v] == 0){
		           continue;
		   }
		   if (g.isEdge(City(u),City(v))&& in_degree[v]!= 0)
		   {
			   in_degree[v]--;
		   }
		   if (in_degree[v] == 0)
		   {
			   q.push(v);
		   }
	   }
	   cnt++;
   }
   // check if there is a cycle
   if (cnt == g.size())
   {
	   // start use reversed dfs for topological sorting
	   // int count = g.size();
	   for (int v = 1; v <= g.size(); v++)
	   {
		   if (seen[v] == false)
		   {
			   dfsOut(g, v, seen, lin, index);
		   }
	   }
	   return lin;
   }
   else
   {
	   return NULL;
   }
   
} 

/**
 * This method generates a minimum spanning tree rooted at a given
 * vertex, root. If no such MST exists, then it generates a minimum
 * spanning forest with one of the subtrees at root and with the
 * roots of the other subtrees being the vertex with the smallest
 * key in each  subtree.
 * @param g a weighted directed graph
 * @param r root of the minimum spanning tree, when one exists.
 * @param parent the parent implementation of the minimum spanning tree/forest
 * @return the weight of such a tree or forest.
 * <pre>
 * {@code If a minimum spanning tree rooted at r is in the graph,
 *           the parent implementation of a minimum spanning tree or forest is
 *           determined. If no such tree exist, the parent implementation
 *           of an MST is generated. If the tree is empty, an exception
 *          is generated.
 * }
 * </pre> 
 */ 
double  primMST(const Graph<City>& g, int root, int* parent) throw (GraphException)
{
   //Implement this function  (Project # 4)
   //local Node class to represent vertices of the graph
   class Node
   {
   public:
      int parent, id;
      double key;
      Node()
      {
           
      }
      Node(int p, int v, double k)
      {
         parent = p;
         id = v;
         key = k;
      }           
   };

   auto cmp = [](const Node& v1,const Node& v2) 
   { 
      double d = v1.key - v2.key;
      if (d != 0)
         return d > 0;
      d = v1.id - v2.id;
      return d > 0;           
   };   
   //Defining an instance of the PriorityQueue class that uses the comparator;
   //Then implement the priority-queue-based Prim's MST algorithm
    
   std::priority_queue<Node, std::vector<Node>, decltype(cmp)> pq(cmp);
   int cost = 0;
   vector<bool> visited(g.size() + 1, false);
   vector<int> key(g.size() + 1, int_max);
   for (int i = 0; i < g.size(); ++i){
	parent[i] = -1;
   }
   bool FINISH = false;
   while(!FINISH){
      parent[root-1] = -1;
      Node node(-1, root, 0);
      key[root] = 0;
      pq.push(node);
      while (!pq.empty()){
	      Node u = pq.top();
	      pq.pop();
	      if (visited[u.id]){
		      continue;
	      }
              visited[u.id] = true;
              for(int v = 1; v <= g.size();v++){
                  if((g.isEdge(City(u.id),City(v)) || g.isEdge(City(v),City(u.id))) ){
                        if (visited[v] == false ){
				try{
					int uvweight = g.retrieveEdge(City(u.id),City(v));
                                        if(key[v] > uvweight){
				    		parent[v-1] = u.id;
	                                        Node node(u.id, v, uvweight);
					        pq.push(node);
						key[v] = uvweight;
					}

				} catch (GraphException& e)
				{
					int uvweight = g.retrieveEdge(City(v),City(u.id));
                                         if(key[v] > uvweight){
				    		parent[v-1] = u.id;
	                                        Node node(u.id, v, uvweight);
					        pq.push(node);
						key[v] = uvweight;
					}
				}
			}
		  }
	      }
      }
      FINISH = true;
      for (int k = 1; k <= g.size(); ++k) {
	      if (key[k] == int_max && k != root){
		      FINISH = false;
		      root = k;
		      break;
	      }
      }
      if (FINISH == true){
	      for (int k = 1; k <= g.size(); ++k) {
		      cost += key[k];
	      }
      }
   }
   return cost;
}
