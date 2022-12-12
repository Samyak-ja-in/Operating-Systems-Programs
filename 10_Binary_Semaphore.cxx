#include<iostream>
#include<queue>
using namespace std;

int ct=0;
struct process
{
    int id;
    int bt;
}p1,p2,p3;

struct semaphore
{
    int value;
    queue <process>q1;
} s1;

void signal();
void critical_section(process a);

void wait(process a[],int n)
{
    for(int i=1;i<n;i++)
    (s1.q1).push(a[i]);

    if(s1.value==1)
    {
        s1.value=0;
        critical_section(a[0]);
        
    }

}

void showqueue(queue<process>q)
{
    process p;
    while(!q.empty())
    {
        p=q.front();
        q.pop();
        cout<<" "<<p.id<<" ";
    }
    cout<<"\t"<<s1.value;
}

void critical_section(process a)
{
    cout<<"\n  "<<a.id<<"\t"<<a.bt<<"\t";
    showqueue(s1.q1);
    ct=ct+a.bt;
    signal();
}

void signal()
{
    process p;
    if(!s1.q1.empty())
    {
        p=s1.q1.front();
        s1.q1.pop();
        critical_section(p);
    }
    else
    s1.value=1;
}

int main()
{
    int bt[20];int n;
  

    process a[3];
    
    s1.value=1;
    
    p1.id=1;
    p1.bt=2;
    

    p2.id=2;
    p2.bt=3;
    

    p3.id=3;
    p3.bt=4;
    

    a[0]=p1;
    a[1]=p2;
    a[2]=p3;

    cout<<"\n INITIALLY SEMPAHORE VALUE IS "<<s1.value;

    cout<<"\nPRO ID\tBUR TI\tWAIT\tSEMAPHORE\n";
    wait(a,3);
    
    cout<<"\nFINALLY SEMAPHORE VALUE "<<s1.value;
    cout<<"\nCURRENT TIME NOW BECOMES "<<ct;


}