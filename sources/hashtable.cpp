#include "../headers/hashtable.hpp"

/*---------------------------------------------------------------------------------------------------------------------*/

hashtable::hashtable(){
	size=0;
	_start=NULL;
}

/*---------------------------------------------------------------------------------------------------------------------*/

hashtable::~hashtable(){
	while(size!=0){
		destroy();
	}
}

/*---------------------------------------------------------------------------------------------------------------------*/

void hashtable::destroy(){
	node *t=_start;
	if(size==0){
		return;
	}
	_start=_start->next;
	while(t->size!=0){
		node::tran *t2=t->edge;
		t->edge=t->edge->next;
		delete t2;
		t->size--;
	}
	delete t;
	size--;
}

/*---------------------------------------------------------------------------------------------------------------------*/

node * hashtable::return_ptr(int id){
	node *t=_start;
	if(size==0){
		cout << "List empty" << endl;
		return NULL;
	}
	while(t!=NULL){
		if(t->id==id){
			break;
		}
		t=t->next;
	}
	return t;
}

/*---------------------------------------------------------------------------------------------------------------------*/

void hashtable::addtran(int id1,int id2,double amount,node *t2){
	node *t=_start;
	if(size==0){
		cout << "List empty" << endl;
		return;
	}
	while(t!=NULL){
		if(t->id==id1){
			break;
		}
		t=t->next;
	}
	if(t==NULL){
		cout << "Could not find id" << endl;
		return;
	}
	node::tran *t3=t->edge;
	while(t3!=NULL){
		if(t3->ptr->id==id2){
			t3->amount=t3->amount+amount;
			t3->ptr->money=t3->ptr->money+amount;
			cout << "Amount added to an existed transcation" << endl;
			return;
		}
		t3=t3->next;
	}
	t->edge=new node::tran(amount,t2,t->edge);
	if(t->edge==NULL){
		cout << "Could Not Add Transcations->RAM problem" << endl;
		exit(1);
	}
	else{
		cout << "success: added transcaction (" << id1 << "," << id2 << "," << amount << ")" << endl;
	}
	t->edge->ptr->counter++;
	t->edge->ptr->money=t->edge->ptr->money+amount;
	t->size++;
}

/*---------------------------------------------------------------------------------------------------------------------*/

void hashtable::createNode(int id){
	node *t=_start;
	while(t!=NULL){
		if(t->id==id){
			cout << "Id exists" << endl;
			return;
		}
		t=t->next;
	}
	_start=new node(id,_start);
	if(_start==NULL){
		cout << "Could Not Add Transcations->RAM problem" << endl;
		exit(1);
	}
	size++;
}

/*---------------------------------------------------------------------------------------------------------------------*/
void hashtable::lookup1(int id){
	node *t=_start;
	if(size==0){
		cout << "List empty" << endl;
		return;
	}
	while(t!=NULL){
		if(t->id==id){
			cout << "success: in(" << id << ") = " << t->money << endl;
			return;
		}
		t=t->next;
	}
	cout << "Error:Could not find such id for in(" << id << ")" << endl;
}

/*---------------------------------------------------------------------------------------------------------------------*/
void hashtable::lookup2(int id){
	node *t=_start;
	if(size==0){
		cout << "List empty" << endl;
		return;
	}
	while(t!=NULL){
		if(t->id==id){
			int counter=0;
			node::tran *t2=t->edge;
			while(t2!=NULL){
				counter=counter+t2->amount;
				t2=t2->next;
			}
			cout << "success: out(" << id << ") = " << counter << endl;
			return;
		}
		t=t->next;
	}
	cout << "Error:Could not find such id for out(" << id << ")" << endl;

}

/*---------------------------------------------------------------------------------------------------------------------*/
void hashtable::lookup3(int id){
	node *t=_start;
	if(size==0){
		cout << "List empty" << endl;
		return;
	}
	while(t!=NULL){
		if(t->id==id){
			int counter=0;
			node::tran *t2=t->edge;
			while(t2!=NULL){
				counter=counter+t2->amount;
				t2=t2->next;
			}
			counter=t->money-counter;
			cout << "success: sum(" << id << ") = " << counter << endl;
			return;
		}
		t=t->next;
	}
	cout << "Error:Could not find such id for sum(" << id << ")" << endl;

}


/*---------------------------------------------------------------------------------------------------------------------*/

