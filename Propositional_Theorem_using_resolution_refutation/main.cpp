#include<iostream>
#include<stdio.h>
#include"clause.h"
#include <fstream>
#include <boost/algorithm/string.hpp>
#include<vector>
#include"resolve.h"
#include"visit.h"
#include"respair.h"
#include"priority_queue.h"

using namespace std;

vector<clause*> claus;
map<string, string> mapping;
map<string, bool> visited;
map<int, bool> input_conv_map;
int id=0, flag, cou=0;
bool resolution(vector<clause*> &);
void print_tree(clause*, int);
string conversion(int);

int main()
{
  int flag = 1;
  ifstream infile("kb.txt");
  string line;
  mapp(mapping, flag);
  while (getline(infile, line))
  {
    cou++;
    istringstream iss(line);
    if(line.find('#') != string::npos)
    {
      cou--;
      continue;
    }
    claus.push_back(new clause(line, id));
    id++;
  }
  for(int i=0; i<cou; i++)
    input_conv_map[i] = "Input";

  if(resolution(claus))
    cout<<"Resolved"<<endl;
  else
    cout<<"Not Resolved"<<endl; 
  return 0;
}

bool resolution(vector<clause*> &claus)
{
  int iter=1;
  priority_queue<respair*,vector<respair*>, Compare> candidates;
  for(int i=0; i<claus.size()-1; i++)
  {
    for(int j=i+1; j<claus.size(); j++)
    {
      res_pair check_pair= isresolvabble(claus[i], claus[j]);
      if(check_pair.isres)
      {
        respair* pair_clause = new respair(claus[i], claus[j]);
	isvisited(claus[i]->c, visited, mapping);
	isvisited(claus[j]->c, visited, mapping);
	candidates.push(pair_clause);
      }
    }
  }
  while(!candidates.empty())
  {
    cout<<"Iteration "<<iter<<" , Queue Size "<<candidates.size()<<endl;
    iter++;
    if(iter == 10000)
      return false;
    respair* clause_pair = candidates.top();
    candidates.pop();
    res_pair check_pair= isresolvabble(clause_pair->c1, clause_pair->c2);
    vector<pair<int, int>> pairs = check_pair.pairs;
    for(int i=0; i<pairs.size(); i++)
    {
      string line = resolve(clause_pair->c1, clause_pair->c2, pairs[i].first, pairs[i].second);
      cout<<"Resolution on "<<(clause_pair->c1)->c<<"("<<(clause_pair->c1)->id<<")"<<" and "<<(clause_pair->c2)->c<<"("<<(clause_pair->c2)->id<<")"<<" resulted in "<<line<<endl<<endl;
      if(line.size()==0)
        {
	  cout<<"Printing Trace "<<endl;
	  respair* temp = clause_pair;
	  clause* t = new clause(line, id++);
	  t->parenty = clause_pair->c1;
          t->parentx = clause_pair->c2;
	  print_tree(t, 0);
	  return true;
	}
      else
      {
	if(!isvisited(line, visited, mapping ))
	{
	  clause* t = new clause(line, id++);
	  claus.push_back(t);
	  t->parenty = clause_pair->c1;
	  t->parentx = clause_pair->c2;
	  for(int i=0; i<claus.size()-1; i++)
	  {
	    res_pair check_pair= isresolvabble(claus[i], claus[claus.size()-1]);
	    if(check_pair.isres)
	    {
	      respair* pair_clause = new respair(claus[i], claus[claus.size()-1]);
	      pair_clause->parent = clause_pair;
	      // Heapify Again
	      vector<respair*> temp;
	      while(candidates.size() !=0)
	      {
	        temp.push_back(candidates.top());
		candidates.pop();
	      }
	      temp.push_back(pair_clause);
	      for(int j=0; j<temp.size(); j++)
	        candidates.push(temp[j]);
	    }
	  }
	}
      }
    }
  }
  return false;
}

void print_tree(clause* c, int spaces)
{
  if(c->parentx == NULL and c->parenty == NULL)
  {
   for(int i=0;i<spaces;i++)
     cout<<" ";
    if((c->c).size()!=0) 
      cout<<c->id<<": "<<c->c<<" [input]"<<endl;
    else
      cout<<c->id<<": []" <<"[input]"<<endl;
  }
  else
  {
    for(int i=0;i<spaces;i++)
      cout<<" ";
    cout<<c->id<<": "<<c->c<<" ["<<c->parentx->id<<" ,"<<c->parenty->id<<" ]"<<endl;
    print_tree(c->parentx, spaces+1);
    print_tree(c->parenty, spaces+1);
  }
  return;
}

string conversion(int id)
{
 if(input_conv_map.find(id) != input_conv_map.end())
   return "Input";
 else
   return to_string(id);
}
