#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Give the subsequence as 10,2,5,7
Find longest increasing subsequence
Ans is 2,5,7 longest length and the values are increasing order
*/

void print_1D_int_array(vector<int> v)
{
    for(auto d:v)
    {
        cout << d << " ";
    }
    cout << endl;
}

bool IncreasingSubsequence(vector<int> ArrList)
{
    vector<int> Cpy_ArrList = ArrList;
    sort(Cpy_ArrList.begin(),Cpy_ArrList.end());

    int sz = ArrList.size();

    for(int i=0;i<sz;i++)
    {
        if(ArrList[i]==Cpy_ArrList[i])
            continue;
        else
            return false;
    }
    return true;

}
//Recursion TC --> O(2^N) + N*O(Nlogn) // NLog-N for Sort Used
// SC --> O(N) // Recursion Stack
int Longest_Increasing_Subsequences(vector<int> LIS,vector<int>& ArrList,int index,vector<int>& Max_LIS)
{
    int n = ArrList.size();
    if(index==n)
    {
        if(IncreasingSubsequence(LIS))
        {
            if(Max_LIS.size()<LIS.size())
                Max_LIS = LIS;
            return LIS.size();
        }

        else
            return 0;
    }
    else if(!IncreasingSubsequence(LIS))
        return 0;

    // not take
    int not_take = Longest_Increasing_Subsequences(LIS,ArrList,index+1,Max_LIS);

    // take
    LIS.push_back(ArrList[index]);
    int take = Longest_Increasing_Subsequences(LIS,ArrList,index+1,Max_LIS);

    auto f = find(LIS.begin(),LIS.end(),ArrList[index]);
    LIS.erase(f);

    return max(take,not_take);
}

int findLIS(int index,int prev_index,vector<int>& ArrList)
{
    int n = ArrList.size();
    if(index==n)
        return 0;

    int not_take_len = findLIS(index+1,prev_index,ArrList);

    int take_len = -1e9;
    if(prev_index==-1 || ArrList[index]>ArrList[prev_index])
        take_len = 1 + findLIS(index+1,index,ArrList);

    return max(take_len,not_take_len);
}

int findLIS(int index,int prev_index,vector<int>& ArrList,vector<vector<int>>& dp)
{
    int n = ArrList.size();
    if(index==n)
        return 0;

    if(dp[index][prev_index]!=-1)
    {
        return dp[index][prev_index+1];
    }
    int not_take_len = findLIS(index+1,prev_index,ArrList,dp);

    int take_len = -1e9;
    if(prev_index==-1 || ArrList[index]>ArrList[prev_index])
        take_len = 1 + findLIS(index+1,index,ArrList,dp);

    return dp[index][prev_index+1] = max(take_len,not_take_len);
}

int main()
{
    vector<int> ArrList = {10,9,2,5,3,7,101,18};
    vector<int> LIS;
    vector<int> MAX_LIS;
    int ans = Longest_Increasing_Subsequences(LIS,ArrList,0,MAX_LIS);

    cout << "Longest_Increasing_Subsequences len =" << ans << endl;
    cout << "Longest_Increasing_Subsequences Value= =";
    print_1D_int_array(MAX_LIS);

    ans = findLIS(0,-1,ArrList);
    cout << "Longest_Increasing_Subsequences len Using Sol 2 =" << ans << endl;


    int n = ArrList.size();
    vector<vector<int>> dp(n+1,vector<int>(n+1,-1));
    ans = findLIS(0,-1,ArrList);
    cout << "Longest_Increasing_Subsequences len Using Sol 2 Memoization =" << ans << endl;


    return 0;
}
