#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Bitonic Subsequence : A Bitonic Subsequence is either set of
increasing + decreasing or just increasing or just decreasing


If arr = {1,11,2,10,4,5,2,1};

Ans = {1,2,5,10,2,1} Length = 6

If Arr is below, find Longest Increasing subsequence
   arr = {1,11,2,10,4,5,2,1};
   LIS = {1,2, 2, 3,3,4,2,1}

Reverse the Arr and find Longest Increasing subsequence or Longest Decreasing subsequence
   arr = {1,2,5,4,10,2,11,1}
   LDS = {1,2,3,3, 4,1, 5,1}

   LIS = {1,2,2,3,3,4,2,1}
   LDS = {1,2,3,3,4,1,5,1}

SUM LIS ={2,4,5,6,7,5,7,2}

Find Max in Sum  LIS, that will the answer

At each index increasing subsequence/decreasing index is repeated

Like make sum = 7
so Bitonic Subsequence = 1,2,10,10,4,2,1
Here 10 is repeated So remove 10
So Final Ans = {1,2,10,4,2,1}

Length = 6

Also maintain Hash[] to store the indexes and form back the subsequence

*/

void print_1D_Str(vector<string>& S)
{
    for(auto d:S)
        cout << d << " ";
    cout << endl;
}

void print_1D_Int(vector<int>& V)
{
    for(auto d:V)
        cout << d << " ";
    cout << endl;
}
void findSubsequence(vector<int>& Subsequence,int max_idx,vector<int>& Hash,vector<int>& ArrList,bool NoReverse)
{
    int index = max_idx;
    Subsequence.push_back(ArrList[index]);

    while(Hash[index]!=index)
    {
        index = Hash[index];
        Subsequence.push_back(ArrList[index]);
    }
    if(NoReverse)
        reverse(Subsequence.begin(),Subsequence.end());
}


int max_LIS_len(vector<int>& ArrList,vector<int>& dp,vector<int>& Hash,int& max_idx)
{
    int max_len=-1;

    int n = ArrList.size();

    for(int index=0;index<n;index++)
    {
        for(int prev=index-1;prev>=0;prev--)
        {
            if(ArrList[prev]<ArrList[index] && dp[index]<1+dp[prev])
            {
                dp[index] = 1 + dp[prev];
                Hash[index] = prev;
            }
        }
        if(max_len<dp[index])
        {
            max_len = dp[index];
            max_idx = index;
        }
    }

    return max_len;
}
int main()
{
    vector<int> ArrList = {1,11,2,10,4,5,2,1};

    int max_idx1=-1,max_idx2=-1;

    int n = ArrList.size();

    vector<int> dp1(n,1),dp2(n,1);
    vector<int> Hash1(n),Hash2(n);

    for(int i=0;i<n;i++)
    {
        Hash1[i]=i;
        Hash2[i]=i;
    }

    vector<int> Rev_ArrList = ArrList;
    reverse(Rev_ArrList.begin(),Rev_ArrList.end());

    int max_len1 = max_LIS_len(ArrList,dp1,Hash1,max_idx1);

    int max_len2 = max_LIS_len(Rev_ArrList,dp2,Hash2,max_idx2);

    vector<int> dp_SUM(n,1);
    int max_idx = -1,max_len=-1;
    for(int i=0;i<n;i++)
    {
        dp_SUM[i] = dp1[i]+dp2[i]-1;
        if(max_len<dp_SUM[i])
        {
            max_len = dp_SUM[i];
            max_idx = i;
        }
    }

    cout << "max_idx =" << max_idx << endl;
    cout << "val=" << ArrList[max_idx] << endl;
    cout << "Arrlist=" << endl;
    print_1D_Int(ArrList);
    cout << "dp1=" << endl;
    print_1D_Int(dp1);
    cout << "Hash1=" << endl;
    print_1D_Int(Hash1);

    cout << "Reverse Arrlist=" << endl;
    print_1D_Int(Rev_ArrList);
    cout << "dp2=" << endl;
    print_1D_Int(dp2);
    cout << "Hash2=" << endl;
    print_1D_Int(Hash2);

    cout << "dp Sum=" << endl;
    print_1D_Int(dp_SUM);
    // Find Subsequence
    vector<int> Subsequence;
    findSubsequence(Subsequence,max_idx,Hash1,ArrList,true);

    cout << "Increasing Subsequence =" << endl;
    print_1D_Int(Subsequence);
    // Remove Last index
    int sz = Subsequence.size();
    Subsequence.erase(Subsequence.begin()+sz-1);

    cout << "Increasing & Decreasing Subsequence =" << endl;
    findSubsequence(Subsequence,max_idx,Hash2,Rev_ArrList,false);

    print_1D_Int(Subsequence);

    cout << "Length of subsequence = " << max_len << endl;

    cout << "Bitonic Subsequence =" << endl;
    print_1D_Int(Subsequence) ;
    return 0;
}


