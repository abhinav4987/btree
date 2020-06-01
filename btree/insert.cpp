#include "btree.hpp"
#include<bits/stdc++.h>

node* get_node()
{
	node* neww = (node*)malloc(sizeof(node));
	neww->net_key = 0;
	neww->leaf = true;
	for(int i = 0 ; i< POINTER; i++)
	{
		neww->child_pointer[i] = NULL;
		neww->key_value[i] = 0;
	}

	return neww;
}



node*  split_node(node* parent, node* to_split)
{
	 int mid = KEY/2;

	 node* left = get_node();
    // entering into new node
	if(!to_split->leaf)
	{
		left->leaf = false;
	}
	 for(int i=0;i<mid;i++)
	 {
		 left->key_value[i] = to_split->key_value[i];
	 }
      int en_key = to_split->key_value[mid];

	 for(int i=0;i<=mid;i++)
	 {
		 left->child_pointer[i] = to_split->child_pointer[i];
	 }


     //deleting and shifting
	 for(int i = mid +1;i< KEY;i++)
	 {
       to_split->key_value[i-mid-1] = to_split->key_value[i];
	   to_split->key_value[i] = 0;
	 }
	 for(int i = mid + 1;i<POINTER;i++)
	 {
         to_split->child_pointer[i-mid-1]  = to_split->child_pointer[i];
		 to_split->child_pointer[i] = NULL;
	 }
	
	left->net_key = mid;
	to_split->net_key = KEY - mid-1;

// 	for(int i = 0;i<to_split->net_key;i++)
// 	cout << to_split->key_value[i]<<" ";
// 	cout << endl;
// 	// finding the apt position in parent
// cout << left->net_key << " \n" << to_split->net_key << endl;
	int i = parent->net_key ;
	while(parent->key_value[i-1] > en_key && i >0)
	{
		parent->key_value[i] = parent->key_value[i-1];
		i--;
	}
	parent->key_value[i] = en_key;
    int j = parent->net_key+1;
	while(j>i)
	{
		parent->child_pointer[j+1] = parent->child_pointer[j];
		j--; 
	} 
	parent->child_pointer[j] = left;
	parent->child_pointer[j+1] = to_split;
	parent->net_key++;

	return parent;
}

node* non_full_insert(int key,node* nodet)
{
   if(nodet->leaf == true)
   {
        //insert in right place
		int i = nodet->net_key;
		while (nodet->key_value[i-1] > key && i > 0)
		{
			nodet->key_value[i] = nodet->key_value[i-1];
			i--;
		}
		nodet->key_value[i] = key;
		nodet->net_key++;
		return nodet;
   }

   else
   {
	   int i = nodet->net_key-1;
	   while(nodet->key_value[i] > key && i>= 0)
	   {
		   i--;
	   }

	   if(nodet->child_pointer[i+1]->net_key == KEY)
	   {
          nodet = split_node(nodet,nodet->child_pointer[i+1]);
		  if(key > nodet->key_value[i+1])
		  i = i+1;	
 	      nodet->child_pointer[i+1] = non_full_insert(key,nodet->child_pointer[i+1]);	  	   
	   }

	   else
	   {
		   nodet->child_pointer[i+1] = non_full_insert(key,nodet->child_pointer[i+1]);
	   }

    }

	return nodet; 
   
}


void insert(int key, btree*  nodet)
{
    result* is_it_in = search(key,nodet->root);
	if(is_it_in->found == true)
	{
		cout << " already in ";
		return ;
	}
	node* root = nodet->root;

	if(root->net_key == KEY)
	{
		node* new_root = get_node();
		new_root->leaf = false;
		new_root = split_node(new_root,root);
		nodet->root = new_root;
		nodet->root = non_full_insert(key,nodet->root);
	}

	else
	{
		nodet->root = non_full_insert(key,nodet->root);
	}
	
	
} 
