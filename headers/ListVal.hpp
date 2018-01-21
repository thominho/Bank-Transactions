#ifndef LISTVAL_HPP
#define LISTVAL_HPP
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
using namespace std;


struct node
{
	struct tran{

		int amount;
		tran *next;
		node *ptr;
		
		tran(int a,node *b,tran* n);
		~tran();

	};

		int id; //the unique id of node
		int counter; //a counter which will increase when another node will have transcaction with this one useful for delete faction
		int money;

		node*  next;
		tran*  edge;
		int size;


		node (int a,node* n);
};


#endif
