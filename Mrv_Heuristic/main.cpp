#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include"node.h"
#include"house_input.h"
#include"job_input.h"
#include"backtrack.h"
#include"house_contraint.h"
#include"job_constraint.h"
#include"mrv_heuristic.h"

using namespace std;

int main(int argc, char *argv[])
{
  if(argc <3)
  {
    cout<<"Less Nummber of arguments Given"<<endl;
    return 1;
  }
  
  vector<node*> zebra_var();
  vector<int> zebra_domain();
  vector<node*> job_var();
  vector<int> job_domain();
  bool backtrack_house_no_mrv(vector<node*>, vector<int>, int);
  bool backtrack_house_mrv(vector<node*>, vector<int>, int);
  bool backtrack_job_no_mrv(vector<node*>, vector<int>, int);
  bool backtrack_job_mrv(vector<node*>, vector<int>, int);
  int puzzle = atoi(argv[1]);
  int mrv = atoi(argv[2]);
  vector<node*> var, goal;
  vector<int> dom;
  if(puzzle)
  {
    var = zebra_var();
    dom = zebra_domain();
    if(mrv)
      if(backtrack_house_mrv(var, dom, 0))
        cout<<"Problm Solved";
      else
        cout<<"Sorry, problem not solved";
    else
      if(backtrack_house_no_mrv(var, dom, 0))
        cout<<"Problm Solved";
      else
        cout<<"Sorry, problem not solved";


  }
  else
  {
    var = job_var();
    dom = job_domain();
    if(mrv)
      if(backtrack_job_mrv(var, dom, 0))
        cout<<"Problm Solved";
      else
        cout<<"Sorry, problem not solved";
    else
      if(backtrack_job_no_mrv(var, dom, 0))
        cout<<"Problm Solved";
      else
        cout<<"Sorry, problem not solved";


  }
}
