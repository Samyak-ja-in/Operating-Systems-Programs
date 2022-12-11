#include<iostream>
#include<queue>

using namespace std;

int n;      //Number of Frames in main memory

queue<char>ongoing;
queue<char>lru;

//TO CHECK WHEATHER A CHARACTER IS PRESENT IN A GIVEN QUEUE
bool present_in(char ch,queue<char>myqueue)
{
    queue<char>local;
    local=myqueue;
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

//TO FILL THE LEAST RECENTLY USED QUEUE
/*
    step1)If the size of lru is not equal to n(means less then n,n is the number of frames)
            CASE1)If character is present in LRU,Then remove the charater from its occuring position without disturbing the order of other elements and add it to the last in lru queue so that it becomes most recently used
            CASE2)If character is not present in the LRU then simply add character to the LRU list

    step2)If the size of lru is equal to n(n is the number of frames)
            CASE1)If character is present in LRU,Then remove the character from its occuring position without disturbing the order of other elements and add it to the last in lru queue so that it becomes most recently used.
            CASE2)If character is not present in the LRU then simply  pop out a character from LRU add character to the LRU list
*/

void update_lru(char ch)
{
    queue<char>local;
    while(lru.size()!=0)
    {
        if(lru.front()==ch)
        {
            lru.pop();
        }
        else
        {
            local.push(lru.front());
            lru.pop();
        }
    }
    local.push(ch);
    lru=local;
}


void fill_lru(char ch)
{
    bool present;
    present=present_in(ch,lru);
    

    if(lru.size()!=n)
    {
        
        if(present)
            update_lru(ch);
        else
            lru.push(ch);
    }

    else
    {
        if(present)
            update_lru(ch);
        else
        {
            lru.pop();
            lru.push(ch);
        }
    }
}

void least(char string[])
{
    char ch;
    int i=0;
    float fault=0;
    float hit=0;
    bool present;
    
    ch=string[0];
    while(ch!='\0')
    {
        present=present_in(ch,ongoing);
        
        if(ongoing.size()!=n)
        {
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
            if(present)
                hit=hit+1;
            else
            {
                char replace;
                replace=lru.front();

                queue<char>local;        
                                                  
                fault=fault+1;
                
                while(!ongoing.empty())
                {
                    if(ongoing.front()==replace)
                    {
                        ongoing.pop();
                        local.push(ch);
                    
                    }
                    else
                    {
                        local.push(ongoing.front());
                        ongoing.pop();
                    }
                }
                ongoing=local;


            }
        }
        

        fill_lru(ch);
        
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

    least(string);

}