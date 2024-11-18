#include <iostream>
#include <vector>

using namespace std;

/*
Problem statement: Pick as many instances of a single items to achieve maximum value
*/

int findValueInKnapSack(int index,int Weight,vector<int> Wt_array,vector<int> Val_array)
{
    if(index==0)
    {
        return (Weight/Wt_array[0])*Val_array[0];
    }

    int not_take = findValueInKnapSack(index-1,Weight,Wt_array,Val_array);
    int take = -1e9;
    if(Wt_array[index]<=Weight)
        take = Val_array[index] + findValueInKnapSack(index,Weight-Wt_array[index],Wt_array,Val_array);

    return max(take,not_take);
}

int findValueInKnapSack(int index,int Weight,vector<int> Wt_array,vector<int> Val_array,vector<vector<int>>& dp)
{
    if(index==0)
    {
        return (Weight/Wt_array[0])*Val_array[0];
    }

    if(dp[index][Weight]!=-1)
    {
        return dp[index][Weight];
    }
    int not_take = findValueInKnapSack(index-1,Weight,Wt_array,Val_array);
    int take = -1e9;
    if(Wt_array[index]<=Weight)
        take = Val_array[index] + findValueInKnapSack(index,Weight-Wt_array[index],Wt_array,Val_array);

    return dp[index][Weight] = max(take,not_take);
}


int findValueInKnapSack(int Weight,vector<int> Wt_array,vector<int> Val_array)
{
    int n = Wt_array.size();
    vector<vector<int>> dp(n,vector<int>(Weight+1,-1));

    for(int target=0;target<Weight+1;target++)
    {
        dp[0][target] = (target/Wt_array[0])*Val_array[0];
    }

    for(int index=1;index<n;index++)
    {
        for(int target = 0;target<Weight+1;target++)
        {
            int not_take = dp[index-1][target];
            int take = -1e9;
            if(Wt_array[index]<=target)
                take = Val_array[index] + dp[index][target-Wt_array[index]];

            dp[index][target] = max(take,not_take);
        }
    }

    return dp[n-1][Weight];

}

int findValueInKnapSack_Space(int Weight,vector<int> Wt_array,vector<int> Val_array)
{
    int n = Wt_array.size();
    vector<int> Prev(Weight+1,0);
    //vector<int> Cur(Weight+1,0);

    for(int target=0;target<Weight+1;target++)
    {
        Prev[target] = (target/Wt_array[0])*Val_array[0];
    }

    for(int index=1;index<n;index++)
    {
        for(int target=0;target<Weight+1;target++)
        {
            int not_take = Prev[target];
            int take = -1e9;
            if(Wt_array[index]<=target)
                take = Val_array[index] + Prev[target-Wt_array[index]];

            Prev[target] = max(take,not_take);
        }
        //Prev=Cur;
    }

    return Prev[Weight];

}

int main()
{
    vector<int> Wt_array = {2,4,6};
    vector<int> Val_array ={5,11,13};
    int n = Wt_array.size();
    int K = 11; // bag Weight
    int ans = findValueInKnapSack(n-1,K,Wt_array,Val_array);
    cout << "findValueInKnapSack = " << ans << endl;

    vector<vector<int>> dp(n,vector<int>(K+1,-1));
    ans = findValueInKnapSack(n-1,K,Wt_array,Val_array,dp);
    cout << "findValueInKnapSack Using Memo= " << ans << endl;

    ans = findValueInKnapSack(K,Wt_array,Val_array);
    cout << "findValueInKnapSack Using Tabu= " << ans << endl;

    ans = findValueInKnapSack_Space(K,Wt_array,Val_array);
    cout << "findValueInKnapSack Using Space= " << ans << endl;

    return 0;
}
