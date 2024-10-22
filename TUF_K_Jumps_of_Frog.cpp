#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

void print_v(vector<int> v)
{
    for(auto d:v)
    {
        cout << d << ",";
    }
    cout << endl;
}

int frogKJumps(int index,vector<int>ht,int k) // Top to bottom Jump
{
    if(index==0) // In order to reach 0 from 0 we need 0 step
    {
        return 0;
    }

    int min_jump_energy = INT_MAX;
    for(int i=1;i<=k;i++)
    {
        int new_val = INT_MAX;
        if(index-i>=0)
        {
            new_val = frogKJumps(index-i,ht,k)+abs(ht[index-i]-ht[index]);
        }
        cout << "new_val =" << new_val << endl;
        min_jump_energy = min(min_jump_energy,new_val);
        cout << "min_jump_energy =" << min_jump_energy << endl;
    }
    cout << "For index = " << index << " Returning min_jump_energy =" << min_jump_energy << endl;
    return min_jump_energy;
}

int frogKJumps_Using_Memoization(int index,vector<int>ht,int k,vector<int>& dp) // Top to bottom Jump
{
    if(index==0) // In order to reach 0 from 0 we need 0 step
    {
        return 0;
    }

    if(dp[index]!=-1)
    {
        return dp[index];
    }

    int min_jump_energy = INT_MAX;
    for(int i=1;i<=k;i++)
    {
        int new_val = INT_MAX;

        if(index-i>=0)
        {
            new_val = frogKJumps_Using_Memoization(index-i,ht,k,dp)+abs(ht[index-i]-ht[index]);
        }
        min_jump_energy = min(min_jump_energy,new_val);
    }
    dp[index] = min_jump_energy;
    return min_jump_energy;
}

int frogKJumps_Using_Tabulation(vector<int>ht,int k) // Top to bottom Jump
{
    int n= ht.size();
    vector<int> dp(n+1);

    dp[0]=0; // In order to reach 0 from 0 we need 0 step

    for(int index=1;index<n;index++)
    {
        int min_jump_energy = INT_MAX;
        for(int j=1;j<=k;j++)
        {
            int new_val = INT_MAX;

            if(index-j>=0)
            {
                new_val = dp[index-j]+abs(ht[index-j]-ht[index]);
            }
            min_jump_energy = min(min_jump_energy,new_val);
        }
        cout << "min_jump_energy =" << min_jump_energy << " for index=" << index << endl;
        dp[index]=min_jump_energy;//+abs(ht[index-1]-ht[index]);
    }

    return dp[n-1];
}

int frogKJumps_Using_Tabulation_SpaceOptimalK(vector<int>ht,int k) // Top to bottom Jump
{
    int n= ht.size();
    vector<int> Prev(k,0);

    for(int index=1;index<n;index++)
    {
        int min_jump_energy = INT_MAX;
        for(int j=1;j<=k;j++)
        {
            int new_val = INT_MAX;

            if(index-j>=0)
            {
                new_val = Prev[k-j]+abs(ht[index-j]-ht[index]);
            }
            min_jump_energy = min(min_jump_energy,new_val);
        }

        for(int i=0;i<k-1;i++)
        {
            Prev[i] = Prev[i+1];
        }
        Prev[k-1] = min_jump_energy;
        cout << "min_jump_energy =" << min_jump_energy << " for index=" << index << endl;
        //dp[index]=min_jump_energy;//+abs(ht[index-1]-ht[index]);
    }
    print_v(Prev);
    return Prev[k-1];
}


int main()
{
    /*
    vector<int> ht = {30,10,60,10,60,50};

    int n = 5;
    int k=2;
    int minEneryLost = frogKJumps(n,ht,k);
    cout << "Min Energy Lost if Frog Jumps K =" << k << " steps =" << minEneryLost << endl;



    vector<int> ht = {30,10,60,10,60,50};

    int n = 5;
    int k=2;
    vector<int> dp(n+1,-1);
    int minEneryLost = frogKJumps_Using_Memoization(n,ht,k,dp);
    cout << "Min Energy Lost if Frog Jumps K Using_Memoization =" << k << " steps =" << minEneryLost << endl;


    vector<int> ht = {30,10,60,10,60,50};

    int n = 5;
    int k=2;
    int minEneryLost = frogKJumps_Using_Tabulation(ht,k);
    cout << "Min Energy Lost if Frog Jumps K  Using_Tabulation=" << k << " steps =" << minEneryLost << endl;

    */

    vector<int> ht = {30,10,60,10,60,50};

    int n = 5;
    int k=2;
    int minEneryLost = frogKJumps_Using_Tabulation_SpaceOptimalK(ht,k);
    cout << "Min Energy Lost if Frog Jumps K  Using SpaceOptimalK =" << k << " steps =" << minEneryLost << endl;

    return 0;
}
