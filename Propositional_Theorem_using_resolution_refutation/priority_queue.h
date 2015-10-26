#include<iostream>
#include <queue>
#include <iomanip>
#include<math.h>
#include<vector>
#include<utility>

using namespace std;

class Compare {
  public:
    float calculate(clause*, clause*);
    bool operator()(respair * p1, respair* p2);
};

bool Compare::operator()(respair* p1, respair* p2)
{

  if(calculate(p1->c1, p1->c2) > calculate(p2->c1, p2->c2))
    return true;
  else
    return false; 
}

float Compare::calculate(clause *c1, clause *c2)
{
  vector<string> sa, sb;
  string a_clause = c1->c;
  string b_clause = c2->c;
  boost::split(sa, a_clause, boost::is_any_of(" "));
  boost::split(sb, b_clause, boost::is_any_of(" "));
  return (sa.size() + sb.size());
}

