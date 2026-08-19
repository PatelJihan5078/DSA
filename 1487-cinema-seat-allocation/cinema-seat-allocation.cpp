class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> mp;

        // Store reserved seats using a bitmask for each row
        for (auto &seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            // Only seats 2 to 9 affect the answer
            if (col >= 2 && col <= 9) {
                mp[row] |= (1 << col);
            }
        }

        long long ans = 2LL * (n - mp.size());

        // Masks for the three possible groups
        int left  = (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5);
        int middle = (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
        int right = (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9);

        for (auto &[row, mask] : mp) {
            bool canLeft = (mask & left) == 0;
            bool canMiddle = (mask & middle) == 0;
            bool canRight = (mask & right) == 0;

            if (canLeft && canRight) {
                // 2 groups: seats 2-5 and 6-9
                ans += 2;
            }
            else if (canLeft || canMiddle || canRight) {
                // At least one group can fit
                ans += 1;
            }
        }

        return (int)ans;
    }
};