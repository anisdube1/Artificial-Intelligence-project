#include<iostream>
#include<stdio.h>
#include<vector>
using namespace std;
  
class Node
{
  public:
    int vertex, x, y;
    Node *parent;
    int depth;
    float heur;
    vector<Node*> adj;
    Node(int vertex, int x, int y)
      {
	this->vertex = vertex;
	this->x=x;
	this->y=y;
	depth = 0;
	parent = NULL;
      }
    Node(int I , Node* p) 
      {
      }
    void addEdge(Node *dst);
    vector<Node*> successors();
    vector<int> traceback(Node* root);
  };

void Node::addEdge(Node* dst)
 {
    adj.push_back(dst);
 }

vector<Node*> Node::successors()
  {
    return adj;
  }

vector<int> Node::traceback(Node* root)
  {
	vector<int> path;
	Node *curr = this;
	int flag=0;
	while( curr && curr->vertex != root->vertex)
	  {
		path.push_back(curr->vertex);
		curr = curr->parent;
		flag++;
	  }
	path.push_back(root->vertex);
	return path;
  }

