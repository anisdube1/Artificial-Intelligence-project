#include<iostream>
#include<stdio.h>
#include<vector>
//#include"node.h"

using namespace std;

// CHEF = 1;
// GUARD = 2;
// NURSE = 3;
// CLERK = 4;
// POLICE = 5;
// TEACHER = 6;
// ACTOR = 7;
// BOXER =8;

// 0 MALE
// 1 FEMALE

void assign_job_domain(vector<node*> &var , vector<int> domain, int job, int index)
{
  var[index]->job = job;
  return;
}

bool consistent_job(vector<node*> var, vector<int> domain, int index)
{
  //for(int i=0; i<=index;i++)
  for(int i=0; i< var.size(); i++)  
  {
    if(i != index && var[index]->job == var[i]->job)
        return false;

    node* nod = var[i];
    if(nod->job == 3)
      if(nod->sex != 0)
        return false;

    if(nod->job == 1)
      if(nod->sex !=1)
        return false;

    if(nod->job == 4)
      if(nod->sex !=0)
        return false;

    if(nod->job == 7)
      if(nod->sex != 0)
        return false;

    if(nod->index == 1 || nod->index == 2)
      if(nod->job == 8)
        return false;

    if(nod->index == 7 || nod->index == 8)
      if(nod->job == 3 || nod->job == 6 || nod->job == 5)
        return false;

    if(nod->index == 1 || nod->index== 2) // Roberta
      if(nod->job == 1 || nod->job == 5)
        return false;

   if(nod->index== 3 && (nod->job == 5 || nod->job == 1))
    {
      node* prev = var[index-1];
      if((prev->job == 5 || prev->job == 1) && (var[index]->job == 5 || var[index]->job == 1))
        return false;
    }

   if(nod->index== 5 && (nod->job == 5 || nod->job == 1))
    {
      node *prev = var[index-1];
      if((prev->job == 5 || prev->job == 1) && (var[index]->job == 5 || var[index]->job == 1))
        return false;
    }

   if(nod->index== 7 && (nod->job == 5 || nod->job == 1))
    {
      node *prev = var[index-1];
      if((prev->job == 5 || prev->job == 1) && (var[index]->job == 5 || var[index]->job == 1))
        return false;
    }
  }
  return true;
}

