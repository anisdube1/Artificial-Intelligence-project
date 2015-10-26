#include<iostream>
#include<stdio.h>
#include<vector>

using namespace std;

vector<node*> zebra_var()
{
  vector<node*> var;
  var.push_back(new node("house", "Red"));
  var.push_back(new node("house", "Green"));
  var.push_back(new node("house", "Yellow"));
  var.push_back(new node("house", "Blue"));
  var.push_back(new node("house", "Ivory"));
  var.push_back(new node("man", "Englishman"));
  var.push_back(new node("man", "Spaniard"));
  var.push_back(new node("man", "Norwgian"));
  var.push_back(new node("man", "Japanese"));
  var.push_back(new node("man", "Ukranian"));
  var.push_back(new node("animal", "Dog"));
  var.push_back(new node("animal", "Fox"));
  var.push_back(new node("animal", "Snails"));
  var.push_back(new node("animal", "Horse"));
  var.push_back(new node("animal", "Zebra"));
  var.push_back(new node("eat", "Hershey"));
  var.push_back(new node("eat", "KitKat"));
  var.push_back(new node("eat", "Smarties"));
  var.push_back(new node("eat", "Snicker"));
  var.push_back(new node("eat", "Milky Way"));
  var.push_back(new node("drink", "Orange"));
  var.push_back(new node("drink", "Tea"));
  var.push_back(new node("drink", "Coffee"));
  var.push_back(new node("drink", "Milk"));
  var.push_back(new node("drink", "Water"));
  return var;

}

vector<int> zebra_domain()
{
  vector<int> domain;
  domain.push_back(1);
  domain.push_back(2);
  domain.push_back(3);
  domain.push_back(4);
  domain.push_back(5);
  return domain;
}


