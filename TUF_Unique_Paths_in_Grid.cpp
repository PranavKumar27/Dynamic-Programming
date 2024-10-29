#include <iostream>
#include <vector>

using namespace std;

void print_v(vector<int> v)
{
    for(auto d:v)
    {
        cout << d << ",";
    }
    cout << endl;
}

/// TC = 2^(m*n)
/// SC = O(path Length)
int uniqueGridPaths(int row,int col,vector<vector<int>> Grid)
{
    int rGrid = Grid.size();
    int cGrid = Grid[0].size();

    if(row == 0 && col == 0)
    {
        return 1;
    }
    if(row>=rGrid || col>=cGrid || row<0 || col<0)
    {
        return 0;
    }

    int up_path = uniqueGridPaths(row-1,col,Grid);
    int left_path = uniqueGridPaths(row,col-1,Grid);

    return up_path+left_path;
}


/// TC = (m*n)
/// SC = O(,m-1 + n-1) + O(n) for dp Array

int uniqueGridPaths_Memoization(int row,int col,vector<vector<int>> Grid,vector<vector<int>> dp)
{
    int rGrid = Grid.size();
    int cGrid = Grid[0].size();

    if(row == 0 && col == 0)
    {
        dp[row][col]=1;
        return 1;
    }
    if(row>=rGrid || col>=cGrid || row<0 || col<0)
    {
        return 0;
    }

    if(dp[row][col]!=-1)
    {
        return dp[row][col];
    }
    int up_path = uniqueGridPaths(row-1,col,Grid);
    int left_path = uniqueGridPaths(row,col-1,Grid);

    dp[row][col] = up_path+left_path;
    return dp[row][col];
}

/// O(m*n)
/// O(m*n)

int uniqueGridPaths_Tabulation(vector<vector<int>> Grid)
{
    int rGrid = Grid.size();
    int cGrid = Grid[0].size();

    vector<vector<int>> dp(rGrid,vector<int>(cGrid,-1));

    dp[0][0] = 1;

    for(int r=0;r<rGrid;r++)
    {
        for(int c=0;c<cGrid;c++)
        {
            if(r==0 && c==0) continue;
            int down_path=0;
            int right_path= 0;

            if(dp[r][c]!=-1)
                return dp[r][c];
            if(r>=1)
             down_path = dp[r-1][c];
            if(c>=1)
             right_path = dp[r][c-1];

             //cout << "down=" << down_path << " right=" << right_path << endl;

            dp[r][c] = down_path+right_path;
        }
    }

    for(int r=0;r<rGrid;r++)
    {
        for(int c=0;c<cGrid;c++)
        {
            cout << dp[r][c] << ",";
        }
        cout << endl;
    }


    return dp[rGrid-1][cGrid-1];
}

/// If there is a previous row and
/// previous column we can space optimize it


int uniqueGridPaths_SpaceOptimization(vector<vector<int>> Grid)
{
    int rGrid = Grid.size();
    int cGrid = Grid[0].size();

    vector<int> Prev(cGrid,0);

    //print_v(Prev);
    for(int r=0;r<rGrid;r++)
    {
        vector<int> Current(cGrid,0);
        for(int c=0;c<cGrid;c++)
        {
            if(r==0 && c==0)  ///Base Case No of ways once Node reaches 0,0 is 1 Always
            {
                Current[c] = 1;
                continue;
            }
            else
            {
                if(c>0)
                    Current[c] = Prev[c] + Current[c-1];  ///if col>1 then only we can move left of the current node Hence checked
                else
                    Current[c] = Prev[c];  ///If col = 0 , current node can only move row-1 and we have Prev data there so Use it Here
            }
        }
        Prev = Current;
        print_v(Prev);
    }

    //print_v(Prev);
    return Prev[cGrid-1];
}


int main()
{

    vector<vector<int>> Grid = { {1,1,1},{1,1,1},{1,1,1} };


    int uniquePaths = uniqueGridPaths(2,2,Grid);
    cout << "No of unique Paths from 0,0 to m,n =" << uniquePaths << endl;

    vector<vector<int>> dp(Grid.size(),vector<int>(Grid[0].size(),-1));
    int uniquePaths_Memoization = uniqueGridPaths_Memoization(2,2,Grid,dp);
    cout << "No of unique Paths from 0,0 to m,n Using Memoization =" << uniquePaths_Memoization << endl;

    int uniquePaths_Tabulation = uniqueGridPaths_Tabulation(Grid);
    cout << "No of unique Paths from 0,0 to m,n Using Tabulation =" << uniquePaths_Tabulation << endl;

    int uniquePaths_Space = uniqueGridPaths_SpaceOptimization(Grid);
    cout << "No of unique Paths from 0,0 to m,n Using Space =" << uniquePaths_Space << endl;

    return 0;
}
