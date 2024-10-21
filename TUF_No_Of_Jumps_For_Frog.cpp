#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

void minFrogJump(int index,vector<int> ht,int TotalEnery, int& minEneryLost)
{
    //cout << "index=" << index << " TotalEnergy=" << TotalEnery << " MinEneryLost So far =" << minEneryLost << endl;
    int n = ht.size()-1;
    if(index>=n)
    {
        if(minEneryLost>TotalEnery)
        {
            cout << "Total Energy=" << TotalEnery << endl;
            minEneryLost = TotalEnery;
        }
        return;
    }


    minFrogJump(index+1,ht,TotalEnery+abs(ht[index+1]-ht[index]),minEneryLost);


    minFrogJump(index+2,ht,TotalEnery+abs(ht[index+2]-ht[index]),minEneryLost);

}


int fun(int index,vector<int>ht,vector<int>& dp)
{
    if(index==0)
        return 0;

    int left = fun(index-1,ht,dp)+abs(ht[index]-ht[index-1]);

    int right = INT_MAX;
    if(index>=2)
    {
        right = fun(index-2,ht,dp)+abs(ht[index]-ht[index-2]);
    }

    if(left>right)
    {
        return right;
    }
    else
    {
        return left;
    }

}

int fun_With_Memoization(int index,vector<int>ht,vector<int>& dp)
{
    if(index==0)
        return 0;

    int left;
    if(dp[index]!=-1)
    {
        cout << "dp Known =" << dp[index] << endl;
        return dp[index];

    }
    left = fun(index-1,ht,dp)+abs(ht[index]-ht[index-1]);

    int right = INT_MAX;
    if(index>=2)
    {
        right = fun(index-2,ht,dp)+abs(ht[index]-ht[index-2]);
    }

    if(left>right)
    {
        dp[index]=right;
        return right;
    }
    else
    {
        dp[index]=left;
        return left;
    }

}

int fun_With_Tabulation(vector<int> ht)
{
    int n = ht.size();
    cout << "n=" << n << endl;
    vector<int> dp(n+1,0);
    dp[0]=0;
    for(int i=1;i<n+1;i++)
    {
        int fs = dp[i-1]+abs(ht[i]-ht[i-1]);
        int ss = INT_MAX;
        if(i>1)
        {
            ss = dp[i-2]+abs(ht[i]-ht[i-2]);
        }
        dp[i]=(fs>ss)?ss:fs;
    }

    for(auto d:dp)
    {
        cout << d << ",";
    }
    return dp[n-1];  // The value to reach n is stored at n-1
}

int fun_With_SpaceOptimation(vector<int> ht)
{
    int n = ht.size();
    cout << "n=" << n << endl;
    int prev1=0;
    int prev2 = 0;
    int cur;
    for(int i=1;i<n;i++)
    {
        int fs = prev1+abs(ht[i]-ht[i-1]);
        int ss = INT_MAX;
        if(i>1)
        {
            ss = prev2+abs(ht[i]-ht[i-2]);
        }
        cur=(fs>ss)?ss:fs;
        prev2=prev1;
        prev1=cur;
    }

    return prev1;  // The value to reach n is stored at n-1 and is reached by prev1
}


int main()
{
    vector<int> ht = {30,10,60,10,60,50};
    int minEneryLost = INT_MAX;

    //minFrogJump(0,ht,0, minEneryLost);
   //cout << "MinEneryLost Possible =" << minEneryLost << endl;


    vector<int> dp;
    dp.resize(ht.size()+1,-1);
    //int ans = fun_With_Memoization(ht.size()-1,ht,dp);
    //cout << "MinEneryLost Possible =" << ans << endl;

   // int ans = fun_With_Tabulation(ht);
    //cout << "MinEneryLost Possible =" << ans << endl;


    int ans = fun_With_SpaceOptimation(ht);
    cout << "MinEneryLost Possible =" << ans << endl;



    return 0;
}
