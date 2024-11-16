#include <iostream>
#include <vector>

using namespace std;

void print_2D_v(vector<vector<int>> dp)
{
    for(int i=0;i<dp.size();i++)
    {
        for(int j=0;j<dp[0].size();j++)
        {
            cout << dp[i][j] << "\t";
        }
        cout << endl;
    }
}

int countNoOfZeros(vector<int> arr)
{
    int cnt = 0;
    for(auto d:arr)
    {
        if(d==0)
            cnt++;
    }
    return cnt;
}

int countSubSetsSumK(int index,int sum,vector<int> arr)
{
    if(index==0)
    {
        if(sum==0 && arr[0]==0)
            return 2;
        else if(sum==0)
            return 1;
        else if(arr[0]==sum)
            return 1;
        else
            return 0;
    }

    if(index!=0 && sum==0)
    {
        int cnt = countNoOfZeros(arr);
        if(cnt>=1)
        {
            return 2*cnt;
        }
        else
            return 1;
    }


    int not_take = countSubSetsSumK(index-1,sum,arr);

    int take = 0;
    if(arr[index]<=sum)
    {
        take = countSubSetsSumK(index-1,sum-arr[index],arr);
    }

    return take+not_take;
}



int countSubSetsSumK_Memo(int index,int sum,vector<int> arr,vector<vector<int>>& dp)
{
    if(index==0)
    {
        if(sum==0 && arr[0]==0)
            return 2;
        else if(sum==0)
            return 1;
        else if(arr[0]==sum)
            return 1;
        else
            return 0;

    }

    if(index!=0 && sum==0)
    {
        int cnt = countNoOfZeros(arr);
        if(cnt>=1)
        {
            return 2*cnt;
        }
        else
            return 1;
    }



    if(dp[index][sum]!=-1)
    {
        return dp[index][sum];
    }

    int not_take = countSubSetsSumK_Memo(index-1,sum,arr,dp);

    int take = 0;
    if(arr[index]<=sum)
    {
        take = countSubSetsSumK_Memo(index-1,sum-arr[index],arr,dp);
    }

    return dp[index][sum]=take+not_take;
}

int countSubSetsSumK_Tabu(vector<int> arr,int targetSum)
{
    int n = arr.size();
    vector<vector<int>> dp(n,vector<int>(targetSum+1,0));

    for(int i=0;i<n;i++)
    {
        dp[i][0]=1;
    }

    if(arr[0]==0)
    {
        dp[0][arr[0]] = 2;
    }
    else if(arr[0]<=targetSum)
    {
        dp[0][arr[0]] = 1;
    }


    print_2D_v(dp);
    cout << endl;
    for(int index=1;index<n;index++)
    {
        for(int target=0;target<targetSum+1;target++)
        {
            int not_take = dp[index-1][target];

            int take = 0;
            if(arr[index]<=target)
            {
               take = dp[index-1][target - arr[index]];
            }

            dp[index][target] = take + not_take;
        }
    }

    print_2D_v(dp);
    return dp[n-1][targetSum];
}


int findSum(vector<int> arr)
{
    int sum = 0;
    for(auto d:arr)
        sum+=d;
    return sum;
}

int main()
{
    vector<int> arr ={2,5,6,4};
    int K = 3;
    int totalSum = findSum(arr);
    int S1 = (totalSum - K)/2;
    cout <<  " S1 =" << S1 << endl;
    int n = arr.size();
    int ans_Recursion = countSubSetsSumK(n-1,S1,arr);
    cout <<" countSubSetsSumK = " << ans_Recursion << endl;



    vector<vector<int>> dp(n,vector<int>(S1+1,-1));
    int ans_Memo = countSubSetsSumK_Memo(n-1,S1,arr,dp);
    cout <<" countSubSetsSumK Using Memo= " << ans_Memo << endl;


    int ans_Tabu = countSubSetsSumK_Tabu(arr,S1);
    cout <<" countSubSetsSumK Using Tabu= " << ans_Tabu << endl;

    return 0;
}
