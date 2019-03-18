#include "dsets.h"

/* creates n unconnceted root nodes at the end of the vector*/
void DisjointSets::addelements(int num)
{
  //get the size before adding elements
//  int size = sets.size();
  for(int i = 0; i < num; i++)
  {
  //  sets.push_back((-1) * (i + size));
    sets.push_back(-1);
  }
}

/* compress paths*/
int DisjointSets::find(int elem)
{
  //root
  if(sets[elem] < 0)
    return elem;
  sets[elem] = find(sets[elem]);
  return sets[elem];
}

/* union by size*/
void DisjointSets::setunion(int a, int b)
{
  int root_1 = find(a);
  int root_2 = find(b);

  if(root_1 == root_2) return;

  //a negative number
  int new_size = sets[root_1] + sets[root_2];

  //root_1 more negative-> greater size
  if(sets[root_1] <= sets[root_2])
  {
    sets[root_2] = root_1;
    sets[root_1] = new_size;
  }else
  {
    sets[root_1] = root_2;
    sets[root_2] = new_size;
  }
  return;
}

/* return the number of nodes in the up-tree containing the element*/
int DisjointSets::size(int elem)
{
  return (-1) * sets[find(elem)];
}
