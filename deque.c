// Implementation of a double ended queue (deque)

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "deque.h"
#include "util.h"

// Create a new empty Deque and return a pointer to it
Deque *new_deque() {
	Deque *deque = malloc(sizeof(*deque));
	assert(deque);

	deque->top = NULL;
	deque->bottom = NULL;
	deque->size = 0;

	return deque;
}

// Free the memory associated with a Deque
void free_deque(Deque *deque) {
  // Remove (and thus free) all of the nodes in the Deque.
  while (deque->size > 0) {
    deque_remove(deque);
  }

	// Free the deque struct itself
	free(deque);
}

// Create a new Node with a given piece of data
Node *new_node(Data data) {
  Node *node = malloc(sizeof(*node));
  assert(node);

  node->next = NULL;
  node->prev = NULL;
  node->data = data;

  return node;
}

// Free the memory associated with a Node
void free_node(Node *node) {
  free(node);
}

// Add an element to the top of a Deque
void deque_push(Deque *deque, Data data) {
  Node *new = new_node(data);

  if (deque->size > 0) {
    new->next = deque->top;
    deque->top->prev = new;
  } else {
    // If the Deque was initially empty then new is both the top and bottom
    deque->bottom = new;
  }

  deque->top = new;
  deque->size++;
}

// Add an element to the bottom of a Deque
void deque_insert(Deque *deque, Data data) {
  Node *new = new_node(data);

  if (deque->size > 0) {
    new->prev = deque->bottom;
    deque->bottom->next = new;
  } else {
    // If the Deque was initially empty then new is both the top and bottom
    deque->top = new;
  }

  deque->bottom = new;
  deque->size++;
}

// Remove and return the top element from a Deque
Data deque_pop(Deque *deque) {
  if (deque->size == 0) {
    exit_with_error("can't pop from empty Deque");
  }

  Data data = deque->top->data;
  Node *old_top = deque->top;

  if (deque->size == 1) {
    deque->top = NULL;
    deque->bottom = NULL;
  } else {
    deque->top = old_top->next;
    deque->top->prev = NULL;
  }

  deque->size--;

  free(old_top);

  return data;
}

// Remove and return the bottom element from a Deque
Data deque_remove(Deque *deque) {
  if (deque->size == 0) {
    exit_with_error("can't remove from empty Deque");
  }

  Data data = deque->bottom->data;
  Node *old_bottom = deque->bottom;

  if (deque->size == 1) {
    deque->top = NULL;
    deque->bottom = NULL;
  } else {
    deque->bottom = old_bottom->prev;
    deque->bottom->next = NULL;
  }

  deque->size--;

  free(old_bottom);

  return data;
}

// Return the number of elements in a Deque
int deque_size(Deque *deque) {
  return deque->size;
}

// Print the Deque on its own line with the following format:
//   [x_1, x_2, ..., x_n]
//     ^              ^
//    top           bottom
void print_deque(Deque *deque) {
  Node *current = deque->top;
  int i = 0;

  printf("[");

  while (current) {
    printf("%d", current->data);
    // Print a comma unless we just printed the final element
    if (i < deque->size - 1) {
      printf(", ");
    }
    current = current->next;
    i++;
  }

  printf("]\n");
}

// Reverse the Deque using an iterative approach
void iterative_reverse(Deque *deque) {
  Node *next_node;
  Node *curr_node;
  int iter;

  curr_node = deque->top;

  for (iter = 0; iter < deque->size; iter++) {
    // storing the address of the next node
    next_node = curr_node->next;
    // swapping next and prev pointers 
    curr_node->next = curr_node->prev;
    curr_node->prev = next_node;
    // moving onto next node
    curr_node = next_node;
  }

  // swapping top and bottom to complete reversal 
  curr_node = deque->top;
  deque->top = deque->bottom;
  deque->bottom = curr_node;
}

// Reverse the Deque using a recursive approach
void recursive_reverse(Deque *deque) {
  Node *old_top = deque->top;

  // switching next and prev pointers and changing deque->top 
  deque->top = reversal(deque->top);
  // changing deque->bottom
  deque->bottom = old_top;
}

Node *reversal(Node *node) {
  Node *temp_node;

  // swapping next and prev pointers
  temp_node = node->next;
  node->next = node-> prev;
  node->prev = temp_node;

  // triggers when end of deque is reached
  if(node->prev == NULL) {
    temp_node = NULL;
    free(temp_node);
    return node;
  }

  // recursive call if end hasnt been reached
  temp_node = NULL;
  free(temp_node);
  return reversal(node->prev);
}

// Split the Deque given a critical value k, such that the Deque contains
// all elements greater than equal to k above (i.e., closer to the top)
// the elements less than k.
//
// Within the two parts of the array (>= k and < k) the elements should
// be in their original order.
//
// This function must run in linear time.
void split_deque(Deque *deque, int k) {
  Deque *big_deque = new_deque();
  Deque *small_deque = new_deque();
  Node *curr_old_node;
  Node *curr_small_node;
  Node *curr_big_node;
  Node *curr_new_node;
  int iter;

  // iterating through deque and copying nodes to big deque and small
  // deque depending on the nodes relation to k

  // curr_old_node is the node currently being read from the input deque 
  // curr_new_node is going to be added to either small or big deque
  // curr_small_node is the last made small node 
  // curr_big_node is the last made big node
  curr_old_node = deque->top;
  for (iter = 0; iter < deque->size; iter++){
    curr_new_node = new_node(curr_old_node->data);

    if (curr_new_node->data < k) { 
      // when no nodes have been added to small deque yet
      if (small_deque->size == 0) {
        small_deque->top = curr_new_node;

      } 
      // when theyre are already nodes in small deque
      else {
        curr_new_node->prev = curr_small_node;
        curr_small_node->next = curr_new_node;
      }
      curr_small_node = curr_new_node;
      small_deque->size += 1;
    } 

    else {
      // when no nodes have been added to big deque yet
      if (big_deque->size == 0) {
        big_deque->top = curr_new_node;

      } 
      // when theyre are already nodes in small deque
      else {
        curr_new_node->prev = curr_big_node;
        curr_big_node->next = curr_new_node;
      }
      curr_big_node = curr_new_node;
      big_deque->size += 1;
    }

    curr_old_node = curr_old_node->next;
  }
  
  // if every element is bigger or smalle than k then deque 
  // can be returned un-altered 
  if (small_deque->size != 0 && big_deque->size != 0) {
   // joining big and small deque into big deque
    curr_big_node->next = small_deque->top;
    small_deque->top->prev = curr_big_node;
    big_deque->bottom = curr_small_node;

    // setting deque equal to big deque
    deque->top = big_deque->top;
    deque->bottom = big_deque->bottom;
    deque->size = small_deque->size + big_deque->size;
  }
}

