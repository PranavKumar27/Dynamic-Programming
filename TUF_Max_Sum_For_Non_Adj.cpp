#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int maxSumOfNonAdjJumps(int index,vector<int> Num) // Pass the last index
{
    if(index == 0)
        return Num[index];

    if(index<0)
        return 0;

    int pick = Num[index] + maxSumOfNonAdjJumps(index-2,Num);

    int not_pick = 0 + maxSumOfNonAdjJumps(index-1,Num);

    return max(pick,not_pick);

}

int maxSumOfNonAdjJumps_Memoization(int index,vector<int> Num,vector<int>& dp) // Pass the last index
{
    if(index == 0)
    {
        dp[0]=Num[index];
        return Num[index];
    }


    if(index<0)
        return 0;

    if(dp[index]!=-1)
    {
        cout << "dp found dp =" << dp[index] << endl;
        return dp[index];
    }

    int pick = Num[index] + maxSumOfNonAdjJumps_Memoization(index-2,Num,dp);

    int not_pick = 0 + maxSumOfNonAdjJumps_Memoization(index-1,Num,dp);

    return dp[index] = max(pick,not_pick);

}


int maxSumOfNonAdjJumps_Tabulation(int index,vector<int> Num) // Pass the last index
{
    int n = Num.size();
    vector<int> dp(n+1);

    dp[0]=Num[0];

    for(int i=1;i<n;i++)
    {
        int pick = 0;

        if(i>=2)
            pick = Num[i]+dp[i-2];
        else
            pick = Num[i];

        int not_pick = 0 + dp[i-1];

        dp[i]=max(pick,not_pick);

    }
    return dp[n-1];

}

int maxSumOfNonAdjJumps__Space_Optimized(vector<int> Num) // Pass the last index
{
    int n = Num.size();
    int prev1 = 0;
    int prev2 = 0;

    for(int i=0;i<n;i++)
    {
        int cur = max(Num[i]+prev2,prev1);
        prev2=prev1;
        prev1=cur;
    }

    return prev1;
}


int main()
{
    vector<int> Num ={2,1,4,9};
    int n = Num.size()-1;
    //int ans = maxSumOfNonAdjJumps(n,Num);

    vector<int> dp(n+1,-1);
    //int ans = maxSumOfNonAdjJumps_Memoization(n,Num,dp);

    //int ans = maxSumOfNonAdjJumps_Tabulation(n,Num);


    int ans = maxSumOfNonAdjJumps__Space_Optimized(Num);
    cout << "MaxSumOfNonAdjJumps = " << ans << endl;



    return 0;
}
