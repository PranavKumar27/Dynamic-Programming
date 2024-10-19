#include <iostream>
#include <vector>

using namespace std;

/// Fibbonaaci Series 0 1 1 2 3 5 8 ......

int fib_UsingMemoization(int n,vector<int>& dp)
{
    if(n<=1)
        return n;
    else if(dp[n]!=-1)
    {
        return dp[n];
    }
    else
        dp[n]=fib_UsingMemoization(n-1,dp)+fib_UsingMemoization(n-2,dp);
        return dp[n];

    /// TC:O(n)
    /// SC:O(n) for Array + O(n) for Recursion
}

int fib_UsingTabulation(int n,vector<int>& dp)
{
    dp[0]=0;
    dp[1]=1;

    for(int i=2;i<n+1;i++)
    {
        dp[i]=dp[i-1]+dp[i-2];
    }

    return dp[n];

    /// TC:O(n)
    /// SC:O(n) No Recursion
}

int fib_UsingOptimizedTabulation(int n)
{
    int prev2=0;
    int prev1=1;

    for(int i=2;i<n+1;i++)
    {
        int cur = prev1+prev2;
        prev2=prev1;
        prev1=cur;
    }

    return prev1;

    /// TC:O(n)
    /// SC:0 No Space Used
}

int main()
{
    vector<int> dp;
    int n = 5;
    dp.resize(n+1,-1);
    // find fib of n
    cout << "Fib(5) Using Memoization =" << fib_UsingMemoization(n,dp) << endl;

    cout << "Fib(5) Using Tabulation =" << fib_UsingTabulation(n,dp) << endl;

    cout << "Fib(5) Using Optimized Tabulation =" << fib_UsingOptimizedTabulation(n) << endl;
    return 0;
}

