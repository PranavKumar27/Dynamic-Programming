#include <iostream>
#include <vector>

using namespace std;

void print_v(vector<int> v)
{
    int sz = v.size();
    if(sz==0)
    {
        cout << "[]" ;
    }
    else
    {
        for(auto d:v)
        {
            cout << d << ",";
        }
    }

    cout << endl;
}

/// Print All Subsequences whose sum is K
void subsequenceSumK(int index,vector<int> ArrList,vector<int> arr,int sum,int K)
{
    int n = arr.size();
    if(index>=n)
    {
        if(sum==K)
        {
            print_v(ArrList);
        }
        return;
    }
    ArrList.push_back(arr[index]);
    subsequenceSumK(index+1,ArrList,arr,sum+arr[index],K);
    ArrList.pop_back();
    subsequenceSumK(index+1,ArrList,arr,sum,K);
}

/// inorder to print only the first subsequence whose sum = K

bool OnlyOneSubsequenceSumK(int index,vector<int> ArrList,vector<int> arr,int sum,int K)
{
    int n = arr.size();
    if(index>=n)
    {
        if(sum==K)
        {
            print_v(ArrList);
            return true;
        }
        return false;
    }
    ArrList.push_back(arr[index]);
    if(OnlyOneSubsequenceSumK(index+1,ArrList,arr,sum+arr[index],K) == true)
        return true;
    ArrList.pop_back();
    if(OnlyOneSubsequenceSumK(index+1,ArrList,arr,sum,K) == true)
        return true;

    return false;
}

/// count of number of subsequences

int countSubsequenceSumK(int index,vector<int> arr,int sum,int K)
{
    int n = arr.size();
    if(index>=n)
    {
        if(sum==K)
        {
            return 1;
        }
        return 0;
    }
    int l = countSubsequenceSumK(index+1,arr,sum+arr[index],K);
    int r = countSubsequenceSumK(index+1,arr,sum,K);

    return l+r;
}

int main()
{
    vector<int> arr ={1,2,3};
    vector<int> ArrList;
    int K=3;
    cout << "Subsequences whose sum is k =" << K << endl;
    OnlyOneSubsequenceSumK(0,ArrList,arr,0,K);

    int ans = countSubsequenceSumK(0,arr,0,K);
    cout << "No of Subsequences whose sum is k =" << ans << endl;


    return 0;
}