void hashtable::delNode(int id1){//need fixing diagrafw mono an den uparxoun kombei pou na deixnoun se auton h autos na deixnei kapou tha rwthsw aurio
	node *t=_start;
	node *t2=_start->next;
	if(size==0){
		cout << "List empty" << endl;
		return;
	}
	if(t->id==id1){
		if(t->counter!=0 || t->size!=0){
			cout << "Failed to delete Node existed imports or exports transcactions" << endl;
			return;
		}
		else if(t->counter==0 && t->size==0){
			_start=t2;
			delete t;
			size--;
			return;
		}
	}
	while(t2!=NULL){
		if(t2->id==id1){
			break;
		}
		t=t->next;
		t2=t2->next;
	}
	if(t2==NULL){
		cout << "Error:Could not find such node to delete" << endl;
		return;
	}
	if(t2->counter!=0 || t2->size!=0){
		cout << "Failed to delete Node existed imports or exports transcactions" << endl;
		return;
	}
	else if(t2->counter==0 && t2->size==0){
		t->next=t2->next;
		delete t2;
		size--;
	}
	cout << "success: deleted " << id1 << endl;
}


/*----------------------------------------------------------------------------------------------------*/


void hashtable::delTran(int id1,int id2){
	node *t=_start;
	if(size==0){
		cout << "List empty" << endl;
		return;
	}
	if(t->size==0){
		cout << "No transcaction to delete" << endl;
		return;
	}
	while(t!=NULL){
		if(t->id==id1){
			break;
		}
		t=t->next;
	}
	if(t==NULL){
		cout << "Error:Could not find such transcaction with selected id to delete:" << id1 << endl;
		return;
	}
	node::tran *t2=t->edge;
	node::tran *t3=t->edge->next;
	if(t2->ptr->id==id2){
		t2->ptr->money=t2->ptr->money-t2->amount;
		t2->ptr->counter--;
		t->edge=t3;
		delete t2;
		t->size--;
		return;
	}
	while(t3!=NULL){
		if(t3->ptr->id==id2){
			t3->ptr->money=t3->ptr->money-t2->amount;
			t3->ptr->counter--;
			t2->next=t3->next;
			delete t3;
			t->size--;
			return;
		}
		t3=t3->next;
		t2=t2->next;
	}
	cout << "Error:Could not find such transcaction" << endl;
}


/*---------------------------------------------------------------------------------------------------------------------*/


void hashtable::print(){
	node *t=_start;
	if(size==0){
		return;
	}
	while(t!=NULL){
		cout << "vertex(" << t->id << ") =";
		node::tran *t2=t->edge;
		while(t2!=NULL){
			cout << "(" << t2->ptr->id << "," << t2->amount << "),";
			t2=t2->next;
		}
		t=t->next;
		cout << endl;
	}
}


/*---------------------------------------------------------------------------------------------------------------------*/

void hashtable::triangle(int id,int k){//it just simple iterate until three nodes no recursion
	node *t=_start;
	if(size==0){
		cout << "List empty" << endl;
		return;
	}
	while(t!=NULL){
		if(t->id==id){
			break;
		}
		t=t->next;
	}
	if(t==NULL){
		cout << "Not Such Id" << endl;
		return;
	}
	int *checked;
	checked=(int *) malloc(sizeof(int)*50);
	int csize=0;
	int msize=50;
	for(int i=0;i<msize;i++){
		checked[i]=0;
	}
	node::tran *t2=t->edge;
	while(t2!=NULL){
		node *t3=t2->ptr;//iterator depth 1
		node::tran *t4=t3->edge;
		while(t4!=NULL){
			node *t5=t4->ptr;//iterator depth 2 if we have after this circle then this is one of paths of triangle
			node::tran *t6=t5->edge;
			while(t6!=NULL){
				if(csize<msize && t6->amount>=k && t2->amount>=k && t6->ptr->id==id){
					checked[csize]=t3->id;
					checked[csize+1]=t5->id;
					csize=csize+2;
				}
				else if(csize>=msize && t6->amount>=k && t2->amount>=k && t6->ptr->id==id){
					msize=msize*2;
					checked=(int *) realloc(checked,sizeof(int)*msize);
					checked[csize]=t3->id;
					checked[csize+1]=t5->id;
					csize=csize+2;
				}
				t6=t6->next;
			}
			t4=t4->next;
		}
		t2=t2->next;
	}
	int i=0;
	if(csize!=0){
		cout << "Success: " << "Triangle(" << id << "," << k << ")" << "=" << endl; 
	}
	else{
		cout << "Not Triangle Found" << endl;
		free(checked);
		return;
	}
	while(i<csize){
		if(checked[i]!=0){
			cout << "(" << id << "," << checked[i] << "," << checked[i+1] << ")" << endl;
		}
		i=i+2;
	}
	free(checked);

}

/*---------------------------------------------------------------------------------------------------------------------*/


