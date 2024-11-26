#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct LCS
{
    string str;
    int len;
};

LCS findLcs(string s1,string s2)
{
    int m = s1.size(),n = s2.size();

    vector<vector<int>> dp(m+1,vector<int>(n+1,0));

    for(int index1 = 1;index1<m+1;index1++)
    {
        for(int index2 = 1;index2<n+1;index2++)
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

    // Find LCS Here

    string s = "";
    int index1 = m,index2 = n;

    while(index1>0 && index2>0)
    {
        if(s1[index1-1]==s2[index2-1])
        {
            s+=s1[index1-1];
            index1 = index1-1;
            index2 = index2-1;
        }
        else if(dp[index1-1][index2]>dp[index1][index2-1])
            index1 = index1-1;
        else
            index2 = index2-1;

    }
    reverse(s.begin(),s.end());

    LCS L;
    L.len = dp[m][n];
    L.str = s;
    return L;
}


int main()
{
    string s1 = "abcd",s2 = "anc";
    int m = s1.size(),n = s2.size();
    LCS L = findLcs(s1,s2);
    cout << "len of lcs =" << L.len << endl;
    cout << "string lcs =" << L.str << endl;
    int len_lcs = L.len;
    int deletions = m-len_lcs;
    int insertions = n-len_lcs;
    int total = deletions + insertions;

    cout << "Total modifications delete/inserts to transform " << s1 << " <-into -> " << s2 << "  = " << total << endl;
    return 0;
}
