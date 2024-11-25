#include <iostream>
#include <vector>

using namespace std;

void print_1D_char_array(vector<char> v)
{
    cout << endl;
    int sz = v.size();
    for(int d = sz-1;d>=0;d--)
    {
        cout << v[d];
    }
    cout << "\n" << endl;
}

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

// Using Recursion
int findLongestSubsequence(string& s1,string& s2,int index1,int index2,vector<char> lcs,vector<char>& max_lcs)
{

    if(index1<0 || index2<0)
        return 0;

    if(s1[index1]==s2[index2])
    {
        lcs.push_back(s1[index1]);
        if(lcs.size()>max_lcs.size())
        {
            max_lcs = lcs;
        }
        return 1+findLongestSubsequence(s1,s2,index1-1,index2-1,lcs,max_lcs);
    }


    return 0+max( findLongestSubsequence(s1,s2,index1,index2-1,lcs,max_lcs),
                 findLongestSubsequence(s1,s2,index1-1,index2,lcs,max_lcs) );
}
//Using Memoization
int findLongestSubsequence_0Based_Index(string& s1,string& s2,int index1,
                            int index2,vector<char> lcs,vector<char>& max_lcs,vector<vector<int>>& dp)
{

    if(index1<0 || index2<0)
        return 0;

    if(dp[index1][index2]!=-1)
    {
        //cout << "Returned From dp f( " << index1 << " , " << index2 << " ) " << endl;
        return dp[index1][index2];
    }

    if(s1[index1]==s2[index2])
    {
        lcs.push_back(s1[index1]);
        if(lcs.size()>max_lcs.size())
        {
            max_lcs = lcs;
        }
        return dp[index1][index2] = 1+findLongestSubsequence_0Based_Index(s1,s2,index1-1,index2-1,lcs,max_lcs,dp);
    }


    return dp[index1][index2] = 0+max( findLongestSubsequence_0Based_Index(s1,s2,index1,index2-1,lcs,max_lcs,dp),
                                        findLongestSubsequence_0Based_Index(s1,s2,index1-1,index2,lcs,max_lcs,dp) );
}

//Using Memoization By Shifting index to right by 1,
/// 1 Based Index
int findLongestSubsequence_1Based_Index(string& s1,string& s2,int index1,
                            int index2,vector<char> lcs,vector<char>& max_lcs,vector<vector<int>>& dp)
{

    if(index1==0 || index2==0)
        return 0;

    if(dp[index1][index2]!=-1)
    {
        //cout << "Returned From dp f( " << index1 << " , " << index2 << " ) " << endl;
        return dp[index1][index2];
    }

    if(s1[index1-1]==s2[index2-1])
    {
        lcs.push_back(s1[index1-1]);
        if(lcs.size()>max_lcs.size())
        {
            max_lcs = lcs;
        }
        return dp[index1][index2] = 1+findLongestSubsequence_1Based_Index(s1,s2,index1-1,index2-1,lcs,max_lcs,dp);
    }


    return dp[index1][index2] = 0+max( findLongestSubsequence_1Based_Index(s1,s2,index1,index2-1,lcs,max_lcs,dp),
                                        findLongestSubsequence_1Based_Index(s1,s2,index1-1,index2,lcs,max_lcs,dp) );
}
// Using Tabulation
/// 0 Based Index
int findLongestSubsequence_0Based_Index(string& s1,string& s2,vector<char> max_lcs)
{
    int n1 = s1.size(),n2 = s2.size();
    vector<vector<int>> dp(n1,vector<int>(n2,0));

    for(int index=0;index<n2;index++)
    {
        if(s1[0]==s2[index])
        {
            dp[0][index] = 1;
        }
    }

    for(int index1 = 1;index1<n1;index1++)
    {
        for(int index2=0;index2<n2;index2++)
        {
            if(index2>0) // index 1 is Always > 0
            {
                if(s1[index1]==s2[index2])
                {
                    dp[index1][index2] = 1+dp[index1-1][index2-1];
                }
                else
                {
                    dp[index1][index2] = max( dp[index1][index2-1],dp[index1-1][index2] );
                }
            }
            else
            {
                if(s1[index1]==s2[index2])
                {
                    dp[index1][index2] = 1;
                }
                else
                {
                    dp[index1][index2] = dp[index1-1][index2];
                }
            }
        }
    }

    print_2D_int_array(dp);
    return dp[n1-1][n2-1];

}


