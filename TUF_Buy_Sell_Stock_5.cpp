#include <iostream>
#include <vector>

using namespace std;

//Recursion TC --> O(2^N)
// SC --> O(N) Recursion Stack
int max_profit(int index,int canBuy,vector<int>& StockPriceList,int fee)
{
    int n = StockPriceList.size();
    if(index==n)
        return 0;

    int profit = 0;
    if(canBuy)
    {
        profit = max(-StockPriceList[index]+max_profit(index+1,0,StockPriceList,fee),
                     0 + max_profit(index+1,1,StockPriceList,fee));
    }
    else
    {
        profit = max(StockPriceList[index]-fee+max_profit(index+1,1,StockPriceList,fee),
                     0 + max_profit(index+1,0,StockPriceList,fee));
    }
    return profit;
}

//Memoization TC --> O(2*N)
// SC --> O(N) + O(2*N) 
int max_profit(int index,int canBuy,vector<int>& StockPriceList,int fee,vector<vector<int>>& dp)
{
    int n = StockPriceList.size();
    if(index==n)
        return 0;

    if(dp[index][canBuy]!=-1)
    {
        return dp[index][canBuy];
    }

    int profit = 0;
    if(canBuy)
    {
        profit = max(-StockPriceList[index]+max_profit(index+1,0,StockPriceList,fee),
                     0 + max_profit(index+1,1,StockPriceList,fee));
    }
    else
    {
        profit = max(StockPriceList[index]-fee+max_profit(index+1,1,StockPriceList,fee),
                     0 + max_profit(index+1,0,StockPriceList,fee));
    }
    return dp[index][canBuy] = profit;
}

//Tabulation TC --> O(N)
// SC --> O(N*2)
int max_profit(vector<int>& StockPriceList,int fee)
{
    int n = StockPriceList.size();
    vector<vector<int>> dp(n+1,vector<int>(2,0));


    for(int index=n-1;index>=0;index--)
    {

        dp[index][1] = max(-StockPriceList[index]+dp[index+1][0],
                            0 + dp[index+1][1]);

        dp[index][0] = max(StockPriceList[index]-fee+dp[index+1][1],
                            0 + dp[index+1][0]);

    }

    return dp[0][1]; // Return from dp[0][1] so that dp is at canBuy State 1 means can Buy;

}

//Space Optimized TC --> O(N)
// SC --> O(4) Constant
int max_profit(vector<int>& StockPriceList,int fee,int SpaceOptimzed)
{
    int n = StockPriceList.size();
    vector<int> Next(2,0);
    vector<int> Cur(2,0);


    for(int index=n-1;index>=0;index--)
    {

        Cur[1] = max(-StockPriceList[index]+Next[0],
                            0 + Next[1]);

        Cur[0] = max(StockPriceList[index]-fee+Next[1],
                            0 + Next[0]);

        Next = Cur;

    }

    return Next[1]; // Return from Next[1] so that dp is at canBuy State 1 means can Buy;

}

//Space Optimized TC --> O(N)
// SC --> O(4) Constant
int max_profit_2_Var(vector<int>& StockPriceList,int fee,int SpaceOptimzed)
{
    int n = StockPriceList.size();
    int NextBuy,NextNotBuy,CurBuy,CurNotBuy;
    NextBuy = 0;  // 1 Means Buy
    NextNotBuy = 0; // 0 means NotBuy

    for(int index=n-1;index>=0;index--)
    {

        CurBuy = max(-StockPriceList[index]+NextNotBuy,
                            0 + NextBuy);

        CurNotBuy = max(StockPriceList[index]-fee+NextBuy,
                            0 + NextNotBuy);

        NextBuy = CurBuy;
        NextNotBuy = CurNotBuy;
    }

    return NextBuy; // Return from Next[1] so that dp is at canBuy State 1 means can Buy;

}

int main()
{
    vector<int> StockPriceList = {1,3,2,8,4,9};
    int fee = 2;
    int ans = max_profit(0,1,StockPriceList,fee);
    cout << "max_profit Using Recursion = " << ans << endl;


    int n = StockPriceList.size();
    vector<vector<int>> dp(n,vector<int>(2,-1));
    ans = max_profit(0,1,StockPriceList,fee,dp);
    cout << "max_profit Using Memoization = " << ans << endl;

    ans = max_profit(StockPriceList,fee);
    cout << "max_profit Using Tabulation = " << ans << endl;

    ans = max_profit(StockPriceList,fee,true);
    cout << "max_profit Using Space Optimization = " << ans << endl;

    ans = max_profit_2_Var(StockPriceList,fee,true);
    cout << "max_profit Using Space Optimization Sol 2 = " << ans << endl;
    return 0;
}
