#include<iostream>
#include<stdio.h>
#include<vector>
#include<map>

map<string, int> house;
map<string, int> man;
map<string, int> animal;
map<string, int> eat;
map<string, int> drink;

using namespace std;

/*
void next_unassign_house_var(vector<node*> &var)
{
  for(int i=0; i<var.size();i++)
  {
    if(var[i]->assign == -1)
      {
        var[i]->assign = 1; 
        return;
      }
  }
  return;
}
*/


void next_unassign_house_var(vector<node*> &var, int index)
{
//    if(var[index]->assign == -1)
        var[index]->assign = 1; 

  return;
}

/*	
void unassign_next_unassign_house_var(vector<node*> &var)
{
  for(int i=var.size()-1; i>=0 ;i--)
  {
    if(var[i]->assign == 1)
      {
        var[i]->assign = -1;
        return;
      }
  }
  return;
}

*/

void unassign_next_unassign_house_var(vector<node*> &var, int index)
{
  //  if(var[index]->assign == 1)
        var[index]->assign = -1;
  return;
}

/*
void assign_house_domain(vector<node*> &var, vector<int> domain, int pos)
{
  for(int i=var.size()-1; i>=0; i--)
  {
    if(var[i]->assign == 1)
    {
      var[i]->house_no = pos+1;
      if(var[i]->category == "house")
	house[var[i]->name] = pos+1;
      else if(var[i]->category == "man")
        man[var[i]->name] = pos+1;
      else if(var[i]->category == "animal")
        animal[var[i]->name] = pos+1;
      else if(var[i]->category == "eat")
        eat[var[i]->name] = pos+1;
      else 
        drink[var[i]->name] = pos+1;
 
      return;
    }
  }
}

*/

void assign_house_domain(vector<node*> &var, vector<int> domain, int pos, int i)
{
   // if(var[i]->assign == 1)
   // {
      var[i]->house_no = pos+1;
      if(var[i]->category == "house")
        house[var[i]->name] = pos+1;
      else if(var[i]->category == "man")
        man[var[i]->name] = pos+1;
      else if(var[i]->category == "animal")
        animal[var[i]->name] = pos+1;
      else if(var[i]->category == "eat")
        eat[var[i]->name] = pos+1;
      else 
        drink[var[i]->name] = pos+1;
 
      return;
   // }
}

/*
void unassign_house_domain(vector<node*> &var, vector<int> domain, int pos)
{
  for(int i=var.size()-1; i>=0; i--)
  {
    if(var[i]->assign == 1)
    {
      var[i]->house_no = -1;
      if(var[i]->category == "house")
        house[var[i]->name] = -1;
      else if(var[i]->category == "man")
        man[var[i]->name] = -1;
      else if(var[i]->category == "animal")
        animal[var[i]->name] = -1;
      else if(var[i]->category == "eat")
        eat[var[i]->name] = -1;
      else 
        drink[var[i]->name] = -1;

      return;
    }
  }
}

*/

void unassign_house_domain(vector<node*> &var, vector<int> domain, int pos, int i)
{
    if(var[i]->assign == 1)
    {
      var[i]->house_no = -1;
      if(var[i]->category == "house")
        house[var[i]->name] = -1;
      else if(var[i]->category == "man")
        man[var[i]->name] = -1;
      else if(var[i]->category == "animal")
        animal[var[i]->name] = -1;
      else if(var[i]->category == "eat")
        eat[var[i]->name] = -1;
      else 
        drink[var[i]->name] = -1;

      return;
    }
}

bool consistent_house(vector<node*> vars, vector<int> domain , int index)
{
  bool pre_exist(node* , string , map<string,int>); 
  bool check(vector<node*> , int , int );
  bool adjacent_house(vector<node*>, int, int);
  node* var = vars[index];
  if(pre_exist(var, "house", house) || pre_exist(var, "man", man) || pre_exist(var, "animal", animal) || pre_exist(var, "eat", eat) || pre_exist(var, "drink", drink))
    return false;
  
  if(check(vars, 0,5) || check(vars, 6,10) || check(vars, 2,16) || check(vars, 12,17) || check(vars, 18,20) || check(vars, 9,21) || check(vars, 8,19) || check(vars, 22,1))
   return false;
  
  if(vars[7]->assign ==1)
    if(vars[7]->house_no != 1)
      return false;

  if(vars[1]->assign == 1 && vars[4]->assign == 1 )
    if(vars[4]->house_no + 1 != vars[1]->house_no)
      return false;

  if(adjacent_house(vars, 15, 11) || adjacent_house(vars, 7, 3) || adjacent_house(vars, 16, 13))
    return false;

  if(vars[23]->assign ==1)
    if(vars[23]->house_no != 3)
      return false;

  return true;
}

bool adjacent_house(vector<node*> vars , int m, int n)
{
  if(vars[m]->assign == 1 && vars[n]->assign == 1)
     if(abs(vars[m]->house_no - vars[n]->house_no) != 1)
       return true;
  
  return false;
}
bool check(vector<node*> var, int m , int n)
{
  if(var[m]->assign == 1 && var[n]->assign ==1)
    if(var[m]->house_no !=  var[n]->house_no)
        return true;
   
  return false;
}

bool pre_exist(node* var, string category, map<string,int> mymap)
{
  if(var->category == category)
   {
     int count =0;
     for(auto it = mymap.begin(); it!=mymap.end(); it++)
     {
       if(it->second == var->house_no && it->second != -1)
         count++;
     }
     if(count ==2)
        return true;
   }
   return false;  
}

