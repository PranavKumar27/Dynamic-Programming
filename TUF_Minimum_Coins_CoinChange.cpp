#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print_2D_v(vector<vector<int>> dp)
{
    cout << endl;
    for(int i=0;i<dp.size();i++)
    {
        for(int j=0;j<dp[0].size();j++)
        {
            cout << dp[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void print_1D_v(vector<int> v)
{
    for(auto d:v)
        cout << d << "\t";

    cout << endl;
}


int minCoinChange(int NoOfcoins,int CoinVal,vector<int> Coins,vector<int> CoinsList)
{
    if(CoinVal<0)
    {
        return 0;
    }
    if(CoinVal==0)
    {
        print_1D_v(CoinsList);
        return NoOfcoins;
    }

    int n = Coins.size();
    int minCoins = 1e9;
    for(int index=0;index<n;index++)
    {
        CoinsList.push_back(Coins[index]);
        int val = minCoinChange(NoOfcoins+1,CoinVal-Coins[index],Coins,CoinsList);
        if(val!=0)
            minCoins = min(minCoins,val);

        auto pos = find(CoinsList.begin(),CoinsList.end(),Coins[index]);
        CoinsList.erase(pos);
    }
    return minCoins;
}

int findMinCoinCount(int index,int target,vector<int> Coins)
{
    if(index==0)
    {

        if(target%Coins[0]==0)// target is multiple of Coins[0]
            return target/Coins[0]; // Return Count of Coins of denominator Coins[0]
        else
            return 1e9;
    }

    int not_take = findMinCoinCount(index-1,target,Coins);

    int take = 1e9;
    if(Coins[index]<=target)
    {
        take = 1+findMinCoinCount(index,target-Coins[index],Coins);
    }

    return min(take,not_take);
}


int findMinCoinCount_Memo(int index,int target,vector<int> Coins,vector<vector<int>>& dp)
{
    if(index==0)
    {
        if(target%Coins[0]==0)// target is multiple of Coins[0]
            return target/Coins[0]; // Return Count of Coins of denominator Coins[0]
        else
            return 1e9;
    }



    if(dp[index][target]!=-1)
    {
        return dp[index][target];
    }

    int not_take = findMinCoinCount_Memo(index-1,target,Coins,dp);

    int take = 1e9;
    if(Coins[index]<=target)
    {
        take = 1+findMinCoinCount_Memo(index,target-Coins[index],Coins,dp);
    }

    return dp[index][target] = min(take,not_take);
}

int findMinCoinCount_Tabu(int target,vector<int> Coins)
{
    int n = Coins.size();
    vector<vector<int>> dp(n,vector<int>(target+1,0));

    for(int tar=0;tar<target+1;tar++)
    {
        int rem = tar%Coins[0];
        int div = tar/Coins[0];
        if(rem==0) // Divisible
            dp[0][tar]=div;
        else
            dp[0][tar]=1e9;
    }


    for(int index=1;index<n;index++)
    {
        for(int tar=0;tar<target+1;tar++)
        {
            int not_take = dp[index-1][tar];

            int take = 1e9;
            if(Coins[index]<=tar)
            {
                take = 1+dp[index][tar-Coins[index]];
            }
            dp[index][tar] = min(take,not_take);
        }
    }
    print_2D_v(dp);
    return dp[n-1][target];
}


int findMinCoinCount_Space_Optimized(int target,vector<int> Coins)
{
    int n = Coins.size();
    vector<int>Prev(target+1,0);
    vector<int>Cur(target+1,0);

    for(int tar=0;tar<target+1;tar++)
    {
        int rem = tar%Coins[0];
        int div = tar/Coins[0];
        if(rem==0) // Divisible
            Prev[tar]=div;
        else
            Prev[tar]=1e9;
    }


    for(int index=1;index<n;index++)
    {
        for(int tar=0;tar<target+1;tar++)
        {
            int not_take = Prev[tar];

            int take = 1e9;
            if(Coins[index]<=tar)
            {
                take = 1+Cur[tar-Coins[index]];
            }
            Cur[tar] = min(take,not_take);
        }
        Prev = Cur;
    }
    return Prev[target];
}

int main()
{
    vector<int> Coins = {2,1,3};
    vector<int> CoinsList;
    int target = 7;
    int ans = minCoinChange(0,target,Coins,CoinsList);
    cout << "minCoinChange = " << ans << endl;

    int n = Coins.size();
    int ans_Min_cnt = findMinCoinCount(n-1,target,Coins);
    cout << "findMinCoinCount = " << ans_Min_cnt << endl;

    vector<vector<int>> dp(n,vector<int>(target+1,-1));
    int ans_Min_cnt_Memo = findMinCoinCount_Memo(n-1,target,Coins,dp);
    cout << "findMinCoinCount Memo = " << ans_Min_cnt_Memo << endl;

    int ans_Min_cnt_Tabu = findMinCoinCount_Tabu(target,Coins);
    cout << "findMinCoinCount Tabu = " << ans_Min_cnt_Tabu << endl;

    int ans_Min_cnt_Space = findMinCoinCount_Space_Optimized(target,Coins);
    cout << "findMinCoinCount Space Optimized = " << ans_Min_cnt_Space << endl;

    return 0;
}
