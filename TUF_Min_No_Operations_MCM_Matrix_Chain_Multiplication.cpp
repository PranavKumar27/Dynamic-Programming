#include <iostream>
#include <vector>

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

int main()
{
    vector<int> ArrList= {10,20,30,40,50};
    int j = ArrList.size();
    int ans = NoOfOperations(1,j-1,ArrList);
    cout << "No of Steps =" << ans << endl;
    return 0;
}
