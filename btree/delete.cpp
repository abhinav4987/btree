#include "btree.hpp"
#include<bits/stdc++.h>

int get_pred(int pos, node* nodet)
{
   node* pred = nodet->child_pointer[pos];

   while(!pred->leaf)
   {
	   pred = pred->child_pointer[pred->net_key];
   }

   return pred->key_value[pred->net_key-1];

}
int get_succ(int pos,node* nodet)
{
    node* suc = nodet->child_pointer[pos+1];

	while(!suc->leaf)
	{
		suc = suc->child_pointer[0];
	}

	return suc->key_value[0];
}


node* rem_from_leaf(int key,node* nodet,int pos)
{
    int i = pos;

	while(i< nodet->net_key)
	{
		nodet->key_value[i]= nodet->key_value[i+1];
		i++;
	}
	nodet->key_value[nodet->net_key-1] = 0;
	nodet->net_key--;
	return nodet;
}

node* rem_from_int(int key,node* nodet,int pos)
{
   if(nodet->child_pointer[pos]->net_key >= t)
   {
      int pred = get_pred(pos,nodet);
	  nodet->key_value[pos] = pred;
	  nodet->child_pointer[pos] = remove_key(nodet->child_pointer[pos],pred);
   }

   else if(nodet->child_pointer[pos+1]->net_key >= t)
   {
      int suc = get_succ(pos,nodet);
	  nodet->key_value[pos] = suc;
	  nodet->child_pointer[pos+1] = remove_key(nodet->child_pointer[pos+1],suc);
   }

   else
   {
	   
	   merge(nodet,pos);
	   nodet->child_pointer[pos] = remove_key(nodet->child_pointer[pos],key);
   }
   
   return nodet;
}

node* borrow_from_left(node* nodet,int  pos)
{
    int from_parrent;
	int from_left;
	node* left_sib = nodet->child_pointer[pos-1];
    from_parrent = nodet->key_value[pos-1];
	from_left = left_sib->key_value[left_sib->net_key-1];
	
	
	
	node* borrowed_from_left = left_sib->child_pointer[left_sib->net_key];
	left_sib->key_value[left_sib->net_key-1] = 0;
	left_sib->child_pointer[left_sib->net_key] = NULL;

	nodet->key_value[pos-1] = from_left;
    node* main_sib = nodet->child_pointer[pos];
	
	int i = main_sib->net_key;
	while(i>=1)
	{
		main_sib->key_value[i] = main_sib->key_value[i-1];
		i--;
	}
	main_sib->key_value[0] = from_parrent;
   
	
	
    i = main_sib->net_key+1;
	while(i<0)
	{
		main_sib->child_pointer[i] = main_sib->child_pointer[i-1];
		i--;
	}
	main_sib->child_pointer[0] = borrowed_from_left;
	main_sib->net_key++;
	left_sib->net_key--;
	return nodet;
}

node* merge(node* nodet, int pos)
{
   node* merged_child = get_node();

   node* left_child = nodet->child_pointer[pos];
   node* right_child = nodet->child_pointer[pos+1];
   left_child->key_value[left_child->net_key] = nodet->key_value[pos];
   int i =0,j = left_child->net_key+1;
   while(i < right_child->net_key)
   {
	   left_child->key_value[j] = right_child->key_value[i];
	   i++,j++;
   }

    i = 0, j = left_child->net_key+1;
    
   while(i<=right_child->net_key)
   {
	   left_child->child_pointer[j] = right_child->child_pointer[i];
	   i++,j++;
   }

   i = pos;
   while(i<nodet->net_key-1)
   {
	   nodet->key_value[i] = nodet->key_value[i+1];
	   i++;
   }nodet->key_value[nodet->net_key-1] = 0;
   
   left_child->net_key = left_child->net_key + right_child->net_key+1;
   int l =0;
   while(l < left_child->net_key)
   {
	   cout<<left_child->key_value[l]<<" ";
	   l++;
   }
   cout << endl;
   nodet->child_pointer[pos] = left_child;
   i = pos+1;
   while(i< nodet->net_key)
   {
	   nodet->child_pointer[i] = nodet->child_pointer[i+1];
	   i++;
   }
   nodet->child_pointer[nodet->net_key] = NULL;
   nodet->net_key--;
   
   if(nodet->net_key == 0)
   nodet = nodet->child_pointer[0];
   return nodet;
}


node* borrow_from_right(node* nodet, int pos)
{
	// key form parent
   int from_parent;
//    key form sib
   int from_right;
//    the right sibling
   node* right_sib = nodet->child_pointer[pos+1];
   from_parent = nodet->key_value[pos];
   from_right = right_sib->key_value[0];
//    child borrowed from right sib
   node*borrowed_from_right = right_sib->child_pointer[0];
   nodet->key_value[pos] = from_right;
   nodet->child_pointer[pos]->key_value[nodet->child_pointer[pos]->net_key] = from_parent;

   int i = 0;
   while(i<right_sib->net_key)
   {
	   right_sib->key_value[i] = right_sib->key_value[i+1];
	   i++;
   }  
   i = 0;
   while(i <= right_sib->net_key)
   {
	   right_sib->child_pointer[i] = right_sib->child_pointer[i+1];
	   i++;
   }
   node* main_sib = nodet->child_pointer[pos];
   main_sib->child_pointer[main_sib->net_key + 1] = borrowed_from_right;
   right_sib->net_key--;
   nodet->child_pointer[pos]->net_key++;
   return nodet;
}

node* remove_key(node* nodet,int key)
{
	int i = 0;
    while(nodet->key_value[i] < key && i< nodet->net_key)
	{
		i++;
	}
	
//   if key is found
	if(i < nodet->net_key && nodet->key_value[i] == key)
	{
		cout << "found\n";
		if(nodet->leaf)
		{
           nodet = rem_from_leaf(key,nodet,i);
		}
		else
		{
			nodet = rem_from_int(key,nodet,i);
		}
	}
	else
	{   cout << "not in this node \n";
		// if node is a leaf node
		if(nodet->leaf)
		{
			cout << " key not present\n";
		}
       
		else
		{
			// if the next child node has atleast t keys
			if(nodet->child_pointer[i]->net_key >= t)
			{
              nodet->child_pointer[i] = remove_key(nodet->child_pointer[i],key);
			}
			
			else
			{
				// checking for left sibling to borrow
				if(i > 0 && !(nodet->child_pointer[i-1]->net_key < t))
				{
                   nodet = borrow_from_left(nodet,i);  
				}
                //  if left sib. doesn't have enough key then lookn at right node
				else if(i < nodet->net_key && !(nodet->child_pointer[i+1]->net_key < t))
				{
					
                   nodet = borrow_from_right(nodet,i);
				}

                // if none of the imm. sib. has enough children 
				// merge with a sibbling
				else
				{
					// merge with left
					if(i>0)
					{
                      nodet =  merge(nodet,i-1);
					}
                    
					// merge with right
					else
					{
					   nodet = 	merge(nodet,i);
					}
					
				}

				//   a a   a   a
				//  b b |b| |b| b
				nodet = remove_key(nodet,key);
				
			}
			
		}
		
	}
	return nodet;
}

