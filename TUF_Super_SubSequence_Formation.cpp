#include <iostream>
#include <vector>
#include <algorithm>

// Super Subsequence : If we have two strings s1 and s2
// then super subsequence contains s1+s2-lcs
// eg: s1 = bleed s2 = blue
// super subsequence =
// lcs = ble
// blueed contains all characters which contains both words
// Total len of supperSubSequence = m + n - len(lcs)

using namespace std;

struct LCS
{
    string str;
    int len;
};


LCS findLCS(string s1,string s2)
{
    int m = s1.size(),n=s2.size();
    vector<vector<int>> dp(m+1,vector<int>(n+1,0));

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
                dp[index1][index2] = max( dp[index1-1][index2],
                                            dp[index1][index2-1] );
            }
        }
    }


    string s = "";
    int index1 = m,index2=n;

    while(index1>0 && index2>0)
    {
        if(s1[index1-1]==s2[index2-1])
        {
            s+=s1[index1-1];
            index1 = index1-1;
            index2 = index2-1;
        }
        else if(dp[index1-1][index2]>dp[index1][index2-1])
        {
            s+=s1[index1-1];
            index1 = index1-1;
        }
        else
        {
            s+=s2[index2-1];
            index2 = index2-1;
        }
    }

    while(index1>0)
    {
        s+=s1[index1-1];
        index1 = index1-1;
    }
    while(index2>0)
    {
        s+=s2[index2-1];
        index2 = index2-1;
    }

    reverse(s.begin(),s.end());

    LCS l;
    l.len = dp[m][n];
    l.str = s;
    return l;

}

int main()
{
    string s1 = "groot",s2 = "brute";
    int m = s1.size(),n = s2.size();
    LCS L = findLCS(s1,s2);
    cout << "len of lcs =" << L.len << endl;
    cout << "string lcs =" << L.str << endl;

    return 0;
}
