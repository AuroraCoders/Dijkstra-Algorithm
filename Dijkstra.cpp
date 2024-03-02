#include<iostream>
using namespace std;
struct edge{
	char dest;
	edge *link;
	int dist;	
};
struct node{
	node *next;
	char name;
	edge *adj;
	char color;
	int dist;
	char pred;
	
}*start=NULL;

struct queue{
	node *add_node;
	queue *link;
	
};
queue *front=NULL;
queue *rear=NULL;


int num;
node *find(char item){
	node *ptr;
	node *loc;
	ptr=start;
	while(ptr!=NULL){
		if(item==ptr->name){
			loc =ptr;
			return loc;
			
		}
		else{
		ptr=ptr->next;
		}
	
	}
	loc=NULL;
	return loc;
}
void insert_node(char name){
	node *tmp,*ptr;
	tmp=new node();
	tmp->name=name;
	tmp->color='w';
	tmp->dist=999;
	tmp->pred='n';
	
	tmp->next=NULL;
	tmp->adj=NULL;
     if(start==NULL){
     	start=tmp;
     	return;
	 }
	 ptr=start;
	 while(ptr->next!=NULL){
	 	ptr=ptr->next;
	 	
	 }
	 ptr->next=tmp;
}
void insert_edge(char u,char v,int d){
	node *locu,*locv;
	edge *ptr,*tmp;
	locu=find(u);
	locv=find(v);
	
	if(locu==NULL){
		cout<<"Source is not present "<<endl;
		return;
	}
	if(locv==NULL){
		cout<<"Destination is not present "<<endl;
		return;
	}
	tmp=new edge();
	tmp->dest=v;
	tmp->dist=d;
	tmp->link=NULL;
	if(locu->adj==NULL){
		locu->adj=tmp;
		return;
	}
	ptr=locu->adj;
	while(ptr->link!=NULL){
		ptr=ptr->link;
	}
	ptr->link=tmp;
}
void display(){
	node *ptr;
	edge *q;
	ptr=start;
	while(ptr!=NULL){
		cout<<"Node "<<ptr->name<<" ";
		q=ptr->adj;
		while(q!=NULL){
			cout<<"Edge "<<q->dest<<" ";
			q=q->link;
		}
		cout<<endl;
		ptr=ptr->next;
	}
}

void sort(){
	queue *q=front;
	node *tmp;
	while(q!=NULL){
		queue *p=q->link;
		while(p!=NULL){
			if(q->add_node->dist > p->add_node->dist){
				tmp=p->add_node;
				p->add_node=q->add_node;
				q->add_node=tmp;
			}
			p=p->link;
		}
		q=q->link;
	}
} 
void dequeue(){
    if(front == NULL){
        cout << "Queue is empty" << endl;
        return;
    }
    queue *tmp = front;
    front = front->link;
    tmp->link = NULL;
    delete (tmp);
}

	
void enque(node **c){
	queue *tmp=new queue();
	tmp->add_node=*c;
	tmp->link=NULL;
	if(front==NULL){
		front=tmp;
		rear=tmp;
	}
	rear->link=tmp;
	rear=tmp;
	
}
void traverse_path(char s,char d){
	node *locd=find(d);
	while(locd->pred!='n'){
		cout<<locd->name<<"<--";
		locd=find(locd->pred);
	
	}
	cout<<s<<endl;
}

void displayQ(){
	queue *w=front;
	while(w!=NULL){
		cout<<w->add_node->name<<"  "<<w->add_node->dist<<endl;
		w=w->link;
	}
}
void find_path(char s){

		node *q=start;
		while(q!=NULL){
			enque(&q);
			q=q->next;
		}
		
		node *ptr=find(s);
		ptr->dist=0;
		while(front!=NULL){	
			sort();
			node *source=front->add_node;
			edge *e= source->adj;
		    while(e!=NULL){
		    		
			node *qtr=find(e->dest);
			if(qtr->color!='B'){
				int add=source->dist+e->dist;
				if(qtr->dist>add){	
				qtr->dist=add;
				qtr->pred=source->name;
			    }
			}
				e=e->link;
		}
		    front->add_node->color='B';
			dequeue();
			
					
		}
	
}

int main(){
	char a,s,d;
	char type;
	cout<<"Enter type of graph "<<endl;
	cout<<"Enter 1 for directed graph "<<endl;
	cout<<"Enter 0 for undirectd graph "<<endl;
	cin>>type;
	
	cout<<"Enter number of nodes "<<endl;
	cin>>num;
	for(int i=0;i<num;i++){
		cout<<"Enter char "<<endl;
		cin>>a;
		insert_node(a);	
	}
	
	
	
	int e;
	cout<<"Enter number of edges "<<endl;
	cin>>e;
	
	for(int i=0;i<e;i++){
		cout<<"Enter source and destination "<<endl;
		cin>>s;
		cin>>d;
		int distance;
		cout<<"enter distance "<<endl;
		cin>>distance;
		if(type==1){
		insert_edge(s,d,distance);
	}
	else{
		insert_edge(s,d,distance);
		insert_edge(d,s,distance);
	}
	}
	display();
	char destination;
	char s1,d1;
	cout<<"Enter source "<<endl;
	cin>>s1;
	find_path(s1);
	for(int i=0;i<num-1;i++){
	cout<<"Enter destination for path"<<endl;
	cin>>destination;
	traverse_path(s1,destination);
	}	
}
