#include<iostream>
#include<stdio.h>
#include"generate_input.h"
#include<limits.h>
#include"node.h"
#include"priority_queue.h"
using namespace std;

vector<Node*> n;
int index=0;
int main(int argc, char *argv[])
{
    if (argc < 4)
   {
     cout<<"Less number of arguments given"<<endl;
     return 1;
   }
  int num_stacks = atoi(argv[1]) , num_blocks = atoi(argv[2]), debug_flag = atoi(argv[3]);
  float calculate_heuristic(vector<vector<char> >, int);
  Node* a_star_search(vector<vector<char> >, int, int);
  vector<vector<char> > initial_block;
  initial_block = gen_input(num_stacks, num_blocks);
  cout<<"Initial State"<<endl;
  for (int i=0; i<initial_block.size(); i++)
    {
      for (int j=0; j<initial_block[i].size();j++)
        cout<<" "<<initial_block[i][j];
      cout<<endl;
    }
  cout<<"-----"<<endl;
  
  for(int i=0 ; i<2; i++)
  {
    if(i==0)
     cout<<"Implemented Heuristic Used----------------------------------------------------->"<<endl;
    else
     cout<<endl<<endl<<"Standard heuristic Used (h0) Used---------------------------------------------->"<<endl;
    Node* goal = a_star_search(initial_block, num_blocks, i);
    if(goal)
     {
	cout<<"Goal Reached"<<endl;
	vector<Node*> path_vector = goal->traceback(n[0]);
	cout<<"Depth "<<path_vector.size()<<endl;
      if(debug_flag)
       { 
	for (int i=path_vector.size()-1; i>=0 ; i--)
        {
	  vector<vector<char> > path = path_vector[i]->state;
         cout<<"Heuristic value is "<<calculate_heuristic(path, num_blocks)<<endl;
	  cout<<"Depth at "<<i+1<<endl;
	  for (int j=0; j<path.size();j++)
          {
	    cout<<j<<" | ";
            for (int k=0; k<path[j].size(); k++)
              cout<<" "<<path[j][k];
            cout<<endl;
          }
          cout<<"-----------"<<endl;
         }
       }
      
    }
    else
	{
	  cout<<"Goal not reached";
	}
   // Free the node memory
    while(!n.empty())  
      {
	n.pop_back();
      }
  }
}


