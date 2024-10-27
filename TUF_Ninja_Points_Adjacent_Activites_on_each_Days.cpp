#include <iostream>
#include <vector>
#include <map>
#include <climits>

using namespace std;

void print_v(vector<int> v)
{
    for(auto d:v)
    {
        cout << d << ",";
    }
    cout << endl;
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

int max_in_vector(vector<int> v,int last=INT_MAX)
{
    int maxi = INT_MIN;
    for(int i=0;i<v.size();i++)
    {
        if(i!=last)
        {
            maxi = max(maxi,v[i]);
        }
    }
    return maxi;
}

int NinjaTrainingPoints_Bottom_Up_Tabulation(vector<vector<int>> Training)
{
    int days = Training.size();
    int activites = Training[0].size();
    vector<vector<int>> dp(days,vector<int>(activites+1,-1));

    for(int i=0;i<activites+1;i++)
    {
        dp[0][i] = max_in_vector(Training[0],i);
    }

    int max_points=INT_MIN;
    for(int day=1;day<days;day++)
    {
        for(int last=0;last<activites+1;last++)
        {
            dp[day][last] = 0;
            int maxk = INT_MIN;
            for(int activity=0;activity<activites;activity++)
            {
                if(activity!=last)
                {
                    int points = Training[day][activity]+dp[day-1][activity];
                    maxk = max(maxk,points);
                }
            }
            dp[day][last] = maxk;
        }
        //max_points = max(max_points,max_in_vector(dp[day]));
    }

    return dp[days-1][activites];


}

int NinjaTrainingPoints_Bottom_Up_Space_Optimized(vector<vector<int>> Training)
{
    int days = Training.size();
    int activites = Training[0].size();
    vector<int> Prev(activites+1,-1);

    for(int i=0;i<activites+1;i++)
    {
        Prev[i] = max_in_vector(Training[0],i);
    }

    for(int day=1;day<days;day++)
    {
        print_v(Prev);
        vector<int> Temp(activites+1,0);
        for(int last=0;last<activites+1;last++)
        {
            cout << "-----------" << endl;
            int maxk = INT_MIN;
            for(int activity=0;activity<activites;activity++)
            {
                cout << "activity =" << activity << endl;
                if(activity!=last)
                {
                    //cout << "activity =" << activity << endl;
                    cout << "Prev[activity] =" << Prev[activity] << endl;
                    cout << "Training[day][activity]=" << Training[day][activity] << endl;
                    int points = Training[day][activity]+Prev[activity];
                    cout << "points=" << points << endl;
                    maxk = max(maxk,points);
                }
            }
            cout << "-----------" << endl;
            Temp[last] = maxk;
        }
        Prev = Temp;
    }
    print_v(Prev);
    return Prev[activites];


}

int main()
{
    //vector<vector<int>> Training = {{10,50,1},{5,100,11}};

    vector<vector<int>> Training = {{3,2,1},{4,2,3},{7,6,8},{2,1,7}};
    vector<vector<int>> dp(Training.size()+1,vector<int>(Training[0].size()+1,-1));

    vector<vector<int>> dp2(Training.size()+1,vector<int>(Training[0].size()+1,-1));


    int ans_Tab = NinjaTrainingPoints_Bottom_Up_Tabulation(Training);
    cout << "Max_training_value for Ninja Training Points Bottom Up Tabulation = "<< ans_Tab << endl;

     int ans_Space_Optimized = NinjaTrainingPoints_Bottom_Up_Space_Optimized(Training);
    cout << "Max_training_value for Ninja Training Points Bottom Up ans_Space_Optimized = "<< ans_Space_Optimized << endl;


    //int Max_training_value = NinjaTrainingValue_Bottom_Up_Memoization(0,Training,0,3,dp);

    //int Max_training_Points = NinjaTrainingPoints_Top_Down_Memoization(Training,Training.size()-1,3,dp2);

    //print_2Dv(dp);
    //cout << "Max_training_value for Ninja Training Value Bottom Up= "<< Max_training_value << endl;

    //cout << "Max_training_value for Ninja Training Points Top Down = "<< Max_training_Points << endl;
    return 0;
}
