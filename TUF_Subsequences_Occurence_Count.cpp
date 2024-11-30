#include <iostream>
#include <vector>

using namespace std;

int countSubsequence(string s1,string s2)
{
    int m = s1.size(),n=s2.length();
    if(n==0)
    {
        // String s2 is exhausted and Matched with s1
        return 1;
    }

    if(m<n)
    {
        // String s1 is exhausted and no need to search s2 now
        //cout << " m<n " << " s1 =" << s1 << " s2=" << s2 << endl;
        return 0;
    }

    int not_take = 0;
    if(m>=1)
        not_take = countSubsequence(s1.substr(0,m-1),s2);

    int take = 0;
    if( m>=1 && n>=1 && s1[m-1]==s2[n-1])
    {
        take = countSubsequence(s1.substr(0,m-1),s2.substr(0,n-1));
    }

    return take+not_take;
}

int countSubsequence(string s1,string s2,int index1,int index2)
{
    //cout << "s1 =" << s1 << " s2=" << s2 << endl;

    if(index2<0)
    {
        //cout << " n== 0 " << " s1 =" << s1 << " s2=" << s2 << endl;
        return 1;
    }

    if(index1<0)
    {
        return 0;
    }

    if( s1[index1]==s2[index2])
    {
        return countSubsequence(s1,s2,index1-1,index2-1) + countSubsequence(s1,s2,index1-1,index2);
    }
    else
    {
        return countSubsequence(s1,s2,index1-1,index2);
    }
}

int main()
{
    string s1 = "babgbag",s2="bag";
    int m = s1.size(),n=s2.length();
    int ans = countSubsequence(s1,s2,m-1,n-1);
    cout << "count of Subsequence Occurence Using Indexes = " << ans << endl;
    ans = countSubsequence(s1,s2);
    cout << "count of Subsequence Occurence Using String= " << ans << endl;
    return 0;
}
