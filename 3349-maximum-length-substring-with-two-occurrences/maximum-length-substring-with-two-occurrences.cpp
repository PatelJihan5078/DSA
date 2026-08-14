class Solution {
public:
    int maximumLengthSubstring(string s) {

        int count[26] = {0};

        int left = 0;
        int ans = 0;

        for (int right = 0; right < s.size(); right++) {

            count[s[right] - 'a']++;

            // If any character occurs more than 2 times
            while (count[s[right] - 'a'] > 2) {
                count[s[left] - 'a']--;
                left++;
            }

            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};