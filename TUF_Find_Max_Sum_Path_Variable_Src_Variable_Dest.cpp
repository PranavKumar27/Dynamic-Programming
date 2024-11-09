#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;
#define MIN INT_MIN


void print_v(vector<int> v)
{
    for(auto d:v)
    {
        cout << d << "\t";
    }
    cout << endl;
}


int find_Max_Paths_Sum(int row,int col,vector<vector<int>> Grid)
{
    int m = Grid.size();
    int n = Grid[0].size();


    if(row==0 && col>=0 && col<n)
        return Grid[row][col];

    if(row<0 || col<0 || row>=m || col>=n)
        return MIN;

    int up = find_Max_Paths_Sum(row-1,col,Grid);

    int up_left = find_Max_Paths_Sum(row-1,col-1,Grid);

    int up_right = find_Max_Paths_Sum(row-1,col+1,Grid);

    //cout << "up =" << up  << " up_left =" << up_left << " up_right =" << up_right << endl;
    //return (up>up_left)?(up>up_right)?up+Grid[row][col]:up_right+Grid[row][col]:(up_left>up_right)?up_left+Grid[row][col]:up_right+Grid[row][col];

    return max(up,max(up_left,up_right))+Grid[row][col];
}


int find_Max_Paths_Sum_Memoization(int row,int col,vector<vector<int>> Grid,vector<vector<int>>& dp)
{
    int m = Grid.size();
    int n = Grid[0].size();


    if(row==0 && col>=0 && col<n)
        return Grid[row][col];

    if(row<0 || col<0 || row>=m || col>=n)
        return MIN;

    if(dp[row][col]!=-1)
    {
        //cout << "Found in dp" << endl;
        return dp[row][col];
    }

    int up = find_Max_Paths_Sum_Memoization(row-1,col,Grid,dp);

    int up_left = find_Max_Paths_Sum_Memoization(row-1,col-1,Grid,dp);

    int up_right = find_Max_Paths_Sum_Memoization(row-1,col+1,Grid,dp);

    //cout << "up =" << up  << " up_left =" << up_left << " up_right =" << up_right << endl;
    //return (up>up_left)?(up>up_right)?up+Grid[row][col]:up_right+Grid[row][col]:(up_left>up_right)?up_left+Grid[row][col]:up_right+Grid[row][col];

    return dp[row][col] = max(up,max(up_left,up_right))+Grid[row][col];
}


int find_Max_Paths_Sum_Tabulation(vector<vector<int>> Grid)
{
    int m = Grid.size();
    int n = Grid[0].size();

    vector<vector<int>> dp(m,vector<int>(n,-1));


    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==0)
            {
                dp[i][j] = Grid[i][j];
            }
            else
            {
                int up,up_left,up_right;

                if(i>=1)
                 up = dp[i-1][j];
                else
                    up=MIN;
                if(i>=1&&j>=1)
                 up_left = dp[i-1][j-1];
                else
                    up_left = MIN;
                if(i>=1 && j+1<n)
                 up_right = dp[i-1][j+1];
                else
                    up_right = MIN;

                dp[i][j]=max(up,max(up_left,up_right))+Grid[i][j];
            }
        }
    }

    print_v(dp[m-1]);
    // Find Max in a vector dp[m-1] Last row
    int ans = *std::max_element(dp[m-1].begin(),dp[m-1].end());
    return ans;
}


int find_Max_Paths_Sum_Space_Optimized(vector<vector<int>> Grid)
{
    int m = Grid.size();
    int n = Grid[0].size();

    vector<int> Prev(n,MIN);
    vector<int> Current(n);

    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==0)
            {
                Current[j] = Grid[i][j];
            }
            else
            {
                int up,up_left,up_right;

                up = Prev[j];

                if(j>=1)
                    up_left = Prev[j-1];
                else
                    up_left = MIN;

                if(j+1<n)
                    up_right = Prev[j+1];
                else
                    up_right = MIN;


                Current[j]=max(up,max(up_left,up_right))+Grid[i][j];
            }
        }
        Prev = Current;
    }

    print_v(Prev);
    // Find Max in a vector Prev Last row
    int ans = *std::max_element(Prev.begin(),Prev.end());
    return ans;
}


int main()
{
    vector<vector<int>> Grid = { {1,2,10,4},{100,3,2,1},{1,1,20,20},{1,2,2,1} };

    int m = Grid.size();
    int n = Grid[0].size();

    vector<vector<int>> dp(m,vector<int>(n,-1));

    int maxj = INT_MIN;
    for(int j=0;j<n;j++)
    {
        int ans_Using_Recur = find_Max_Paths_Sum(m-1,j,Grid);
        cout << "ans_Using_Recur =" << ans_Using_Recur << endl;
        maxj = max(ans_Using_Recur,maxj);
    }
    cout << "Max Sum Path Using Recursion=" << maxj << endl;

    maxj = INT_MIN;
    for(int j=0;j<n;j++)
    {
        int ans_Using_Memo = find_Max_Paths_Sum_Memoization(m-1,j,Grid,dp);
        cout << "ans_Using_Memo =" << ans_Using_Memo << endl;
        maxj = max(ans_Using_Memo,maxj);
    }
    cout << "Max Sum Path Using Memoization=" << maxj << endl;

    int ans_Using_Tab = find_Max_Paths_Sum_Tabulation(Grid);

    cout << "Max Sum Path Using Tabulation =" << ans_Using_Tab << endl;

    int ans_Using_Space_Optimized = find_Max_Paths_Sum_Space_Optimized(Grid);

    cout << "Max Sum Path Using Space Optimized =" << ans_Using_Space_Optimized << endl;

    return 0;
}

