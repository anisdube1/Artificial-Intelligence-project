#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<map>

using namespace std;

map<string, bool> mymap;

vector<vector<char> > gen_input(int num_stack, int num_block)
{
  int num_path = 25;
  srand (time(NULL));
  vector<vector<char> > block;
  vector <int> element;
  bool state_checked(vector<vector<char> >);

 for (int i=0; i<num_block; i++)
      element.push_back(i);

  for (int i=0; i <num_stack-1; i++)
    {
      int ran = rand() % num_block ;
      vector <char> row;
      for (int j=0; j<ran ; j++)
	{
	  int sel = rand() % num_block;
	  row.push_back(element[sel] + 'A');
	  swap(element[sel], element[num_block-1]);
	  num_block--;
	}
      block.push_back(row);
    }
  
  if(num_block > 0)
    {
      vector <char> temp;
      int num_block_temp = num_block;
      for (int i=0; i<num_block_temp; i++)
        {
          int sel = rand() % num_block;
          temp.push_back(element[sel] + 'A');
	  swap(element[sel], element[num_block-1]);
	  num_block--;
        }
      block.push_back(temp);
    }


/*
   Different Sample Input-----------------------------------------------------------
 J O N P R K H G M F
 A D S B E Q L C I





 T
  vector<char> temp;
  temp.push_back('J');
  temp.push_back('O');
  temp.push_back('N');
  temp.push_back('P');
  temp.push_back('R');
  temp.push_back('K');
  temp.push_back('H');
  temp.push_back('G');
  temp.push_back('M');
  temp.push_back('F');
  block.push_back(temp);
  vector<char> temp1;
  temp1.push_back('A');
  temp1.push_back('D');
  temp1.push_back('S');
  temp1.push_back('B');
  temp1.push_back('E');
  temp1.push_back('Q');
  temp1.push_back('L');
  temp1.push_back('C');
  temp1.push_back('I');
  block.push_back(temp1);
  vector<char> temp3;
  block.push_back(temp3);
  block.push_back(temp3);
  block.push_back(temp3);
  block.push_back(temp3);
  block.push_back(temp3);
  vector<char> temp4;
  temp4.push_back('T');
  block.push_back(temp4);
*/

/*
  vector<char> temp;
  temp.push_back('D');
  block.push_back(temp);
  vector<char> temp1;
  temp1.push_back('E');
  temp1.push_back('F');
    temp1.push_back('I');
    temp1.push_back('J');
    block.push_back(temp1);
    vector<char> temp2;
   temp2.push_back('B');
     temp2.push_back('G');
      block.push_back(temp2);
      vector<char> temp3;
     temp3.push_back('C');
     temp3.push_back('H');
        block.push_back(temp3);
         vector<char> temp4;
      temp4.push_back('A');
    block.push_back(temp4);
*/

/*  
   vector<char> temp;
     temp.push_back('B');
    block.push_back(temp);
   vector<char> temp1;
  temp1.push_back('C');
    temp1.push_back('E');
    block.push_back(temp1);
   vector<char> temp2;
  temp2.push_back('A');
    temp2.push_back('D');
      block.push_back(temp2);
  */


  return block;
}
void swap(int &a, int &b)
{
  int temp;
  temp=a;
  a=b;
  b=temp;
}

bool state_checked(vector<vector<char> > state)
{
  string key ="";
  for(int i=0; i<state.size(); i++)
    {
      for(int j=0; j<state[i].size(); j++)
	{
	  key+= state[i][j];
	}
      key+= i;
    }  
  if(mymap.find(key) != mymap.end())
    return true;
  else
    {
      mymap[key] = true;
      return false;
    }

}
