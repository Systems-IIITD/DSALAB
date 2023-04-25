#ifndef __PA1_H__
#define __PA1_H__

#include "../include/common.h"

void insert_record_bst(struct record r);
void insert_record_avl(struct record r);
struct record search_record_avl(char uid[MAX_LEN]);
struct record search_record_bst(char uid[MAX_LEN]);
struct record delete_record_bst(char uid[MAX_LEN]);
struct record delete_record_avl(char uid[MAX_LEN]);
struct record *get_bst_root();
struct record *get_avl_root();
size_t get_num_bst_records();
size_t get_num_avl_records();

size_t get_num_records_with_name_bst(char name[MAX_LEN]);
size_t get_num_records_with_name_avl(char name[MAX_LEN]);
void destroy_bst();
void destroy_avl();
void preorder(struct record *r);
int make_friends_bst(char uid1[MAX_LEN], char uid2[MAX_LEN]);
int make_friends_avl(char uid1[MAX_LEN], char uid2[MAX_LEN]);
struct list_records *get_friends_list_bst(char uid[MAX_LEN]);
struct list_records *get_friends_list_avl(char uid[MAX_LEN]);

#endif
