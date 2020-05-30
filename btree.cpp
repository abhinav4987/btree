using namespace std;
#include<bits/stdc++.h>

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

result* get_result_node()
{
  result* neww = (result*)malloc(sizeof(result));
   neww->res = NULL;
  return neww;
}


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

result* search(int key, node* nodet)
{
	int i;
	i = nodet->net_key-1;

	while(i >= 0 && (key < nodet->key_value[i]))
	{
		i--;
	}

	if(i >=0 && key == nodet->key_value[i])
	{
		result* re_node= get_result_node();
		re_node->res = nodet;
		re_node->pos = i;
		re_node->found = true;
		return re_node;
	}

	if(nodet->leaf)
	{
        result* re_node= get_result_node();
		re_node->found = false;
		return re_node;
	}

	else 
	{
		return search(key, nodet->child_pointer[i+1]);
	}
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


void print_node(node* noode)
{
	queue <node*> qu;
	qu.push(noode);
	while (!qu.empty())
	{
		int count = qu.size();
		// cout << count<<endl;
		 cout <<"|| ";

		while (count > 0)
		{
			node* top = qu.front();

			for(int i = 0;i<top->net_key;i++)
			{
				cout << top->key_value[i] << " ";
			}
            
			if(!top->leaf)
			for(int i = 0;i<=top->net_key;i++)
			{
				qu.push(top->child_pointer[i]);
			}

			qu.pop();
			cout << "||" ;
			count--;
		}
		cout << endl;
		// cout << "done\n";
	}
	// cout << "done\n";

	return;
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


int main()
{
	btree* root = (btree*)malloc(sizeof(btree));
	root->root = get_node();


    //1.insert
	//2.search
	//3.print
	//4.delete
    while(true)
	{
	  cout << "1.insert \n 2.search \n 3.print \n 4.delete \n";
	  int choice = -1;
      while(choice >0 && choice < 5)
	  cin >> choice;

	  if(choice == 1)
	  {
         int in ;
		 cin >> in;
		 insert(in,root);
		 cout << root->root->net_key<<endl;
	  }

	 else if(choice == 2)
	  {
		  int in;
		  cin >> in;
          result* res = search(in,root->root);
          if(res->found)
		  {
			  cout << " found ";
		  } 

		  else
		  {
			  cout << " missing ";
		  }
		  
	  }

	  else if(choice == 3)
	  {
		  cout << "your tree\n" << " --------------------------- \n";
          print_node(root->root);
		  cout << " --------------------------- \n";
	  }

	  else if(choice == 4)
	  {
		  int to_del;
		  cin >> to_del;
		  result* check_presence = search(to_del,root->root);

		  if(check_presence->found)
		  {
			  cout << "found and ready to dlete\n";
			  root->root = remove_key(root->root,to_del);
		  }
	  }
	}

}


