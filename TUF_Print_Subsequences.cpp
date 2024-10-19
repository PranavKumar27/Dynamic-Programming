#include <iostream>
#include <vector>

using namespace std;

int cnt = 0 ;

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
void subsequences(int index,vector<int> ArrLst,vector<int> arr)
{
    int n = arr.size();
    if(index>=n)
    {
        print_v(ArrLst);
        cnt++;
        return;
    }

    ArrLst.push_back(arr[index]);
    subsequences(index+1,ArrLst,arr);
    ArrLst.pop_back();
    subsequences(index+1,ArrLst,arr);
}

/// TC =  O(2^n)*n for  for loop

/// SC = O(n) since depth of recursion tree is n
int main()
{
    vector<int> arr = {1,2,3};
    int n = arr.size();
    vector<int> ArrList;
    cout << "All the subsequences are as :" << endl;
    subsequences(0,ArrList,arr);
    cout << "Total Number of Subsequences =" << cnt << endl;

    return 0;
}
