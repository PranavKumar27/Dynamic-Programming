#include <iostream>
#include <vector>
#include <algorithm>

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

bool IsSame(string s1,string s2,int i,int j)
{
    if(j<0 && i>=0)
    {
        for(int idx=i;idx>=0;idx--)
        {
            if(s1[idx]!='*')
                return false;
        }
        return true;
    }
    if(i<0 && j<0)
    {
        return true;
    }
    if(i<0 && j>=0)
        return false;

    if(s1[i]==s2[j]||s1[i]=='?')
    {
        return IsSame(s1,s2,i-1,j-1);
    }
    else
    {
        if(s1[i]=='*')
        {
            return IsSame(s1,s2,i-1,j) || IsSame(s1,s2,i,j-1);
            // IsSame(s1,s2,i-1,j) means * has empty char of s2
            // IsSame(s1,s2,i,j-1) means * has 1 char i.e. s2[j]
        }
        else
        {
            return false;
        }
    }
}

bool IsSame(string s1,string s2,int i,int j,vector<vector<int>>& dp)
{
    cout << "s1=" << s1 << " s2=" << s2 << " i=" << i << " j=" << j << endl;
    if(j==0 && i>=1)
    {
        for(int idx=i;idx>=1;idx--)
        {
            if(s1[idx-1]!='*')
                return 0;
        }
        return 1;
    }
    if(i==0 && j==0)
    {
        return 1;
    }
    if(i==0 && j>=1)
        return  0;


    if(dp[i][j]!=-1)
    {
        cout << "Returning From dp =" << " i=" << i << " j=" << j << endl;
        return dp[i][j];
    }

    if(s1[i-1]==s2[j-1]||s1[i-1]=='?')
    {
        cout << "Calling =" << " i=" << i << " j=" << j << endl;
        return dp[i][j] = IsSame(s1,s2,i-1,j-1,dp);
    }
    else
    {
        if(s1[i-1]=='*')
        {
            return dp[i][j] = IsSame(s1,s2,i-1,j,dp) || IsSame(s1,s2,i,j-1,dp);
            // IsSame(s1,s2,i-1,j) means * has empty char of s2
            // IsSame(s1,s2,i,j-1) means * has 1 char i.e. s2[j]
        }
        else
        {
            return dp[i][j] = 0;
        }
    }
}

int IsSame(string s1,string s2)
{
    int m = s1.size(),n=s2.size();
    vector<vector<int>> dp(m+1,vector<int>(n+1,-1));

    for(int i=1;i<m+1;i++)
    {
        int fl = 1;
        for(int ii=1;ii<=i;ii++)
        {
            if(s1[ii-1]=='*')
                continue;
            else
            {
                fl = 0;
                break;
            }
        }
        dp[i][0] = fl; // Since we i starting from 1 It means we need to make changes for Cur in Space Optimization
    }

    dp[0][0] = 1;

    for(int j=1;j<n+1;j++)
    {
        dp[0][j]=0;
    }

    for(int i=1;i<m+1;i++)
    {
        for(int j=1;j<n+1;j++)
        {
            if(s1[i-1]==s2[j-1]||s1[i-1]=='?')
            {
                dp[i][j] = dp[i-1][j-1];
            }
            else
            {
                if(s1[i-1]=='*')
                {
                    dp[i][j] = dp[i-1][j] || dp[i][j-1];
                    // IsSame(s1,s2,i-1,j) means * has empty char of s2
                    // IsSame(s1,s2,i,j-1) means * has 1 char i.e. s2[j]
                }
                else
                {
                    dp[i][j] = 0;
                }
            }
        }
    }

    print_2D_int_array(dp);
    return dp[m][n];

}


int IsSame_Space(string s1,string s2)
{
    int m = s1.size(),n=s2.size();
    vector<int> Prev(n+1,0);
    vector<int> Cur(n+1,0);

    Prev[0]=1;

    for(int j=1;j<n+1;j++)
    {
        Prev[j]=0;
    }

    for(int i=1;i<m+1;i++)
    {
        // Runs for every Cur and update 0th col
        int fl = 1;
        for(int ii=1;ii<=i;ii++)
        {
            if(s1[ii-1]=='*')
                continue;
            else
            {
                fl = 0;
                break;
            }
        }
        Cur[0] = fl;

        for(int j=1;j<n+1;j++)
        {
            if(s1[i-1]==s2[j-1]||s1[i-1]=='?')
            {
                Cur[j] = Prev[j-1];
            }
            else if(s1[i-1]=='*')
            {
                Cur[j] = Prev[j] || Cur[j-1];
            }
            else
            {
                Cur[j] = 0;
            }
        }
        Prev = Cur;
    }

    print_1D_int_array(Prev);
    return Prev[n];

}
int main()
{
    string s1 = "**d?f*",s2="abcdef";
    int m = s1.size(),n=s2.size();
    bool ans1 = IsSame(s1,s2,m-1,n-1);
    cout << "Using Recursion Are s1=" << s1 << " s2=" << s2 << " Are Same =" << ans1 << endl;

    vector<vector<int>> dp(m+1,vector<int>(n+1,-1));
    int ans = IsSame(s1,s2,m,n,dp);
    cout << "Using Memoization Are s1=" << s1 << " s2=" << s2 << " Are Same =" << ans << endl;

    ans = IsSame(s1,s2);
    cout << "Using Tabulation Are s1=" << s1 << " s2=" << s2 << " Are Same =" << ans << endl;

    ans = IsSame_Space(s1,s2);
    cout << "Using Space Optimization Are s1=" << s1 << " s2=" << s2 << " Are Same =" << ans << endl;

    return 0;
}
