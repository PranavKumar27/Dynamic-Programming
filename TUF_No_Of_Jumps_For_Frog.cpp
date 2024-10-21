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



int main()
{
    vector<int> ht = {30,10,60,10,60,50};
    int minEneryLost = INT_MAX;

    //minFrogJump(0,ht,0, minEneryLost);
   //cout << "MinEneryLost Possible =" << minEneryLost << endl;


    vector<int> dp;
    dp.resize(ht.size()+1,-1);
    int ans = fun_With_Memoization(ht.size()-1,ht,dp);
    cout << "MinEneryLost Possible =" << ans << endl;

    return 0;
}
