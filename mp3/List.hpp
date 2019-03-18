#include <iostream>
using namespace std;
/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */


/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
//  return List<T>::ListIterator(head_); //head_?
  return ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
//  return List<T>::ListIterator(tail_);//tail_?
    return ListIterator(NULL);
}

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <typename T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  _destroy();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode * curr = head_;
  while (curr)
  {
    ListNode * old = curr;
    curr = curr->next;
    delete old;
  }
  head_ = NULL;
  tail_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * node_ = new ListNode(ndata);

  if(head_ == NULL) //list empty
  {
    node_->prev = NULL;
    node_->next = NULL;
    head_ = node_;
    tail_ = head_;
  }
  else
  {
    node_->next = head_;
    head_->prev = node_;
    head_ = node_;
   }
  length_++;
  node_ = NULL;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * node_ = new ListNode(ndata);

  if(tail_ == NULL) //list empty
  {
    node_->prev = NULL;
    node_->next = NULL;
    head_ = node_;
    tail_ = head_;
  }else
  {
    node_->prev = tail_;
    tail_->next = node_;
    tail_ = node_;
  }
  length_++;
  node_ = NULL;
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1
  //edge cases when start before head or end after tail, or only one node to reverse
/*  if(startPoint == NULL || endPoint == NULL || startPoint == endPoint) return;

    ListNode * original_start = startPoint;
    ListNode * original_end = endPoint;

    //swap startPoint and endPoint until they meet in the middle
    while(startPoint != endPoint )
    {
      swap(startPoint, endPoint);
      cout << "Swapped!" << endl;
      //move startPoint to next of the current endPoint
      //endPoint to prev of current startPoint
      ListNode * temp = startPoint;
      startPoint = endPoint->next;
      startPoint->prev = endPoint;
      endPoint = temp->prev;
      endPoint->next = temp;
    }

    //update new startPoint and endPoint
    if(original_start->prev != NULL)
      original_start->prev->next = startPoint;
    else
      head_ = startPoint;
    if(original_end->next != NULL)
      original_end->next->prev = endPoint;
    else
      tail_ = endPoint;*/

    //empty list or no elements to be reversed - do nothing
    if(!startPoint|| !endPoint|| startPoint == endPoint) return;

    //preserve original startPoint and endPoint
     ListNode * original_start = startPoint;
     ListNode * original_prev = startPoint->prev;
     ListNode * original_end = endPoint;
     ListNode * original_next = endPoint->next;

      //swap the prev and next of the current node
      //change direction of the prev and next pointers
      while(startPoint != endPoint)
      {
        ListNode * temp = startPoint->next;
        startPoint->next = startPoint->prev;
        startPoint->prev = temp;

        startPoint = startPoint->prev;
      }
      //startPoint is now at endPoint
      //endPoint is now at startPoint

      //update links
      ListNode * temp = startPoint->prev;
      startPoint->prev = original_prev;
      startPoint->next = temp;
      endPoint = original_start;
      endPoint->next = original_next;

      //Update startPoint to point at new startPoint
      if(original_next)
        original_next->prev = endPoint;
      else
        tail_ = endPoint;

      //Update endPoint to point at new endPoint
      if(original_prev)
        original_prev->next = startPoint;
      else
        head_ = startPoint;
}

