#include<bits/stdc++.h>
#include "btree.hpp"
using namespace std;

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
    //   while(choice <= 0 && choice >= 5)
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


