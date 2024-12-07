#include <iostream>
#include <vector>

using namespace std;

void print_1D_int_array(vector<int> v)
{
    for(auto d:v)
    {
        cout << d << " ";
    }
    cout << endl;
}

void print_2D_int_array(vector<vector<int>> v)
{
    cout << endl;
    for(auto d:v)
    {
        print_1D_int_array(d);
    }
    cout << "\n" << endl;
}
/*
If someone buys stock and sells it, he can either earn Profit or loss
Again if he buys new stocks and sells it he again can earn Profit or loss
Now in given set if some-one can buy 1 stock at time and can hold only 1 stock,
then find the maximum Profit for the entire Set
eg : Stock Prices 7 1 5 3 6 4
if some buys stocks at 1 on day2 and sold at 5 on day3, Profit = 4
    Again he buys stocks at 3 on day4 and sold at 6 on day5, Profir = 3
        Overall Profit = 7

Condition : One can have 1 stock in hand,
            One can either buy or sell stock in a day, Can't do both
            Once someone has stock, First it has to be sold,
            then only on the next day stocks can be bought

Note Start from Canbuy as true It means you can start with Empty Container of stocks
If you start with CanBuy as false, It means you are holding stock already and wants to start from Selling the stock
*/


int maxProfitInStocks(int index,bool canBuy,vector<int> SPrices)
{
    if(index==SPrices.size())
    {
        return 0;
    }

    // canBuy = true stock can be bought and held
    // canBuy = false stock can be sold now

    if(canBuy)
    {
        return max( -SPrices[index]+maxProfitInStocks(index+1,false,SPrices),
                     0 + maxProfitInStocks(index+1,true,SPrices) );
    }
    else
    {
        return max ( SPrices[index]+maxProfitInStocks(index+1,true,SPrices) ,
                     0 + maxProfitInStocks(index+1,false,SPrices) );
    }
}

int maxProfitInStocks(int index,int canBuy,vector<int> SPrices,vector<vector<int>>& dp)
{
    if(index==SPrices.size())
    {
        return 0;
    }

    if(dp[index][canBuy]!=-1)
    {
        cout << "Returned from dp" << endl;
        return dp[index][canBuy];
    }


    int profit = 0;
    if(canBuy)
    {
        profit = max( -SPrices[index]+maxProfitInStocks(index+1,false,SPrices,dp), // Can sell since bought
                     0 + maxProfitInStocks(index+1,true,SPrices,dp) ); // Can buy Only
    }
    else
    {
        profit = max ( SPrices[index]+maxProfitInStocks(index+1,true,SPrices,dp) , // Can Buy since sold
                     0 + maxProfitInStocks(index+1,false,SPrices,dp) ); // Can sell Only
    }

    return dp[index][canBuy] = profit;
}

int maxProfitInStocks(vector<int> SPrices)
{
    int m = SPrices.size();
    vector<vector<int>> dp(m+1,vector<int>(2,0));

    for(int j=0;j<2;j++)
        dp[m][j]=0;


    for(int index=m-1;index>=0;index--)
    {
        for(int canBuy=0;canBuy<2;canBuy++)
        {
            int profit = 0;
            if(canBuy)
            {
                profit = max( -SPrices[index]+dp[index+1][0], // Can sell since bought
                             0 + dp[index+1][1] ); // Can buy Only
            }
            else
            {
               profit = max ( SPrices[index]+dp[index+1][1], // Can Buy since sold
                             0 + dp[index+1][1] ); // Can sell Only
            }
            dp[index][canBuy] = profit;
        }
    }
    print_2D_int_array(dp);
    return dp[0][1];
}

int maxProfitInStocks_Space(vector<int> SPrices)
{
    int m = SPrices.size();
    vector<int> Next(2,-1);
    vector<int> Cur(2,-1);

    for(int j=0;j<2;j++)
        Next[j]=0;


    for(int index=m-1;index>=0;index--)
    {
        for(int canBuy=0;canBuy<2;canBuy++)
        {
            int profit = 0;
            if(canBuy)
            {
                profit = max( -SPrices[index]+Next[0], // Can sell since bought
                             0 + Next[1] ); // Can buy Only
            }
            else
            {
               profit = max ( SPrices[index]+Next[1] , // Can Buy since sold
                             0 + Next[1] ); // Can sell Only
            }
            Cur[canBuy] = profit;

        }
        Next = Cur;
    }
    print_1D_int_array(Next);
    return Next[1];
}

int main()
{
    vector<int> SPrices = {7,1,5,3,6,4};
    int ans = maxProfitInStocks(0,true,SPrices); // Start from Can Buy , ** Do not start from true -> Means start from Sell
    cout << "Max - Profit -- InStocks =" << ans << endl;

    int m = SPrices.size();
    vector<vector<int>> dp(m,vector<int>(2,-1));
    ans = maxProfitInStocks(0,1,SPrices,dp);
    print_2D_int_array(dp);
    cout << "Max - Profit -- InStocks Using Memoization=" << ans << endl;

    ans = maxProfitInStocks(SPrices);
    cout << "Max - Profit -- InStocks Using Tabulation=" << ans << endl;

    ans = maxProfitInStocks_Space(SPrices);
    cout << "Max - Profit -- InStocks Using Space Optimization=" << ans << endl;

    return 0;
}