/*template <typename T>
   void List<T>::swap(ListNode * n1, ListNode * n2)
  {
    if(!n1 || !n2) return;

    //swapping n1 and n2
    ListNode * temp = n1;

    if(temp->prev && temp->next)
    {
      temp->prev = n1->prev;
      temp->next = n1->next;

      n1->prev = n2->prev;
      n1->next = n2->next;

    n2->prev = temp->prev;
    n2->next = temp->next;
  }

    //updating outer pointers
    if(n1->next) n1->next->prev = n2;
    if(n1->prev) n1->prev->next = n2;
    if(n2->next) n2->next->prev = n1;
    if(n2->prev) n2->prev->next = n1;


  }*/


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1

  //List empty
  if(!head_) return;

  ListNode * startPoint = head_;
  ListNode * endPoint = head_;

  while(startPoint && endPoint && startPoint->next && endPoint->next) //loop while not reaching the end of the list
  {
    //finding endpoint for every block
    endPoint = startPoint;
    for(int i = 0; i < n-1; i++)
    {
      //locate the endPoint
      //n = 0, endPoint = head_
      //n = 1, endPoint = head_ - no reverse
      //n = 2, endPoint = head_->next
      if(endPoint->next) //take care of when less than n elements left
        endPoint = endPoint->next;
    }
    reverse(startPoint, endPoint);
    startPoint = endPoint->next;
  //  cout << "startPoint: " << startPoint->data << endl;
  //  cout << "endPoint: " << endPoint->data << endl;


  }


}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1

  if (length_ > 1) {
		ListNode* curr = head_->next;
		ListNode* next = curr->next;
		while (curr != NULL) {
			next = curr->next;

      if (curr != tail_) {
		if (curr->prev != NULL) {
			curr->prev->next = curr->next;
		}
		if (curr->next != NULL) {
			curr->next->prev = curr->prev;
		}

		tail_->next = curr;
		curr->prev = tail_;
		curr->next = NULL;
		tail_ = curr;
	}

			if (next != NULL && next->next != NULL) {
				curr = next->next;
			} else {
				return;
			}
		}
	}


}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <typename T>
List<T> List<T>::split(int splitPoint) {
  //splitPoint past end of the list, return empty list
    if (splitPoint > length_)
        return List<T>();

    //splitPoint before end, split from head
    if (splitPoint < 0)
        splitPoint = 0;

    //store the head of the split list as secondHead
    ListNode * secondHead = split(head_, splitPoint);

    //preserve original list length
    int oldLength = length_;

    if (secondHead == head_) { //split from head (split list equal to original list)
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL) //loop until tail of first list is found
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  //split from head - split list is original list
  if(splitPoint == 0) return head_;

  //split from tail - split list starts at tail->next
  else if(splitPoint == length_) return NULL;

  else
  {
    //find newStartpoint
    //set tail->next of first list to null, head->prev of new list to null
      while(splitPoint > 0)
      {
        start = start->next;
        splitPoint--;
      }
      //start is now at new start point
      tail_ = start->prev;
      tail_->next = NULL;
      start->prev = NULL;
      return start;
  }

}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
/*  if(first == NULL)

  if(second == NULL)

  ListNode * curr = first;
  while(curr && second)
  {
    if(curr->data < second->data)
    {
      second->prev = curr;
      ListNode * temp1 = curr->next;
      curr->next = second;
      ListNode * temp2 = second->next;
      second->next = temp1;
      second = temp2;
      curr = curr->next;
    }else
    {
      ListNode * temp2 = second->next;
      second->next = curr;
      curr->prev = second;
      ListNode * temp1 = curr->next;
      curr->next = temp2;

    }
  }
  return first;*/


  if(!first || !second) return NULL;

	if(first == second) return first;

	ListNode * curr1 = first;
	ListNode * curr2 = second;
	ListNode * newHead = first;

	if(first->data < second->data)
	{
		curr1 = first->next;
	}
	else
	{
		newHead = second;
		curr2 = second->next;
	}

	ListNode * result = newHead;
	while(curr1 && curr2)
	{
		if(curr1->data < curr2->data || !curr2)
		{
			result->next = curr1;
			curr1->prev = result;
			result = curr1;
			curr1 = curr1->next;
		}
		else
		{
			result->next = curr2;
			curr2->prev = result;
			result = curr2;
			curr2 = curr2->next;
		}
	}
	if(curr1 == NULL)
	{
		result->next = curr2;
		curr2->prev = result;
	}
	else
	{
		result->next = curr1;
		curr1->prev = result;
	}
	second = NULL;
	return newHead;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <typename T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  ListNode * newHead = start;

   	if (chainLength == 1)
	{
		start->next = start->prev = NULL;
		return start;
	}
	else
	{
		ListNode * curr = start;
		for(int i = 0; i < chainLength/2; i++)
			curr = curr->next;
		curr->prev->next = NULL;
		curr->prev = NULL;
		start = mergesort(start, chainLength/2);
		curr = mergesort(curr, chainLength-chainLength/2);
		newHead = merge(start, curr);
	}
	return newHead;
}
