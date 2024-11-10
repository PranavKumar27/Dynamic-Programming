#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void print_3D_v(vector<vector<vector<int>>> dp)
{
    int m = dp.size();
    int n= dp[0].size();

    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            for(int k=0;k<n;k++)
            {
                cout << dp[i][j][k] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl;
}

void print_2D_v(vector<vector<int>> dp)
{
    int m = dp.size();
    int n= dp[0].size();

    for(int i=0;i<m;i++)
    {

        for(int k=0;k<n;k++)
        {
            cout << dp[i][k] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

int max_Cherrt_Picked(int i,int j1,int j2,vector<vector<int>> Grid)
{
    int m = Grid.size();
    int n = Grid[0].size();

    if(j1<0 || j1>=n || j2<0 || j2>=n)
    {
        return -1e8;
    }
    if(i==m-1)
    {
        if(j1==j2)
        {
            return Grid[i][j1];
        }
        else
        {
            return Grid[i][j1]+Grid[i][j2];
        }
    }


    vector<int> delJ{-1,0,1};
    int maxi = -1e9;
    for(int J1=0;J1<delJ.size();J1++)
    {
       for(int J2=0;J2<delJ.size();J2++)
        {
            int updated_J1 = j1+delJ[J1];
            int updated_J2 = j2+delJ[J2];
            //cout << "updated_J1=" << updated_J1 << " updated_J2=" << updated_J2 << endl;

            if(updated_J1>=0 && updated_J1<n && updated_J2>=0 && updated_J2<n)
            {
                //cout << "J1 J2 Valid" << endl;
                 if(updated_J1 == updated_J2)
                {
                    //cout << "Same J1 and J2 updated_J1=" << updated_J1 << " updated_J2=" << updated_J2 << endl;
                    maxi = max(maxi,Grid[i][j1]+max_Cherrt_Picked(i+1,updated_J1,updated_J2,Grid));
                }
                else
                {
                    maxi= max(maxi,Grid[i][j1] + Grid[i][j2] + max_Cherrt_Picked(i+1,updated_J1,updated_J2,Grid));
                }
            }
            else
            {
                continue;
            }

        }
    }
    return maxi;
}


int max_Cherrt_Picked_Memoization(int i,int j1,int j2,vector<vector<int>> Grid,vector<vector<vector<int>>>& dp)
{
    int m = Grid.size();
    int n = Grid[0].size();

    if(j1<0 || j1>=n || j2<0 || j2>=n)
    {
        return -1e9;
    }
    if(i==m-1)
    {
        if(j1==j2)
        {
            return dp[i][j1][j2] = Grid[i][j1];
        }
        else
        {
            return dp[i][j1][j2] = Grid[i][j1]+Grid[i][j2];
        }
    }


    if(dp[i][j1][j2]!=-1)
    {
        cout << "Value Found in dp Array" << endl;
        return dp[i][j1][j2];
    }

    cout << "Value in dp Array =" << dp[i][j1][j2] << endl;

    int maxi = -1e9;
    vector<int> delJ = {-1,0,1};

    for(int J1=0;J1<delJ.size();J1++)
    {
        for(int J2=0;J2<delJ.size();J2++)
        {
            int updated_J1 = j1+delJ[J1];
            int updated_J2 = j2+delJ[J2];

            if(updated_J1>=0 && updated_J1<n && updated_J2>=0 && updated_J2<n)
            {
                if(updated_J1==updated_J2)
                {
                    maxi = max(maxi,Grid[i][j1]+max_Cherrt_Picked_Memoization(i+1,updated_J1,updated_J2,Grid,dp));
                }
                else
                {
                    maxi = max(maxi,Grid[i][j1]+Grid[i][j2]+max_Cherrt_Picked_Memoization(i+1,updated_J1,updated_J2,Grid,dp));
                }
            }
            else
            {
                continue;
            }
        }
    }
    dp[i][j1][j2] = maxi;
    cout << "Value Updated in dp Array =" << dp[i][j1][j2] << endl;
    return dp[i][j1][j2];
    //return maxi;
}


int max_Cherry_Picked_Tabulation(vector<vector<int>> Grid)
{
    int m = Grid.size();
    int n = Grid[0].size();

    vector<vector<vector<int>>> dp(m,vector<vector<int>>(n,vector<int>(n,-1)));

    for(int j1=0;j1<n;j1++)
    {
        for(int j2=0;j2<n;j2++)
        {
            if(j1==j2)
            {
                dp[m-1][j1][j2] = Grid[m-1][j1];
            }
            else
            {
                dp[m-1][j1][j2] = Grid[m-1][j1] + Grid[m-1][j2];
            }
        }
    }

    vector<int> delJ = {-1,0,1};

    for(int i=m-2;i>=0;i--)
    {
        for(int j1=0;j1<n;j1++)
        {
            for(int j2=0;j2<n;j2++)
            {
               int maxi = -1e9;

               for(int J1=-1;J1<=1;J1++)
                {
                    for(int J2=-1;J2<=1;J2++)
                    {
                        int value = 0;
                        if(j1==j2)
                        {
                            value+=Grid[i][j1];
                        }
                        else
                        {
                            value+=Grid[i][j1]+Grid[i][j2];
                        }

                        int updated_J1 = j1+J1;
                        int updated_J2 = j2+J2;

                        if(updated_J1>=0 && updated_J1<n && updated_J2>=0 && updated_J2<n)
                        {
                            value+=dp[i+1][updated_J1][updated_J2];
                        }
                        else
                        {
                            value=-1e9;
                        }

                        maxi = max(maxi,value);
                    }
                }
                dp[i][j1][j2] = maxi;
            }
        }
    }
    print_3D_v(dp);
    return dp[0][0][m-1];
}

int max_Cherry_Picked_Space_Optimized(vector<vector<int>> Grid)
{
    int m = Grid.size();
    int n = Grid[0].size();

    vector<vector<vector<int>>> dp(m,vector<vector<int>>(n,vector<int>(n,-1)));

    vector<vector<int>> Prev(n,vector<int>(n,-1));

    vector<vector<int>> Current(n,vector<int>(n,-1));

    for(int j1=0;j1<n;j1++)
    {
        for(int j2=0;j2<n;j2++)
        {
            if(j1==j2)
            {
                Prev[j1][j2] = Grid[m-1][j1];
            }
            else
            {
                Prev[j1][j2] = Grid[m-1][j1] + Grid[m-1][j2];
            }
        }
    }

    vector<int> delJ = {-1,0,1};

    for(int i=m-2;i>=0;i--)
    {
        for(int j1=0;j1<n;j1++)
        {
            for(int j2=0;j2<n;j2++)
            {
               int maxi = -1e9;

               for(int J1=-1;J1<=1;J1++)
                {
                    for(int J2=-1;J2<=1;J2++)
                    {
                        int value = 0;
                        if(j1==j2)
                        {
                            value+=Grid[i][j1];
                        }
                        else
                        {
                            value+=Grid[i][j1]+Grid[i][j2];
                        }

                        int updated_J1 = j1+J1;
                        int updated_J2 = j2+J2;

                        if(updated_J1>=0 && updated_J1<n && updated_J2>=0 && updated_J2<n)
                        {
                            value+=Prev[updated_J1][updated_J2];
                        }
                        else
                        {
                            value=-1e9;
                        }

                        maxi = max(maxi,value);
                    }
                }
                Current[j1][j2] = maxi;
            }
        }
        Prev = Current;
    }
    print_2D_v(Prev);
    return Prev[0][m-1];
}

int main()
{
    vector<vector<int>> Grid = { {2,3,1,2},{3,4,2,2},{5,6,3,5} };
    int m = Grid.size();
    int n =  Grid[0].size();

    int ans = max_Cherrt_Picked(0,0,n-1,Grid);

    cout << "Max Cheery Picked Using Recursion=" << ans << endl;


    vector<vector<vector<int>>> dp(m,vector<vector<int>>(n,vector<int>(n,-1)));

    
    
    int ans_Memo = max_Cherrt_Picked_Memoization(0,0,n-1,Grid,dp);

    cout << "Max Cheery Picked Using Memoization=" << ans_Memo << endl;

    
    
    int ans_Tabu = max_Cherry_Picked_Tabulation(Grid);

    cout << "Max Cheery Picked Using Tabulation=" << ans_Tabu << endl;



    int ans_Space_Optimized = max_Cherry_Picked_Space_Optimized(Grid);

    cout << "Max Cheery Picked Using Space Optimized=" << ans_Space_Optimized << endl;



    return 0;
}
