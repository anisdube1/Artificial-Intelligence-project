#include<iostream>
#include<stdio.h>
#include<map>
#include<algorithm>

using namespace std;

void mapp(map<string, string> &mapping , int flag)
{
if(flag ==1)
{
mapping["L1W"] = "a";
mapping["-L1W"] = "A";
mapping["L1Y"] = "b";
mapping["-L1Y"] = "B";
mapping["L1B"] = "c";
mapping["-L1B"] = "C";
mapping["L2W"] = "d";
mapping["-L2W"] = "D";
mapping["L2Y"] = "e";
mapping["-L2Y"] = "E";
mapping["L2B"] = "f";
mapping["-L2B"] = "F";
mapping["L3W"] = "g";
mapping["-L3W"] = "G";
mapping["L3Y"] = "h";
mapping["-L3Y"] = "H";
mapping["L3B"] = "i";
mapping["-L3B"] = "I";
mapping["O1W"] = "j";
mapping["-O1W"] = "J";
mapping["O1Y"] = "k";
mapping["-O1Y"] = "K";
mapping["O1B"] = "l";
mapping["-O1B"] = "L";
mapping["O2W"] = "m";
mapping["-O2W"] = "M";
mapping["O2Y"] = "n";
mapping["-O2Y"] = "N";
mapping["O2B"] = "o";
mapping["-O2B"] = "O";
mapping["O3W"] = "p";
mapping["-O3W"] = "P";
mapping["O3Y"] = "q";
mapping["-O3Y"] = "Q";
mapping["O3B"] = "r";
mapping["-03B"] = "R";
mapping["C1W"] = "s";
mapping["-C1W"] = "S";
mapping["C1Y"] = "t";
mapping["-C1Y"] = "T";
mapping["C1B"] = "u";
mapping["-C1B"] = "U";
mapping["C2W"] = "v";
mapping["-C2W"] = "V";
mapping["C2Y"] = "w";
mapping["-C2Y"] = "W";
mapping["C2B"] = "x";
mapping["-C2B"] = "X";
mapping["C3W"] = "y";
mapping["-C3W"] = "Y";
mapping["C3Y"] = "z";
mapping["-C3Y"] = "Z";
mapping["C3B"] = "#";
mapping["-C3B"] = "$";
}
else
{
  mapping["P"] = "a";
  mapping["-P"] = "A";
  mapping["Q"] = "b";
  mapping["-Q"] = "B";
  mapping["R"] = "c";
  mapping["-R"] = "C";
  mapping["S"] = "d";
  mapping["-S"] = "D";
  mapping["A"] = "e";
  mapping["-A"] = "E";
  mapping["R"] = "f";
  mapping["-R"] = "F";
}
}


bool isvisited(string line , map<string,bool> &visited, map<string, string> mapping)
{
  vector<string> sa;
  string ans="";
  boost::split(sa, line, boost::is_any_of("\t "));
  for(int i=0; i<sa.size(); i++)
    ans+=mapping[sa[i]];
  sort(ans.begin(), ans.end());
  if(visited.find(ans) == visited.end())
  {
    visited[ans] = true;
    return false;
  }
  return true;
}