Node* a_star_search(vector<vector<char> > initial, int num_blocks, int flag)
  {
    bool goal_reached(vector<vector<char> >, int);
    bool state_same(vector<vector<char> >, Node*);
    float calculate_heuristic(vector<vector<char> >, int);
    float normal_heuristic(vector<vector<char> >, int);
    int states_visited=1 , max_frontier_size=INT_MIN, total_iteration=0;
    priority_queue<Node*,vector<Node*>, Compare> frontier;
    Node* n_initial = new Node(initial);
    n_initial->moves = 0 ;
    if(flag==0)
    	n_initial->heur = calculate_heuristic(n_initial->state, num_blocks);
    else
	n_initial->heur = normal_heuristic(n_initial->state, num_blocks);
    n_initial->cost = n_initial->moves + n_initial->heur;
    n.push_back(n_initial);
    n_initial->visited = true;
    frontier.push(n_initial);
    while(!frontier.empty())
    {
        total_iteration++;
	if(total_iteration > 25000)
	  {
	      cout<<"Iteration Limit Exceeded"<<endl;
	      return NULL;
	  }

        Node *first = frontier.top();
        frontier.pop();
        if(goal_reached(first->state, num_blocks))
          {
	    vector<vector<char> > st = first->state;
	   cout<<"Final State"<<endl; 
           for (int i=0; i<st.size(); i++)
	      {
      	        for (int j=0; j<st[i].size();j++)
        	  cout<<" "<<st[i][j];
      		cout<<endl;
              }
  	    cout<<"-----"<<endl;
    
            cout<<"Search Algorithm A Star Search"<<endl;
            cout<<"Total Iterations "<<total_iteration<<endl;
            cout<<"Max Frontier Size "<<max_frontier_size<<endl;
            return first;
          }

        vector<vector<vector<char> > > succ;
        succ = first->successors();
        for(int i =0; i < succ.size(); i++)
          {
	    int fl=1;
	    for(int j=0; j<n.size(); j++)
	      {
		if(state_same(succ[i], n[j]))
		  {
		    float moves = n[j]->moves;
		    float heur=0.0;
		    if(flag==0)
		      heur = calculate_heuristic(n[j]->state, num_blocks);
		    else
		      heur = normal_heuristic(n[j]->state, num_blocks);
		    if(moves > first->moves+1)
		      {
		        n[j]->moves = first->moves + 1;
			n[j]->heur = heur;
			n[j]->cost = n[j]->moves + heur;
			n[j]->parent = first;
			vector<Node*> temp;
			// Heapify again
			while(!frontier.empty())
			  {
			    temp.push_back(frontier.top());
			    frontier.pop();
			  } 
			for (int i=0; i<temp.size(); i++)
			  frontier.push(temp[i]);
		      }
		    fl=0;
		    break;
		  }
	      }
	    if(fl)
	      {
		Node* n_succ = new Node(succ[i]);
	 	n_succ->parent = first;
		float heur =0.0;
		if(flag==0)
		  heur = calculate_heuristic(n_succ->state, num_blocks);
		else
		  heur = normal_heuristic(n_succ->state, num_blocks);
		n_succ->heur = heur;
		n_succ->moves = first->moves + 1;
                n_succ->cost = first->moves + 1 + heur;
		n_succ->visited = true;
		frontier.push(n_succ);
		n.push_back(n_succ);
		states_visited++;
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


bool goal_reached(vector<vector<char> > initial, int num_blocks)
{
  vector<char> top_row;
  if (initial[0].size() != num_blocks)
    return false;

  for (int i=0; i<num_blocks; i++)
    {
      if(initial[0][i] != 'A'+i)
	return false;
    } 
  return true;
}

float calculate_heuristic(vector<vector<char> > state, int num_blocks)
{
  vector<vector<int> > info(num_blocks, vector<int>(2));
  int curr_move =0, fut_moves =0, k;
  for (int i=0; i<state.size(); i++)
   {
     for(int j=0; j<state[i].size(); j++)
	{
	  info[state[i][j] - 'A'][0] = i;
	  info[state[i][j] - 'A'][1] = j;
	}
   }
   
   int i=0;
   for (i=0; i<state[0].size(); i++)
     {
	if(state[0][i] - 'A' == i)
	  continue;
	else
	  break;
     }
  if(i < num_blocks)
    {
	curr_move = (state[0].size() -i ) + (state[info[i][0]].size() - info[i][1]);
   	i++;
	k=i;
   	while(i<num_blocks)
    	  {
		fut_moves+= (state[info[i][0]].size() - info[i][1]);
		i++;
    	  }
    }

  float heur=0.0;  
   for (int i=0; i<state.size(); i++)
    {
      for (int j=0; j<state[i].size(); j++)
        {
          if(state[i][j] - 'A' == j)
              heur = heur;
          else
            heur = heur + j;
        }
    }
	return  (2.5*curr_move + fut_moves + 0.5*num_blocks/k - 0.2*heur) ;
}

float normal_heuristic(vector<vector<char> > state, int num_blocks)
{
  vector<vector<int> > info(num_blocks, vector<int>(2));
  int curr_move =0, fut_moves =0, k=0;
  for (int i=0; i<state.size(); i++)
   {
     for(int j=0; j<state[i].size(); j++)
        {
          info[state[i][j] - 'A'][0] = i;
          info[state[i][j] - 'A'][1] = j;
        }
   }
  
  for(int i=0; i<num_blocks; i++)
   {
      if(info[i][0] == 0 && info[i][1] == i)
	k++;
   }
  return k;
}



bool state_same(vector<vector<char> > initial, Node* n)
{
  vector<vector<char> > fina = n->state;
  if (initial.size() != fina.size())
    return false;
  for (int i=0; i<initial.size(); i++)
    {
      if(initial[i].size() != fina[i].size())
        return false;
      else
        {
	  for (int j=0; j<initial[i].size() ; j++)
	    if(initial[i][j] != fina[i][j])
	      return false;
	}    
    } 
  return true;
}
