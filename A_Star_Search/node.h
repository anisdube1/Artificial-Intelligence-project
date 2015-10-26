#include<iostream>
#include<stdio.h>
#include<vector>
using namespace std;

class Node
{
  public:
    vector<vector<char> > state;
    float heur, moves, cost;
    bool visited;
    Node* parent;
    Node(vector<vector<char> > state)
      {
	this->state = state;
	this->parent = NULL;
      }
    vector<vector<vector<char> > > successors();
    vector<Node*> traceback(Node*);
  };


vector<vector<vector<char> > > Node::successors()
  {
    vector<vector<vector<char> > > succ;
    for (int i=0; i<state.size(); i++)
      {
	if (state[i].size() > 0)
	  {
	    char pop_ele = state[i][state[i].size()-1];
	    state[i].pop_back();
	    for (int j=0; j<state.size(); j++)
	      {
	        if(i!=j)
	          {
		    state[j].push_back(pop_ele);
		    succ.push_back(state);
		    state[j].pop_back();
		  }
	      }
        state[i].push_back(pop_ele);  
	  }
      }
    return succ;
  }

vector<Node*> Node::traceback(Node* initial)
  {
    Node* path = this;
    vector<Node*> ans;
    while(path!=NULL)// || path->parent != NULL)
    {
      ans.push_back(path);
      path = path->parent;
    }
    return ans;
  }