// Using Tabulation
/// 1 Based Index
int findLongestSubsequence_1Based_Index(string& s1,string& s2,vector<char> max_lcs)
{
    int n1 = s1.size(),n2 = s2.size();
    vector<vector<int>> dp(n1+1,vector<int>(n2+1,0));

    for(int index1 =0 ;index1<n1+1;index1++)
    {
        dp[index1][0] = 0; // col 0
    }

    for(int index2 =0 ;index2<n2+1;index2++)
    {
        dp[0][index2] = 0; // row 0
    }

    for(int index1=1;index1<n1+1;index1++)
    {
        for(int index2=1;index2<n2+1;index2++)
        {
            // index1 and index2 is Always > 0

            if(s1[index1-1]==s2[index2-1])
            {
                dp[index1][index2] = 1+dp[index1-1][index2-1];
            }
            else
            {
                dp[index1][index2] = max( dp[index1][index2-1],dp[index1-1][index2] );
            }
        }
    }

    print_2D_int_array(dp);
    return dp[n1][n2];

}


// Using Space Optimization
int findLongestSubsequence_0Based_Index_Space(string& s1,string& s2,vector<char> max_lcs)
{
    int n1 = s1.size(),n2 = s2.size();
    //vector<vector<int>> dp(n1,vector<int>(n2,0));

    vector<int> Prev(n2,0);
    vector<int> Curr(n2,0);

    for(int index=0;index<n2;index++)
    {
        if(s1[0]==s2[index])
        {
            Prev[index] = 1;
        }
    }

    for(int index1 = 1;index1<n1;index1++)
    {
        for(int index2=0;index2<n2;index2++)
        {
            if(index2>0) // index 1 is Always > 0
            {
                if(s1[index1]==s2[index2])
                {
                    Curr[index2] = 1+Prev[index2-1];
                }
                else
                {
                    Curr[index2] = max( Curr[index2-1],Prev[index2] );
                }
            }
            else
            {
                if(s1[index1]==s2[index2])
                {
                    Curr[index2] = 1;
                }
                else
                {
                    Curr[index2] = Prev[index2];
                }
            }
        }
        Prev = Curr;
    }

    print_1D_int_array(Prev);
    return Prev[n2-1];

}
/// 1 Based Index Space
int findLongestSubsequence_1Based_Index_Space(string& s1,string& s2,vector<char> max_lcs)
{
    int n1 = s1.size(),n2 = s2.size();
    //vector<vector<int>> dp(n1+1,vector<int>(n2+1,0));

    vector<int> Prev(n2+1,0);
    vector<int> Curr(n2+1,0);

    for(int index2 =0 ;index2<n2+1;index2++)
    {
        Prev[index2] = 0; // row 0
    }

    for(int index1=1;index1<n1+1;index1++)
    {
        for(int index2=1;index2<n2+1;index2++)
        {
            // index1 and index2 is Always > 0

            if(s1[index1-1]==s2[index2-1])
            {
                Curr[index2] = 1+Prev[index2-1];
            }
            else
            {
                Curr[index2] = max( Curr[index2-1],Prev[index2] );
            }
        }
        Prev = Curr;
    }

    print_1D_int_array(Prev);
    return Prev[n2];

}

int main()
{
    string s1 = "adebc",s2 = "dcadb";
    int n1 = s1.size(),n2 = s2.size();
    vector<char> max_lcs = {};
    int ans = findLongestSubsequence(s1,s2,n1-1,n2-1,{},max_lcs);
    cout << "findLongestSubsequence Using Recursion =" << ans << endl;
    print_1D_char_array(max_lcs);
    cout << "--------------------------\n"<< endl;


    vector<vector<int>> dp(n1,vector<int>(n2,-1));
    ans = findLongestSubsequence_0Based_Index(s1,s2,n1-1,n2-1,{},max_lcs,dp);
    cout << "findLongestSubsequence 0Based_Index Using dp=" << ans << endl;
    print_1D_char_array(max_lcs);
    cout << "--------------------------\n"<< endl;


    ans = findLongestSubsequence_0Based_Index(s1,s2,max_lcs);
    cout << "findLongestSubsequence 0Based_Index Using Tabu=" << ans << endl;
    cout << "--------------------------\n"<< endl;

    ans = findLongestSubsequence_0Based_Index_Space(s1,s2,max_lcs);
    cout << "findLongestSubsequence 0Based_Index Using Space=" << ans << endl;
    cout << "--------------------------\n"<< endl;


    vector<vector<int>> dp1(n1+1,vector<int>(n2+1,-1));
    ans = findLongestSubsequence_1Based_Index(s1,s2,n1,n2,{},max_lcs,dp1);
    cout << "findLongestSubsequence 1Based_Index Using dp=" << ans << endl;
    print_1D_char_array(max_lcs);
    cout << "--------------------------\n"<< endl;


    ans = findLongestSubsequence_1Based_Index(s1,s2,max_lcs);
    cout << "findLongestSubsequence 1Based_Index Using Tabu=" << ans << endl;
    cout << "--------------------------\n"<< endl;

    ans = findLongestSubsequence_1Based_Index_Space(s1,s2,max_lcs);
    cout << "findLongestSubsequence 1Based_IndexUsing Space=" << ans << endl;
    cout << "--------------------------\n"<< endl;

    return 0;
}
