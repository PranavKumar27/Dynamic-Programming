#include <iostream>
#include <vector>

using namespace std;

/*
If someone buys stock and sells it, he can either earn Profit or loss
Again if he buys new stocks and sells it he again can earn Profit or loss
Now in given set if some-one can buy 1 stock at time and can hold only 1 stock,
then find the maximum Profit for the entire Set
eg : Stock Prices 3 3 5 0 0 3 1 4
if some buys stocks at 3 on day1 and sold at 5 on day2, Profit = 2
    Again he buys stocks at 1 on day6 and sold at 4 on day7, Profit = 3
        Overall Profit = 5

    if some buys stocks at 0 on day4 and sold at 3 on day5, Profit = 3
    Again he buys stocks at 1 on day6 and sold at 4 on day7, Profit = 3
        Overall Profit = 6

    Since We can Buy and Sell Stocks only Twice
    So Max Profit Possible is 6

Condition : One can have 1 stock in hand,
            One can either buy or sell stock in a day, Can't do both
            Once someone has stock, First it has to be sold,
            then only on the next day stocks can be bought
** We can Buy and Sell Stocks only Twice
No of trancations at max can be 4 ( buy + Sell + buy + Sell)
*/

// Recursion TC --> O(2^n)
// SC --> O(n*2)
int maxProfitRestricted_Buy_Sell(int index,int canBuy,int max_Cap,vector<int> StockPriceList)
{
    int n = StockPriceList.size();
    if(index==n || max_Cap==0)
    {
        return 0;
    }

    int profit = 0;
    if(canBuy)
    {
        profit = max(-StockPriceList[index] + maxProfitRestricted_Buy_Sell(index+1,0,max_Cap,StockPriceList),
                     0 + maxProfitRestricted_Buy_Sell(index+1,1,max_Cap,StockPriceList));
    }
    else
    {
        profit = max( StockPriceList[index] + maxProfitRestricted_Buy_Sell(index+1,1,max_Cap-1,StockPriceList),
                     0 + maxProfitRestricted_Buy_Sell(index+1,0,max_Cap,StockPriceList));
    }
    return profit;
}

// Memoization TC --> O(N*2*3)
// SC -->  O(N) + O(N*2*2)
// Auxilliary Space Consumed Here O(N). This can be Removed in Tabulaton
int maxProfitRestricted_Buy_Sell(int index,int canBuy,int max_Cap,vector<int> StockPriceList,vector<vector<vector<int>>>& dp)
{
    int n = StockPriceList.size();
    if(index==n || max_Cap==0)
    {
        return 0;
    }

    if(dp[index][canBuy][max_Cap]!=-1)
    {
        return dp[index][canBuy][max_Cap];
    }
    int profit = 0;
    if(canBuy)
    {
        profit = max(-StockPriceList[index] + maxProfitRestricted_Buy_Sell(index+1,0,max_Cap,StockPriceList,dp),
                     0 + maxProfitRestricted_Buy_Sell(index+1,1,max_Cap,StockPriceList,dp));
    }
    else
    {
        profit = max( StockPriceList[index] + maxProfitRestricted_Buy_Sell(index+1,1,max_Cap-1,StockPriceList,dp),
                     0 + maxProfitRestricted_Buy_Sell(index+1,0,max_Cap,StockPriceList,dp));
    }

    return dp[index][canBuy][max_Cap] = profit;
}

// Tabulation TC --> O(N*2*2)
// SC --> O(N*2*2)
// No Auxilliary Space Consumed Here
int maxProfitRestricted_Buy_Sell(int max_Cap,vector<int> StockPriceList)
{
    int n = StockPriceList.size();
    vector<vector<vector<int>>> dp(n+1,
            vector<vector<int>>(2,
                    vector<int>(max_Cap+1,-1)));


    for(int canBuy=0;canBuy<2;canBuy++)
    {
        for(int cap=0;cap<max_Cap+1;cap++)
        {
            dp[n][canBuy][cap] = 0;
        }
    }

    for(int index=0;index<n;index++)
    {
       for(int canBuy=0;canBuy<2;canBuy++)
       {
           dp[index][canBuy][max_Cap] = 0;
       }
    }

    for(int index =n-1 ;index>=0; index--)
    {
        for(int canBuy =0 ;canBuy<2; canBuy++)
        {
            for(int cap=0 ; cap<max_Cap+1; cap++)
            {
                int profit = 0;
                if(canBuy)
                {
                    profit = max(-StockPriceList[index] + dp[index+1][0][cap],
                                 0 + dp[index+1][1][cap]);
                }
                else
                {
                    if(cap>0)
                    {
                        profit = max( StockPriceList[index] + dp[index+1][1][cap-1],
                                 0 + dp[index+1][0][cap]);
                    }
                    else
                    {
                        profit = 0 + dp[index+1][0][cap];
                    }

                }

                dp[index][canBuy][cap] = profit;
            }
        }
    }

    return dp[0][1][max_Cap];

}
// Space Optimization TC --> O(N*2*3)
// SC --> O(2*3)  constant
int maxProfitRestricted_Buy_Sell_Space(int max_Cap,vector<int> StockPriceList)
{
    int n = StockPriceList.size();

    vector<vector<int>> Next(2,vector<int>(max_Cap+1,-1));

    vector<vector<int>> Cur(2,vector<int>(max_Cap+1,-1));


    for(int canBuy=0;canBuy<2;canBuy++)
    {
        for(int cap=0;cap<max_Cap+1;cap++)
        {
            Next[canBuy][cap] = 0;
        }
    }

    for(int index=0;index<n;index++)
    {
       for(int canBuy=0;canBuy<2;canBuy++)
       {
           Next[canBuy][max_Cap] = 0;
       }
    }

    for(int index =n-1 ;index>=0; index--)
    {
        for(int canBuy =0 ;canBuy<2; canBuy++)
        {
            for(int cap=0 ; cap<max_Cap+1; cap++)
            {
                int profit = 0;
                if(canBuy)
                {
                    profit = max(-StockPriceList[index] + Next[0][cap],
                                 0 + Next[1][cap]);
                }
                else
                {
                    if(cap>0)
                    {
                        profit = max( StockPriceList[index] + Next[1][cap-1],
                                 0 + Next[0][cap]);
                    }
                    else
                    {
                        profit = 0 + Next[0][cap];
                    }

                }

                Cur[canBuy][cap] = profit;
            }
        }
        Next = Cur;
    }

    return Next[1][max_Cap];

}

