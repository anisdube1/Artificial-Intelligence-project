#include<iostream>
#include<stdio.h>

using namespace std;

class respair
{
  public:
  clause *c1, *c2;
  respair* parent;
  respair(clause *c1, clause *c2)
  {
    this->c1 = c1;
    this->c2 = c2;
    this->parent = NULL;
  }
};
