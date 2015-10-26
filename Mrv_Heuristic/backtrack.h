#include<iostream>
#include<stdio.h>
#include<vector>
using namespace std;

void next_unassign_house_var(vector<node*> &, int);

void assign_house_domain(vector<node*> &, vector<int> , int, int );
void assign_job_domain(vector<node*> & , vector<int> , int, int);

bool consistent_house(vector<node*> , vector<int> , int);
bool consistent_job(vector<node*> , vector<int> , int );

void unassign_house_domain(vector<node*> & , vector<int> , int, int);

void print(vector<node*>);
void print_job(vector<node*>);

void unassign_next_unassign_house_var(vector<node*> &, int);

int mrv_heuristic_job(vector<node*> , vector<int> );
int mrv_heuristic_house(vector<node*> , vector<int> );


int iter =0;


bool backtrack_house_no_mrv(vector<node*> var, vector<int> domain, int index)
{
  if(index == var.size())
  {
    cout<<endl<<"(No MRV)Goal Reached with iterations "<<iter<<endl;
    print(var);
    return true;
  }
  else
  {
    next_unassign_house_var(var, index);
    for(int i=0; i<domain.size(); i++)
    {
      iter++;
      assign_house_domain(var, domain, i, index);
      if(consistent_house(var, domain, index))
	if(backtrack_house_no_mrv(var,domain,index+1))
          return true;
      
      unassign_house_domain(var, domain, i, index);
    }
    unassign_next_unassign_house_var(var, index);
    return false;
  }
}

bool backtrack_house_mrv(vector<node*> var, vector<int> domain, int index)
{
  if(index == var.size())
  {
    cout<<endl<<"(MRV)Goal Reached with iterations "<<iter<<endl;
    print(var);
    return true;
  }
  else
  {
    //next_unassign_house_var(var, index);
    int pos = mrv_heuristic_house(var, domain);
    //cout<<"Position"<<pos<<endl;
    next_unassign_house_var(var, pos);
    for(int i=0; i<domain.size(); i++)
    {
      iter++;
     // cout<<"Before Assigning Index"<<index<<" Pos"<<pos<<endl;
     // int pos = mrv_heuristic_house(var, domain);
      assign_house_domain(var, domain, i, pos);
     // print(var);
      if(consistent_house(var, domain, pos))
        if(backtrack_house_mrv(var,domain,index+1))
          return true;

     // cout<<"Unassigning: Index"<<index<<" Pos "<<pos<<endl;
      unassign_house_domain(var, domain, i, pos);
     // print(var); 
   }
    unassign_next_unassign_house_var(var, pos);
    return false;
  }
}

bool backtrack_job_no_mrv(vector<node*> var, vector<int> domain, int index)
{
  if(index == var.size())
  {
    cout<<endl<<"(No MRV)Goal Reached with iterations "<<iter<<endl;
    print_job(var);
    return true;
  }
  else
  {
    for(int i=1; i <= domain.size(); i++)
    {
      iter++;
      assign_job_domain(var, domain, i, index);
      if(consistent_job(var, domain, index))
        if(backtrack_job_no_mrv(var,domain,index+1))
          return true;
    }
  }
  return false;
}


bool backtrack_job_mrv(vector<node*> var, vector<int> domain, int index)
{   
  if(index == var.size())
  { 
    cout<<endl<<"(MRV)Goal Reached with iterations "<<iter<<endl;
    print_job(var);
    return true;
  } 
  else
  {
    int pos = mrv_heuristic_job(var, domain);
    for(int i=1; i <= domain.size(); i++)
    {
      iter++;
      //assign_job_domain(var, domain, i, index);
     // int pos = mrv_heuristic_job(var, domain);
      //cout<<"Pos"<<pos<<endl;
      var[pos]->job = i;
      if(consistent_job(var, domain, pos))
        if(backtrack_job_mrv(var,domain,index+1))
          return true;
    }
  }
  return false;
}

void print(vector<node*> vars)
{
  cout<<"House No\t"<<"Category\t"<<"        Specification"<<endl;
  for(int i=0; i<vars.size(); i++)
    cout<<vars[i]->house_no<<"\t\t"<<vars[i]->category<<"\t \t \t"<<vars[i]->name<<endl;
}

void print_job(vector<node*> var)
{
  cout<<"Name\t\tSex  \t\tJob"<<endl;
  for (int i=0; i<var.size(); i++)
    cout<<var[i]->name<<"\t \t"<<sex[var[i]->sex]<<"\t \t"<<jobs[var[i]->job]<<endl;
}