void hashtable::conn(int id1,int id2){
	if(size==0){
		cout << "List Empty" << endl;
		return;
	}
	node *t=_start;
	while(t!=NULL){
		if(t->id==id1){
			break;
		}
		t=t->next;
	}
	if(t==NULL){
		cout << "Could Not Find Id to search from" << endl;
		return;
	}
	int *array;
	int msize=50;
	array=(int *) malloc(sizeof(int)*msize);
	for(int i=0;i<msize;i++){
		array[i]=0;
	}
	int temp=0;
	if(t->size==0){
		cout << "No edges to search for" << endl;
		free(array);
		return;
	}
	array[0]=id1;
	node::tran *t2=t->edge;
	temp=temp+2;
	while(t2!=NULL){
		if(t2->ptr->id==id2){
			cout << "success: (" << id1 << "," << id2 << ")" << endl;
			free(array);
			return;
		}
		else{
			array[1]=t2->ptr->id;
			node *t8=t2->ptr;
			int flag=dfs(t8,array,temp,msize,id2);//first call here then recursively generally arrays are my fringes and paths for searching with dfs
			if(flag==1){
				cout << "success: path (" << id1 << "," << id2 << ") = " << "(";
				for(int i=0;i<temp;i++){
					if(i<temp-1){
						cout << array[i] << ",";
					}
					else{
						cout << array[i] << ")" << endl;
					}
				}
				free(array);
				return;
			}
		}
		t2=t2->next;
	}
	if(t2==NULL){
		cout << "Could Not Find Path" << endl;
		free(array);
		return;
	}
}

/*---------------------------------------------------------------------------------------------------------------------*/

int hashtable::dfs(node *t4,int *path,int &csize,int &maxsize,int id1){
	if(t4->size==0){
		return 0;
	}
	node::tran *temp2=t4->edge;
	while(temp2!=NULL){
		if(temp2->ptr->id==id1){
			if(csize<maxsize){
				path[csize]=id1;
				csize++;
			}
			else if(csize==maxsize){
				maxsize=maxsize*2;
				path=(int *) realloc(path,sizeof(int)*maxsize);
				path[csize]=id1;
				csize++;
			}
			temp2=NULL;
				return 1;
		}
		else{
			int flag=0;
			for(int i=0;i<csize;i++){
				if(path[i]==temp2->ptr->id){
					flag=1;
				}
			}
			if(flag!=1){
				if(csize<maxsize){
					path[csize]=temp2->ptr->id;
					csize++;
				}
				else if(csize==maxsize){
					maxsize=maxsize*2;
					path=(int *) realloc(path,sizeof(int)*maxsize);
					path[csize]=temp2->ptr->id;
					csize++;
				}
				node *t9=temp2->ptr;
				flag=dfs(t9,path,csize,maxsize,id1);
				if(flag==1){
					temp2=NULL;
					return 1;
				}
				else{
					path[csize]=0;
					csize--;
				}
			}
		}
		temp2=temp2->next;
	}
	temp2=NULL;
	return 0;
}

/*---------------------------------------------------------------------------------------------------------------------*/

void hashtable::traceflow(int id1,int depth){
	if(size==0){
		cout << "List Empty" << endl;
		return;
	}
	node *t=_start;
	while(t!=NULL){
		if(t->id==id1){
			break;
		}
		t=t->next;
	}
	if(t==NULL){
		cout << "Could Not Find Id to search from" << endl;
		return;
	}
	int *array2;//current path
	int msize2=50;//current path totalsize
	array2=(int *) malloc(sizeof(int)*msize2);
	for(int i=0;i<msize2;i++){
		array2[i]=0;
	}
	int temp2=0;//current path currentsize
	int sum=0;
	if(t->size==0){
		cout << "No edges to search for" << endl;
		free(array2);
		return;
	}
	if(depth==0){
		cout << "success: traceflow(" << id1 << "," << depth << ")" << endl;
		cout << "(" << id1 << ")" << endl;
		free(array2);
		return;
	}
	array2[0]=id1;
	int cdepth=0;//current depth
	int found=0;
	node::tran *t2=t->edge;
	while(t2!=NULL){
		if(depth==1){//if l=1
			if(found==0){
				found=1;
				cout << "success: traceflow(" << id1 << "," << depth << ")" << endl;
			}
			cout << "(" << id1 << "," << t2->ptr->id << "," << t2->amount << ")" << endl;
		}
		else{
			array2[1]=t2->ptr->id;
			cdepth++;
			temp2=2;
			sum=0;
			sum=sum+t2->amount;
			dfs2(t2,array2,temp2,msize2,cdepth,depth,sum,found,id1);
			sum=sum-t2->amount;
			cdepth--;
		}
		t2=t2->next;
	}
	if(t2==NULL && found==0){
		cout << "Could Not Find Traceflow for depth" << endl;
		free(array2);
		return;
	}
	else{
		free(array2);
	}
}

