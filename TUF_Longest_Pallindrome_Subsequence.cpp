#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int longestSubsequencePallindrome(string s1)
{
    string s2 = s1;
    reverse(s2.begin(),s2.end());

    int m = s1.size(),n = s2.size();
    vector<vector<int>> dp(m+1,vector<int>(n+1,0));

    for(int index1=1;index1<m+1;index1++)
    {
        for(int index2=1;index2<n+1;index2++)
        {
            if(s1[index1-1]==s2[index2-1])
            {
                dp[index1][index2]= 1 + dp[index1-1][index2-1];
            }
            else
            {
                dp[index1][index2] = max (dp[index1-1][index2],
                                          dp[index1][index2-1]);
            }
        }
    }
    /// Find the subsequence Now

    string subsequence = "";
    int index1=m,index2=n;

    while(index1>0 && index2>0)
    {
        if(s1[index1-1]==s2[index2-1])
        {
            subsequence+=s1[index1-1];
            index1=index1-1;
            index2=index2-1;
        }
        else
        {
            if(dp[index1-1][index2]<dp[index1][index2-1])
            {
                index2 = index2-1;
            }
            else
            {
                index1 = index1-1;
            }
        }
    }

    reverse(subsequence.begin(),subsequence.end());

    cout << "Longest Pallindrome Subsequence = "  << subsequence << endl;

    return dp[m][n];
}
int main()
{
    string s1 = "bbabcbcab";
    int ans = longestSubsequencePallindrome(s1);
    cout << "Length of longest Subsequence which is Pallindrome =" << ans << endl;
    return 0;
}
