#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


/*
In Array 5,4,11,1,16,8 we have to find the longest increasing subsequence
Now create a dp[n] such that dp[i] signifies the LIS ending at index 'i'
For example dp[0] = 1 , we have LIS ending at value 5 i.e. 5 itself
Hence for all dp[i] the minimum value will be 1 because we will have LIS ending with current value itself
dp[1] means find the LIS ending at value 4, can we have {5,4}, Ans is No
dp[2] means find the LIS ending at value 11, can we have {5,11}, Ans is Yes
                                            can we have {4,11}, Ans is Yes
                                            can we have {5,4,11}, Ans is No
Hence Max Possible LIS length is 2 only. Therefore dp[2] = 2
dp[3] means find the LIS ending at value 1, can we have {5,1}, Ans is No
                                            can we have {4,1}, Ans is No
                                            can we have {11,1}, Ans is No

Hence Max Possible LIS length is 1 only. Therefore dp[3] = 1
dp[4] means find the LIS ending at value 16, can we have {5,16}, Ans is Yes , New dp[4] = 2
                                            can we have {4,16}, Ans is Yes , New dp[4] = 2
                                            can we have {11,16}, Ans is Yes , New dp[4] = 3
                                  since at 11 we know we can have 2 Subsequence ending at 11 and hence
                                  subsequence ending at 16 if 11 is included can be a maximum of 1+2 i.e. 3
Hence Max Possible LIS length is 3 only. Therefore dp[4] = 3


dp[5] means find the LIS ending at value 1, can we have {5,8}, Ans is Yes , New dp[4] = 2
                                            can we have {4,8}, Ans is Yes , New dp[4] = 2
                                            can we have {1,8}, Ans is Yes, New dp[4] = 2

Hence Max Possible LIS length is 2 only. Therefore dp[5] = 2
*/

void print_1D_v(vector<int>& dp)
{
    for(auto d:dp)
    {
        cout << d << "  ";
    }
    cout << endl;
}

int findMaxLIS(vector<int>& ArrList)
{
    int n = ArrList.size();
    vector<int> dp(n,1); // Min Length of LIS can be 1
    vector<int> Hash(n);
    for(int index=0;index<n;index++)
        Hash[index]=index;

    int max_len = -1;
    int max_idx = -1;
    for(int index=1;index<n;index++)
    {
        for(int prev=0;prev<index;prev++)
        {
            if(ArrList[prev]<ArrList[index])
            {
                if(dp[index]<1+dp[prev])
                {
                    Hash[index] = prev;
                    dp[index] = 1+dp[prev];
                }

            }

            if(max_len<dp[index])
            {
                max_idx = index;
                max_len = dp[index];
            }

        }
    }
    cout << "\nHash -->         ";
    print_1D_v(Hash);
    cout << "\nDp --->          ";
    print_1D_v(dp);

    // find max value index
    vector<int> Subsequence;
    int index = max_idx;
    Subsequence.push_back(ArrList[max_idx]);

    while(Hash[index]!=index)
    {
        index = Hash[index];
        Subsequence.push_back(ArrList[index]);
    }
    cout << "\n LIS Subsequence =   ";
    reverse(Subsequence.begin(),Subsequence.end());
    print_1D_v(Subsequence);
    return max_len;
}



int main()
{
    vector<int> ArrList ={5,4,11,1,16,8};

    int ans = findMaxLIS(ArrList);
    cout << "\nMax Length of LIS Possible =" << ans << endl;
    return 0;
}
