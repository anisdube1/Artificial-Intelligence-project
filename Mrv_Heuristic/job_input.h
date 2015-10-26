#include<iostream>
#include<stdio.h>
#include<vector>
#include<map>
using namespace std;


map<int, string> jobs = {{1, "CHEF"}, {2, "GUARD"}, {3, "NURSE"}, {4, "CLERK"}, {5, "POLICE OFFICER"}, {6, "TEACHER"}, {7, "ACTOR"}, {8, "BOXER"}};
map<int, string> sex = {{0, "MALE"}, {1, "FEMALE"}};


vector<node*> job_var()
{
  vector<node*> var;
  var.push_back(new node("Roberta",1, 1 ));
  var.push_back(new node("Roberta",1, 2 ));
  var.push_back(new node("Thelma",1, 3 ));
  var.push_back(new node("Thelma",1, 4 ));
  var.push_back(new node("Steve",0, 5 ));
  var.push_back(new node("Steve",0, 6 ));
  var.push_back(new node("Pete",0, 7 ));
  var.push_back(new node("Pete",0, 8 ));
  return var;

}

vector<int> job_domain()
{
  vector<int> domain;
  domain.push_back(1);
  domain.push_back(2);
  domain.push_back(3);
  domain.push_back(4);
  domain.push_back(5);
  domain.push_back(6);
  domain.push_back(7);
  domain.push_back(8);
  return domain;
}


