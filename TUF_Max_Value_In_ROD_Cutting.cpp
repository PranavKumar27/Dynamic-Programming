#include <iostream>
#include <vector>

using namespace std;

int findMaxValue(int index,int rod_len,vector<int> Val_array)
{
    if(index==0)
    {
        return (rod_len/(index+1))*Val_array[index];  // OR rod_len*Val_array[index]; since index+1 = 1 Here
    }

    int not_take = findMaxValue(index-1,rod_len,Val_array);
    int take = -1e9;
    if(index+1<=rod_len)
        take = Val_array[index] + findMaxValue(index,rod_len-(index+1),Val_array);

    return max(take,not_take);
}

int findMaxValue(int index,int rod_len,vector<int> Val_array,vector<vector<int>>& dp)
{
    if(index==0)
    {
        return (rod_len/(index+1))*Val_array[index];  // OR rod_len*Val_array[index]; since index+1 = 1 Here
    }

    if(dp[index][rod_len]!=-1)
    {
        return dp[index][rod_len];
    }
    int not_take = findMaxValue(index-1,rod_len,Val_array);
    int take = -1e9;
    if(index+1<=rod_len)
        take = Val_array[index] + findMaxValue(index,rod_len-(index+1),Val_array);

    return dp[index][rod_len] = max(take,not_take);
}

int findMaxValue(int rod_len,vector<int> Val_array)
{
    int n = Val_array.size();

    vector<vector<int>> dp(n,vector<int>(rod_len+1,0));

    for(int target=0;target<rod_len+1;target++)
    {
        dp[0][target] = target*Val_array[0];
    }

    for(int index=1;index<n;index++)
    {
        for(int target=0;target<rod_len+1;target++)
        {
            int not_take = dp[index-1][target];
            int take = -1e9;
            if(index+1<=target)
                take = Val_array[index] + dp[index][target-(index+1)];

            dp[index][target] = max(take,not_take);
        }
    }

    return dp[n-1][rod_len];

}

int findMaxValue_Space_2D(int rod_len,vector<int> Val_array)
{
    int n = Val_array.size();

    vector<int> Prev(rod_len+1,0);
    vector<int> Cur(rod_len+1,0);

    for(int target=0;target<rod_len+1;target++)
    {
        Prev[target] = target*Val_array[0];
    }

    for(int index=1;index<n;index++)
    {
        for(int target=0;target<rod_len+1;target++)
        {
            int not_take = Prev[target];
            int take = -1e9;
            if(index+1<=target)
                take = Val_array[index] + Cur[target-(index+1)];

            Cur[target] = max(take,not_take);
        }
        Prev = Cur;
    }
    return Prev[rod_len];
}

int findMaxValue_Space_1D(int rod_len,vector<int> Val_array)
{
    int n = Val_array.size();

    vector<int> Prev(rod_len+1,0);

    for(int target=0;target<rod_len+1;target++)
    {
        Prev[target] = target*Val_array[0];
    }

    for(int index=1;index<n;index++)
    {
        for(int target=0;target<rod_len+1;target++)
        {
            int not_take = Prev[target];
            int take = -1e9;
            if(index+1<=target)
                take = Val_array[index] + Prev[target-(index+1)];

            Prev[target] = max(take,not_take);
        }
    }
    return Prev[rod_len];
}


int main()
{
    vector<int> Val_array ={2,5,7,8,10};
    int n = Val_array.size();
    int K = 7;
    int ans = findMaxValue(n-1,K,Val_array);
    cout << "findMaxValue of Rod Cutting = " << ans << endl;

    vector<vector<int>> dp(n,vector<int>(K+1,-1));
    ans = findMaxValue(n-1,K,Val_array,dp);
    cout << "findMaxValue of Rod Cutting Using Memo= " << ans << endl;

    ans = findMaxValue(K,Val_array);
    cout << "findMaxValue of Rod Cutting Using Tabu = " << ans << endl;

    ans = findMaxValue_Space_2D(K,Val_array);
    cout << "findMaxValue of Rod Cutting Using Space Optimized 2D = " << ans << endl;

    ans = findMaxValue_Space_1D(K,Val_array);
    cout << "findMaxValue of Rod Cutting Using Space Optimized 1D = " << ans << endl;
    return 0;
}
