#include <iostream>
#include <vector>

using namespace std;

int find_Sum(vector<int> S)
{
    int total=0;
    for(auto d:S)
    {
        total+=d;
    }
    return total;
}

bool IsSumKPossible(vector<int>arr,int targetSum,int index)
{
    if(targetSum == 0)
    {
        return true;
    }
    if(index == 0)
    {
        if(arr[0] == targetSum)
            return true;
        else
            return false;
    }

    bool not_take = IsSumKPossible(arr,targetSum,index-1);

    bool take = false;
    if(arr[index]<=targetSum)
        take = IsSumKPossible(arr,targetSum-arr[index],index-1);

    return take|not_take;
}


bool IsSumKPossible_Memo(vector<int>arr,int targetSum,int index,vector<vector<int>>& dp)
{
    if(targetSum == 0)
    {
        return true;
    }
    if(index == 0)
    {
        if(arr[0] == targetSum)
            return true;
        else
            return false;
    }

    if(dp[index][targetSum] != -1)
    {
        return dp[index][targetSum];
    }

    bool not_take = IsSumKPossible_Memo(arr,targetSum,index-1,dp);

    bool take = false;
    if(arr[index]<=targetSum)
        take = IsSumKPossible_Memo(arr,targetSum-arr[index],index-1,dp);

    return dp[index][targetSum ] = take|not_take;
}

bool IsSumKPossible_Tabu(vector<int>arr,int targetSum)
{
    int n = arr.size();
    vector<vector<bool>> dp(n,vector<bool>(targetSum+1,false));

    for(int i=0;i<n;i++)
        dp[i][targetSum] = true;

    dp[0][arr[0]] = true;

    for(int index = 1;index<n;index++)
    {
        for(int target=1;target<targetSum+1;target++)
        {
            bool not_take = dp[index-1][target];

            bool take = false;
            if(arr[index]<=targetSum)
                take = dp[index-1][targetSum-arr[index]];

            dp[index][target] = take|not_take;
        }
    }

    return dp[n-1][targetSum];

}

bool IsSumKPossible_Space_Optimized(vector<int>arr,int targetSum)
{
    int n = arr.size();
    vector<bool> Prev(targetSum+1,false);
    vector<bool> Current(targetSum+1,false);

    for(int i=0;i<n;i++)
        Prev[targetSum] = true;

    Prev[arr[0]] = true;

    for(int index = 1;index<n;index++)
    {
        for(int target=1;target<targetSum+1;target++)
        {
            bool not_take = Prev[target];

            bool take = false;
            if(arr[index]<=targetSum)
                take = Prev[targetSum-arr[index]];

            Current[target] = take|not_take;
        }
        Prev = Current;
    }

    return Prev[targetSum];

}



int main()
{
    vector<int> S ={2,3,4,4,7,10};
    int total_Sum = find_Sum(S);

    if(total_Sum%2) // Odd Sum Cannot divide into Equal Sets
    {
        cout << "Can't divide S1 into two Equal Sets with Same Sum" << endl;
    }
    else
    {
        int half_sum = total_Sum/2;
        int n = S.size();
        bool ans_Full_Sum  = IsSumKPossible(S,total_Sum,n-1);
        bool ans_Half_Sum = IsSumKPossible(S,half_sum,n-1);

        vector<vector<int>> dp1(n,vector<int>(total_Sum+1,-1));

        vector<vector<int>> dp2(n,vector<int>(half_sum+1,-1));

        bool ans_Full_Sum_Memo  = IsSumKPossible_Memo(S,total_Sum,n-1,dp1);
        bool ans_Half_Sum_Memo = IsSumKPossible_Memo(S,half_sum,n-1,dp2);

        bool ans_Full_Sum_Tabu  = IsSumKPossible_Tabu(S,total_Sum);
        bool ans_Half_Sum_Tabu = IsSumKPossible_Tabu(S,half_sum);


        bool ans_Full_Sum_Space  = IsSumKPossible_Space_Optimized(S,total_Sum);
        bool ans_Half_Sum_Space = IsSumKPossible_Space_Optimized(S,half_sum);


        cout << "ans_Full_Sum =" << ans_Full_Sum  << " ans_Half_Sum =" << ans_Half_Sum << endl;

        cout << "ans_Full_Sum_Memo =" << ans_Full_Sum_Memo  << " ans_Half_Sum_Memo =" << ans_Half_Sum_Memo << endl;

        cout << "ans_Full_Sum_Tabu =" << ans_Full_Sum_Tabu  << " ans_Half_Sum_Tabu =" << ans_Half_Sum_Tabu << endl;

        cout << "ans_Full_Sum_Space =" << ans_Full_Sum_Space  << " ans_Half_Sum_Space =" << ans_Half_Sum_Space << endl;


        if(ans_Full_Sum && ans_Half_Sum)
        {
            cout << "Recursion Can be Divided into 2 Equal Sets of Equal Sum" << endl;
        }
        else
        {
            cout << " Recursion Can't Divide into 2 Equal Sets of Equal Sum" << endl;
        }


        if(ans_Full_Sum_Memo && ans_Half_Sum_Memo)
        {
            cout << "Memoization Can be Divided into 2 Equal Sets of Equal Sum" << endl;
        }
        else
        {
            cout << "Memoization Can't Divide into 2 Equal Sets of Equal Sum" << endl;
        }


        if(ans_Full_Sum_Tabu && ans_Half_Sum_Tabu)
        {
            cout << "Tabulation Can be Divided into 2 Equal Sets of Equal Sum" << endl;
        }
        else
        {
            cout << "TabulationCan't Divide into 2 Equal Sets of Equal Sum" << endl;
        }

        if(ans_Full_Sum_Space && ans_Half_Sum_Space)
        {
            cout << "Space Optimization Can be Divided into 2 Equal Sets of Equal Sum" << endl;
        }
        else
        {
            cout << "TabulationCan't Divide into 2 Equal Sets of Equal Sum" << endl;
        }
    }
    return 0;
}
