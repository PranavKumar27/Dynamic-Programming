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

int minInsertions(string s1)
{
    int cnt_inserts = 0;
    int index1=0,index2=s1.size()-1;
    while(index1<index2)
    {
        if(s1[index1]==s1[index2])
        {
            index1 = index1+1;
            index2 = index2-1;
        }
        else
        {
            cnt_inserts++;
            index2 = index2-1;
        }
    }
    return cnt_inserts;
}

// find Length of LCS Longest Common Subsequence
int LCS(string s1,string s2)
{
    int m = s1.size(),n=s2.size();

    vector<vector<int>> dp(m+1,vector<int>(n+1,-1));
    // Fill First Row
    for(int index2=0;index2<n+1;index2++)
        dp[0][index2] = 0;

    for(int index1=0;index1<m+1;index1++)
        dp[index1][0]=0;

    for(int index1=1;index1<m+1;index1++)
    {
        for(int index2=1;index2<n+1;index2++)
        {
            if(s1[index1-1]==s2[index2-1])
            {
                dp[index1][index2] = 1 + dp[index1-1][index2-1];
            }
            else
            {
                dp[index1][index2] = max(dp[index1-1][index2],
                                         dp[index1][index2-1]);
            }
        }
    }

    print_2D_int_array(dp);
    return dp[m][n];
}

int main()
{
    string s = "abcd";
    int ans = minInsertions(s);
    cout << "Min Insertions to a Make Pallindrome = " << ans << endl;

    string s1 = s;
    reverse(s1.begin(),s1.end());
    int len_LCS = LCS(s,s1);

    ans = s.size()-len_LCS;
    cout << "Min Insertions to a Make Pallindrome Using LCS= " << ans << endl;
    return 0;
}
