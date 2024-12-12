#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool isIndexDivisible(int val, vector<int>& ArrList)
{
    int sz = ArrList.size();

    for(int i=0;i<sz;i++)
    {
        if(ArrList[i]!=0 && val!=0 && ( ArrList[i]%val==0 || val%ArrList[i]==0) )
            continue;
        else
            return false;
    }
    return true;
}

void print_1D_v(vector<int> v)
{
    cout << endl;
    for(auto d:v)
        cout << d << "  ";
    cout << endl;
}
int maxLenDivisibleSubset(int index,vector<int> ArrList, vector<int>& Arr,vector<int>& MaxArr)
{
    int n = Arr.size();
    if(index<0)
    {
        if(ArrList.size()>MaxArr.size())
            MaxArr = ArrList;
       return 0;
    }


    int not_take = maxLenDivisibleSubset(index-1,ArrList,Arr,MaxArr);

    // If ArrList is non-empty Make sure Arr[index] is divisible by all values in ArrList as well as vice-vera

    bool divisible = isIndexDivisible(Arr[index],ArrList);


    int take = -1e9;
    if(divisible)
    {
       ArrList.push_back(Arr[index]);
       take = 1 + maxLenDivisibleSubset(index-1,ArrList,Arr,MaxArr);
        //auto itr = find(ArrList.begin(),ArrList.end(),Arr[index]);
        //ArrList.erase(itr);
    }

    return max(take,not_take);


}

int main()
{
    vector<int> Arr = {0,19,1,13,16,7,8,4};
    int n = Arr.size();
    vector<int> ArrList = {};
    vector<int> MaxArr = {};
    int ans = maxLenDivisibleSubset(n-1,ArrList,Arr,MaxArr);

    cout << "Max Len Divisible Subset = " << ans << endl;
    cout << "Subset Is -- >";
    print_1D_v(MaxArr);
    return 0;
}
