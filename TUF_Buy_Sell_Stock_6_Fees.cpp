#include <iostream>
#include <vector>

using namespace std;


/*
If someone buys stock and sells it, he can either earn Profit or loss
Again if he buys new stocks and sells but in each Sell He has to subtract the Processing fee 
it he again can earn Profit or loss. Fee can be paid upfront during buying as well but not 
at buying as well as selling
Now in given set if some-one can buy 1 stock at time and can hold only 1 stock,
then find the maximum Profit for the entire Set
eg : Stock Prices 3 3 5 0 0 3 1 4
if some buys stocks at 3 on day1 and sold at 5 on day2, Profit = 2
    Again he buys stocks at 1 on day6 and sold at 4 on day7, Profit = 3
        Overall Profit = 5 - 2(fee) = 3

    So Max Profit Possible is 3

Condition : One can have 1 stock in hand,
            One can either buy or sell stock in a day, Can't do both
            Once someone has stock, First it has to be sold,
            then only on the next day stocks can be bought
** We can Buy and Sell Stocks any No Of times
No of transactions are unlimited
*/

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
