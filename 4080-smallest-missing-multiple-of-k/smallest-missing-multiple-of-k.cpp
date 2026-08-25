class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        unordered_set<int> num_set(nums.begin(), nums.end());
        int multiple = k;
        
        while (num_set.count(multiple)) {
            multiple += k;
        }
        
        return multiple;
    }
};