#include<bits/stdc++.h>
using namespace std;
#define KEY 5
#define POINTER 6
#define t  3

#define KEY 5
#define POINTER 6
#define t  3
typedef struct tree
{
	int net_key;
	int key_value[POINTER];
	struct tree* child_pointer[POINTER];
	bool leaf;
}node;

typedef struct search_result
{
	node* res;
	bool found;
	int pos;
}result;
typedef struct btree
{
	node* root;
	int order;
}btree;


node* remove_key(node* nodet,int key);
result* get_result_node();
node* get_node();
result* search(int key, node* nodet);

node*  split_node(node* parent, node* to_split);
node* non_full_insert(int key,node* nodet);
void insert(int key, btree*  nodet);
void print_node(node* noode);
node* merge(node* nodet, int pos);

int get_pred(int pos, node* nodet);
int get_succ(int pos,node* nodet);
node* rem_from_leaf(int key,node* nodet,int pos);
node* rem_from_int(int key,node* nodet,int pos);
node* borrow_from_left(node* nodet,int  pos);
node* borrow_from_right(node* nodet, int pos);
node* remove_key(node* nodet,int key);



