#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void print_2D_v(vector<vector<bool>> dp)
{
    int m = dp.size();
    int n= dp[0].size();

    for(int i=0;i<m;i++)
    {
        for(int k=0;k<n;k++)
        {
            cout << dp[i][k] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int min_abs_diff_SubSet_Partition(vector<int> arr)
{
    int total_sum = 0;
    for(auto d:arr)
    {
        total_sum+=d;
    }
    int n = arr.size();
    vector<vector<bool>> dp(n,vector<bool>(total_sum+1,false));

    // Base Case 1  If sum required is 0
    for(int i=0;i<n;i++)
    {
        dp[i][0] = true;
    }

    // Base Case 2, If sum required is arr[0]
    if(arr[0]<=total_sum)
        dp[0][arr[0]] = true;

    for(int index=1;index<n;index++)
    {
        for(int target=1;target<total_sum+1;target++)
        {
            bool not_take = dp[index-1][target];

            bool take = false;

            if(arr[index]<=target)
            {
                take = dp[index-1][target-arr[index]];
            }

            dp[index][target] = take|not_take;
        }
    }

    print_2D_v(dp);
    int min_diff = INT_MAX;
    for(int target=0;target<(total_sum+1)/2;target++)
    {
        int S1 = target;
        int S2 = total_sum-S1;
        if(dp[n-1][target]==true) // Sum upto i (target) is possible
        {
            min_diff = min(min_diff,abs(S1-S2));
        }
    }
    return min_diff;
}
int main()
{
    vector<int> arr ={1,3,4,10};
    int ans = min_abs_diff_SubSet_Partition(arr);
    cout << "min_abs_diff_SubSet_Partition =" << ans << endl;
    return 0;
}
