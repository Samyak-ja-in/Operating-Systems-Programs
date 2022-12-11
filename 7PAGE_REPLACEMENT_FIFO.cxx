#include<iostream>
#include<queue>

using namespace std;

int n;      //Number of Frames in main memory

queue<char>ongoing;

bool present_in(char ch)
{
    queue<char>local;
    local=ongoing;
    while(local.size()!=0)
    {
        if(local.front()==ch)
        {
            return true;
        }
        local.pop();
    }
    return false;

}


void fifo(char string[])
{
    char ch;
    int i=0;
    float fault=0;
    float hit=0;
    bool present;
    
    ch=string[0];
    while(ch!='\0')
    {
        if(ongoing.size()!=n)
        {
            present=present_in(ch);

            if(present)
                hit=hit+1;
            else
            {
                ongoing.push(ch);
                fault=fault+1;
            }
            
        }
        else
        {
           present=present_in(ch);
            
            if(present)
                hit=hit+1;
            else
            {
               ongoing.pop();
               ongoing.push(ch);
                fault=fault+1;
            }
        }


        
        i++;
        ch=string[i];
    }

    float hit_ratio,miss_ratio;
    hit_ratio=hit/i;
    miss_ratio=fault/i;

    cout<<"\nNUMBER OF PAGES IN STRING IS "<<i;
    cout<<"\nNUMBER OF FAULTS IS "<<fault;
    cout<<"\nNUMBER OF HITS IS "<<hit;
    cout<<"\nHIT RATIO "<<hit_ratio;
    cout<<"\nMISS RATIO "<<miss_ratio;
}


int main()
{
    char string[40];

    cout<<"\n Enter the string ";
    cin>>string;

    cout<<"\nEnter number of frames ";
    cin>>n;

    fifo(string);

}