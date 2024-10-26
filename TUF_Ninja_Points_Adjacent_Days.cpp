#include <iostream>
#include <vector>
#include <map>
#include <climits>

using namespace std;

void print_v(vector<int> v)
{
    for(auto d:v)
    {
        cout << d << endl;
    }
}

void print_2Dv(vector<vector<int>> _2DV)
{
    for(auto v:_2DV)
    {
        for(auto d:v)
        {
            cout << d << ",";
        }
        cout << endl;
    }
}

int NinjaTrainingValue_Bottom_Up(int value,vector<vector<int>> Training,int row,int last)
{
    int days = Training.size();
    if(row == days)
    {
        //dp[row][last] = value;
        return value;
    }

    vector<int> daysValue(Training[row]); // Value like day[0] = {10,50,1}

    int max_val = INT_MIN;
    for(int i=0;i<daysValue.size();i++)
    {
        int v = daysValue[i];

        if(i!=last) // Not present in Map
        {
            int val = value + NinjaTrainingValue_Bottom_Up(v,Training,row+1,i);

            if(val>max_val)
            {
                max_val = val;
            }
        }
    }
    cout << " for Ninja Training val = "<< max_val << "for last =" << last << endl;
    return max_val;
}

int NinjaTrainingValue_Bottom_Up_Memoization(int value,vector<vector<int>> Training,int row,int last,vector<vector<int>>& dp)
{
    int days = Training.size();
    if(row == days)
    {
        //dp[row][last] = value;
        return value;
    }

    vector<int> daysValue(Training[row]); // Value like day[0] = {10,50,1}

    if(last !=3 && dp[row][last]!=-1)
    {
        cout << "Returned from Dp Array last =" << last << " row=" << row  << endl;
        return dp[row][last];
    }
    int max_val = INT_MIN;
    for(int i=0;i<daysValue.size();i++)
    {
        int v = daysValue[i];

        if(i!=last) // Not present in Map
        {
            int val = value + NinjaTrainingValue_Bottom_Up_Memoization(v,Training,row+1,i,dp);

            if(val>max_val)
            {
                max_val = val;
            }
        }
    }
    dp[row][last] = max_val;
    cout << " for Ninja Training val = "<< max_val << "for last =" << last << endl;
    return max_val;
}


int NinjaTrainingPoints_Top_Down(vector<vector<int>>Training,int row,int last)
{
    int n = Training[0].size();
    int maxi = INT_MIN;
    if(row==0)
    {
        for(int i=0;i<n;i++)
        {
            if(i!=last)
            {
                maxi = max(maxi,Training[row][i]);
            }
        }
        return maxi;
    }

    maxi = INT_MIN;

    for(int i=0;i<n;i++)
    {
        if(i!=last)
        {
            int points = Training[row][i] + NinjaTrainingPoints_Top_Down(Training,row-1,i);
            cout << "Points =" << points << endl;
            maxi = max(maxi,points);
        }
    }
    return maxi;
}

int NinjaTrainingPoints_Top_Down_Memoization(vector<vector<int>>Training,int row,int last,vector<vector<int>>& dp)
{
    int n = Training[0].size();
    int maxi = INT_MIN;
    if(row==0)
    {
        for(int i=0;i<n;i++)
        {
            if(i!=last)
            {
                maxi = max(maxi,Training[row][i]);
            }
        }
        return maxi;
    }

    if(last!=3 && dp[row][last]!=-1)
    {
        return dp[row][last];
    }
    maxi = INT_MIN;

    for(int i=0;i<n;i++)
    {
        if(i!=last)
        {
            int points = Training[row][i] + NinjaTrainingPoints_Top_Down_Memoization(Training,row-1,i,dp);
            cout << "Points =" << points << endl;
            maxi = max(maxi,points);
        }
    }
    dp[row][last] = maxi;
    return maxi;
}

int main()
{
    //vector<vector<int>> Training = {{10,50,1},{5,100,11}};

    vector<vector<int>> Training = {{2,1,3},{3,4,6},{10,1,6},{8,3,7}};
    vector<vector<int>> dp(Training.size()+1,vector<int>(Training[0].size(),-1));

    vector<vector<int>> dp2(Training.size()+1,vector<int>(Training[0].size(),-1));

    int Max_training_value = NinjaTrainingValue_Bottom_Up_Memoization(0,Training,0,3,dp);

    int Max_training_Points = NinjaTrainingPoints_Top_Down_Memoization(Training,Training.size()-1,3,dp2);

    //print_2Dv(dp);
    cout << "Max_training_value for Ninja Training Value Bottom Up= "<< Max_training_value << endl;

    cout << "Max_training_value for Ninja Training Points Top Down = "<< Max_training_Points << endl;
    return 0;
}
