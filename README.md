# dag_and_deque
Double ended queue (deque) implementation with increased functionality: reversal and splitting by value. Also Performing Topological sort on a DAG

DEQUE

A deque is a double-ended queue in which elements can
be inserted and removed from both ends (top and the bottom). It has the following functions:
  • Push(x) – inserts the element x at the top of the deque,
  • Insert(x) – inserts the element x at the bottom of the deque,
  • Pop() – removes and returns the element at the top of the deque, and
  • Remove() – removes and returns the element at the bottom of the deque.
I have implemented the type Deque for you in the deque module (consisting
of deque.h and deque.c) using a doubly-linked list.

    Problem 2 A
Implements the function iterative_reverse(Deque *deque) which takes a pointer to a
Deque and reverses this deque using an iterative approach.
For example if the deque initially looks like:
  Top 4 8 9 0 1 Bottom
Then after calling iterative_reverse() the deque should look like:
  Top 1 0 9 8 4 Bottom

    Problem 2 B
The recursive_reverse(Deque *deque) function reverses the deque, although this time you uses a
recursive approach.

    Problem 2 C
The Function split(Deque *deque, int k) that rearranges the elements in the deque such that
each element with a value greater than or equal to the critical value (i.e., ≥ k) precedes (i.e., is closer
to the top of the deque) each element with a value less than k.
Within the two groups of elements (i.e., ≥ k and < k) the elements must be in their original order.
For example if we were to split the following deque with a critical value k = 3,
    Top 1 4 3 2 5 Bottom
then the resulting deque would be,
    Top 4 3 5 1 2 Bottom
This function runs in O(n) time, where n is the number of elements in the deque.

    Problem 3 A
You are provided with a Directed Acyclic Graph representing a map
of the trees on the ski slope with the possible routes between trees. A park ranger is attempted to trim 
all of the trees starting from the top of the mountain and only travelling between defined edges.
My algorithm doesn’t the order in which the trees should be visited, only
determine whether or not there does exist a valid run from the top of the mountain that visits all the
trees. If there are n trees and m edges between trees then my algorithm runs in O(n + m). My algorithm is 
implemented in C in the function is_single_run_possible() located in parkranger.c and parkranger.h. 

My program takes input (ski slope map) via stdin in the following format:
• One line containing integers n and m. n indicates the number of trees, and m indicates the
number of possible routes (i.e., edges) between trees (or between the top of the mountain and a
tree).
• m lines containing two integers u and v, which indicates that it’s possible for the park ranger to
ski from u directly to v.
The trees are labelled 1 to n, while the top of the mountain is always labelled 0.
My function performs the following steps:
• Read in the data from stdin.
• Store the data in an appropriate data structure.
• Determine whether the park ranger can trim all the trees in a single run.
• Do any clean up required (e.g., free any allocated memory).
• Return true or false depending on the result of your algorithm. Note that true and false
are of type bool, which is included from the stdbool.h library.
The following ski slope is an example of the input format your program will be given.
    4 8
    0 1
    0 3
    0 4
    1 2
    1 4
    3 1
    3 4
    4 2

    Testing functions via the following commands :
    make
    ./a1 p2a < tests/p2a-in-1.txt
Or the equivalent.
