/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include "kdtree.h"

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    if(first[curDim] < second[curDim])
      return true;
    if(first[curDim] > second[curDim])
      return false;
    return first < second;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
  double dist1 = _getDistance(target, potential);
  double dist2 = _getDistance(target, currentBest);

  if(dist1 < dist2) return true;
  if(dist1 > dist2) return false;
  return (potential < currentBest);

  /*  if (potential[0] == -8 && potential[1] == 7) {
      std::cout << target << '\n';
      std::cout << currentBest << '\n';
      std::cout << potential << '\n';
    }
    double d1, d2;
    double dis1 = 0;
    double dis2 = 0;

    for(int i = 0; i < Dim; i++)
    {
      d1 = pow(target[i] - potential[i], 2);
      d2 = pow(target[i] - currentBest[i], 2);
      dis1 = dis1 + d1;
      dis2 = dis2 + d2;
    }

    bool foo;
    if(dis1 < d2) //target closer to potential
    {
      foo = true;
    }
    else if(dis1 == dis2) //break tie with operator <
      foo = potential < currentBest;
    else
     foo = false;

     std::cout << foo << '\n';
    return foo;*/
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
  size = newPoints.size();

  //copy the inputs points into a point std::vector
  points = newPoints;

  root = NULL;

  if(size == 0) return; //size == 1??

//  cout << "new node: " << endl;

  _build_tree(0, size - 1, 0, root);

}

template <int Dim>
void KDTree<Dim>::_build_tree(int start, int end, int dimension, KDTreeNode *& subRoot)
{
  //automatically round to floor value
  int med_index = (start + end) / 2;

  if(start > end)
    return;

  //find median
  _quick_select(start, end, med_index, dimension);

  subRoot = new KDTreeNode(points[med_index]);

  _build_tree(start, med_index - 1, (dimension + 1) % Dim, subRoot->left);
  _build_tree(med_index + 1, end, (dimension + 1) % Dim, subRoot->right);


}

//selects the kth smallest value in a list
//here k is just meidan_index
//but we want the function to be general
template <int Dim>
void KDTree<Dim>::_quick_select(int start, int end, int k, int dimension)
{
  if(start >= end)
    return;

  int pivot_index = _partition(start, end, dimension);

  if(k < pivot_index)
    _quick_select(start, pivot_index - 1, k, dimension);

  if(k > pivot_index)
    _quick_select(pivot_index + 1, end, k, dimension);

}

//sort the vector around the pivot
//everything before pivot are smaller, after greater
template <int Dim>
int KDTree<Dim>::_partition(int start, int end, int dimension)
{
  //set pivot to last element in the part of vector to be partitioned
  Point<Dim> pivot = points[end];
  //set marker index to start index
  int i = start;

  for(int j = start; j < end; j++)
  {
    //place points smaller than pivot before marker
    if(smallerDimVal(points[j], pivot, dimension))
    {
      swap(points[i], points[j]);
      i++;
    }
  }
  //update marker position
  swap(points[i], points[end]);
  //return position of marker
  return i;

}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /*points = other.points;
  size = other.size;
  _copy(other.root);*/
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::_copy(const KDTreeNode *& node)
{
  if(node != NULL)
   {
     KDTreeNode * new_node = new KDTreeNode(node->point);
     new_node->left = _copy(node->left);
     new_node->right = _copy(node->right);
     return new_node;
   }
   return NULL;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  if(this != &rhs)
  {
    _clear();
    _copy(rhs);
  }
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  _clear(root);
}

