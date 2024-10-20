#include <iostream>
#include <vector>

using namespace std;

// This problem is same as Fibbonaacci Series Problem

/// Type1 for Problem 1: Using Recursion
int countNoOfStairs_2_Steps(int index)
{
    if(index==0)
    {
        return 1;
    }
    if(index==1)
    {
        return 1;
    }

    int l = countNoOfStairs_2_Steps(index-1);
    int r = countNoOfStairs_2_Steps(index-2);

    return (l+r);
}
/// Type2 for Problem 1: Using Memoization Large to Small
int countNoOfStairs_2_Steps_Memoization(int index,vector<int> dp)
{
    if(index==0)
    {
        return 1;
    }
    if(index==1)
    {
        return 1;
    }

    if(dp[index]!=-1)
        return dp[index];
    else
    {
        int l = countNoOfStairs_2_Steps(index-1);
        int r = countNoOfStairs_2_Steps(index-2);
        dp[index] = l+r;
        return dp[index];
    }

}

/// Type 3 for Problem 1: Using Tabulation Small to Large
int countNoOfStairs_2_Steps_Tabulation(int n)
{
    vector<int> dp(n+1);
    dp[0]=1;

    for(int i=1;i<n+1;i++)
    {
        if(i==1)
        {
            dp[i]=dp[i-1];
        }
        else
        {
            dp[i]=dp[i-1]+dp[i-2];
        }
    }
    return dp[n];
}

/// Type1 for Problem 2 : Using Recursion
int countNoOfStairs_3_Steps(int n)
{
    if(n==0)
        return 1;
    if(n==1)
        return 1;
    if(n==2)
        return 2;

    int way1=countNoOfStairs_3_Steps(n-1);
    int way2=countNoOfStairs_3_Steps(n-2);
    int way3=countNoOfStairs_3_Steps(n-3);

    return way1+way2+way3;
}

/// Type2 for Problem 2: Using Memoization Large to Small
int countNoOfStairs_3_Steps_Memoization(int n,vector<int> dp)
{
    if(n==0)
        return 1;
    if(n==1)
        return 1;
    if(n==2)
        return 2;

    if(dp[n]!=-1)
        return dp[n];
    else
    {
        int way1=countNoOfStairs_3_Steps(n-1);
        int way2=countNoOfStairs_3_Steps(n-2);
        int way3=countNoOfStairs_3_Steps(n-3);
        dp[n]=way1+way2+way3;
    }
    return dp[n];
}

/// Type 3 for Problem 2: Using Tabulation Small to Large
int countNoOfStairs_3_Steps_Tabulation(int n)
{
    vector<int> dp;
    dp.resize(n+1);
    dp[0]=1;

    for(int i=1;i<n+1;i++)
    {

        if(i==1)
        {
            dp[i]=dp[i-1];
        }
        else if(i==2)
        {
            dp[i] = dp[i-1]+dp[i-2];
        }
        else
        {
            dp[i] = dp[i-1]+dp[i-2]+dp[i-3];
        }
    }
    return dp[n];
}

int main()
{

    /// Problem 1 with 2 Steps on Stairs 0 and 1  This problem is same as Fibbonaacci Series
    int n = 3;
    vector<int> arr;
    int K = n; // Total number of Stairs
    int ans = countNoOfStairs_2_Steps(n);
    cout << "No of ways to climb stairs with steps 1 and 2 for Stair for height " << n << "  = " << ans << endl;

    vector<int> dp(n+1,-1);
    ans = countNoOfStairs_2_Steps_Memoization(n,dp);
    cout << "No of ways to climb stairs with steps 1 and 2 Using Memoization for Stair for height " << n << "  = " << ans << endl;

    ans = countNoOfStairs_2_Steps_Tabulation(n);
    cout << "No of ways to climb stairs with steps 1 and 2 Using Tabulation for Stair for height " << n << "  = " << ans << endl;



    /// Problem 2 with 3 Steps on Stairs 0 1 and 2
    int n2 = 4;
    /// Type1 : Using Recursion
    int ans2 = countNoOfStairs_3_Steps(n2);
    cout << "No of ways to climb stairs with steps 1, 2 and 3 for Stair for height " << n2 << "  = " << ans2 << endl;

    /// Type2: Using Memoization Large to Small
    dp.resize(n2+1,-1);
    ans2 = countNoOfStairs_3_Steps_Memoization(n2,dp);
    cout << "No of ways to climb stairs with steps 1, 2 and 3 Using Memoization for Stair for height " << n2 << "  = " << ans2 << endl;

    /// Type 3: Using Tabulation Small to Large
    ans2 = countNoOfStairs_3_Steps_Tabulation(n2);
    cout << "No of ways to climb stairs with steps 1, 2 and 3 Using Tabulation for Stair for height " << n2 << "  = " << ans2 << endl;

    return 0;
}
