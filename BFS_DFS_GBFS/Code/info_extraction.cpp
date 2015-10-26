#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<stack>
#include<queue>
#include<limits.h>
#include<map>
#include<iomanip>
#include<list>
#include"Node.h"
#include"mypriority_queue.h"
using namespace std;

int num_vertices , debug_flag=0, i_x, i_y, f_x, f_y, search;
map<string, int> map_vertex_coord;
int Compare::f_x ,  Compare::f_y ;
vector<Node*> n;

int main(int argc, char *argv[])
{
 
  if (argc < 7)
   {
     cout<<"Less number of arguments given"<<endl;
     return 1;
   }

  i_x = atoi(argv[1]) , i_y = atoi(argv[2]) , f_x = atoi(argv[3]), f_y = atoi(argv[4]) , debug_flag = atoi(argv[5]), search = atoi(argv[6]);
  Compare::f_x = f_x, Compare::f_y =f_y;
  string l;
  Node* dfs_search(Node*, Node*);
  Node* bfs_search(Node*, Node*);
  Node *gbfs_search(Node*, Node*);
  int flag=1, num_edges, ini, fin;
  ifstream file("atmgraph.txt");
  getline(file, l);
  if(l.find("vertices")!=string::npos)
    {
      num_vertices = atoi(l.substr(10, l.size()-1).c_str());
    }
 // Vector<Node> *n;
  string line;
   while (getline(file, line))
    {
       if(line.find("edges")!=string::npos && flag == 1)
       {
         num_edges = atoi(line.substr(7, line.size()-1).c_str()); 
         flag=2;
       }
      else if(flag == 1)
	{
	  istringstream iss(line);
	  int a, b, c;
    	  if (!(iss >> a >> b >> c)) 
	  {
	     break; 
	    } 
	  n.push_back(new Node(a, b, c));
	  string coord = to_string(b) + ":" + to_string(c);
	  map_vertex_coord[coord] = a;
	}	
      else
       {
	  istringstream iss(line);
          int a, b, c;
          if (!(iss >> a >> b >> c))  
          {
             break;  
          } 
	  n[b]->addEdge(n[c]);
          n[c]->addEdge(n[b]);
       }
    }
  
  ini = map_vertex_coord[to_string(i_x)+":"+to_string(i_y)];
  fin = map_vertex_coord[to_string(f_x)+":"+to_string(f_y)];
  Node *goal = NULL;
  if(search == 1 )
    goal = dfs_search(n[ini], n[fin]); 
  else if (search == 2)
    goal = bfs_search(n[ini], n[fin]);
 else 
    goal = gbfs_search(n[ini], n[fin]);
  
  if(goal)
  {
    vector<int> path = goal->traceback(n[ini]);
        cout<<"Path Length "<<path.size()-1<<endl;
    cout<<"Path Direction:"<<endl;
    for(int i=path.size()-1; i >= 0 ;i--)
     {
         //cout<<"Vertex  "<<path[i]<<"   ("<<n[path[i]]->x<<" , "<<n[path[i]]->y<<")"<<endl;
       	   cout<<"Vertex "<<path[i]<<"("<<n[path[i]]->x<<", "<<n[path[i]]->y<<") -->  ";
	//  cout<<n[path[i]]->x<<" "<<n[path[i]]->y<<endl;
     }
    cout<<endl;
    
    for(int i=path.size()-1; i >= 0 ;i--)
     {
         cout<<n[path[i]]->x<<" "<<n[path[i]]->y<<endl;
     }

  }
  else
  {
    cout<<"Target Path not found"<<endl;
  }
  return 0;
}

Node* dfs_search(Node* initial, Node* goal)
{
    bool *visited = new bool[num_vertices];
    for(int i=0; i<num_vertices; i++)
	visited[i] = false;

    int vertices_visited=1, max_frontier_size=INT_MIN, total_iteration=0;
    stack<Node*> frontier;
    frontier.push(initial);
    visited[initial->vertex] = true;
    while(frontier.size()!=0)
    {
	total_iteration++;
	Node *first = frontier.top();
	frontier.pop();
        if(debug_flag)
          {
		 double dist =  sqrt((pow(f_x - n[first->vertex]->x, 2.0f)) + pow(f_y - n[first->vertex]->y, 2.0f));
            cout<<"Iteration = "<<total_iteration<<" , frontier = "<<frontier.size()<<" , Depth =  "<<first->depth<<" , dist2goal= "<<dist<<endl;
	cout<<"-Popped "<<first->vertex<<" ("<<n[first->vertex]->x<<", "<<n[first->vertex]->y<<")"<<endl;
 
         }
	
	if(first->vertex == goal->vertex)
	 {
	                    cout<<"Search Algorithm DFS"<<endl;
        cout<<"Total Iterations "<<total_iteration<<endl;
            cout<<"Max Frontier Size "<<max_frontier_size<<endl;
        cout<<"Vertices Visited "<<vertices_visited<<"/"<<num_vertices<<endl;

	   return goal;
	}
	vector<Node*> succ;
	succ = first->successors();
        for(int i =0; i < succ.size(); i++)
	  {
	    if(!visited[succ[i]->vertex])
	    {

	      if(debug_flag)
                cout<<"+Pushed "<<succ[i]->vertex<<" ("<<n[succ[i]->vertex]->x<<", "<<n[succ[i]->vertex]->y<<")"<<endl;

	      frontier.push(succ[i]);
	      succ[i]->parent = first;
	      visited[succ[i]->vertex]=true;
	      vertices_visited++;
	      succ[i]->depth = first->depth+1;
	    }
	  }
	 int f_size = frontier.size();
        if(f_size > max_frontier_size)
          {
                max_frontier_size = frontier.size();
          }

    }
    return NULL;
}

