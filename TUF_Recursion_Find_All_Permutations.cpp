#include <iostream>
#include <vector>
#include <map>

using namespace std;

/*
 The Result is n! =  n*(n-1)*(n-2)....1
*/
void print_v(vector<int> v)
{
    for(auto d:v)
    {
        cout << d << ",";
    }
    cout << endl;
}

void print_v_char(vector<char> v)
{
    for(auto d:v)
    {
        cout << d << ",";
    }
    cout << endl;
}
void AllPermutations(vector<int> ArrList,map<int,int> ArrMap,vector<int> arr)
{
    //cout << "-----------" << __FUNCTION__ << "-----------" << endl;
    int n = arr.size();
    int k = ArrList.size();
    if(n==k)
    {
        print_v(ArrList);
        return;
    }
    for(int i=0;i<n;i++)
    {
        int data = arr[i];
        auto itr = ArrMap.find(data);
        if(itr==ArrMap.end())
        {
            ArrList.push_back(data);
            //cout << "Pushing Data =" << data << endl;
            //cout << "Size of map =" << ArrMap.size() << endl;
            ArrMap[data]=1;
            AllPermutations(ArrList,ArrMap,arr);
            ArrMap.erase(data);
            //cout << "******** Recursion Back ***********" << endl;
            ArrList.pop_back();
        }
        else
        {
            //cout << "data present in Map data =" << data << endl;
        }
    }

}

void AllPermutationsForString(vector<char> ArrList,map<char,int> ArrMap,vector<char> arr)
{
    int n = arr.size();
    int k = ArrList.size();
    if(n==k)
    {
        print_v_char(ArrList);
        return;
    }
    for(int i=0;i<n;i++)
    {
        char data = arr[i];
        auto itr = ArrMap.find(data);
        if(itr==ArrMap.end())
        {
            ArrList.push_back(data);
            ArrMap[data]=1;
            AllPermutationsForString(ArrList,ArrMap,arr);
            ArrMap.erase(data);
            ArrList.pop_back();
        }
    }

}
int main()
{
    vector<int> arr = {1,2,3};
    vector<int> ArrList;
    map<int,int> ArrMap;

    cout << "All Possible Permutations :" << endl;
    AllPermutations(ArrList, ArrMap,arr);


    vector<char> char_arr = {'a','b','c','d'};
    vector<char> char_ArrList;
    map<char,int> char_ArrMap;

    cout << "All Possible Permutations :" << endl;
    AllPermutationsForString(char_ArrList, char_ArrMap,char_arr);
    return 0;
}
