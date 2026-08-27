class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.length();
        multiset<char> avail(s.begin(), s.end()); // sorted available chars
        string matched = "";  // prefix matched with target so far
        string result  = "";  // best answer found (later split = smaller)

        for (int i = 0; i < n; i++) {

            // ── Option 1: Go GREATER at position i ──────────────────────
            // Find smallest char strictly > target[i]
            auto it = avail.upper_bound(target[i]);
            if (it != avail.end()) {
                // Build: matched + *it + sorted(remaining chars)
                string cand = matched + *it;
                multiset<char> rest = avail;
                rest.erase(rest.find(*it));
                for (char c : rest) cand += c; // multiset is sorted → optimal suffix
                result = cand; // overwrite: later split always gives smaller result
            }

            // ── Option 2: Stay EQUAL at position i ──────────────────────
            // Use target[i] and continue to next position
            auto eq = avail.find(target[i]);
            if (eq != avail.end()) {
                matched += target[i];
                avail.erase(eq);
            } else {
                break; // can't match → no later split possible → stop
            }
        }

        return result;
    }
};