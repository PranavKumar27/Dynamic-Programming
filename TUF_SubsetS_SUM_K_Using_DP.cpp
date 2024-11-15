#include <iostream>
#include <vector>

using namespace std;

void print_2D_v(vector<vector<int>> dp)
{
    int m = dp.size();
    int n= dp[0].size();

    for(int i=0;i<m;i++)
    {
        for(int k=0;k<n;k++)
        {
            cout << dp[i][k] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int SubsequencesSumK(int index,int sum,vector<int> arr)
{
    if(index==0)
    {
        if(arr[0]==sum)
            return 1;
        else
            return 0;
    }
    if(sum==0)
    {
        return 1;
    }

    int not_take = SubsequencesSumK(index-1,sum,arr);
    int take=0;
    if(arr[index]<=sum)
    {
        take = SubsequencesSumK(index-1,sum-arr[index],arr);
    }

    return take+not_take;
}

int SubsequencesSumK_Memo(int index,int sum,vector<int> arr,vector<vector<int>>& dp)
{
    if(index==0)
    {
        if(arr[0]==sum)
            return 1;
        else
            return 0;
    }
    if(sum==0)
    {
        return 1;
    }

    if(dp[index][sum]!=-1)
    {
        return dp[index][sum];
    }
    int not_take = SubsequencesSumK_Memo(index-1,sum,arr,dp);
    int take=0;
    if(arr[index]<=sum)
    {
        take = SubsequencesSumK_Memo(index-1,sum-arr[index],arr,dp);
    }

    return dp[index][sum]=take+not_take;
}

int SubsequencesSumK_Tabulation(vector<int> arr,int targetSum)
{
    int n = arr.size();
    vector<vector<int>> dp(n,vector<int>(targetSum+1,0));

    for(int i=0;i<n;i++)
    {
        dp[i][0] = 1;
    }

    if(arr[0]<=targetSum)
        dp[0][arr[0]] = 1;

    print_2D_v(dp);
    for(int index=1;index<n;index++)
    {
        for(int target=0;target<targetSum+1;target++)
        {
            int not_take = dp[index-1][target];
            int take = 0;
            if(arr[index]<=target)
            {
                take = dp[index-1][target-arr[index]];
            }

            // not_take as -1 will lower the actual Possible Sum Subsequence of K Sum
            dp[index][target] = take+not_take;

        }
    }

    print_2D_v(dp);
    return dp[n-1][targetSum];

}

int SubsequencesSumK_Space_Optimized(vector<int> arr,int targetSum)
{
    int n = arr.size();
    vector<int> Prev(targetSum+1,0);
    vector<int> Current(targetSum+1,0);

    Prev[0] = 1;


    if(arr[0]<=targetSum)
        Prev[arr[0]] = 1;

    for(int index=1;index<n;index++)
    {
        for(int target=0;target<targetSum+1;target++) // We start from 0 since target can also be xero
        {
            int not_take = Prev[target];
            int take = 0;
            if(arr[index]<=target)
            {
                take = Prev[target-arr[index]];
            }

            // not_take as -1 will lower the actual Possible Sum Subsequence of K Sum
            Current[target] = take+not_take;
        }
        Prev = Current;
    }

    return Prev[targetSum];

}

int main()
{
    vector<int> arr ={1,2,2,3};
    int  k = 3;
    int n = arr.size();
    int ans = SubsequencesSumK(n-1,k,arr);
    cout << "SubsequencesSumK =" << ans << endl;


    vector<vector<int>> dp(n,vector<int>(k+1,-1));
    int ans_Memo = SubsequencesSumK_Memo(n-1,k,arr,dp);
    cout << "SubsequencesSumK Using Memoization =" << ans_Memo << endl;


    int ans_Tabu = SubsequencesSumK_Tabulation(arr,k);
    cout << "SubsequencesSumK Using Tabulation =" << ans_Tabu << endl;


    int ans_Space_Optimized = SubsequencesSumK_Space_Optimized(arr,k);
    cout << "SubsequencesSumK Using Space_Optimized =" << ans_Space_Optimized << endl;

    return 0;
}
