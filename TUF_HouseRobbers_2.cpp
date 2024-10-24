#include <iostream>
#include <vector>

// If the wealth is arranged in Circle and Robber can only break-in adjacent House
// What is max wealth the robber can run safely with ??

// If houses are arranged in Circle, then either first or last can be in list Not both
// If we get Max wealth removing last House as ans1
// And we get Max Wealth by removing the first House as ans2
// The maximum of ans1 and ans2 should be the answer

using namespace std;

int maxWealthRobbery(vector<int> AllWealth)  // One call is without last and other is without first
{
    int prev2 = 0;
    int prev1 = 0;
    int n = AllWealth.size();

    for(int i=0;i<n;i++)
    {
        int pick = AllWealth[i];
        if(n>1)
            pick+=prev2;

        int not_pick = 0 + prev1;
        int cur = max(pick,not_pick);

        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;

}

int main()
{
    vector<int> AllWealth = {1,4,9};
    int n = AllWealth.size();
    vector<int> WithoutLast;
    vector<int> WithoutFirst;
    for(int i=0;i<n;i++)
    {
        if(i!=0)
        {
           WithoutFirst.push_back( AllWealth[i] );
        }
        if(i!=n-1)
        {
            WithoutLast.push_back( AllWealth[i] );
        }
    }



    int ansAll = maxWealthRobbery(AllWealth);
    cout << "Max Wealth Robbery ansAll =" << ansAll << endl;
    int ans1 = maxWealthRobbery(WithoutLast);
    cout << "Max Wealth Robbery ans1 =" << ans1 << endl;
    int ans2 = maxWealthRobbery(WithoutFirst);
    cout << "Max Wealth Robbery ans2 =" << ans2 << endl;

    int ans = max(ans1,ans2);

    cout << "Max Wealth Robbery if Houses in Circle =" << ans << endl;
    return 0;
}


/// Solutions 2 Leetcode  https://leetcode.com/problems/house-robber-ii/

class Solution {
public:
    int max_rob_sum_dp_tabulation(vector<int> nums)
    {
        int n = nums.size();
        vector<int> dp(n+1);

        dp[0] = nums[0];
        
        for(int i=1;i<n;i++)
        {
            int pick = nums[i];
            if(i>1)
            {
                pick+=dp[i-2];
            }

            int not_pick = 0 + dp[i-1];

            dp[i] = max(pick,not_pick);

        }

        return dp[n-1];


    }
    int rob(vector<int>& nums) {

        int n = nums.size();
        vector<int> WithoutFirst,WithoutLast;

        if(n==1)
        {
            return nums[0];
        }

        for(int i=0;i<n;i++)
        {
            if(i!=0)
            {
                WithoutFirst.push_back(nums[i]);
            }
            if(i!=n-1)
            {
                WithoutLast.push_back(nums[i]);
            }
        }

        int ans = max(max_rob_sum_dp_tabulation(WithoutFirst),max_rob_sum_dp_tabulation(WithoutLast));
        
        return ans;
    }
};
