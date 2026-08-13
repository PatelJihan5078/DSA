class Solution {
public:

    struct Node {
        char leftChar;
        char rightChar;

        int len;
        int prefix;
        int suffix;
        int best;

        Node() {
            leftChar = '#';
            rightChar = '#';
            len = 0;
            prefix = 0;
            suffix = 0;
            best = 0;
        }
    };

    vector<Node> tree;

    Node merge(Node a, Node b) {

        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;

        res.len = a.len + b.len;

        res.leftChar = a.leftChar;
        res.rightChar = b.rightChar;

        res.prefix = a.prefix;
        res.suffix = b.suffix;

        res.best = max(a.best, b.best);

        // The two middle characters are equal
        if (a.rightChar == b.leftChar) {

            // A repeating sequence crosses the boundary
            res.best = max(res.best, a.suffix + b.prefix);

            // Entire left segment has one character
            if (a.prefix == a.len) {
                res.prefix = a.len + b.prefix;
            }

            // Entire right segment has one character
            if (b.suffix == b.len) {
                res.suffix = a.suffix + b.len;
            }
        }

        return res;
    }

    void build(string &s, int node, int l, int r) {

        if (l == r) {
            tree[node].leftChar = s[l];
            tree[node].rightChar = s[l];

            tree[node].len = 1;
            tree[node].prefix = 1;
            tree[node].suffix = 1;
            tree[node].best = 1;

            return;
        }

        int mid = (l + r) / 2;

        build(s, node * 2, l, mid);
        build(s, node * 2 + 1, mid + 1, r);

        tree[node] = merge(tree[node * 2],
                           tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int pos, char c) {

        if (l == r) {

            tree[node].leftChar = c;
            tree[node].rightChar = c;

            tree[node].len = 1;
            tree[node].prefix = 1;
            tree[node].suffix = 1;
            tree[node].best = 1;

            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid) {
            update(node * 2, l, mid, pos, c);
        }
        else {
            update(node * 2 + 1, mid + 1, r, pos, c);
        }

        tree[node] = merge(tree[node * 2],
                           tree[node * 2 + 1]);
    }

    vector<int> longestRepeating(
        string s,
        string queryCharacters,
        vector<int>& queryIndices
    ) {

        int n = s.size();

        tree.resize(4 * n);

        build(s, 1, 0, n - 1);

        vector<int> ans;

        for (int i = 0; i < queryCharacters.size(); i++) {

            update(
                1,
                0,
                n - 1,
                queryIndices[i],
                queryCharacters[i]
            );

            ans.push_back(tree[1].best);
        }

        return ans;
    }
};