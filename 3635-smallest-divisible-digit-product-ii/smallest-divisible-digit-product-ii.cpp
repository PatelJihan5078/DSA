class Solution {
public:
    // FACTOR[d][p] = exponent of prime p in digit d, for p in {2,3,5,7}
    array<array<int,8>,10> FACTOR{};

    void initFactor() {
        for (auto &row : FACTOR) row.fill(0);
        FACTOR[2][2] = 1;
        FACTOR[3][3] = 1;
        FACTOR[4][2] = 2;
        FACTOR[5][5] = 1;
        FACTOR[6][2] = 1; FACTOR[6][3] = 1;
        FACTOR[7][7] = 1;
        FACTOR[8][2] = 3;
        FACTOR[9][3] = 2;
    }

    using PrimeCnt = array<long long,8>;   // indexed by prime 2,3,5,7
    using FactorCnt = array<int,10>;       // indexed by digit 2..9

    static PrimeCnt subP(const PrimeCnt &a, const PrimeCnt &b) {
        PrimeCnt res = a;
        for (int p : {2,3,5,7}) res[p] = max((long long)0, res[p] - b[p]);
        return res;
    }

    static bool isSubset(const PrimeCnt &need, const PrimeCnt &have) {
        for (int p : {2,3,5,7}) if (have[p] < need[p]) return false;
        return true;
    }

    static int sumF(const FactorCnt &fc) {
        int s = 0;
        for (int d = 2; d <= 9; ++d) s += fc[d];
        return s;
    }

    PrimeCnt digitToPrime(int d) {
        PrimeCnt res{};
        for (int p : {2,3,5,7}) res[p] = FACTOR[d][p];
        return res;
    }

    PrimeCnt primeCountOfT(long long t, bool &ok) {
        PrimeCnt cnt{};
        for (int p : {2,3,5,7}) {
            while (t % p == 0) { t /= p; cnt[p]++; }
        }
        ok = (t == 1);
        return cnt;
    }

    PrimeCnt primeCountFromStr(const string &s) {
        PrimeCnt cnt{};
        for (char ch : s) {
            int d = ch - '0';
            for (int p : {2,3,5,7}) cnt[p] += FACTOR[d][p];
        }
        return cnt;
    }

    // Canonical shortest digit-count representation of required prime exponents
    // (ties broken toward the smaller resulting number).
    FactorCnt factorCount(const PrimeCnt &cnt) {
        long long c2 = cnt[2], c3 = cnt[3], c5 = cnt[5], c7 = cnt[7];
        long long n8 = c2 / 3, r2 = c2 % 3;
        long long n9 = c3 / 2, n3 = c3 % 2;
        long long n4 = r2 / 2, n2 = r2 % 2;
        long long n6 = 0;
        if (n2 == 1 && n3 == 1) { n2 = 0; n3 = 0; n6 = 1; }
        if (n3 == 1 && n4 == 1) { n2 = 1; n6 = 1; n3 = 0; n4 = 0; }
        FactorCnt fc{};
        fc[2] = (int)n2; fc[3] = (int)n3; fc[4] = (int)n4; fc[5] = (int)c5;
        fc[6] = (int)n6; fc[7] = (int)c7; fc[8] = (int)n8; fc[9] = (int)n9;
        return fc;
    }

    string construct(const FactorCnt &fc) {
        string res;
        for (int d = 2; d <= 9; ++d) res.append(fc[d], char('0' + d));
        return res;
    }

    string smallestNumber(string num, long long t) {
        initFactor();

        bool ok;
        PrimeCnt primeCount = primeCountOfT(t, ok);
        if (!ok) return "-1";

        FactorCnt fc0 = factorCount(primeCount);
        int n = (int)num.size();
        if (sumF(fc0) > n) {
            return construct(fc0);
        }

        PrimeCnt prefix = primeCountFromStr(num);
        int firstZero;
        size_t zpos = num.find('0');
        if (zpos != string::npos) {
            firstZero = (int)zpos;
        } else {
            firstZero = n;
            if (isSubset(primeCount, prefix)) return num;
        }

        for (int i = n - 1; i >= 0; --i) {
            int d = num[i] - '0';
            prefix = subP(prefix, digitToPrime(d));   // prefix = factors of num[:i]
            int space = n - 1 - i;
            if (i > firstZero) continue;              // can't leave an earlier '0' unfixed
            for (int big = d + 1; big <= 9; ++big) {
                PrimeCnt diff = subP(primeCount, prefix);
                PrimeCnt need = subP(diff, digitToPrime(big));
                FactorCnt fc = factorCount(need);
                int s = sumF(fc);
                if (s <= space) {
                    int ones = space - s;
                    return num.substr(0, i) + char('0' + big) + string(ones, '1') + construct(fc);
                }
            }
        }

        FactorCnt fcE = factorCount(primeCount);
        return string(n + 1 - sumF(fcE), '1') + construct(fcE);
    }
};