Node* bfs_search(Node* initial, Node* goal)
{
    bool *visited = new bool[num_vertices];
    for(int i=0; i<num_vertices; i++)
        visited[i] = false;

    int vertices_visited=1, max_frontier_size=INT_MIN, total_iteration=0;
    list<Node*> frontier;
    frontier.push_back(initial);
    visited[initial->vertex] = true;
    while(frontier.size()!=0)
    {
        total_iteration++;
        Node *first = frontier.front();
        frontier.pop_front();

	if(debug_flag)
	  {
            double dist =  sqrt((pow(f_x - n[first->vertex]->x, 2.0f)) + pow(f_y - n[first->vertex]->y, 2.0f));
            cout<<"Iteration = "<<total_iteration<<" , frontier = "<<frontier.size()<<" , Depth =  "<<first->depth<<" , dist2goal= "<<dist<<endl;
            cout<<"-Popped "<<first->vertex<<" ("<<n[first->vertex]->x<<", "<<n[first->vertex]->y<<")"<<endl;
	  }
        if(first->vertex == goal->vertex)
          {
		    cout<<"Search Algorithm BFS"<<endl;
    	cout<<"Total Iterations "<<total_iteration<<endl;
	    cout<<"Max Frontier Size "<<max_frontier_size<<endl;
    	cout<<"Vertices Visited "<<vertices_visited<<"/"<<num_vertices<<endl;

		return goal;
	  }
        vector<Node*> succ;
        succ = first->successors();
        for(int i =0; i < succ.size(); i++)
          {
            if(!visited[succ[i]->vertex])
            {
	      if(debug_flag)
	        cout<<"+Pushed "<<succ[i]->vertex<<" ("<<n[succ[i]->vertex]->x<<", "<<n[succ[i]->vertex]->y<<")"<<endl;
              frontier.push_back(succ[i]);
              succ[i]->parent = first;
	      succ[i]->depth = first->depth+1;
	      visited[succ[i]->vertex]=true;
	      vertices_visited++;
            }
          }
        int f_size = frontier.size();
	if(f_size > max_frontier_size)
 	  {
		max_frontier_size = frontier.size();
	  }
    }
    return NULL;
}

Node* gbfs_search(Node* initial, Node* goal)
{
    bool *visited = new bool[num_vertices];
    for(int i=0; i<num_vertices; i++)
        visited[i] = false;
    
    int vertices_visited=1 , max_frontier_size=INT_MIN, total_iteration=0;
    priority_queue<Node*,vector<Node*>, Compare> frontier;
    frontier.push(initial);
    visited[initial->vertex] = true;
    while(!frontier.empty())
    {
        total_iteration++;
        Node *first = frontier.top();
        frontier.pop();

        if(debug_flag)
          {
	         double dist =  sqrt((pow(f_x - n[first->vertex]->x, 2.0f)) + pow(f_y - n[first->vertex]->y, 2.0f));
            cout<<"Iteration = "<<total_iteration<<" , frontier = "<<frontier.size()<<" , Depth =  "<<first->depth<<" , dist2goal= "<<dist<<endl;
        cout<<"-Popped "<<first->vertex<<" ("<<n[first->vertex]->x<<", "<<n[first->vertex]->y<<")"<<endl; 
	  }
        if(first->vertex == goal->vertex)
          {
                    cout<<"Search Algorithm GBFS"<<endl;
        cout<<"Total Iterations "<<total_iteration<<endl;
            cout<<"Max Frontier Size "<<max_frontier_size<<endl;
        cout<<"Vertices Visited "<<vertices_visited<<"/"<<num_vertices<<endl;

                return goal;
          }
        vector<Node*> succ;
        succ = first->successors();
        for(int i =0; i < succ.size(); i++)
          {
            if(!visited[succ[i]->vertex])
            {
              if(debug_flag)
                {
		  cout<<"+Pushed  "<<succ[i]->vertex<<" ("<<n[succ[i]->vertex]->x<<", "<<n[succ[i]->vertex]->y<<")"<<endl;
                  double dist =  sqrt((pow(f_x - n[succ[i]->vertex]->x, 2.0f)) + pow(f_y - n[succ[i]->vertex]->y, 2.0f));
		}
		frontier.push(succ[i]);
              succ[i]->parent = first;
	      succ[i]->depth = first->depth+1;
              visited[succ[i]->vertex]=true;
              vertices_visited++;
            }
          }
        int f_size = frontier.size();
        if(f_size > max_frontier_size)
          {
                max_frontier_size = frontier.size();
          }
    }
    return NULL;
}






