#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int findLongestSubString(string s1,string s2,int index1,int index2,int max_val)
{
    if(index1<1||index2<1)
    {
        return max_val;
    }

    int val;
    if(s1[index1-1]==s2[index2-1])
    {
        val = findLongestSubString(s1,s2,index1-1,index2-1,max_val+1);
    }
    else
    {
        val = findLongestSubString(s1,s2,index1-1,index2-1,0);
    }
    max_val = max(max_val,val);
    return max_val;

}

int findLongestSubString(string s1,string s2)
{
    int m = s1.size(),n=s2.size();
    vector<vector<int>> dp(m+1,vector<int>(n+1,0));

    // Row 0 and Col 0 we keep as 0 itself
    // So start iteration from row 1 and col 1

    int maxVal_In_dp = 0;
    int max_row =-1;
    int max_col=-1;
    for(int index1=1;index1<m+1;index1++)
    {
        for(int index2=1;index2<n+1;index2++)
        {
            if(s1[index1-1]==s2[index2-1])
            {
                dp[index1][index2] = 1 + dp[index1-1][index2-1];
                if(maxVal_In_dp<dp[index1][index2])
                {
                    max_row = index1;
                    max_col = index2;
                }
                maxVal_In_dp = max(maxVal_In_dp,dp[index1][index2]);
            }

            else
            {
                /// dp[index1][index2] stays 0;
            }
        }
    }

    //cout << "max_row=" << max_row << " max_col=" << max_col << endl;
    string subString = "";
    while(max_row>0 && max_col>0)
    {
        if(s1[max_row-1]==s2[max_col-1])
        {
            subString+=s1[max_row-1];
            max_row = max_row-1;
            max_col = max_col-1;
        }
    }

    reverse(subString.begin(),subString.end());
    cout << "Longest subString Value = " << subString << endl;

    return maxVal_In_dp;
}




int main()
{
    string s1 ="abcd",s2="abxd";
    int ans = findLongestSubString(s1,s2);
    cout << "Length of the Longest SubString = " << ans << endl;

    int m = s1.size(),n=s2.size();
    ans = findLongestSubString(s1,s2,m,n,0);
    cout << "Length of the Longest SubString Using Recursion= " << ans << endl;
    return 0;
}
