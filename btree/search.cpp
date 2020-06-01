#include "btree.hpp"
#include<bits/stdc++.h>

result* get_result_node()
{
  result* neww = (result*)malloc(sizeof(result));
   neww->res = NULL;
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
