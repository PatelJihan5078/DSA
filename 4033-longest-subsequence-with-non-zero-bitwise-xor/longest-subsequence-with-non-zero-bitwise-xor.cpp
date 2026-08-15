class Solution {
public:
    int longestSubsequence(vector<int>& nums) {

        int x = 0;
        bool hasNonZero = false;

        for (int num : nums) {
            x ^= num;

            if (num != 0)
                hasNonZero = true;
        }

        // Total XOR is already non-zero
        if (x != 0)
            return nums.size();

        // Total XOR is zero, but we have a non-zero number
        if (hasNonZero)
            return nums.size() - 1;

        // All numbers are zero
        return 0;
    }
};