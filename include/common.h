#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <sys/time.h>

#define MAX_LEN 16
#define MAX_MSG_LEN 128
#define MSG_SCALE 3
#define PI (22.0 / 7.0)
#define INVALID_STATUS (-1)


struct trie_node;
struct list_tri;
struct list_rec;

struct location {
	double lat;
	double lon;
};

struct record {
  /* character string terminated with '\0'
   * maximum length is 16
   */
  char name[MAX_LEN];
  /* a character array of 16 characters
   * not-necessarily terminated with '\0'
   * a uid may conatin multiple '\0''s
   * anywhere in the character array
   */
  char uid[MAX_LEN];

  int age;

  /* location */
	struct location loc;

  /* list of posts */
  struct list_tri *posts;

  /* list of friends */
  struct list_rec *friends;

	/* needed for shortest Path */
	int status;
	struct record *pred;

  /* needed for the tree data-structure */
  int height;
  struct record *left;
  struct record *right;
  struct record *parent;
};

struct trie_node {
  char val;
  /*first is the first child of trie node */
  struct trie_node *child;
  /* next is a sibling of a trie node */
  struct trie_node *next;

  /* If the current trie node is last character
   * of a post, active is the list of all the users 
   * who have posted this message, but haven't deleted yet.
	 */
  struct list_rec *active;

  /* If the current trie node is last character
	 * of a post, deleted is the list of all the users
   * who have deleted this message after posting. 
   */
  struct list_rec *deleted;
};

// list of trie_nodes
struct list_tri {
  struct trie_node *node;
  struct list_tri *next;
};

// list of record pointers
struct list_rec {
  struct record *rec;
  struct list_rec *next;
};

void *__mymalloc(size_t size);
void __myfree(void *ptr);
size_t __get_size(void *ptr);
void create_record(struct record *r, int seed);
void create_uid(char uid[MAX_LEN], int seed, int verify);
void create_uid_new(char uid[MAX_LEN], int seed);
void verify_size_insert(struct record *arr, int num_records);
void verify_size_delete(struct record *arr, int num_records);
void verify_memory_leak();
void start_time(struct timeval *start);
unsigned long end_time(struct timeval *start);
void create_msg(char msg[MAX_MSG_LEN], int id, int size);
void initialize_hash_tables(size_t size);
void delete_msg(int id, int size);
double distance(struct location *loc1, struct location *loc2);
void create_name(char name[MAX_LEN], int seed);
void check_array_is_sorted_by_uid(struct record *record_arr, size_t num_record, size_t chksum);
void check_array_is_sorted_by_name(struct record *record_arr, size_t num_record, size_t chksum);
void verify_chksum(struct record *record_arr, size_t num_record, size_t chksum);

#endif
