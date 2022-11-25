//Shortest Job First Method

#include<iostream>
using namespace std;
struct process
{
	int id;
	int bt;
	int at;
	int wt;
	int tat;
	bool flag;
};

void showdata(struct process * array[],int n)
{
		struct process *p;
		cout<<"\nPro\t"<<"Arr\t"<<"Bur\tWait\tTurn\t\n";
		for(int i=0;i<n;i++)
		{
			p=array[i];
			cout<<p->id<<"\t"<<p->at<<"\t"<<p->bt<<"\t"<<p->wt<<"\t"<<p->tat<<"\t"<<"\n";
		}
}

int execorder[20];
int ct=0;
int sjf(struct process * array[],int n)
{
	
	struct process * p;

	struct process * together[20];
	int j=0;
	for(int i=0;i<n;i++)
	{
		p=array[i];
		if((p->flag==0) && (p->at<=ct))
         	{
	          	together[j]=p;
	           	j++;
         	}
	}

	if(j==0)
	return 0;
	else
	{
	int min;
	p=together[0];
	min=p->bt;
	struct process *exec;
	exec=p;
	for(int i=0;i<=j-1;i++)
	{
		struct process * q;
		q=together[i];
		
		if(q->bt<min)
		exec=q;
	}
	
	int sum=0;
	for(int i=0;i<n;i++)
	{
	p=array[i];
	if(p->flag==1)
	sum=sum+p->bt;
	}
	
	
	cout<<exec->id<<"-> ";
	exec->tat=sum+exec->bt-exec->at;
	exec->wt=exec->tat-exec->bt;
	exec->flag=1;
	ct=sum+exec->bt;
	// cout<<"\nCurrent time now becomes"<<ct;
	
	
		sjf(array,n);
	}

}	

void awt_atat(struct process * array[],int n)
{
	struct process * p;
	float wt=0,tat=0;
	float awt,atat;
	for(int i=0;i<n;i++)
	{
		p=array[i];
		wt=wt+p->wt;
		tat=tat+p->tat;
	}
	
	awt=wt/n;
	atat=tat/n;
	cout<<"\nAverage Waiting Time="<<awt<<" Average Turnaround Time is="<<atat;
}
	
	

int main()
{
	int n;
	cout<<"Enter number of process ";
	cin>>n;
	struct process * array[20];
	for(int i=0;i<n;i++)
	{
		int b,a;
		struct process *p;
		p=(struct process *) malloc(sizeof(struct process));
		array[i]=p;
		p->id=i+1;
		cout<<"\nEnter ARRIVAL time and BURST time for process"<<i+1<<" ";
		cin>>a;
		
		cin>>b;
		p->bt=b;
		p->at=a;
		p->flag=0;
		p->wt=0;
		p->tat=0;
		
	}
	
	cout<<"\nOrder of execution of process is ";
	sjf(array,n);
	showdata(array,n);
	awt_atat(array,n);
	
}


		