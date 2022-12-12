#include<iostream>
#include<queue>
using namespace std;


int main()
{
    int p,r,i,j;
    int allocated[20][20];
    int max[20][20];
    int needed[20][20];
    int available[20];
    int total_allocated[20];
    int total_available[20];
    int flag[20];

    cout<<"\nEnter number of process and number of resources ";
    cin>>p;
    cin>>r;

    //TELLING COMPILER THAT THIS PROCESS IS NOT EXECUTED YET
    for(i=0;i<p;i++)
    flag[i]=0;

    cout<<"\nEnter total available resources of each type ";
    for(i=0;i<r;i++)
    cin>>total_available[i];

    cout<<"\nEnter data of resources each process allocated with ";
    for(i=0;i<p;i++)
    {
        for(j=0;j<r;j++)
        {
            cin>>allocated[i][j];
        }
    }

    cout<<"\nEnter data of resources each process needs maximum ";
    for(i=0;i<p;i++)
    {
        for(j=0;j<r;j++)
        {
            cin>>max[i][j];
        }
    }
    
    //CALCULATING NEED MATRIX
    for(i=0;i<p;i++)
    {
        for(j=0;j<r;j++)
        {
            needed[i][j]=max[i][j]-allocated[i][j];
        }
    }

    cout<<"\n THE NEED MATRIX IS\n";
    for(i=0;i<p;i++)
    {
        for(j=0;j<r;j++)
        {
            cout<<needed[i][j]<<"\t";
        }
        cout<<"\n";
    }

    int sum;
    int k=0;
    while(k<r)
    {
        sum=0;
        for(i=0;i<p;i++)
        {
            sum=sum+allocated[i][k];
        }
        total_allocated[k]=sum;
        k++;
    }

    cout<<"\nTotal number of resources allocated is ";
    for(i=0;i<r;i++)
    cout<<total_allocated[i]<<'\t';

    cout<<"\nTotal resources available is ";
    for(i=0;i<r;i++)
    {
        available[i]=total_available[i]-total_allocated[i];
        cout<<available[i]<<"\t";
    }

    queue<int>sequence;

    int count =0;
    while(count!=p)
    {
        for(i=0;i<p;i++)
        {
            
            int k=0;
            if(flag[i]==0)
            {   
                int nota=1;
                while(k<r)
                {
                    if(needed[i][k]>available[k])
                    {
                        nota=0;
                        break;
                    }
                    k++;
                }
                if(nota==1)
                {
                    k=0;
                    while(k<r)
                    {
                    available[k]=available[k]+allocated[i][k];
                    k++;
                    }
                    flag[i]=1;
                    sequence.push(i);
                    break;                  //NOT REQUIRED JUST WRITTEN FOR START EXECUTION FROM UPWARDS ALWAYS
                }

            }
        }
        count++;
    }

    int safe=1;
    for(i=0;i<p;i++)
    {
        if(flag[i]==0)
        safe=0;

    }
    if(safe==1)
    {
        cout<<"\nONE OF THE SAFE SEQUENCE IS ";
        while(!sequence.empty())
        {
            cout<<sequence.front()<<" ";
            sequence.pop();
        }
    
        cout<<"\nAT LAST AVAILABLE MATRIX IS ";
        for(i=0;i<r;i++)
        cout<<available[i]<<"\t";
    }
    else
    {
        cout<<"\nSAFE SEQUENCE COULD NOT BE FOUND";
    }
}