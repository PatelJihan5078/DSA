class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();

        vector<int> suffix(n + 1, 0);

        for (int i = n - 1; i >= 0; i--)
            suffix[i] = suffix[i + 1] + piles[i];

        vector<vector<int>> dp(n, vector<int>(n + 1, -1));

        function<int(int, int)> solve = [&](int i, int M) {
            if (i == n)
                return 0;

            if (dp[i][M] != -1)
                return dp[i][M];

            int taken = 0;
            int ans = 0;

            for (int X = 1; X <= 2 * M && i + X <= n; X++) {
                taken += piles[i + X - 1];

                int opponent = solve(i + X, max(M, X));

                int current = taken + suffix[i + X] - opponent;

                ans = max(ans, current);
            }

            return dp[i][M] = ans;
        };

        return solve(0, 1);
    }
};