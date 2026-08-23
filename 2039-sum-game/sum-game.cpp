class Solution {
public:
    bool sumGame(string num) {
        int n = num.size();
        int left = 0, right = 0;
        int lq = 0, rq = 0;

        for (int i = 0; i < n / 2; i++) {
            if (num[i] == '?')
                lq++;
            else
                left += num[i] - '0';
        }

        for (int i = n / 2; i < n; i++) {
            if (num[i] == '?')
                rq++;
            else
                right += num[i] - '0';
        }

        int diff = left - right;
        int qdiff = lq - rq;

        if (qdiff % 2 != 0)
            return true;

        diff += (qdiff / 2) * 9;

        return diff != 0;
    }
};