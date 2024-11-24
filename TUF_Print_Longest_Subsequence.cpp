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

int findLongestSubsequenceString(string s1,string s2)
{
    int m = s1.size(),n=s2.size();

    vector<vector<int>> dp(m+1,vector<int>(n+1,-1));

    /// fill the row 0
    for(int j=0;j<n+1;j++)
    {
        dp[0][j]=0;
    }

    /// fill the col 0
    for(int i=0;i<m+1;i++)
    {
        dp[i][0] = 0;
    }

    for(int index1=1;index1<m+1;index1++)
    {
        for(int index2=1;index2<n+1;index2++)
        {
            if(s1[index1-1]==s2[index2-1])
                dp[index1][index2] = 1 + dp[index1-1][index2-1];
            else
                dp[index1][index2] = max( dp[index1-1][index2],
                                          dp[index1][index2-1] );
        }
    }
    print_2D_int_array(dp);

    /// Find the Subsequence which is the longest

    // Length of the longest Subsequence
    // We need to trace how we reached this value
    // At the end of trace we will get the longest Subsequence
    string lcs = "";
    int index1 = m,index2=n;
    while(index1>0 && index2>0)
    {
        if(s1[index1-1]==s2[index2-1])
        {
            lcs+=s1[index1-1];
            // update the new indexs
            index1 = index1-1;
            index2 = index2-1;
        }
        else
        {
            // update the indexes
            if(dp[index1-1][index2]>dp[index1][index2-1])
            {
                index1 = index1-1;
            }
            else
            {
                index2 = index2-1;
            }
        }

    }

    reverse(lcs.begin(),lcs.end());

    cout << "Longest Subsequence = " << lcs << endl;
    return dp[m][n];
}



int main()
{
    string s1 = "adebc", s2="dcadba";
    int ans = findLongestSubsequenceString(s1,s2);
    cout << "Length of the LongestSubsequenceString =" << ans << endl;
    return 0;
}