template <int Dim>
void KDTree<Dim>::_clear(KDTreeNode *& root)
{

  //recursively delete the whole tree
   if(root != NULL)
   {
  //   if(root->left != NULL)
      _clear(root->left);
  //   if(root->right != NULL)
      _clear(root->right);
     delete root;
      root = NULL;
   }
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{

  Point<Dim> curr_best = root->point;
  double best_dist = 0;

  _findNearestNeighbor_helper(query, curr_best, best_dist, root, 0);

  return curr_best;

}

template <int Dim>
void KDTree<Dim>::_findNearestNeighbor_helper(const Point<Dim> & query, Point<Dim> & curr_best,
   double & best_dist, KDTreeNode * subRoot, int curr_dim) const
{

//  if(subRoot)
  //  std::cout << "Current point: " << subRoot->point << '\n';

  if(subRoot == NULL) return;

  //base case: leaf node automatically become curr_best, update distance
  if((subRoot->left == NULL && subRoot->right == NULL && shouldReplace(query, curr_best, subRoot->point))
    || subRoot->point == query)
  {
      curr_best = subRoot->point;
      best_dist = _getDistance(query, subRoot->point);
    //  std::cout << "Current best set to leaf: " << curr_best << std::endl;
    //  std::cout << "Best dist update to: " << best_dist << std::endl;

    return;
  }

  //recursively traverse kdtree
  //traverse left tree if curr_dim of target point less than current point
  //move onto next dimension
  if(smallerDimVal(query, subRoot->point, curr_dim))
  {
  //  std::cout << "Go left" << std::endl;
    if(subRoot->left != NULL)
      _findNearestNeighbor_helper(query, curr_best, best_dist, subRoot->left, (curr_dim + 1) % Dim);

    //check if closer points present in parent nodes
    if(shouldReplace(query, curr_best, subRoot->point))
    {
      curr_best = subRoot->point;
      best_dist = _getDistance(query, subRoot->point);
    //  std::cout << "Current best update to: " << curr_best << std::endl;
    //  std::cout << "Best dist updated to: " << best_dist << std::endl;
    }

    //check if other side contains closer node
    //check if current splitting plan's dist from target node is within current raidus
    //only check opposite subtree if within radius
    if(pow(subRoot->point[curr_dim] - query[curr_dim], 2) <= best_dist)
    {
  //  std::cout << "Current radius: " << pow(subRoot->point[curr_dim] - query[curr_dim], 2) << '\n';
  //  std::cout << "Check right side" << std::endl;
      _findNearestNeighbor_helper(query, curr_best, best_dist, subRoot->right, (curr_dim + 1) % Dim);
    }
  }
  else
  {
  //  std::cout << "Go right" << std::endl;
    if(subRoot->right != NULL)
    _findNearestNeighbor_helper(query, curr_best, best_dist, subRoot->right, (curr_dim + 1) % Dim);

    //check if parent nodes are closer, update if necessary
    if(shouldReplace(query, curr_best, subRoot->point))
    {
      curr_best = subRoot->point;
      best_dist = _getDistance(query, subRoot->point);
    //  std::cout << "Current best updated to: " << curr_best << std::endl;
    //  std::cout << "Best dist updated to: " << best_dist << std::endl;

    }


    //check if other side contains closer node
    //check if current splitting plan's dist from target node is within current raidus
    //only if within radius, check opposite subtree
    if(pow(subRoot->point[curr_dim] - query[curr_dim], 2) <= best_dist)
    {
    //  std::cout << "Current radius: " << pow(subRoot->point[curr_dim] - query[curr_dim], 2) << '\n';
    //  std::cout << "Check left side" << std::endl;
      _findNearestNeighbor_helper(query, curr_best, best_dist, subRoot->left, (curr_dim + 1) % Dim);
    }
  }

}

/**
 * Helper function to get squared distance between two points.
 */
template <int Dim>
double KDTree<Dim>::_getDistance(const Point<Dim>& p1, const Point<Dim>& p2) const
{
  double distance = 0;
  for (int i = 0; i < Dim; i++) {
    distance += pow((p1[i] - p2[i]), 2);
  }
  return distance;
}

/**
 * Helper function to tell if the nearest neighbor could be on the other side
 * of the KD tree.
 */
/*template <int Dim>
bool KDTree<Dim>::_check_other_side(const Point<Dim>& query,
  const Point<Dim>& curr, int dimension, double distance) const
{
  return pow((curr[dimension]- query[dimension]), 2) <= distance;
}*/
