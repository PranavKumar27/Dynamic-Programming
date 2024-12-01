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

int countSubsequence(string s1,string s2)
{
    int m = s1.size(),n=s2.length();
    if(n==0)
    {
        // String s2 is exhausted and Matched with s1
        return 1;
    }

    if(m<n)
    {
        // String s1 is exhausted and no need to search s2 now
        //cout << " m<n " << " s1 =" << s1 << " s2=" << s2 << endl;
        return 0;
    }

    int not_take = 0;
    if(m>=1)
        not_take = countSubsequence(s1.substr(0,m-1),s2);

    int take = 0;
    if( m>=1 && n>=1 && s1[m-1]==s2[n-1])
    {
        take = countSubsequence(s1.substr(0,m-1),s2.substr(0,n-1));
    }

    return take+not_take;
}

int countSubsequence(string s1,string s2,int index1,int index2)
{
    //cout << "s1 =" << s1 << " s2=" << s2 << endl;

    if(index2<0)
    {
        //cout << " n== 0 " << " s1 =" << s1 << " s2=" << s2 << endl;
        return 1;
    }

    if(index1<0)
    {
        return 0;
    }

    int take=0,not_take =0;
    if( s1[index1]==s2[index2])
    {
        take = countSubsequence(s1,s2,index1-1,index2-1) + countSubsequence(s1,s2,index1-1,index2);
    }
    else
    {
        not_take = countSubsequence(s1,s2,index1-1,index2);
    }
    cout << "take=" << take << " not_take=" << not_take << endl;
    return take+not_take;
}

int countSubsequence(string s1,string s2,int index1,int index2,vector<vector<int>>& dp)
{
    if(index2<0)
    {
        return 1;
    }

    if(index1<0)
    {
        return 0;
    }

    if(dp[index1][index2]!=-1)
    {
        //cout << "Returned From DP" << endl;
        return dp[index1][index2];
    }

    if( s1[index1]==s2[index2])
    {
        return dp[index1][index2] = countSubsequence(s1,s2,index1-1,index2-1,dp) + countSubsequence(s1,s2,index1-1,index2,dp);
    }
    else
    {
        return dp[index1][index2] = countSubsequence(s1,s2,index1-1,index2,dp);
    }

}

int countSubsequence_Tab(string s1,string s2)
{
    int m = s1.size(),n=s2.length();
    vector<vector<int>> dp(m+1,vector<int>(n+1,-1));

    for(int index1=0;index1<m+1;index1++)
    {
        dp[index1][0] = 1;
    }

    for(int index2=1;index2<n+1;index2++)
    {
        dp[0][index2] = 0;
    }

    for(int index1=1;index1<m+1;index1++)
    {
        for(int index2=1;index2<n+1;index2++)
        {
            if( s1[index1-1]==s2[index2-1])
            {
                dp[index1][index2] = dp[index1-1][index2-1] + dp[index1-1][index2];
            }
            else
            {
                dp[index1][index2] = dp[index1-1][index2];
            }
        }
    }

    print_2D_int_array(dp);
    return dp[m][n];

}

int countSubsequence_Space_2D(string s1,string s2)
{
    int m = s1.size(),n=s2.length();
    vector<int> Prev(n+1,0);
    vector<int> Cur(n+1,0);

    Prev[0] = 1;
    Cur[0] = 1;

    for(int index1=1;index1<m+1;index1++)
    {
        for(int index2=1;index2<n+1;index2++)
        {
            if( s1[index1-1]==s2[index2-1])
            {
                Cur[index2] = Prev[index2-1] + Prev[index2];
            }
            else
            {
                Cur[index2] = Prev[index2];
            }
        }
        Prev = Cur;
    }

    print_1D_int_array(Prev);
    return Prev[n];

}

int countSubsequence_Space_1D(string s1,string s2)
{
    int m = s1.size(),n=s2.length();
    vector<int> Prev(n+1,0);

    Prev[0] = 1;

    for(int index1=1;index1<m+1;index1++)
    {
        for(int index2=n;index2>=0;index2--)
        {
            if( s1[index1-1]==s2[index2-1])
            {
                Prev[index2] = Prev[index2-1] + Prev[index2];
            }
            else
            {
                Prev[index2] = Prev[index2];
            }
        }
    }

    print_1D_int_array(Prev);
    return Prev[n];

}

int main()
{
    string s1 = "babgbag",s2="bag";
    int m = s1.size(),n=s2.length();
    int ans = countSubsequence(s1,s2,m-1,n-1);
    cout << "count of Subsequence Occurence Using Indexes = " << ans << endl;
    ans = countSubsequence(s1,s2);
    cout << "count of Subsequence Occurence Using String= " << ans << endl;

    vector<vector<int>> dp(m,vector<int>(n,-1));
    ans = countSubsequence(s1,s2,m-1,n-1,dp);
    cout << "count of Subsequence Occurences Using Memoization = " << ans << endl;

    ans = countSubsequence_Tab(s1,s2);
    cout << "count of Subsequence Occurences Using Tabulation = " << ans << endl;

    ans = countSubsequence_Space_2D(s1,s2);
    cout << "count of Subsequence Occurences Using Space 2D = " << ans << endl;

    ans = countSubsequence_Space_1D(s1,s2);
    cout << "count of Subsequence Occurences Using Space 1D = " << ans << endl;

    return 0;
}
