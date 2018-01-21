#include "../headers/ListVal.hpp"



node::tran::tran(int a,node *b,tran* n){
	amount=a;
	ptr=b;
	next=n;
}

node::tran::~tran(){
	ptr=NULL;
}

node::node (int a,node* n){
		id=a;
		counter=0;
		money=0;
		next=n;
		edge=NULL;
		size=0;
}