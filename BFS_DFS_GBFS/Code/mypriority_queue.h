#include<iostream>
#include <queue>
#include <iomanip>
#include<math.h>
using namespace std;

class Compare {
public:    
    static int f_x, f_y;
    bool operator()(Node* n1, Node* n2);
    double distance(Node* n);
};

bool Compare::operator()(Node* n1, Node* n2)
{
  if(distance(n1) >  distance(n2))
	return true;
  else  
 	return false;
}

double Compare::distance(Node* n)
{
   return sqrt((pow(f_x - n->x, 2.0f)) + pow(f_y - n->y, 2.0f));
}
