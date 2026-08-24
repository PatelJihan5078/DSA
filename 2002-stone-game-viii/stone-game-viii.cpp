class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        int n = stones.size();
        vector<int> P(n);
        P[0] = stones[0];
        for (int i = 1; i < n; i++)
            P[i] = P[i-1] + stones[i];

        int dp = P[n-1];
        for (int i = n-2; i >= 1; i--)
            dp = max(dp, P[i] - dp);

        return dp;
    }
};