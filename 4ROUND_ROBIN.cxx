#include<iostream>
#include<queue>

using namespace std;


struct process
{
	int id;
	int bt;				//to store the burst time
	int bti;			//to store the initial burst time
	int at;
	int wt;
	int c;
	int tat;
	int rt;
	int flag;
};

int tq;
queue<struct process *>q;
int ct=0;

void showdata(struct process * arry[],int n)
{
		struct process *p;
		cout<<"\nPro\t"<<"Arr\t"<<"Bur\tRes\tCom\tTurn\tWait\n";
		for(int i=0;i<n;i++)
		{
			p=arry[i];
			cout<<p->id<<"\t"<<p->at<<"\t"<<p->bti<<"\t"<<p->rt<<"\t"<<p->c<<"\t"<<p->tat<<"\t"<<p->wt<<"\n";
		}
}


void check_arrival(struct process *a[],int n)
{
	struct process *p;
	
	for(int i=0;i<n;i++)
	{
		
		p=a[i];
		
		if((p->flag==0) && (p->at<=ct ))
		{
			
			p->flag=3;//so that process cant be repushed
			q.push(p);
		}
	}
}

void round_robin(struct process * a[],int n)
{
	struct process *p;
	struct process *min_at_array[20];
	struct process *exec;
	int min_at;
	p=a[0];
	min_at=p->at;
	exec=p;
	for(int i=0;i<n;i++)
	{
		p=a[i];
		
		if(p->at<min_at)
		exec=p;
		
	}	
	q.push(exec);
	
	while(!q.empty())
	{
		
		exec=q.front();
		cout<<"->"<<exec->id;
		
		
		if(exec->flag==0 || exec->flag==3)
		{
			exec->rt=ct-exec->at;
			
			exec->flag=2;//Process responded but remaining executing fully
			
		}
		if(tq<exec->bt)
		{
			ct=ct+tq;
			exec->bt=exec->bt-tq;
			exec->flag=2;

			check_arrival(a,n);
			
			q.push(exec);

		}
		else
		{
			if((tq==exec->bt) || (tq>exec->bt))
			{
				ct=ct+exec->bt;
				exec->c=ct;
				exec->bt=exec->bt-tq;
				exec->flag=1;
				check_arrival(a,n);
			}
		}
			
		q.pop();
	}
}
		
void update_data(struct process * a[],int n)
{
	struct process * p;
	for(int i=0;i<n;i++)
	{
		p=a[i];
		p->tat=p->c-p->at;
		p->wt=p->tat-p->bti;
	}
}
					
					
void awt_atat_art(struct process *a[],int n)
{
	struct process *p;
	float awt=0,atat=0,art=0;
	for(int i=0;i<n;i++)
	{
		p=a[i];
		awt=awt+p->wt;
		atat=atat+p->tat;
		art=art+p->rt;
	}
	awt=awt/n;
	atat=atat/n;
	art=art/n;
	cout<<"\nAverage Response Time is "<<art<<"\nAverage Turn Around Time is "<<atat<<"\nAverage Waiting Time is "<<awt;
}
					
		
	
int main()
{
	
	int n;
	cout<<"Enter the time quantum ";
	cin>>tq;
	cout<<"Enter number of process ";
	cin>>n;
	struct process * array[20];
	for(int i=0;i<n;i++)
	{
		int b,a,pr,ct=0;
		struct process *p;
		p=(struct process *) malloc(sizeof(struct process));
		array[i]=p;
		p->id=i+1;
		cout<<"\nEnter arrival time and burst time for process"<<i+1<<" ";
	
		cin>>a;
		cin>>b;
		
		
		p->bt=b;
		p->bti=b;
		p->at=a;
	    p->flag=0;
		p->wt=0;
		p->tat=0;
		p->rt=0;
		p->c=ct;
	}
	
	cout<<"\nOrder of execution is ";
	round_robin(array,n);
	update_data(array,n);
	showdata(array,n);
	awt_atat_art(array,n);
}