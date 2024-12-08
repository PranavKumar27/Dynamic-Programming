#include <iostream>
#include <vector>

using namespace std;

int maxProfit(int index,int canBuy,int Max_cap,vector<int> StockPriceList)
{
    int n = StockPriceList.size();
    if(index==n||Max_cap==0)
        return 0;

    int profit = 0;
    if(canBuy)
    {
        profit = max(-StockPriceList[index]+maxProfit(index+1,0,Max_cap,StockPriceList),
                     0 + maxProfit(index+1,1,Max_cap,StockPriceList));
    }
    else
    {
        profit = max(StockPriceList[index]+maxProfit(index+1,1,Max_cap-1,StockPriceList),
                     0 + maxProfit(index+1,0,Max_cap,StockPriceList));
    }
    return profit;

}
// Recursion Sol2 TC --> O(2^N)
// SC --> O(N*2*K)
int maxProfit(int index,int tran_No,vector<int> StockPriceList,int k)
{
    int n = StockPriceList.size();
    int Max_transactons = 2*k;
    if(index==n||tran_No == Max_transactons)
        return 0;

    int profit = 0;
    if(tran_No%2==0) // can_buy case
    {
        profit = max(-StockPriceList[index]+maxProfit(index+1,tran_No+1,StockPriceList,k),
                     0 + maxProfit(index+1,tran_No,StockPriceList,k));
    }
    else
    {
        profit = max(StockPriceList[index]+maxProfit(index+1,tran_No+1,StockPriceList,k),
                     0 + maxProfit(index+1,tran_No,StockPriceList,k));
    }
    return profit;

}
// Memoization TC --> O(N*2*K)
// SC --> O(N*2*K) + O(N*2*K)
int maxProfit(int index,int tran_No,vector<int> StockPriceList,int k,vector<vector<int>>& dp)
{
    int n = StockPriceList.size();
    int Max_transactons = 2*k;
    if(index==n||tran_No == Max_transactons)
        return 0;

    if(dp[index][tran_No]!=-1)
    {
        return dp[index][tran_No];
    }
    int profit = 0;
    if(tran_No%2==0) // can_buy case
    {
        profit = max(-StockPriceList[index]+maxProfit(index+1,tran_No+1,StockPriceList,k,dp),
                     0 + maxProfit(index+1,tran_No,StockPriceList,k,dp));
    }
    else
    {
        profit = max(StockPriceList[index]+maxProfit(index+1,tran_No+1,StockPriceList,k,dp),
                     0 + maxProfit(index+1,tran_No,StockPriceList,k,dp));
    }

    return dp[index][tran_No] = profit;

}

// Tabulation TC --> O(N*2*K)
// SC -->  O(N*2*K)
int maxProfit(vector<int> StockPriceList,int k)
{

    int n = StockPriceList.size();
    int Max_transactons = 2*k;
    vector<vector<int>> dp(n+1,vector<int>(Max_transactons+1,-1));

    for(int trans_No=Max_transactons;trans_No>=0;trans_No--)
    {
        dp[n][trans_No] = 0;
    }

    for(int index=0;index<n+1;index++)
    {
        dp[index][Max_transactons] = 0;
    }

    // Above Base condition can also be skipped if dp is initially set to 0.


    for(int index=n-1;index>=0;index--)
    {
        for(int trans_No = Max_transactons-1;trans_No>=0;trans_No--)
        {
            int profit = 0;
            if(trans_No%2==0) // can_buy case
            {
                profit = max(-StockPriceList[index]+dp[index+1][trans_No+1],
                             0 + dp[index+1][trans_No]);
            }
            else
            {
                profit = max(StockPriceList[index]+dp[index+1][trans_No+1],
                             0 + dp[index+1][trans_No]);
            }

            dp[index][trans_No] = profit;
        }
    }

    return dp[0][0];

}

// Space Optimization TC --> O(N*2*K)
// SC -->  O(N*2*K)
int maxProfit(vector<int> StockPriceList,int k,bool IsSpaceOptimized)
{

    int n = StockPriceList.size();
    int Max_transactons = 2*k;
    vector<int> Next(Max_transactons+1,-1);
    vector<int> Cur (Max_transactons+1,-1);

    for(int trans_No=Max_transactons;trans_No>=0;trans_No--)
    {
        Next[trans_No] = 0;
    }

    for(int index=0;index<n+1;index++)
    {
        Next[Max_transactons] = 0;
    }

    // Above Base condition can also be skipped if dp is initially set to 0.


    for(int index=n-1;index>=0;index--)
    {
        for(int trans_No = Max_transactons-1;trans_No>=0;trans_No--)
        {
            int profit = 0;
            if(trans_No%2==0) // can_buy case
            {
                profit = max(-StockPriceList[index]+Next[trans_No+1],
                             0 + Next[trans_No]);
            }
            else
            {
                profit = max(StockPriceList[index]+Next[trans_No+1],
                             0 + Next[trans_No]);
            }

            Cur[trans_No] = profit;
        }
        Next = Cur;
    }

    return Next[0];

}

int main()
{
    vector<int> StockPriceList = {3,3,5,0,0,3,1,4};
    int n = StockPriceList.size();
    int max_Cap = 2;// A transaction is complete when Sell is performed,
    // Each Sell transaction will have corresponding Buy already done.
    int ans = maxProfit(0,1,max_Cap,StockPriceList);
    cout << "Max Profit Restricted_Buy_Sell Twice Using Recursion Sol1 = " << ans << endl;

    int K_noOfBuys_Or_Sell = 3;
    ans = maxProfit(0,0,StockPriceList,K_noOfBuys_Or_Sell);
    cout << "Max Profit Restricted_Buy_Sell Twice Using Recursion Sol2 = " << ans << endl;

    K_noOfBuys_Or_Sell = 2;
    vector<vector<int>> dp(n,vector<int>(2*K_noOfBuys_Or_Sell,-1));
    ans = maxProfit(0,0,StockPriceList,K_noOfBuys_Or_Sell,dp);
    cout << "Max Profit Restricted_Buy_Sell Twice Using Memoization Sol2 = " << ans << endl;

    ans = maxProfit(StockPriceList,K_noOfBuys_Or_Sell+1);
    cout << "Max Profit Restricted_Buy_Sell Twice Using Tabulation Sol2 = " << ans << endl;

    ans = maxProfit(StockPriceList,K_noOfBuys_Or_Sell,true);
    cout << "Max Profit Restricted_Buy_Sell Twice Using Space Optimized Sol2 = " << ans << endl;

    return 0;
}
