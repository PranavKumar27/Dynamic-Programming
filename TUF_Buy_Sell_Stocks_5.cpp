#include <iostream>
#include <vector>

using namespace std;

// Recursion TC --> O(2^N)
// SC --> O(N)
int max_profit(int index,int canBuy,vector<int> StockPriceList)
{
    int n = StockPriceList.size();
    if(index>=n)
        return 0;

    int profit = 0;
    if(canBuy)
    {
        profit = max(-StockPriceList[index]+max_profit(index+1,0,StockPriceList),
                     0 + max_profit(index+1,1,StockPriceList));
    }
    else
    {
        profit = max(StockPriceList[index]+max_profit(index+2,1,StockPriceList),
                     0 + max_profit(index+1,0,StockPriceList));
    }

    return profit;
}

// Memoization TC --> O(2*N)
// SC --> O(N) + O(2N)
int max_profit(int index,int canBuy,vector<int> StockPriceList,vector<vector<int>>& dp)
{
    int n = StockPriceList.size();
    if(index>=n)
        return 0;

    if(dp[index][canBuy]!=-1)
        return dp[index][canBuy];

    int profit = 0;
    if(canBuy)
    {
        profit = max(-StockPriceList[index]+max_profit(index+1,0,StockPriceList,dp),
                     0 + max_profit(index+1,1,StockPriceList,dp));
    }
    else
    {
        profit = max(StockPriceList[index]+max_profit(index+2,1,StockPriceList,dp),
                     0 + max_profit(index+1,0,StockPriceList,dp));
    }

    return dp[index][canBuy] = profit;
}


// Tabulation TC --> O(2*N)
// SC --> O(2N)
int max_profit(vector<int> StockPriceList)
{
    int n = StockPriceList.size();
    vector<vector<int>> dp(n+2,vector<int>(2,0));
    // Initialize dp with 0, this will include handling of the base case


    for(int index=n-1;index>=0;index--)
    {
        for(int canBuy=0;canBuy<2;canBuy++)
        {
            int profit = 0;
            if(canBuy)
            {
                profit = max(-StockPriceList[index]+dp[index+1][0],
                             0 + dp[index+1][1]);
            }
            else
            {
                profit = max(StockPriceList[index]+dp[index+2][1],
                             0 + dp[index+1][0]);
            }
            dp[index][canBuy] = profit;
        }
    }
    return dp[0][1];  // Return from dp[0][1] so that dp is at canBuy State 1 means can Buy;
}

// Tabulation TC --> O(N)
// SC --> O(6) Constant
int max_profit(vector<int> StockPriceList,bool IsSpaceOpt)
{
    int n = StockPriceList.size();
    vector<int> Next(2,0);
    vector<int> Next_2(2,0);
    vector<int> Cur(2,0);

    // Initialize dp with 0, this will include handling of the base case


    for(int index=n-1;index>=0;index--)
    {

        Cur[1] = max(-StockPriceList[index]+Next[0],
                             0 + Next[1]);
        Cur[0] = max(StockPriceList[index]+Next_2[1],
                             0 + Next[0]);
        Next_2 = Next;
        Next = Cur;
    }
    return Next[1];  // Return from dp[0][1] so that dp is at canBuy State 1 means can Buy;
}


int main()
{
    vector<int> StockPriceList = {4,9,0,4,10};
    int ans = max_profit(0,1,StockPriceList);
    cout << "Max Profit Using Recursion=" << ans << endl;

    int n = StockPriceList.size();
    vector<vector<int>> dp(n,vector<int>(2,-1));
    ans = max_profit(0,1,StockPriceList,dp);
    cout << "Max Profit Using Memo =" << ans << endl;

    ans = max_profit(StockPriceList);
    cout << "Max Profit Using Tabulation =" << ans << endl;

    ans = max_profit(StockPriceList,true);
    cout << "Max Profit Using Space Optimization =" << ans << endl;

    return 0;
}
