#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

/*
An Array as [10,20,30,40,50]
Here it means we have an arrays of below dimention
A: 10*20
B: 20*30
C: 30*40
D: 40*50

So we need to multiply Matrices A*B*C*D
Now there are 3 ways to multiply as below
A*(B*C*D)
(A*B)*(C*D)
(A*B*C)*D

Let's take A*(B*C*D)
consider   i
           k------j
              k---j
               k--j
                 kj

f(i,j) --> means minimum number of multiplications required to multiply matrix i ---> matrix j

f(1,4) means steps required to multiply [ 10*20 * (20*30 * 30*40 * 40*50) ]     [ A * ( B*C*D ) ]

So we see the final dimension of B*C*D we get
20*30 * 30*40 * 40*50

20*40 * 40*50

20*50

        Finally A * (B*C*D)
            10*20 * 20*50

No Of Operations =   10   * 20 * 50
So formulae is
no of Steps         A[i-1]*A[k]*A[j]

We still not solve Number of steps done in Calculation of B*C*D

So Recursion is f(i,j) = A[i-1]*A[k]*A[j] + f(i,k) + f(k+1,j)

if Only 1 Matrix is present No Of Steps of it will be 0
*/

// TC --> Exponential

void print_1D_v(vector<int> v)
{
    for(auto d:v)
    {
        cout << setw(5) <<d << " ";
    }
    cout << endl;
}

void print_2D_v(vector<vector<int>> Vv)
{
    for(auto v:Vv)
    {
        print_1D_v(v);
    }
    cout << endl;
}
int NoOfOperations(int i,int j,vector<int> A)
{
    if(i==j)
        return 0;

    int mini = 1e9;
    for(int k=i;k<j;k++)
    {
        int steps = A[i-1]*A[k]*A[j] + NoOfOperations(i,k,A) + NoOfOperations(k+1,j,A);
        cout << "steps =" << steps << endl;
        mini = min(mini,steps);
    }
    return mini;

}

// Memoization TC --> O(N*N) * N for inner loop Hence TC -> O(N^3)
// Space Complexity --> O(N*N) for dp + O(N) for stack
int NoOfOperations(int i,int j,vector<int> A,vector<vector<int>>& dp)
{
    if(i==j)
        return 0;

    if(dp[i][j]!=-1)
    {
        cout << "Returned from dp" << endl;
        return dp[i][j];
    }
    int mini = 1e9;
    for(int k=i;k<j;k++)
    {
        int steps = A[i-1]*A[k]*A[j] + NoOfOperations(i,k,A,dp) + NoOfOperations(k+1,j,A,dp);
        //cout << "steps =" << steps << endl;
        mini = min(mini,steps);
    }

    return dp[i][j] = mini;

}

int NoOfOperations(vector<int> A)
{
    int n = A.size();
    vector<vector<int>> dp(n,vector<int>(n,0));

    /*
    // Base Case covered in Value initialized in dp itself as 0
    for(int i=0;i<n;i++)
    {
        dp[i][i]=0;
    }
    */




    for(int i=n-1;i>=1;i--)
    {
        cout << "==i Starts== " << i << endl;
        for(int j=i+1;j<n;j++)
        {
            cout << "----j Starts---- " << j << endl;
            int mini = 1e9;
            for(int k=i;k<j;k++)
            {
                cout << "**** k Starts  ***** " << k << endl;
                int steps = A[i-1]*A[k]*A[j] + dp[i][k] + dp[k+1][j];
                cout << "steps =" << steps << endl;
                mini = min(mini,steps);
                cout << "**** k Ends *****" << endl;
            }
            dp[i][j] = mini;
            cout << "----j Ends ----" << endl;
        }
        cout << "=======i Ends =======" << endl;
    }


    print_2D_v(dp);
    return dp[1][n-1];

}
int main()
{
    vector<int> ArrList= {10,20,30,40,50};
    int n = ArrList.size();
    int ans = NoOfOperations(1,n-1,ArrList);
    cout << "No of Steps =" << ans << endl;

    vector<vector<int>> dp(n,vector<int>(n,-1));
    ans = NoOfOperations(1,n-1,ArrList,dp);
    cout << "No of Steps Using Memoization =" << ans << endl;

    print_2D_v(dp);

    ans = NoOfOperations(ArrList);
    cout << "No of Steps Using Tabulation =" << ans << endl;


    return 0;
}
