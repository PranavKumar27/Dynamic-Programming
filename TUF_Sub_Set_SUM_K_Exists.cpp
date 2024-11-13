#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void print_1D_v(vector<bool> v)
{
    for(auto d:v)
    {
        cout << d << ",";
    }
    cout << endl;
}

void print_1D_v_INT(vector<int> v)
{
    for(auto d:v)
    {
        cout << d << ",";
    }
    cout << endl;
}

void print_2D_v(vector<vector<bool>> dp)
{
    int m = dp.size();
    int n= dp[0].size();

    for(int i=0;i<m;i++)
    {

        for(int k=0;k<n;k++)
        {
            cout << dp[i][k] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}
void AllSubsequnces(vector<int> ArrList,int index,vector<int> AllValues)
{
    int data_size = AllValues.size();
    if(index==data_size)
    {
        print_1D_v_INT(ArrList);
        ArrList.clear();
        return;
    }
    //Take and Not Take
    ArrList.push_back(AllValues[index]);
    AllSubsequnces(ArrList,index+1,AllValues);

    auto it = find(ArrList.begin(),ArrList.end(),AllValues[index]);
    ArrList.erase(it);
    AllSubsequnces(ArrList,index+1,AllValues);
}

int SumKSubsequnces(int sum,int index,vector<int> AllValues,int K)
{
    int data_size = AllValues.size();
    if(index==data_size)
    {
        if(sum==K)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    //Take and Not Take
    cout << "f ( " << sum+AllValues[index] << "," << index+1 << " )" << endl;
    int take = SumKSubsequnces(sum+AllValues[index],index+1,AllValues,K);

    cout << "f( " << sum << "," << index+1 << " )"<< endl;
    int Not_take = SumKSubsequnces(sum,index+1,AllValues,K);

    return take+Not_take;
}

bool SumKSubsequncesExist(int index,int targetSum,vector<int> arr)
{
    if(targetSum == 0)
    {
        return true;
    }
    if(index == 0)
    {
        if(arr[index]==targetSum)
            return true;
        else
            return false;
    }

    bool not_take = SumKSubsequncesExist(index-1,targetSum,arr);

    bool take = false;
    if(arr[index]<=targetSum)
    {
        take = SumKSubsequncesExist(index-1,targetSum-arr[index],arr);
    }

    return (take || not_take);
}

int SumKSubsequncesExist_Memo(int index,int targetSum,vector<int> arr,vector<vector<int>>& dp)
{
    // 1 Means True 0 Means False
    if(targetSum == 0)
    {
        return 1;
    }
    if(index == 0)
    {
        if(arr[index]==targetSum)
            return 1;
        else
            return 0;
    }

    if(dp[index][targetSum]!=-1)
    {
        cout << "Value in DP Array" << endl;
        return dp[index][targetSum];
    }
    int not_take = SumKSubsequncesExist_Memo(index-1,targetSum,arr,dp);

    int take = false;
    if(arr[index]<=targetSum)
    {
        take = SumKSubsequncesExist_Memo(index-1,targetSum-arr[index],arr,dp);
    }

    if(take==1||not_take==1)
        dp[index][targetSum] = 1;
    else
        dp[index][targetSum] = 0;
    return dp[index][targetSum];
}


int SumKSubsequncesExist_Tabulation(vector<int> arr,int targetSum,int n)
{
    vector<vector<bool>> dp(n,vector<bool>(targetSum+1,false));
    // 1 Means True 2 Means False

    for(int i=0;i<n;i++)
    {
        dp[i][0] = true; // True
    }

    print_2D_v(dp);

    //if(arr[0]==targetSum) Not Needed Here Since we Read Arr from index 1 
    // so we need to set dp[0][arr[0]] as true Always so that index =1 of dp can use it
    {
        cout << "Setting True" << endl;
        dp[0][arr[0]] = true;
    }

    print_2D_v(dp);

    for(int index=1;index<n;index++)
    {
        for(int target=1;target<targetSum+1;target++)
        {
            // Previous Row value (index-1) Same target Col
            int not_take = dp[index-1][target];
            
            int take = false;
            if(arr[index]<=target)
            {
                // Previous Row value (index-1), Target is modified by
                // subtracting included arr[i] from target target-arr[index]
                take = dp[index-1][target-arr[index]];  
                
            }
            dp[index][target] = (take | not_take);
        }
    }

    print_2D_v(dp);
    return dp[n-1][targetSum];
}

int SumKSubsequncesExist_Space_Optimized(vector<int> arr,int targetSum,int n)
{
    vector<bool> Prev(targetSum+1,false);
    vector<bool> Current(targetSum+1,false);


    Prev[0] = true; // True

    print_1D_v(Prev);

    Prev[arr[0]] = true;


    print_1D_v(Prev);

    for(int index=1;index<n+1;index++)
    {
        for(int target=1;target<targetSum+1;target++)
        {
            int not_take = Prev[target];
            int take = false;
            if(arr[index]<=target)
            {
                take = Prev[target-arr[index]];
            }
            Current[target] = (take || not_take);
        }
        Prev = Current;
    }

    print_1D_v(Prev);
    return Prev[targetSum];
}


int main()
{
    vector<int> AllValues = {4,3,1,8};
    vector<int> ArrList ={};
    cout << "All Subsequences =" << endl;
    AllSubsequnces(ArrList,0,AllValues);

    int sum=0;
    int K=4;
    cout << "Count of  Subsequences Sum=" << K << " are =" << SumKSubsequnces(sum,0,AllValues,K)<< endl;


    int n = AllValues.size();
    bool res = SumKSubsequncesExist(n-1,K,AllValues);
    cout << " Does Subsequences Sum=" << K << " Exists =" << res << endl;



    vector<vector<int>> dp(n+1,vector<int>(K+1,-1));
    int res_Memo = SumKSubsequncesExist_Memo(n-1,K,AllValues,dp);
    cout << " Does Subsequences Sum=" << K << " Exists Using Memoization=" << res_Memo << endl;


    int res_Tab = SumKSubsequncesExist_Tabulation(AllValues, K,n);
    cout << " Does Subsequences Sum=" << K << " Exists Using Tabulation=" << res_Tab << endl;

    int res_Space = SumKSubsequncesExist_Space_Optimized(AllValues, K,n);
    cout << " Does Subsequences Sum=" << K << " Exists Using Space Optimized=" << res_Space << endl;


    return 0;
}