// Use 4 Variables Here instead of vector Next and Cur
int maxProfitRestricted_Buy_Sell_Space_Sol2(int max_Cap,vector<int> StockPriceList)
{
    int n = StockPriceList.size();

    vector<vector<int>> Next(2,vector<int>(max_Cap+1,-1));

    vector<vector<int>> Cur(2,vector<int>(max_Cap+1,-1));


    for(int canBuy=0;canBuy<2;canBuy++)
    {
        for(int cap=0;cap<max_Cap+1;cap++)
        {
            Next[canBuy][cap] = 0;
        }
    }

    for(int index=0;index<n;index++)
    {
       for(int canBuy=0;canBuy<2;canBuy++)
       {
           Next[canBuy][max_Cap] = 0;
       }
    }

    for(int index =n-1 ;index>=0; index--)
    {
        for(int canBuy =0 ;canBuy<2; canBuy++)
        {
            for(int cap=0 ; cap<max_Cap+1; cap++)
            {
                int profit = 0;
                if(canBuy)
                {
                    profit = max(-StockPriceList[index] + Next[0][cap],
                                 0 + Next[1][cap]);
                }
                else
                {
                    if(cap>0)
                    {
                        profit = max( StockPriceList[index] + Next[1][cap-1],
                                 0 + Next[0][cap]);
                    }
                    else
                    {
                        profit = 0 + Next[0][cap];
                    }

                }

                Cur[canBuy][cap] = profit;
            }
        }
        Next = Cur;
    }

    return Next[1][max_Cap];

}

// Solution 2 Memoization using N*4 vector
// TC --> O(2^n)
// SC --> O(N*4)
int maxProfit(int index,int transcation,vector<int> StockPriceList)
{
    int n = StockPriceList.size();
    if(index==n||transcation<0)
    {
        return 0;
    }

    int canBuy = transcation%2;
    int profit = 0;
    if(canBuy)
    {
        profit = max(-StockPriceList[index]+maxProfit(index+1,transcation-1,StockPriceList),
                   0 + maxProfit(index+1,transcation,StockPriceList));
    }
    else
    {
        profit = max(StockPriceList[index]+maxProfit(index+1,transcation-1,StockPriceList),
                     0 + maxProfit(index+1,transcation,StockPriceList));
    }

    return profit;
}

int main()
{
    vector<int> StockPriceList = {3,3,5,0,0,3,1,4};
    int max_Cap = 2;// A transaction is complete when Sell is performed,
    // Each Sell transaction will have corresponding Buy already done.
    int ans = maxProfitRestricted_Buy_Sell(0,1,max_Cap,StockPriceList);
    cout << "Max Profit Restricted_Buy_Sell Twice Using Recursion Sol1 = " << ans << endl;

    int m = StockPriceList.size();
    vector<vector<vector<int>>> dp(m,vector<vector<int>> (2,vector<int>(max_Cap+1,-1)));  // day * Buy/Sell * Max_Cap
    ans = maxProfitRestricted_Buy_Sell(0,1,max_Cap,StockPriceList,dp);
    cout << "Max Profit Restricted_Buy_Sell Twice Using Memoization = " << ans << endl;


    ans = maxProfitRestricted_Buy_Sell(max_Cap,StockPriceList);
    cout << "Max Profit Restricted_Buy_Sell Twice Using Tabulation = " << ans << endl;

    ans = maxProfitRestricted_Buy_Sell_Space(max_Cap,StockPriceList);
    cout << "Max Profit Restricted_Buy_Sell Twice Using Space = " << ans << endl;

    int transaction = 3;
        //  B   S   B   S
        //  0   1   2   3
    //Mod   0   1   0   1
    //CanBuy = Mod

    ans = maxProfit(0,transaction,StockPriceList);
    cout << "Max Profit Restricted_Buy_Sell Twice Using Recursion Sol 2 = " << ans << endl;
    return 0;
}
