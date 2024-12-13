#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Longest String Chain : Two string s1 and s2 are said to be in chain if all characters
of s1 are present in s2  and the difference in size of s1 and s2 is 1. For ex:
s1 = a , s2 = ab , There exists a chain
s1 = ac, s2 = abc, there exists a chain
s1= abd s2 = bcde , only b and d from s2 exists in s2, 'a' is not present
s1= a s2 = abc , s1 is present but s2.size()-s1.size()!=1 Hence Not a Chain

if Arr[] = {"bcda",ab","a","bca","b","bad"}
Sort Arr in increasing size
Arr[]= {"a","b","ab","bad","bca","bcda"}

Create dp[] and Hash[]
dp is for storing Number of chain that can be formed
dp[4] = 3 means with including string from 0 to 4, we can form a chain of 4 strings

dp[i] = 1 for all since each string is a chain in itself

Run a loop from i = 1 to n
at index = 1 , s1, prev_idx = 0, s2
compare (s2,s1) && s1.size() - s2.size() == 1
compare ("b","a") -- > False

at index = 2 , s1 = "ab", prev_idx = 1/0, s2 = "b"
compare (s2,s1) && s1.size() - s2.size() == 1
compare ("ab","b") && s1.size() - s2.size() == 1  -- > True
if(dp[i] < 1 + dp[prev] )
    dp[i] = 1 + dp[prev]
Hence dp[2] = 2
Hash[2] = 1 // Prev_idx

at index = 3 , s1 = "bad", prev_idx = 2/1/0, s2 = "ab"
compare (s2,s1) && s1.size() - s2.size() == 1
compare ("bad","qb") && s1.size() - s2.size() == 1  -- > True
if(dp[i] < 1 + dp[prev] )
    dp[i] = 1 + dp[prev]
Hence dp[3] = 3
Hash[3] = 2 // Prev_idx

at index = 4 , s1 = "bca", prev_idx = 3, s2 = "bad"
compare (s2,s1) && s1.size() - s2.size() == 1
compare ("bca","bad") && s1.size() - s2.size() == 1  -- > False
if(dp[i] < 1 + dp[prev] ) // False
    dp[i] = 1 + dp[prev]


at index = 4 , s1 = "bca", prev_idx = 2/1/0, s2 = "ab"
compare (s2,s1) && s1.size() - s2.size() == 1
compare ("bca","ab") && s1.size() - s2.size() == 1  -- > False
if(dp[i] < 1 + dp[prev] ) // False
    dp[i] = 1 + dp[prev]
Hence dp[3] = 1 + 2 = 3
STore Hash[3] = 4 // Prev_idx

at index = 5 , s1 = "bcda", prev_idx = 4/3/2/1, s2 = "bca"
compare (s2,s1) && s1.size() - s2.size() == 1
compare ("bcda","bca") && s1.size() - s2.size() == 1  -- > False
if(dp[i] < 1 + dp[prev] ) // False
    dp[i] = 1 + dp[prev]
Hence dp[4] = 1 + 3 = 4
Hash[5] = 4 // Prev_idx


*/
void print_1D_Str(vector<string>& S)
{
    for(auto d:S)
        cout << d << " ";
    cout << endl;
}

bool IsChained(string& s1,string& s2)  // Work if string is s1 = "bcda" & s2 = "bad" s1 and s2 are Not subsequence
{
    // Assumption s2 Len <= s1 len since sorted

    if(s1.size()-s2.size() != 1)
        return false;

    int n = s2.size();
    for(int i=0;i<n;i++)
    {
        char ch = s2[i];
        auto itr = find(s1.begin(),s1.end(),ch);

        if(itr==s2.end())
            return false;
    }
    return true;
}

bool IsPossible(string& s1,string& s2) // Work if string is s1 = "bcda" & s2 = "bda" , s1 and s2 are subsequence
{
    // Assumption s2 Len <= s1 len since sorted

    if(s1.size()-s2.size() != 1)
        return false;

    int n1 = s1.size(),n2 = s2.size();
    int index1=0,index2=0;
    while(index1<n1 && index2<n2)
    {
        if(s1[index1]==s2[index2])
        {
            index1++,index2++;
        }
        else
        {
            index1++;
        }
    }

    if(index1<=n1 && index2==n2)
        return true;
    else
        return false;
}

bool cmp(string& a,string& b)
{
    return (a.size()<b.size());
}

// TC --> O(N*N) in For loop + O(NLogN) in Sorting + 2*O(N) in Chain Check,Hash for loop
// SC --> 2*O(N)

vector<string> maxLenChain(vector<string>& ArrList, bool IsSubsequence)
{
    int n = ArrList.size();
    sort(ArrList.begin(),ArrList.end(),cmp);
    print_1D_Str(ArrList);
    vector<int> dp(n,1);
    vector<int> Hash(n);
    for(int i=0;i<n;i++)
        Hash[i]=i;

    int max_len=-1,max_idx=-1;
    for(int index = 1;index<n;index++)
    {
        for(int prev_idx = index-1;prev_idx>=0;prev_idx--)
        {
            bool Chain_Exists = false;
            if(IsSubsequence)
                Chain_Exists = IsPossible(ArrList[index],ArrList[prev_idx]);
            else
                Chain_Exists = IsChained(ArrList[index],ArrList[prev_idx]);


            if(Chain_Exists && dp[index]<1+dp[prev_idx])
            {
                dp[index] = 1 + dp[prev_idx];
                Hash[index] = prev_idx;
            }
        }
        if(max_len<dp[index])
        {
            max_len = dp[index];
            max_idx = index;
        }
    }

    cout << "Max len of chain = " << max_len << endl;

    vector<string> Chain;
    int index = max_idx;
    Chain.push_back(ArrList[index]);


    while(Hash[index]!=index)
    {
        index = Hash[index];
        Chain.push_back(ArrList[index]);
    }
    reverse(Chain.begin(),Chain.end());
    print_1D_Str(Chain);
    return Chain;


}

int main()
{
    vector<string> ArrList = {"bcda","ba","a","b","bca","bda"};
    bool IsSubsequence = true;
    vector<string> Chain = maxLenChain(ArrList,IsSubsequence);
    cout << "Max Len Chain =" << endl;
    print_1D_Str(Chain);

    vector<string> ArrList1 = {"bcda","ba","a","b","abc","bad"};
    IsSubsequence = false;
    vector<string> Chain1 = maxLenChain(ArrList1,IsSubsequence);
    cout << "Max Len Chain =" << endl;
    print_1D_Str(Chain1);
    return 0;
}
