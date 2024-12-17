#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

void print_1D_int_array(vector<int> v)
{
    for(auto d:v)
    {
        cout << setw(10) << d << " ";
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

int findMinCost(int i,int j,vector<int>& ArrList)
{
    //cout << __FUNCTION__ << "( " << i << "," << j << " )" << endl;
    if(i>j)
    {
        //cout << "Base Case Exit" << endl;
        return 0;
    }

    int mini = 1e9;
    for(int k=i;k<=j;k++)
    {
        int cost = ArrList[j+1]-ArrList[i-1] +
                    findMinCost(i,k-1,ArrList) +
                    findMinCost(k+1,j,ArrList);
        //cout << "cost =" << cost << endl;
        mini = min(mini,cost);
    }
    //cout << "=============================" << endl;
    return mini;
}

int findMinCost(int i,int j,vector<int>& ArrList,vector<vector<int>>& dp)
{
    //cout << __FUNCTION__ << "( " << i << "," << j << " )" << endl;
    if(i>j)
    {
        //cout << "Base Case Exit" << endl;
        return 0;
    }

    if(dp[i][j]!=-1)
    {
        return dp[i][j];
    }

    int mini = 1e9;
    for(int k=i;k<=j;k++)
    {
        int cost = ArrList[j+1]-ArrList[i-1] +
                    findMinCost(i,k-1,ArrList,dp) +
                    findMinCost(k+1,j,ArrList,dp);
        //cout << "cost =" << cost << endl;
        mini = min(mini,cost);
    }
    //cout << "=============================" << endl;
    return dp[i][j] = mini;;
}


int findMinCost(vector<int>& ArrList)
{
    int sz = ArrList.size();
    int n = sz-2;
    vector<vector<int>> dp(sz,vector<int>(sz,0));

    for(int i=n;i>=1;i--)
    {
        for(int j=1;j<=n;j++)
        {
            if(i>j)
                continue;
            int mini = 1e9;
            for(int k=i;k<=j;k++)
            {
                int cost = ArrList[j+1]-ArrList[i-1] +
                            dp[i][k-1] +
                            dp[k+1][j];
                cout << "cost =" << cost << endl;
                mini = min(mini,cost);
            }

            dp[i][j] = mini;

        }
    }
    print_2D_int_array(dp);

    return dp[1][n];
}


int main()
{
    vector<int> ArrList = {3,4,5,1};
    int n = ArrList.size();
    int length_of_rod = 7;

    ArrList.insert(ArrList.begin(),0);
    ArrList.push_back(length_of_rod);
    sort(ArrList.begin(),ArrList.end());
    int sz = ArrList.size();

    cout << "sz=" << sz << endl;
    int ans = findMinCost(1,n,ArrList);

    cout << "Min Cost to cut rod =" << ans << endl;



    vector<vector<int>> dp(sz,vector<int>(sz,-1));

    ans = findMinCost(1,n,ArrList,dp);

    cout << "Min Cost to cut rod Using Memoization=" << ans << endl;


    ans = findMinCost(ArrList);

    cout << "Min Cost to cut rod Using Tabulation=" << ans << endl;

    return 0;
}
