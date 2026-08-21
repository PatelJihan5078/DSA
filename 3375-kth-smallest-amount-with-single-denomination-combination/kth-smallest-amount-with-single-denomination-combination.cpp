class Solution {
public:
    // Greatest common divisor
    long long gcd(long long a, long long b) {
        while (b) { a %= b; swap(a, b); }
        return a;
    }

    // Least common multiple, capped so it never overflows.
    // If it would grow bigger than our search range, we just return
    // a huge number (it means "this combo doesn't matter here").
    long long lcm(long long a, long long b, long long cap) {
        long long g = gcd(a, b);
        if (a / g > cap / b) return cap + 1; // signal "too big, ignore"
        return (a / g) * b;
    }

    // Count how many numbers in [1, x] are multiples of AT LEAST ONE coin.
    // We use inclusion-exclusion: for every subset of coins, add or
    // subtract x / lcm(subset) depending on how many coins are in the subset.
    long long countUpTo(long long x, vector<int>& coins) {
        int n = coins.size();
        long long total = 0;

        for (int mask = 1; mask < (1 << n); mask++) {
            long long l = 1;
            int bits = 0;
            bool tooBig = false;

            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    bits++;
                    l = lcm(l, coins[i], x);
                    if (l > x) { tooBig = true; break; }
                }
            }

            if (tooBig) continue;

            long long count = x / l;
            if (bits % 2 == 1) total += count;   // odd-size subset -> add
            else total -= count;                 // even-size subset -> subtract
        }

        return total;
    }

    long long findKthSmallest(vector<int>& coins, int k) {
        // Binary search the answer: smallest x such that
        // "number of makeable amounts <= x" is at least k.
        long long lo = 1, hi = (long long)(*min_element(coins.begin(), coins.end())) * k;

        while (lo < hi) {
            long long mid = lo + (hi - lo) / 2;
            if (countUpTo(mid, coins) >= k) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        return lo;
    }
};