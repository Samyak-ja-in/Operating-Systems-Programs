//Priority based scheduling
//If priority same then check for minimum arrival time if arrival time is also same then process which is having minimum process id is executed

#include<iostream>
using namespace std;

//defining the process as structure
struct process
{
	int id;		//Process Id
	int pr;		//Process Priority
	int bt;		//Process Burst Time
	int at;		//Process arrival time
	int wt;		//Process Waiting Time
	int ct;		//Process Completion time
	int tat;	//Process Turn Aroung Time	
	bool flag;	//Flag to check wheather a process is executed or not 
};


//showdata() function shows the process data
void showdata(struct process * array[],int n)
{
		struct process *p;
		cout<<"\nPro\t"<<"Pri\t"<<"Arr\t"<<"Bur\tWait\tCom\tTurn\n";
		for(int i=0;i<n;i++)
		{
			p=array[i];
			cout<<p->id<<"\t"<<p->pr<<"\t"<<p->at<<"\t"<<p->bt<<"\t"<<p->wt<<"\t"<<p->ct<<"\t"<<p->tat<<"\n";
		}
}

int execorder[20];
int ct;				//current time
int value=0;		//To check the minimum arrival time of process and take it as starting time

//To check all the data of process
int priority(struct process * array[],int n)
{

	struct process * p;

	//To store all the process into a array which arrived before the current time 
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
	
	//together array will contain all the processes which arrived before  current time and is not executed yet 
	if(j==0)
	return 0;
	else
	{

	//Minimum priority number is more prior finding highest priority number among the processes
	int prior;
	p=together[0];
	prior=p->pr;
	
	
	
	for(int i=0;i<=j-1;i++)
	{
		struct process * q;
		q=together[i];
		if(q->pr<prior)
		{
			prior=q->pr;
		}
	}
		
	//Saving all the process of same highest priority(minimum number) into same array
	struct process * finale[20];
	int k=0;
	
	for(int i=0;i<=j-1;i++)
	{
		struct process * q;
		q=together[i];
		
		if(q->pr==prior)
		{
		finale[k]=q;
		k++;
		}
	}

	
	//Finding Process of minimum arrival time in finale array
	int min_arr;
	struct process *exec;

	p=finale[0];
		exec=p;
	min_arr=p->at;

	//Filtering proces of same priority according to minimum arrival time if more then one process have same minimum arrival time then select process with minimum process id
	for(int i=0;i<=k-1;i++)
	{
		struct process *q;
		q=finale[i];
		if(q->at<min_arr)
		exec=q;
	}
	
		
	//finding the sum of burst time of executed processes so as to find current time
	int sum=value;
	for(int i=0;i<n;i++)
	{
	p=array[i];
	if(p->flag==1)
	sum=sum+p->bt;
	}
	
	
	cout<<exec->id<<"->";
	exec->tat=sum+exec->bt-exec->at;
	exec->wt=exec->tat-exec->bt;
	exec->flag=1;
	ct=sum+exec->bt;
	exec->ct=ct;

		priority(array,n);
		
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
	cout<<"\nWt"<<wt<<"tat "<<tat;
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
		int b,a,pr,ct=0;
		struct process *p;
		p=(struct process *) malloc(sizeof(struct process));
		array[i]=p;
		p->id=i+1;
		
		cout<<"\nEnter priority and arrival time and burst time for process"<<i+1<<" ";
		cin>>pr;
		cin>>a;
		cin>>b;
		
		
		p->bt=b;
		p->at=a;
		p->flag=0;
		p->wt=0;
		p->tat=0;
		p->ct=ct;
		p->pr=pr;
		
		
	}

	//Finding the start time of execution of process  start time is minimum among all of the arrival times and minimum arrival time need not to be zero in each case
	int start_time=0;
	struct process *p;
	p=array[0];
	start_time=p->at;
	
	for(int i=0;i<n;i++)
	{
		
		p=array[i];
		if(p->at<start_time)
		{
			start_time=p->at;
			ct=p->at;
		}
		
		
	}
	value=start_time;
	ct=start_time;

	
	cout<<"\nProcesses Execution Order ";
	priority(array,n);
	
	showdata(array,n);
	awt_atat(array,n);
	
}



		