#include<iostream>
#include<stdio.h>
#include<string.h>
#include<vector>
#include <boost/algorithm/string.hpp>
#include<utility>
#include<map>

struct res_pair
{
  bool isres;
  vector<pair<int, int>> pairs;
};

bool check(string, string);

res_pair isresolvabble(clause *a , clause *b)
{
  res_pair ans;
  vector<string> sa, sb;
  string a_clause = a->c;
  string b_clause = b->c;
  boost::split(sa, a_clause, boost::is_any_of("\t "));
  boost::split(sb, b_clause, boost::is_any_of("\t "));
  ans.isres = false;
  for(int i=0; i<sa.size(); i++)
  {
    for(int j=0; j<sb.size(); j++)
    {
      if(check(sa[i], sb[j]))
      {
        pair<int, int> index;
	index = make_pair(i, j);
	(ans.pairs).push_back(index);
	ans.isres = true;
      }
    }
  }
  return ans;
}

bool check(string a, string b)
{
  if(a.size() ==0 || b.size() == 0)
    return false;
  if(a.find(b) != string::npos)
    if(a.find('-') != string::npos && b.find('-') == string::npos)
		return true;
  if(b.find(a) != string::npos)
    if(a.find('-') == string::npos && b.find('-') != string::npos)
		return true;
  return false;
}

string resolve(clause* a, clause* b, int pos1, int pos2)
{
  map<string, bool> mymap;
  string ans="";
  vector<string> sa, sb;
  string a_clause = a->c;
  string b_clause = b->c;
  boost::split(sa, a_clause, boost::is_any_of(" "));
  boost::split(sb, b_clause, boost::is_any_of(" "));
  for(int i=0; i<sa.size(); i++)
  {
    if(i==pos1)
	continue;
    else
    {
      ans+= sa[i] + ' ';
      mymap[sa[i]] = true;
    }
  }
  for(int i=0; i<sb.size(); i++)
  {
    if(i==pos2)
        continue;
    else
    {
      if(mymap.find(sb[i]) == mymap.end())
      {
        mymap[sb[i]] = true;
	ans+= sb[i] + ' ';	   
      }
    }
  }
  if(ans.size()==0)
    return ans;
  else 
    return ans.substr(0, ans.size()-1);
}
