#include<iostream>
using namespace std;

//defining the process as structure
struct process
{
	int id;		//Process Id
	int pr;		//Process Priority
	int bt;		//Process Burst Time
    int bti;    //Process initial burst time
	int at;		//Process arrival time
	int wt;		//Process Waiting Time
	int ct;		//Process Completion time
	int tat;	//Process Turn Aroung Time	
    int rt;     //Process Response Time
	int flag;	//Flag to check wheather a process is executed or not 
};

//Global Variables
int sum_bt=0;
int ct=0;
int nopa=0;         //number of process which is aririved till
int nopwhp=0;       //number of process with highest priority
int nopmat=0;
struct process * arrived[20];   //will contain all of the process arrived till time
struct process * highest[20];   //will contains all the process with highest priority and arrived and incomplete
struct process *executable[20]; //will contain elements of same priority and same minimum arrival time


//showdata() function shows the process data
void showdata(struct process * array[],int n)
{
		struct process *p;
		cout<<"\nPro\t"<<"Arr\t"<<"Pri\t"<<"Bur\tCom\tTurn\tWait\tRes\t\n";
		for(int i=0;i<n;i++)
		{
			p=array[i];
			cout<<p->id<<"\t"<<p->at<<"\t"<<p->pr<<"\t"<<p->bti<<"\t"<<p->ct<<"\t"<<p->tat<<"\t"<<p->wt<<"\t"<<p->rt<<"\t"<<"\n";
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

//To list all the process which is arrived and not completed yet
void update_arrival(struct process *a[],int n)
{
    struct process *p;
    int k=0;                //number of terms in arrived array
    for(int i=0;i<n;i++)
    {
        p=a[i];
        if(p->at<=ct && p->flag!=1)
        {
            arrived[k]=p;
            k++;
        }
    }
    nopa=k;  
}


//To get the array of processes which are arrived,not completed and is of highest priority all together
void update_highest_priority()
{
    int min;
    int k=0;
    struct process *p;
    p=arrived[0];
    min=p->pr;

    for(int i=0;i<nopa;i++)
    {
        p=arrived[i];
        if(p->pr<min)
        min=p->pr;
    }

    for(int i=0;i<nopa;i++)
    {
        p=arrived[i];
        if(p->pr==min )
        {highest[k]=p;
        k++;}
    }
    nopwhp=k;
}

//If highest priority array contains many elements then select process on basis of FCFS
void update_min_arrival_time()
{
    int min;
    int k=0;
    struct process *p;
    p=highest[0];
    min=p->at;

    for(int i=0;i<nopwhp;i++)
    {
        p=highest[i];
        if(p->at<min)
        min=p->at;
    }

    for(int i=0;i<nopwhp;i++)
    {
        p=highest[i];
        if(p->at==min)
        {executable[k]=p;
        k++;}
    }
    nopmat=k;
    
   
}

//Main priority preamption function
void prior_preamp(struct process *a[],int n)
{
    struct process *exec;
    while(ct!=sum_bt)
    {
        
        update_arrival(a,n);
        update_highest_priority();
        update_min_arrival_time();
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
        {
            exec->flag=1;
            exec->ct=ct;
            exec->tat=exec->ct-exec->at;
            exec->wt=exec->tat-exec->bti;
        }
          
    }
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
		cout<<"\nEnter arrival time and priority and burst time for process"<<i+1<<" ";
	
		cin>>a;
        cin>>pr;
        cin>>b;
		
		p->at=a;
        p->pr=pr;
		p->bt=b;
        p->bti=b;
        
		
		
	    p->flag=0;
		p->wt=0;
		p->tat=0;
		p->rt=0;
		p->ct=ct;
	}
	
 
	sbt(array,n);
    cout<<"\nProcess execution order is ";
    prior_preamp(array,n);
    showdata(array,n);
	awt_atat_art(array,n);
	

}