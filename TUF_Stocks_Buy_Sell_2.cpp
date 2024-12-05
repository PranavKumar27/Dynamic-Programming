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
*/


int maxProfitInStocks(int index,bool isBought,vector<int> SPrices)
{
    if(index==SPrices.size())
    {
        return 0;
    }

    // isBought = true means stock is held and can only be sold now
    // isBought = false means no stock is held and can only be Buy Stock now

    if(isBought)
    {
        return max ( SPrices[index]+maxProfitInStocks(index+1,false,SPrices) ,
                     0 + maxProfitInStocks(index+1,true,SPrices) );
    }
    else
    {
        return max( -SPrices[index]+maxProfitInStocks(index+1,true,SPrices),
                     0 + maxProfitInStocks(index+1,false,SPrices) );
    }
}

int maxProfitInStocks(int index,int isBought,vector<int> SPrices,vector<vector<int>>& dp)
{
    if(index==SPrices.size())
    {
        return 0;
    }

    if(dp[index][isBought]!=-1)
    {
        cout << "Returned from dp" << endl;
        return dp[index][isBought];
    }

    // isBought = true means stock is held and can only be sold now
    // isBought = false means no stock is held and can only be Buy Stock now

    int profit = 0;
    if(isBought)
    {
        profit = max ( SPrices[index]+maxProfitInStocks(index+1,0,SPrices,dp) ,
                        0 + maxProfitInStocks(index+1,isBought,SPrices,dp) );

    }
    else
    {
        profit = max( -SPrices[index]+maxProfitInStocks(index+1,1,SPrices,dp),
                        0 + maxProfitInStocks(index+1,isBought,SPrices,dp) );
        cout << "index =" << index << " Profit=" << profit << endl;
    }

    return dp[index][isBought] = profit;
}

int maxProfitInStocks(vector<int> SPrices)
{
    int m = SPrices.size();
    vector<vector<int>> dp(m+1,vector<int>(2,-1));

    for(int j=0;j<2;j++)
        dp[m][j]=0;


    // isBought = true means stock is held and can only be sold now
    // isBought = false means no stock is held and can only be Buy Stock now

    for(int index=m-1;index>=0;index--)
    {
        for(int isBought=0;isBought<2;isBought++)
        {
            int profit = 0;
            if(isBought) // isBought = 1
            {
                profit = max ( SPrices[index]+dp[index+1][0] ,
                                0 + dp[index+1][isBought] );
                cout << "index =" << index << " Profit=" << profit << endl;
                dp[index][isBought] = profit;
                //break;
            }
            else
            {
                profit = max( -SPrices[index]+dp[index+1][1] ,
                                0 + dp[index+1][isBought] );
                cout << "index =" << index << " Profit=" << profit << endl;
                dp[index][isBought] = profit;
                //break;
            }

        }
    }
    print_2D_int_array(dp);
    return dp[0][1];
}

int main()
{
    vector<int> SPrices = {7,1,5,3,6,4};
    int ans = maxProfitInStocks(0,false,SPrices);
    cout << "Max - Profit -- InStocks =" << ans << endl;

    int m = SPrices.size();
    vector<vector<int>> dp(m,vector<int>(2,-1));
    ans = maxProfitInStocks(0,0,SPrices,dp);
    print_2D_int_array(dp);
    cout << "Max - Profit -- InStocks Using Memoization=" << ans << endl;

    ans = maxProfitInStocks(SPrices);
    cout << "Max - Profit -- InStocks Using Tabulation=" << ans << endl;

    return 0;
}
