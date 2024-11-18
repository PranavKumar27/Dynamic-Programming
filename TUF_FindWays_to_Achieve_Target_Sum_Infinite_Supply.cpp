#include <iostream>
#include <vector>

using namespace std;

void print_1D_v(vector<int> v)
{
    for(auto d:v)
        cout << d << " ";

    cout << endl;
}

void print_2D_v(vector<vector<int>> v)
{
    for(auto d:v)
        print_1D_v(d);

    cout << endl;
}
int NoOfWaysToReachTarget(int index,int target,vector<int> arr,vector<int> ArrList)
{
    if(index==0)
    {
        if(target%arr[0]==0)
        {
            int quo = target/arr[0];
            for(int i=0;i<quo;i++)
            {
                ArrList.push_back(arr[0]);
            }
            print_1D_v(ArrList);
            return 1;
        }

        else
            return 0;
    }
    int not_take = NoOfWaysToReachTarget(index-1,target,arr,ArrList);
    int take = 0;
    if(arr[index]<=target)
    {
        ArrList.push_back(arr[index]);
        take = NoOfWaysToReachTarget(index,target-arr[index],arr,ArrList);
    }

    return take+not_take;
}

int NoOfWaysToReachTarget(int index,int target,vector<int> arr,vector<vector<int>>& dp)
{
    if(index==0)
    {
        if(target%arr[0]==0)
        {
            return 1;
        }

        else
            return 0;
    }
    if(dp[index][target]!=-1)
    {
        return dp[index][target];
    }
    int not_take = NoOfWaysToReachTarget(index-1,target,arr,dp);
    int take = 0;
    if(arr[index]<=target)
    {
        take = NoOfWaysToReachTarget(index,target-arr[index],arr,dp);
    }

    return dp[index][target]=take+not_take;
}

int NoOfWaysToReachTarget(int targetSum,vector<int> arr)
{
    int n = arr.size();
    vector<vector<int>> dp(n,vector<int>(targetSum+1,0));

    for(int target=0;target<targetSum+1;target++)
    {
        if(target%arr[0]==0)
            dp[0][target]=1;
    }

    for(int index=1;index<n;index++)
    {
        for(int target=0;target<targetSum+1;target++)
        {
            int not_take = dp[index-1][target];
            int take = 0;
            if(arr[index]<=target)
            {
                take = dp[index][target-arr[index]];
            }

            dp[index][target]=take+not_take;
        }
    }
    print_2D_v(dp);
    return dp[n-1][targetSum];
}

int NoOfWaysToReachTarget_Space(int targetSum,vector<int> arr)
{
    int n = arr.size();
    vector<int> Prev(targetSum+1,0);
    vector<int> Cur(targetSum+1,0);

    for(int target=0;target<targetSum+1;target++)
    {
        if(target%arr[0]==0)
            Prev[target]=1;
    }

    for(int index=1;index<n;index++)
    {
        for(int target=0;target<targetSum+1;target++)
        {
            int not_take = Prev[target];
            int take = 0;
            if(arr[index]<=target)
            {
                take = Cur[target-arr[index]];
            }

            Cur[target]=take+not_take;
        }
        Prev=Cur;
    }
    print_1D_v(Prev);
    return Prev[targetSum];
}

int main()
{
    vector<int> arr = {1,2,3};
    int targetSum = 4;
    int n = arr.size();
    vector<int> ArrList;
    int ans = NoOfWaysToReachTarget(n-1,targetSum,arr,ArrList);
    cout << "## NoOfWaysToReachTarget = "  << ans << endl;

    vector<vector<int>> dp(n,vector<int>(targetSum+1,-1));
    ans = NoOfWaysToReachTarget(n-1,targetSum,arr,dp);
    cout << "## NoOfWaysToReachTarget Using Memo = "  << ans << endl;

    ans = NoOfWaysToReachTarget(targetSum,arr);
    cout << "## NoOfWaysToReachTarget Using Tabu = "  << ans << endl;

    ans = NoOfWaysToReachTarget_Space(targetSum,arr);
    cout << "## NoOfWaysToReachTarget Using Space = "  << ans << endl;

    return 0;
}
