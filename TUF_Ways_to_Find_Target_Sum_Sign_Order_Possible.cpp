#include <iostream>
#include <vector>

using namespace std;

// FInd the ways in which 1,3,2,1 can be arranged to reach diff of K=3
// Way 1: { 1,1,3 }  and { 2 } diff = 3
// Way 2: { 2, 3 } and { 1, 1 } diff = 3

int findTargetSum(int index,int target,vector<int> arr)
{
    if(target == 0)
        return 1;

    if(index==0)
    {
        if(target==arr[0])
            return 1;
        else
            return 0;
    }

    int not_take = findTargetSum(index-1,target,arr);
    int take = 0;
    if(arr[index]<=target)
        take = findTargetSum(index-1,target-arr[index],arr);

    return take+not_take;
}

int findTargetSum(int index,int target,vector<int> arr,vector<vector<int>>& dp)
{
    if(target == 0)
        return 1;

    if(index==0)
    {
        if(target==arr[0])
            return 1;
        else
            return 0;
    }

    if(dp[index][target]!=-1)
        return dp[index][target];
    int not_take = findTargetSum(index-1,target,arr,dp);
    int take = 0;
    if(arr[index]<=target)
        take = findTargetSum(index-1,target-arr[index],arr,dp);

    return dp[index][target]=take+not_take;
}

int findTargetSum(int target,vector<int> arr)
{
    int n = arr.size();
    vector<vector<int>> dp(n,vector<int>(target+1,0));

    for(int i=0;i<n;i++)
    {
        dp[i][0]=1;
    }

    if(arr[0]<=target)
        dp[0][arr[0]]=1;

    for(int index=1;index<n;index++)
    {
        for(int tar=0;tar<target+1;tar++)
        {
            int not_take = dp[index-1][tar];
            int take = 0;
            if(arr[index]<=tar)
                take = dp[index-1][tar-arr[index]];

            dp[index][tar]=take+not_take;
        }
    }
    return dp[n-1][target];
}

int findTargetSum_Space(int target,vector<int> arr)
{
    int n = arr.size();
    vector<int> Prev(target+1,0);
    vector<int> Cur(target+1,0);

    for(int i=0;i<n;i++)
    {
        Prev[0]=1;
    }

    if(arr[0]<=target)
        Prev[arr[0]]=1;

    for(int index=1;index<n;index++)
    {
        for(int tar=0;tar<target+1;tar++)
        {
            int not_take = Prev[tar];
            int take = 0;
            if(arr[index]<=tar)
                take = Prev[tar-arr[index]];

            Cur[tar]=take+not_take;
        }
        Prev = Cur;
    }
    return Prev[target];
}

int findTotalSum(vector<int> arr)
{
    int sum = 0;
    for(auto d:arr)
        sum+=d;
    return sum;
}
int countZeros(vector<int> arr)
{
    int cnt = 0;
    for(auto d:arr)
    {
        if(d==0)
            cnt++;
    }
    return cnt;
}
int main()
{
    vector<int> arr = {0,1,3,2,1};
    int K = 3;
    int totalSum = findTotalSum(arr);
    int S1 = (totalSum - K)/2;
    cout << "S1=" << S1 << endl;
    int n = arr.size();
    int ans = findTargetSum(n-1,S1,arr);
    int cntZeros = countZeros(arr);
    if(cntZeros>0)
        ans = ans*2*cntZeros; // Each Zero modifies ways by 2, take and not take
    cout << "findTargetSum =" << ans << endl;

    vector<vector<int>> dp(n,vector<int>(S1+1,-1));
    ans = findTargetSum(n-1,S1,arr,dp);
    if(cntZeros>0)
        ans = ans*2*cntZeros; // Each Zero modifies ways by 2, take and not take
    cout << "findTargetSum Using Memo =" << ans << endl;

    ans = findTargetSum(S1,arr);
    if(cntZeros>0)
        ans = ans*2*cntZeros; // Each Zero modifies ways by 2, take and not take
    cout << "findTargetSum Using Tabu =" << ans << endl;

    ans = findTargetSum_Space(S1,arr);
    if(cntZeros>0)
        ans = ans*2*cntZeros; // Each Zero modifies ways by 2, take and not take
    cout << "findTargetSum Using Space =" << ans << endl;

    return 0;
}
