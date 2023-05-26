#include "../include/common.h"
#include "pa4.h"


// don't remove these globals
struct heap_elem *min_heap_arr = NULL;

// don't modify this function
void initialize_min_heap_arr(struct heap_elem *arr)
{
  min_heap_arr = arr;
}

// don't modify this function
static void *allocate_memory(size_t size)
{
  return __mymalloc(size);
}

// don't modify this function
static void free_memory(void *ptr)
{
  __myfree(ptr);
}

// ---------------- Add your code below this line ----------------- //


// The friends field in "struct record" stores the
// head of the linked list of friends of a given user.
// return r->friends.
struct list_records* get_friends_list(struct record *r)
{
}

// Make r1 and r2 friends of each other if they aren't already friends.
// The friends field in "struct record" stores the
// head of the linked list of friends of a given user.
// Return 1 if r1 and r2 are already friends before this call.
// Otherwise, make r1 a friend of r2 and return 0.
// To make r1 a friend of r2, 
// insert r1 into the list r2->friends and insert r2 into the list r1->friends.
int make_friends(struct record *r1, struct record *r2)
{
}

// remove all nodes from r->friends and release the corresponding memory
void delete_friends_list(struct record *r)
{
}

// Each friends f of r is connected via an undirected
// edge whose weight is the distance between r and f.
// compute the shortest distance and a shortest path to 
// all other vertices reachable from r.
// initially, the status fields in all records are set to zero.
// distance and pred fields may contain grabage values.
// you need to use the distance function to compute the distance
// between two records.
// you can use min_heap_arr to implement a min heap or
// a linear scan to find a vertex with the minimum distance.
// In addition to distance and pred, you can also update the
// status field in your implementation.
// Don't modify other fields in struct record.
// At the end of this procedure, distance field in each record
// reachable via r, must contain the minimum distance from r;
// and the pred field must contain the predecessor on a shorest
// path.
void compute_sssp(struct record *r)
{
}