/*---------------------------------------------------------------------------------------------------------------------*/

int hashtable::dfs2(node::tran *t,int* path2,int &csize2,int &maxsize2,int &cdepth,int depth,int &sum,int &found,int id1){
	node *temp=t->ptr;
	if(t->ptr->size==0){
		return 0;
	}
	node::tran *temp2=temp->edge;
	cdepth++;
	while(temp2!=NULL){
		int flag=1;
		for(int i=0;i<csize2;i++){
			if(path2[i]==temp2->ptr->id && path2[i]!=0 && flag==1){
				flag=0;
			}
		}
		if(flag==1){
			path2[csize2]=temp2->ptr->id;
			csize2++;
			sum=sum+temp2->amount;
			if(cdepth==depth){
				if(found==0){
					cout << "Success: traceflow (" << id1 << "," << depth << ")" << endl;
				}
				found=1;
				for(int i=0;i<csize2;i++){
					if(i==0){
						cout << "(" << path2[i] << ",";
					}
					else if(i<csize2-1){
						cout << path2[i] << ",";
					}
					else{
						cout << path2[i] << "," << sum << ")" << endl;
					}
				}
			}
			else{
				dfs2(temp2,path2,csize2,maxsize2,cdepth,depth,sum,found,id1);
			}
			csize2--;
			sum=sum-temp2->amount;
		}
		temp2=temp2->next;
	}
	cdepth--;
	return 0;
}

/*---------------------------------------------------------------------------------------------------------------------*/

void hashtable::allcircles(int id1){
	if(size==0){
		cout << "List Empty" << endl;
		return;
	}
	node *t=_start;
	while(t!=NULL){
		if(t->id==id1){
			break;
		}
		t=t->next;
	}
	if(t==NULL){
		cout << "Could Not Find Id to search from" << endl;
		return;
	}
	int *array;//visited suffixes
	int *array2;//current path
	int msize=50;
	int msize2=50;
	array=(int *) malloc(sizeof(int)*msize);
	array2=(int *) malloc(sizeof(int)*msize);
	for(int i=0;i<msize;i++){
		array[i]=0;
		array2[i]=0;
	}
	int temp1=0;
	int temp2=0;
	if(t->size==0){
		cout << "No edges to search for" << endl;
		free(array);
		free(array2);
		return;
	}
	array2[0]=id1;
	int cdepth=0;//current depth
	int found=0;//a variable that checks if we have the first print
	node::tran *t2=t->edge;
	while(t2!=NULL){
		array2[1]=t2->ptr->id;
		cdepth++;
		temp2=2;
		dfs3(t2,array,array2,temp1,temp2,msize,msize2,cdepth,found,id1);
		cdepth--;
		t2=t2->next;
	}
	if(t2==NULL && found==0){
		cout << "Could Not Find Circle" << endl;
		free(array);
		free(array2);
		return;
	}
	else{
		free(array);
		free(array2);
	}
}

/*---------------------------------------------------------------------------------------------------------------------*/

int hashtable::dfs3(node::tran *t,int *path,int* path2,int &csize1,int &csize2,int &maxsize,int &maxsize2,int &cdepth,int &found,int id1){
	node *temp=t->ptr;
	if(t->ptr->size==0){
		return 0;
	}
	node::tran *temp2=temp->edge;
	cdepth++;
	while(temp2!=NULL){
		int flag=1;
		for(int i=1;i<csize2;i++){
			if(path2[i]==temp2->ptr->id && path2[i]!=0 && flag==1){
				flag=0;
			}
		}
		if(flag==1){
			path2[csize2]=temp2->ptr->id;
			csize2++;
			flag=1;
			if(cdepth>=3 && temp2->ptr->id==id1){
				for(int i=0;i<csize1;i++){
					if(flag==1 && path[i]==path2[csize2-2] && path[i]!=0){
						flag=0;
					}
				}
				if(flag==1){

					if(found==0){
						cout << "Success: circle(" << id1 << ")" << endl;
					}
					found=1;
					for(int i=0;i<csize2;i++){
						if(i==0){
							cout << "(" << path2[i] << ",";
						}
						else if(i<csize2-1){
							cout << path2[i] << ",";
						}
						else{
							cout << path2[i] <<")" << endl;
						}
					}
					path[csize1]=path2[csize2-2];
					csize1++;
				}
			}
			else{
				dfs3(temp2,path,path2,csize1,csize2,maxsize,maxsize2,cdepth,found,id1);
			}
			csize2--;
		}
		temp2=temp2->next;
	}
	cdepth--;
	return 0;
}

/*---------------------------------------------------------------------------------------------------------------------*/