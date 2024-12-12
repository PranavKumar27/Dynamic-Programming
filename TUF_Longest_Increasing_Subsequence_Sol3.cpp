#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Lower bound : Consider an array as {1,2,3,4,5,6,7,8,9}
For x = 7, find lower bound
A lower bound is the smallest value greater than or equal to the node
such that arr[index] >= x
Find what is the index ??

This can be done using Binary
low = 0, high = 8, mid = 4

Is arr[4] >= 7 => 5 >= 7 --> False

So value x will be possibly on the right
low = mid+1, high = 8
low = 5, high = 8 , mid = 6

Is arr[6] >= 7  -> 7 >= 7 --> True

Hence lower bound index for x=7 is 6
Ans = 6

Consider An array as 7,10,11,13,20
Apply binary Search and find lower bound of 19

low= 0; high = 4, mid = 2
arr[2]>=19 --> 11>=19 --> False
Move to right
low = mid+1 high = 4
low = 3, high =4 , mid = 3
arr[3]<=19 --> 13>=19 False
Move right

low = mid+1, high = 4
low = 4, high =4 , mid = 4

arr[4]>=19 --> 20>=19 --> True
Hence lower bound index for x =19 is index = 4

UPPER BOUND: An Upper bound is the smallest value greater than the node
such that arr[index] > x . Not equal

For finding upper bound the only change to be done
is in the condition arr[index] < x
*/
// TC --> O(NLogN) Same as for Binary Search
int lower_bound_val(vector<int>& Arr,int x)
{
    // Arr is sorted Array
    int low = 0, high = Arr.size()-1,mid = -1;

    int ans_Idx = high;
    while(low<=high)
    {
        mid = (low+high)/2;
        if(Arr[mid]>=x)
        {
            ans_Idx = mid;
            high = mid-1;
        }
        else
        {
            low = mid+1;
        }
    }
    return ans_Idx;
}

int upper_bound_val(vector<int>& Arr,int x)
{
    // Arr is sorted Array
    int low = 0, high = Arr.size()-1,mid = -1;

    int ans_Idx = high;
    while(low<=high)
    {
        mid = (low+high)/2;
        if(Arr[mid]>x)
        {
            ans_Idx = mid;
            high = mid-1;
        }
        else
        {
            low = mid+1;
        }
    }
    return ans_Idx;
}

// TC --> O(N * logN ) // For Binary Search complexity is logN
// SC -> O(N)
int findLIS(vector<int> ArrList)
{
    int n = ArrList.size();
    vector<int> MaxLenLIS;
    for(int index=0;index<n;index++)
    {
        int val = ArrList[index];
        auto itr = lower_bound(MaxLenLIS.begin(),MaxLenLIS.end(),val);
        int lb_idx = itr - MaxLenLIS.begin();

        cout << "--> lb_idx =" << lb_idx << endl;
        if(MaxLenLIS.size()==lb_idx)
        {
            MaxLenLIS.push_back(val);
        }
        else
        {
            MaxLenLIS[lb_idx] = val;
        }
    }
    // NOTE : MaxLenLIS is not teh LIS, It is just used for calculating max len possible for LIS
    return MaxLenLIS.size();
}

int main()
{
    vector<int> Arr = {7,10,11,13,20};
    int n = Arr.size();
    int x = 13;
    int ans_idx = lower_bound_val(Arr,x);
    cout << "lower bound of " << x <<  " val =" << Arr[ans_idx] << endl;

    ans_idx = upper_bound_val(Arr,x);
    cout << "upper bound of " << x <<  " val =" << Arr[ans_idx] << endl;

    int y = 21;
    auto itr = lower_bound(Arr.begin(),Arr.end(),y);
    int lb_idx = itr - Arr.begin();
    cout << "index =" << lb_idx << endl;
    if(lb_idx!=n)
        cout << "lower bound val of " << y << " Using STL =" << *itr << endl;
    else
        cout << "lower bound Not possible" << endl;


    itr = upper_bound(Arr.begin(),Arr.end(),y);

    if(itr!=Arr.end())
        cout << "upper bound val of " << y << " Using STL =" << *itr << endl;
    else
        cout << "upper bound Not possible" << endl;


    vector<int> ArrList = {1,7,8,4,5,6,-1,9};

    int ans = findLIS(ArrList);

    cout << "Max Len of LIS Possible = " << ans << endl;

    return 0;
}
