#include <iostream>
#include <algorithm>

using namespace std;

bool IsSame(string s1,string s2,int i,int j)
{
    if(j<0 && i>=0)
    {
        for(int idx=i;idx>=0;idx--)
        {
            if(s1[idx]=='*')
                continue;
            else
                return false;
        }
    }
    if(i<0 && j<0)
    {
        return true;
    }
    if(i<0 && j>=0)
        return false;

    if(s1[i]==s2[j]||s1[i]=='?')
    {
        return IsSame(s1,s2,i-1,j-1);
    }
    else
    {
        if(s1[i]=='*')
        {
            return IsSame(s1,s2,i-1,j) || IsSame(s1,s2,i,j-1);
            /*
            char prev_ch = ' ';
            if(i>=1)
            prev_ch = s1[i-1];
            cout << "prev_ch=" << prev_ch << endl;
            cout << "Old J=" << j << endl;
            while(j>=0 && s2[j]!=prev_ch)
            {
                j--;
            }
            cout << "New J=" << j << endl;
            return IsSame(s1,s2,i-1,j);*/

        }
        else
        {
            return false;
        }
    }
}

int main()
{
    string s1 = "**ef",s2="abcdef";
    int m = s1.size(),n=s2.size();
    bool ans = IsSame(s1,s2,m-1,n-1);
    cout << "Are s1=" << s1 << " s2=" << s2 << " Same =" << ans << endl;
    return 0;
}
