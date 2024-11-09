#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>

using namespace std;

int minSumInGrid(int row,int col,vector<vector<int>>& Grid)
{
    int m = Grid.size();
    int n = Grid[0].size();

    if( row>=m || col>=n || row<0 || col<0 )
    {
        return INT_MAX;
    }

    int currentNodeValue = Grid[row][col];
    int right = minSumInGrid(row,col+1,Grid);

    int bottom = minSumInGrid(row+1,col,Grid);

    if(right == INT_MAX && bottom == INT_MAX)
    {
        return currentNodeValue;
    }
    else
    {
        return (right>bottom)?bottom+currentNodeValue:right+currentNodeValue;
    }
}


int minSumInGrid_Memoization(int row,int col,vector<vector<int>>& Grid,vector<vector<int>>& dp)
{
    int m = Grid.size();
    int n = Grid[0].size();

    if( row>=m || col>=n || row<0 || col<0 )
    {
        return INT_MAX;
    }

    if(dp[row][col]!=-1)
    {
        cout << "Returned from DP" << endl;
        return dp[row][col];
    }
    int currentNodeValue = Grid[row][col];
    int right = minSumInGrid_Memoization(row,col+1,Grid,dp);

    int bottom = minSumInGrid_Memoization(row+1,col,Grid,dp);

    if(right == INT_MAX && bottom == INT_MAX)
    {
        return currentNodeValue;
    }
    else
    {
        return dp[row][col] = (right>bottom)?bottom+currentNodeValue:right+currentNodeValue;
    }
}


int minSumInGrid_Tabulation(vector<vector<int>>& Grid)
{
    int m = Grid.size();
    int n = Grid[0].size();

    vector<vector<int>> dp(m+1,vector<int>(n+1,INT_MAX));


    dp[m-1][n-1] = Grid[m-1][n-1];

    // Now moves are Up and left since we are at bottom Up Approach

    for(int i=m-1;i>=0;i--)
    {
        for(int j=n-1;j>=0;j--)
        {
            if(dp[i][j+1] == INT_MAX && dp[i+1][j] == INT_MAX )
                dp[i][j] = Grid[i][j];
            else
                dp[i][j] = min(dp[i][j+1],dp[i+1][j])+Grid[i][j];
        }
    }

    for(int i=0;i<m+1;i++)
    {
        for(int j=0;j<n+1;j++)
        {
            cout << setw(20) << dp[i][j] <<"\t";
        }
        cout << endl;
    }
    return dp[0][0];
}


int minSumInGrid_Tabulation_Bottom(vector<vector<int>>& Grid)
{
    cout << endl;
    int m = Grid.size();
    int n = Grid[0].size();

    vector<vector<int>> dp(m,vector<int>(n,-1));


    dp[0][0] = Grid[0][0];   // Bottom UP , Assign the bottom index value

    // Now moves are Up and left since we are at bottom Up Approach

    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            int up,left;
            if(i>=1)
            {
                up = dp[i-1][j];
            }
            else
            {
                up= INT_MAX;
            }
            if(j>=1)
            {
                left = dp[i][j-1];
            }
            else
            {
               left =INT_MAX;
            }

            if(!(i==0 && j==0))
            {
                dp[i][j] = min(up,left)+Grid[i][j];
            }

        }
    }

    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout << setw(20) << dp[i][j] <<"\t";
        }
        cout << endl;
    }
    return dp[m-1][n-1];
}

void print_v(vector<int> v)
{
    for(auto d:v)
    {
        cout << d << "\t";
    }
    cout << endl;
}

int minSumInGrid_Space_Optimized(vector<vector<int>>& Grid)
{
    int m = Grid.size();
    int n = Grid[0].size();
    vector<int> Prev(n,INT_MAX);
    vector<int> Current(n);

    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==0 && j==0)
                Current[j] = Grid[i][j];
            else
            {
                int up = Prev[j]; // Previous Row Data UP Date

                int left = INT_MAX;

                if(j>=1)
                {
                    left = Current[j-1]; // Previous Column Data Left Data
                }

                Current[j] = min(up,left)+Grid[i][j];

            }
        }
        Prev = Current;
        print_v(Current);

    }


    return Prev[n-1];

}

int minSumInGrid_Recursion_Bottom_Up(int row,int col,vector<vector<int>> Grid)
{
    int m = Grid.size();
    int n = Grid[0].size();


    if(row==0 && col == 0) return Grid[row][col];

    if(row<0 || col <0) return INT_MAX;

    int left =  minSumInGrid_Recursion_Bottom_Up(row,col-1,Grid);

    int up =  minSumInGrid_Recursion_Bottom_Up(row-1,col,Grid);


    cout << "up=" << up << " left=" << left << endl;
    return min(left,up) + Grid[row][col];

}
int main()
{
    vector<vector<int>> Grid = { {5,9,6},{11,5,2} };
    //vector<vector<int>> Grid = { {10,8,2},{10,5,100}, {100,1,2} };
    int m = Grid.size();
    int n = Grid[0].size();
    vector<vector<int>> dp(m,vector<int>(n,-1));

    int min_path_Recursion = minSumInGrid(0,0,Grid);

    int min_path_Recursion_Bottom_Up = minSumInGrid_Recursion_Bottom_Up(m-1,n-1,Grid);

    int min_path_Memo = minSumInGrid_Memoization(0,0,Grid,dp);

    int min_path_Tab = minSumInGrid_Tabulation(Grid);

    int min_path_Tab_Bottom = minSumInGrid_Tabulation_Bottom(Grid);

    int min_path_Space_Optimized = minSumInGrid_Space_Optimized(Grid);

    cout << "Min Path in Grid Recursion=" << min_path_Recursion << endl;
    cout << "Min Path in Grid Recursion_Bottom Up =" << min_path_Recursion_Bottom_Up << endl;
    cout << "Min Path in Grid Memoization =" << min_path_Memo << endl;
    cout << "Min Path in Grid Tabulation =" << min_path_Tab << endl;

    cout << "Min Path in Grid Tabulation Bottom Up =" << min_path_Tab_Bottom << endl;

    cout << "Min Path in Grid Space Optimized =" << min_path_Space_Optimized << endl;

    return 0;
}
