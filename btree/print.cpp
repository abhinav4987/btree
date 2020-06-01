#include "btree.hpp"
#include<bits/stdc++.h>



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