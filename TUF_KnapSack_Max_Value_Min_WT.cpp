#include <iostream>
#include <vector>

using namespace std;

int maxValueInBag_knapsack(vector<int> wt,vector<int> value,int index, int wt_left)
{
    if(index==0)
    {
        // All items tried to pick and tested
        if(wt[index]<=wt_left)
        {
            return value[index];
        }
        else
        {
            return 0;
        }
    }

    int not_take = maxValueInBag_knapsack(wt,value,index-1,wt_left);
    int take = -1e9;
    if(wt[index]<=wt_left && wt_left>=0)
        take = value[index]+maxValueInBag_knapsack(wt,value,index-1,wt_left-wt[index]);

    return max(not_take,take);
}

int maxValueInBag_knapsack_Memo(vector<int> wt,vector<int> value,int index, int wt_left,vector<vector<int>>& dp)
{
    if(wt_left<0)
        return 0;
    if(index==0)
    {
        // All items tried to pick and tested
        if(wt[index]<=wt_left)
        {
            return value[index];
        }
        else
        {
            return 0;
        }
    }

    if(dp[index][wt_left]!=-1)
    {
        return dp[index][wt_left];
    }

    int not_take = maxValueInBag_knapsack_Memo(wt,value,index-1,wt_left,dp);

    int take = -1e9;
    if(wt[index]<=wt_left && wt_left>=0)
        take = value[index]+maxValueInBag_knapsack_Memo(wt,value,index-1,wt_left-wt[index],dp);

    return dp[index][wt_left] = max(not_take,take);
}
int main()
{
    vector<int> wt = {3,2,5};
    vector<int> Value = {30,40,60};

    int n = wt.size();
    int Bag_Capacity = 6;
    int ans = maxValueInBag_knapsack(wt,Value,n-1,Bag_Capacity);
    cout << "maxValueInBag_knapsack =" << ans << endl;


    vector<vector<int>> dp(n,vector<int>(Bag_Capacity+1,-1));
    int ans_Memo = maxValueInBag_knapsack_Memo(wt,Value,n-1,Bag_Capacity,dp);
    cout << "maxValueInBag_knapsack Using Memo =" << ans_Memo << endl;
    return 0;
}
