#include <iostream>
#include <vector>

using namespace std;

int countNoOfStairs(int index)
{
    if(index==0)
    {
        return 1;
    }
    if(index==1)
    {
        return 1;
    }

    int l = countNoOfStairs(index-1);
    int r = countNoOfStairs(index-2);

    return (l+r);
}

int main()
{
    int n = 3;
    vector<int> arr;
    for(int i=0;i<n;i++)
    {
        arr.push_back(1);
    }
    for(int i=0;i<n;i++)
    {
        arr.push_back(2);
    }
    int K = n; // Total number of Stairs
    int ans = countNoOfStairs(n);

    cout << "No of ways to climb stairs with steps 1 and 2 for Stair for height " << n << "  = " << ans << endl;
    return 0;
}
