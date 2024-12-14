#include <iostream>
#include <vector>

using namespace std;

/*
if arr = {1,3,5,4,7,6}

Here we need LIS Dp[] and cnt[]
cnt[] will be initially set to 1 since minimum LIS is possible with value itself same as dp[i] = 1

We start from index = 1;
ArrList[index]>ArrList[prev] && dp[index]<1+dp[prev]
ArrList[1]>ArrList[0] && dp[1]<1+dp[0]
dp[1] = 2
cnt[1] = 1;

At i=2
ArrList[index]>ArrList[prev] && dp[index]<1+dp[prev]
ArrList[2]>ArrList[1] && dp[2]<1+dp[1]
dp[2] = 3
cnt[2] = 1;

At i=3
ArrList[index]>ArrList[prev] && dp[index]<1+dp[prev]
ArrList[3]>ArrList[2] && dp[3]<1+dp[2] --> False
ArrList[3]>ArrList[1] && dp[3]<1+dp[1] --> True
dp[3] = 3
cnt[3] = 1;

At i=4
ArrList[index]>ArrList[prev] && dp[index]<1+dp[prev]
ArrList[4]>ArrList[3] && dp[4]<1+dp[3] --> True
dp[4] = 4
cnt[4] = 1
ArrList[4]>ArrList[2] && dp[4]<1+dp[2] --> False
else  dp[4] == 1+dp[2]  --> True
Hence
dp[4] = 4
cnt[4] = 2;

At i=5
ArrList[index]>ArrList[prev] && dp[index]<1+dp[prev]
ArrList[5]>ArrList[4] && dp[5]<1+dp[4] --> False
ArrList[4]>ArrList[3] && dp[4]<1+dp[3] --> True
dp[5] = r
cnt[5] = 1
ArrList[4]>ArrList[2] && dp[4]<1+dp[2] --> False
else    dp[5] == 1+dp[2]  --> True
Hence
dp[5] = 4
cnt[5] = 2;


Hence
 dp[] = {1,2,3,3,4,4}
cnt[] = {1,1,1,1,2,2}

Max_len = 4
For all dp[i] == maxlen
    sum(cnt[i])
Hence Ans = 4


*/
void print_1D_Int(vector<int>& V)
{
    for(auto d:V)
        cout << d << " ";
    cout << endl;
}
int countLIS(vector<int>& ArrList)
{
    int n = ArrList.size();
    vector<int> dp(n,1),cnt(n,1);

    int max_len = -1;
    for(int index=1;index<n;index++)
    {
        for(int prev=index-1;prev>=0;prev--)
        {
            if(ArrList[index]>ArrList[prev] && dp[index]<1+dp[prev])
            {
                dp[index] = 1 + dp[prev];
                cnt[index] = cnt[prev];
            }
            else if(ArrList[index]>ArrList[prev] && dp[index]==1+dp[prev])
            {
                cnt[index] = cnt[index]+cnt[prev];
            }
        }
        max_len = max(max_len,dp[index]);
    }

    cout << "max_len =" << max_len << endl;
    print_1D_Int(dp);
    print_1D_Int(cnt);
    // max_len  is the maximum length of LIS
    int no_of_lis = 0;
    for(int index=0;index<n;index++)
    {
        if(dp[index]==max_len)
        {
            no_of_lis += cnt[index];
        }
    }
    cout << "no_of_lis =" << no_of_lis << endl;
    return no_of_lis;
}

int main()
{
    vector<int> ArrList = {1,3,5,4,7,6};
    int no_of_lis = countLIS(ArrList);

    cout << "Number of LIS Possible =" << no_of_lis << endl;
    return 0;
}
