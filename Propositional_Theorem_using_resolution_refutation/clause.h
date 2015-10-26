#include<iostream>
#include<stdio.h>
#include <sstream>
#include <string>

using namespace std;

class clause
{
  public:
    string c;
    int id;
    clause* parentx, *parenty;
    clause(string c, int id)
    {
      this->c = c;
      this->id = id;
      parentx = NULL;
      parenty = NULL;
    }
};
