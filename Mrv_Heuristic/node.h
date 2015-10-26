#include<iostream>
#include<stdio.h>
#include<vector>

using namespace std;

class node
{
  public:
    int assign;
    string category;
    int house_no;
    string name;
    int sex, edu, job, index;
    node(string category, string name)
    {
      this->assign= -1;
      this->category = category;
      this->house_no = -1;
      this->name = name;
    }
    node(string name, int sex, int index)
    {
      this->name = name;
      this->sex = sex;
      edu = -1;
      job = -1;
      this->index = index;
    }
};
