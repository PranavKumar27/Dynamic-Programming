#include <iostream>
#include <vector>

using namespace std;

int NoOfEdits(string s1,string s2,int index1,int index2)
{
    cout << " index1=" << index1 << " index2=" << index2 << endl;

    if(index2<0)
        return index1+1;

    if(index1<0)
        return index2+1;

    if(s1[index1]==s2[index2])
    {
        return NoOfEdits(s1,s2,index1-1,index2-1);
    }
    else
    {

        // Can do three things insert,delete,replace

        int inserts = 1 + NoOfEdits(s1,s2,index1,index2-1);

        int deletes = 1 + NoOfEdits(s1,s2,index1-1,index2);

        int replaces = 1 + NoOfEdits(s1,s2,index1-1,index2-1);

        cout << "inserts=" << inserts << " deletes=" << deletes << " replaces=" << replaces << endl;
        return min(inserts,min(deletes,replaces));

    }
}

int NoOfEdits(string s1,string s2,int index1,int index2,vector<vector<int>>& dp)
{
    //cout << " index1=" << index1 << " index2=" << index2 << endl;

    if(index2==0)
        return index1;

    if(index1==0)
        return index2;


    if(dp[index1][index2]!=-1)
    {
        //cout << "Returned From dp" << endl;
        return dp[index1][index2];
    }

    if(s1[index1-1]==s2[index2-1])
    {
        return dp[index1][index2] = NoOfEdits(s1,s2,index1-1,index2-1,dp);
    }
    else
    {

        // Can do three things insert,delete,replace

        int inserts = 1 + NoOfEdits(s1,s2,index1,index2-1,dp);

        int deletes = 1 + NoOfEdits(s1,s2,index1-1,index2,dp);

        int replaces = 1 + NoOfEdits(s1,s2,index1-1,index2-1,dp);

        //cout << "inserts=" << inserts << " deletes=" << deletes << " replaces=" << replaces << endl;
        return dp[index1][index2] = min(inserts,min(deletes,replaces));

    }
}

int NoOfEdits(string s1,string s2)
{
    //cout << " index1=" << index1 << " index2=" << index2 << endl;

    int m = s1.size(),n=s2.size();
    vector<vector<int>> dp(m+1,vector<int>(n+1,-1));

    for(int index1=0;index1<m+1;index1++)
    {
        dp[index1][0] = index1;
    }

    for(int index2=0;index2<n+1;index2++)
    {
        dp[0][index2] = index2;
    }


    for(int index1=1;index1<m+1;index1++)
    {
        for(int index2=1;index2<n+1;index2++)
        {
            if(s1[index1-1]==s2[index2-1])
            {
                dp[index1][index2] = dp[index1-1][index2-1];
            }
            else
            {

                // Can do three things insert,delete,replace

                int inserts = 1 + dp[index1][index2-1];

                int deletes = 1 + dp[index1-1][index2];

                int replaces = 1 + dp[index1-1][index2-1];

                //cout << "inserts=" << inserts << " deletes=" << deletes << " replaces=" << replaces << endl;
                dp[index1][index2] = min(inserts,min(deletes,replaces));

            }
        }
    }

    return dp[m][n];

}

int NoOfEdits_Space(string s1,string s2)
{
    //cout << " index1=" << index1 << " index2=" << index2 << endl;

    int m = s1.size(),n=s2.size();
    vector<int> Prev(n+1,0);
    vector<int> Cur(n+1,0);


    Prev[0] = 0;
    Cur[0] = 0;


    for(int index2=1;index2<n+1;index2++)
    {
        Prev[index2] = index2;
    }


    for(int index1=1;index1<m+1;index1++)
    {
        Cur[0]=index1;
        for(int index2=1;index2<n+1;index2++)
        {
            if(s1[index1-1]==s2[index2-1])
            {
                Cur[index2] = Prev[index2-1];
            }
            else
            {

                // Can do three things insert,delete,replace

                int inserts = 1 + Cur[index2-1]; // Cannot be Space Optimized to 1 D
                                                // since both Prev and Cur are used to fill Cur

                int deletes = 1 + Prev[index2];

                int replaces = 1 + Prev[index2-1];

                //cout << "inserts=" << inserts << " deletes=" << deletes << " replaces=" << replaces << endl;
                Cur[index2] = min(inserts,min(deletes,replaces));

            }
        }
        Prev = Cur;
    }

    return Prev[n];

}

int main()
{
    string s1 = "horse",s2="ros";
    int m = s1.size(),n=s2.size();
    int ans = NoOfEdits(s1,s2,m-1,n-1);
    cout << "NoOfEdits insert + delete + replace Using Recursion =" << ans << endl;

    vector<vector<int>> dp(m+1,vector<int>(n+1,-1));
    ans = NoOfEdits(s1,s2,m,n,dp);
    cout << "NoOfEdits insert + delete + replace Using memoization =" << ans << endl;

    ans = NoOfEdits(s1,s2);
    cout << "NoOfEdits insert + delete + replace Using Tabulation =" << ans << endl;

    ans = NoOfEdits_Space(s1,s2);
    cout << "NoOfEdits insert + delete + replace Using Space Optimization =" << ans << endl;

    return 0;
}
