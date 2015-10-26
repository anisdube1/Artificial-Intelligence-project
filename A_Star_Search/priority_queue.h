#include<iostream>
#include <queue>
#include <iomanip>
#include<math.h>
using namespace std;

class Compare {
public:
    static int f_x, f_y;
    bool operator()(Node* n1, Node* n2);
};

bool Compare::operator()(Node* n1, Node* n2)
{
  if(n1->cost >  n2->cost)
        return true;
  else
        return false;
}

