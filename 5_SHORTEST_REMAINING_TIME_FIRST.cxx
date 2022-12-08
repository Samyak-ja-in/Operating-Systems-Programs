#include<iostream>

using namespace std;

//structure of process
struct process
{
	int id;
	int bt;
	int bti;
	int at;
	int wt;
	int c;
	int tat;
	int rt;
	int flag;
};

int ct=0;							//current time
int nopa=0;							//number of process arrived till
int sum_bt=0;						//sum of burst time used to stop execution at last sbt will be equal to current time
struct process *arrived[20];		//array of processes which arrived till time


//To show the Process
void showdata(struct process * arry[],int n)
{
	struct process *p;
	cout<<"\nPro\t"<<"Arr\t"<<"Bur\tCom\tTurn\tWait\tRes\n";
	for(int i=0;i<n;i++)
	{
		p=arry[i];
		cout<<p->id<<"\t"<<p->at<<"\t"<<p->bti<<"\t"<<p->c<<"\t"<<p->tat<<"\t"<<p->wt<<"\t"<<p->rt<<"\n";
	}
}


//To find sum of burst times 
void sbt(struct process *a[],int n)
{
		int sum=0;
		
		struct process *p;
		for(int i=0;i<n;i++)
		{
			p=a[i];
			sum=sum+p->bti;
		}
		sum_bt=sum;
}

//To find average waiting,turnaround and response time
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

//To update the arrived array according to current time
void check_arrival(struct process *a[],int n)
{
	int i;
			
	int no=0;	//number of terms in arrived array //nopa not taken in place of no because it is global
	struct process *p;
	for(i=0;i<n;i++)
	{
		p=a[i];
		if(p->at<=ct && (p->flag)!=1)
		{
		arrived[no]=p;
		no++;
		}	
	}
    nopa=no;		
}


//Shortest time remaining first function which will find everything for each process	
void srtf(struct process * a[],int n)
{
	struct process *executable[20];		//To store a array containing process with same burst times after filtering them by arrival times
	int previous;						//To store the previous process id because if another process added have same burst time then previous process will not be exempted

	while(ct!=sum_bt)			//current_time is not equal to sum of all values of burst time
	{
		check_arrival(a,n);		//To check for arrival of new process each second
		
		int i;

		struct process *p;

		//TO FIND MINIMUM BURST TIME AMONG ALL PROCESSES
		p=arrived[0];
		int min_bt;
		min_bt=p->bt;
		
		for(i=0;i<nopa;i++)
		{
			p=arrived[i];
			if(p->bt<min_bt)
			min_bt=p->bt;
		}

		//TO FIND PROCESS OF MINIMUM BURST TIME PROCESSES AND STORE IT IN ARRAY NAMED EXECUTABLE
		int k=0;						//Number of processes with min burst time in executable array;
		for(i=0;i<nopa;i++)
		{
			p=arrived[i];
			if(p->bt==min_bt && p->flag!=1)			//With min burst time and process not completed execution
			{executable[k]=p;
			k=k+1;}
		}
		

		//To check for preamption if recently executed process available in executable array then make preamption=0(dont do preamption)
		int preamption=1;
		
		for(i=0;i<k;i++)
		{
			
			p=executable[i];
			if(p->id==previous)
			{
			preamption=0;
			break;
			}
		}

		struct process *exec;
		//If preamption is zero then recently executed process will start executing else take process with minimum process id
		if(preamption==0)
		exec=p;
		else
		exec=executable[0];
		
		cout<<exec->id<<"->";


		//Increase time by one unit and reduce burst time by one unit
		exec->bt=exec->bt-1;

		//Process flag is zero means process is executing first time so update the response time and change flag to 2 flag 2 means process executed once but not fully executed
		if(exec->flag==0)
		{
		exec->rt=ct-exec->at;
		exec->flag=2;
		}
		ct=ct+1;
		
		//If burst time of executable is zero means process is fully executed hence update its completiontime,turn around time,waiting time,flag=1(means process executed fully)
		if(exec->bt==0)
		{exec->flag=1;
		exec->c=ct;
		exec->tat=exec->c-exec->at;
		exec->wt=exec->tat-exec->bti;}
		
		previous=exec->id;		//store current process id for checking for preamption
		
    }
					
}			
	
	

int main()
{
	
	int n;

	
	cout<<"Enter number of process ";
	cin>>n;
	
	//Take input of process
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
	
 
	sbt(array,n);

    cout<<"\nProcess execution order is ";
	
	
    srtf(array,n);

	showdata(array,n);
	awt_atat_art(array,n);
	

}