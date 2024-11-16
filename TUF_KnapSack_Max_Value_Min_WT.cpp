#include <iostream>
#include <vector>

using namespace std;

void print_2D_v(vector<vector<int>> dp)
{
    for(int i=0;i<dp.size();i++)
    {
        for(int j=0;j<dp[0].size();j++)
        {
            cout << dp[i][j] << "\t";
        }
        cout << endl;
    }
}

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

int maxValueInBag_knapsack_Tabu(vector<int> wt,vector<int> value,int Bag_Capacity)
{
    int n = wt.size();
    vector<vector<int>> dp(n,vector<int>(Bag_Capacity+1,0));

    for(int wt_left =wt[0];wt_left<Bag_Capacity+1;wt_left++)
    {
        dp[0][wt_left]=value[0];
    }

    //print_2D_v(dp);
    cout << endl;
    for(int index=1;index<n;index++)
    {
        for(int wt_left=0;wt_left<Bag_Capacity+1;wt_left++)
        {
            int not_take = dp[index-1][wt_left];
            //cout << "not_take" << not_take << endl;
            int take = -1e9;
            if(wt[index]<=wt_left )
                take = value[index]+dp[index-1][wt_left-wt[index]];
             //cout << "take" << take << endl;

            dp[index][wt_left] = max(not_take,take);
        }
    }

    //print_2D_v(dp);
    return dp[n-1][Bag_Capacity];

}

int maxValueInBag_knapsack_Space(vector<int> wt,vector<int> value,int Bag_Capacity)
{
    int n = wt.size();
    vector<int> Prev(Bag_Capacity+1,0); // Single Array Space optimization

    for(int wt_left = wt[0];wt_left<Bag_Capacity+1;wt_left++)
    {
        Prev[wt_left]=value[0];
    }

    for(int index=1;index<n;index++)
    {
        for(int wt_left=Bag_Capacity;wt_left>=0;wt_left--) // Read from Right to left
        // We need values from left of Prev and it is intact in this case too
        {
            int not_take = Prev[wt_left];
            //cout << "not_take" << not_take << endl;
            int take = -1e9;
            if(wt[index]<=wt_left )
                take = value[index]+Prev[wt_left-wt[index]];
             //cout << "take" << take << endl;

            Prev[wt_left] = max(not_take,take);
        }
    }

    return Prev[Bag_Capacity];

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

    int ans_Tabu = maxValueInBag_knapsack_Tabu(wt,Value,Bag_Capacity);
    cout << "maxValueInBag_knapsack Using Tabu =" << ans_Tabu << endl;

    int ans_Space = maxValueInBag_knapsack_Space(wt,Value,Bag_Capacity);
    cout << "maxValueInBag_knapsack Using Space =" << ans_Space << endl;

    return 0;
}
