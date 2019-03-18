#pragma once
#include <vector>

using namespace std;

class DisjointSets
{
public:

  /* creates n unconnceted root nodes at the end of the vector*/
  void addelements(int num);

  /* compress paths*/
  int find(int elem);

  /* union by size*/
  void setunion(int a, int b);

  /* return the number of nodes in the up-tree containing the element*/
  int size(int elem);

private:
  vector<int> sets;

};
