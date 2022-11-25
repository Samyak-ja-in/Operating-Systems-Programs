//FIRST COME FIRST SERVE METHOD FCFS

#include<iostream>

using namespace std;
int wt[50];
int tat[50];

void calculate_tat(int b[],int n)
{
     tat[0]=b[0];
	for(int i=1;i<n;i++)
	{	
		tat[i]=b[i]+tat[i-1];
	}
}
	
void calculate_wt(int b[],int n)
{
	calculate_tat(b,n);
	for(int i=0;i<n;i++)
	{
		wt[i]=tat[i]-b[i];
	}
}


int main()
{
	int n;
	int b[50];
	cout<<"Enter number of processes ";
	cin>>n;
	cout<<"Enter burst time for each process in order ";
	for(int i=0;i<n;i++)
	cin>>b[i];
	calculate_wt(b,n);
	cout<<"Process\tBurst time\tWaiting time\tTurnaroundtime\n";
	for(int i=0;i<n;i++)
	cout<<i<<"\t"<<b[i]<<"\t\t "<<wt[i]<<"\t\t"<<tat[i]<<"\n";
	
	float awt=0,att=0;
	for(int i=0;i<n;i++)
	{
	awt=awt+wt[i];
	att=att+tat[i];
	}
	awt=awt/n;
	att=att/n;
	cout<<"\nAverage waiting time is "<<awt;
	cout<<"\nAverage turn around time is "<<att;
	
}
	

	

