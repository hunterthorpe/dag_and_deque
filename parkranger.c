
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "parkranger.h"
#include "util.h"
#include "deque.h"

#define SIZE 0 
#define MOUNTAIN 0

// This function reads in a ski slope map and determine whether or not
// it is possible for the park ranger to trim all of the trees on the ski slope
// in a single run starting from the top of the mountain.
//
// The ski slope map is provided via stdin in the following format:
//
//   n m
//   from to
//   from to
//   ...
//   from to
//
// Here n denotes the number of trees that need trimming, which are labelled
// {1, ..., n}. The integer m denotes the number "reachable pairs" of trees.
// There are exactly m lines which follow, each containing a (from, to) pair
// which indicates that tree `to` is directly reachable from tree `from`.
// `from` and `to` are integers in the range {0, ..., n}, where {1, ..., n}
// denote the trees and 0 denotes the top of the mountain.
//
// For example the following input represents a ski slope with 3 trees and
// 4 reachable pairs of trees.
//
// input:            map:          0
//   3 4                          / \
//   0 1                         /  2
//   0 2                        / /
//   2 1                        1
//   1 3                          \
//                                 3
//
// In this example your program should return `true` as there is a way to trim
// all trees in a single run. This run is (0, 2, 1, 3).
//
//	  Function does the following
//  - Read in this data from stdin
//  - Store this data in an appropriate data structure
//  - Run the algorithm you have designed to solve this problem
//  - Do any clean up required (e.g., free allocated memory)
//  - Return `true` or `false` (included in the stdbool.h library)


// Performing topological sort by appling depth first search recursivley 
bool find_path (Deque *stack, int **adj_lists, int num_edges, int num_trees) {
	int iter;

	// exits function early if path has already been found
	if (stack->size == num_trees + 1) {
		return true;
	}
	
	for (iter = 1; iter < adj_lists[stack->top->data][SIZE] + 1; iter++) {
		if (stack->size == num_trees + 1){
			return true;
		}
		
		// adding adjacent node onto stack and making recursive call
		deque_push(stack, adj_lists[stack->top->data][iter]);
		if (stack->size == num_trees + 1) {
			return true;
		}

		find_path(stack, adj_lists, num_edges, num_trees);
	} 

	// if no adjacent node is found, a step is taken backwards 
	deque_pop(stack);	
	if (stack->size == 0) {
		return (false);
	}
	return true;
}

bool is_single_run_possible() {
	int num_trees;
	int num_edges;
	int iter;
	int edge_start;
	int edge_finish;
	bool return_value;
	Deque *stack = new_deque();

  	scanf("%d %d", &num_trees, &num_edges);

  	// creating an array of arrays to store edge information  
  	int **adj_lists;
  	adj_lists = malloc((num_trees + 1) * sizeof(int *));
  	for (iter = 0;  iter < num_trees + 1; iter++) {
  		adj_lists[iter] = malloc(num_trees + 1 * sizeof(int));
  		adj_lists[iter][SIZE] = 0;
  	}

  	// adj_list has an array for each node, within each of these node_arrays the first 
  	// value indicates the number of current nodes (size), each value after represents
  	// which nodes can be travelled to from the current node 
  	for (iter = 0; iter < num_edges; iter++){
  		scanf("%d %d", &edge_start, &edge_finish);
  		adj_lists[edge_start][adj_lists[edge_start][SIZE] + 1] = edge_finish;
  		adj_lists[edge_start][SIZE] += 1;
  	}

  	// adding mountain node to stack and searching for path
  	deque_push(stack, MOUNTAIN);
  	return_value = find_path(stack, adj_lists, num_edges, num_trees);

  	free_deque(stack);
  	for (iter = 0; iter < num_trees + 1; iter++) {
  		free(adj_lists[iter]);
  	}

  	return return_value;
}
