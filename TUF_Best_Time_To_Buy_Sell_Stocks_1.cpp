#include <iostream>
#include <vector>
using namespace std;

int max_Profit(vector<int>& Prices)
{
    int n =Prices.size();
    int min_price = Prices[0];
    int max_profit = 0; // Buy and Sell on the Same Day

    for(int i=1;i<n;i++)
    {
        int today_price = Prices[i];
        int today_Profit = today_price - min_price;
        max_profit = max(max_profit,today_Profit);
        min_price = min(min_price,today_price);
    }
    return max_profit;
}
int main()
{
    vector<int> Stock_prices = {7,1,5,3,6,4};
    int ans = max_Profit(Stock_prices);
    cout << "Max Profit =" << ans << endl;
    return 0;
}
