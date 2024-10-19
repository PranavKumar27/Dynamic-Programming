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

int cnt =0 ;
void NoOfWaysToReachK(int index,vector<int> ArrList,int sum,int K)
{
    if(index>=0)
    {
        if(sum==K)
        {
            print_v(ArrList);
            cnt++;
            return;
        }
    }
    else
    {
        // Already Passed the base
        return;
    }
    ArrList.push_back(1);
    NoOfWaysToReachK(index-1,ArrList,sum+1,K);
    ArrList.pop_back();
    ArrList.push_back(2);
    NoOfWaysToReachK(index-1,ArrList,sum+2,K);
    ArrList.pop_back();
    ArrList.push_back(3);
    NoOfWaysToReachK(index-1,ArrList,sum+3,K);
}

int main()
{
    int n=5;
    vector<int> ArrList;
    cout << "All Ways to reach Stairs n =" << n << endl;
    NoOfWaysToReachK(n,ArrList,0,n);
    cout << "Total Number of Ways = " << cnt << endl;
    return 0;
}
