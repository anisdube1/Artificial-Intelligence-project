#include<iostream>
#include<stdio.h>
#include<vector>
#include<limits.h>
#include<algorithm>
using namespace std;

int mrv_heuristic_job(vector<node*> var, vector<int> domain)
{
  vector<int> values(var.size(), -1);

  for(int i=0; i<var.size(); i++)
  {
    if(var[i]->job == -1)
    {
      values[i] = 0;
      for(int job = 1 ; job<=domain.size(); job++)
      {
        var[i]->job = job;
        if(consistent_job(var, domain,i))
          values[i]++;
        var[i]->job = -1;
      }
    }
  }
  int min = INT_MAX, pos=0;
  for(int i=0; i<values.size(); i++)
  {
    if(values[i] == -1)
      values[i] = domain.size() +1;

    if(min>values[i])
     {
       min=values[i];
       pos=i;
     }
  }
  return pos;
  //return (min_element(values.begin(), values.end()) - values.begin());
}


int mrv_heuristic_house(vector<node*> var, vector<int> domain)
{
  vector<int> values(var.size(), -1);

  for(int i=0; i<var.size(); i++)
  {
    if(var[i]->assign == -1)
    {
      values[i]=0;
      var[i]->assign = 1;
      for(int house = 1 ; house<=domain.size(); house++)
      {
        var[i]->house_no = house;
        if(consistent_house(var, domain,i))
          values[i]++;
        var[i]->house_no = -1;
      }
      var[i]->assign = -1;
    }
  }
  int min = INT_MAX, pos=0;

  for(int i=0; i<values.size(); i++)
  {
    if(values[i] == -1)
      values[i] = domain.size()+1;

    if(min>values[i])
     {
       min=values[i];
       pos=i;
     }
  }

  return pos;



}

