#include <iostream>
#include <vector>
#include <algorithm>

/*
Find the Longest Divisible Subset Length and the Subset
If Arr = {1,7,8,4,16} , Find the LDS
Ans = {1,4,8,16} Len = 4, LDS can be in any order since we want LD
        which is a subset not subsequence

To Approach this we can create a dp[] which will hold the number
of Divisors of i in dp[i]
dp[i---n] will be have starting values as 1 since each number is divisible by itself

Step 1: Sort the Arr so that when we discover each node we discover in
increasing multipliers
Also create a Hash Arr to store the previous multiplier to find the LDS

Arr now {1,4,7,8,16}
dp[] = {1,1,1,1,1}
Hash[] = {0,1,2,3,4}

At i = 1 , val = 4
We check Arr[i]%Arr[prev] == 0 and dp[i]<1+dp[prev] , So dp[1] = 2
        Store Hash[1] = 0

At i=2, val = 7
We check Arr[i]%Arr[prev] == 0 and dp[i]<1+dp[prev]
         Arr[2]%Arr[1] == 0 and dp[2]<1+dp[1] ,
         7%4==0  --> False
         Arr[2]%Arr[0] == 0 and dp[2]<1+dp[0]
         7%1 and 1<1+1 --> , So dp[2] = 2
         Store Hash[2] = 1

At i=3, val = 8
We check Arr[i]%Arr[prev] == 0 and dp[i]<1+dp[prev]
         Arr[3]%Arr[2] == 0 and dp[3]<1+dp[2] ,
         8%7==0  --> False
         Arr[3]%Arr[1] == 0 and dp[3]<1+dp[1]
         8%4 and 3<1+2 --> , So dp[3] = 3
         Arr[3]%Arr[0] == 0 and dp[3]<1+dp[0]
         8%1 and 3<1+1 --> False
         Hash[3] = 1

At i=4, val = 16
We check Arr[i]%Arr[prev] == 0 and dp[i]<1+dp[prev]
         Arr[4]%Arr[3] == 0 and dp[3]<1+dp[2] ,
         16%8 and 1<1+3 --> , So dp[4] = 4  --> True

         Arr[4]%Arr[2] == 0 and dp[3]<1+dp[1]
         16%7  --> , False

         Arr[4]%Arr[1] == 0 and dp[3]<1+dp[1]
         16%4 and 4<1+2 --> , False

         Arr[3]%Arr[0] == 0 and dp[3]<1+dp[0]
         16%1 and 4<1+1 --> False
         Hash[4] = 3

AT the end
    dp[] ={1,2,2,3,4}
Hash[]   ={0,0,0,1,3}



*/
using namespace std;

void print_1D_v(vector<int>& v)
{
    for(auto d:v)
        cout << d << " ";
    cout << endl;
}

int max_LDS(vector<int> ArrList)
{
    int n = ArrList.size();
    sort(ArrList.begin(),ArrList.end());
    vector<int>dp(n,1);
    vector<int>Hash(n);
    for(int i=0;i<n;i++)
    {
        Hash[i]=i;
    }

    int max_len=-1,max_idx = -1;
    for(int index=1;index<n;index++)
    {
        for(int prev=index-1;prev>=0;prev--)
        {
            if(ArrList[index]%ArrList[prev]==0)
            {
                if(dp[index]<1+dp[prev])
                {
                    dp[index] = 1+dp[prev];
                    Hash[index] = prev;
                }
            }

        }
        if(max_len<dp[index])
        {
            max_len = dp[index];
            max_idx = index;
        }
    }

    print_1D_v(dp);
    print_1D_v(Hash);


    vector<int> LDS;
    LDS.push_back(ArrList[max_idx]);
    int index = max_idx;

    while(Hash[index]!=index)
    {
        index = Hash[index];
        LDS.push_back(ArrList[index]);
    }

    cout << "LDS =" ;
    print_1D_v(LDS);

    return max_len;
}

int main()
{
    vector<int> ArrList = {1,7,8,4,16};

    int ans = max_LDS(ArrList);
    cout << "Max Len of LDS ( Longest Divisible Subset) =" << ans << endl;
    return 0;
}
