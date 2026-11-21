#include <iostream>
#include <vector>
using namespace std;

// LeetCode defines this globally (not inside Solution), so do the same here.
struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {
    }

    ListNode(int x) : val(x), next(nullptr) {
    }

    ListNode(int x, ListNode *next) : val(x), next(next) {
    }
};

// ---------- Your solution (paste into LeetCode from here) ----------
class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode *ans = new ListNode();
        ListNode *_ans = ans;
        bool carry = false;

        while (l1 != NULL && l2 != NULL) {
            int add = (carry) ? (l1->val + l2->val + 1) : (l1->val + l2->val);
            ans->val = add % 10;
            carry = 10 <= add;

            if (l1->next || l2->next) {
                ans->next = new ListNode();
                ans = ans->next;
            }

            l1 = l1->next;
            l2 = l2->next;
        }

        while (l1 != NULL) {
            int add = (carry) ? (l1->val + 1) : (l1->val);
            ans->val = add % 10;
            carry = 10 <= add;
            if (carry && l1->next) {
                ans->next = new ListNode();
            } else {
                break;
            }
            ans = ans->next;
            l1 = l1->next;
        }

        while (l2 != NULL) {
            int add = (carry) ? (l2->val + 1) : (l2->val);
            ans->val = add % 10;
            carry = 10 <= add;
            if (carry && l2->next) {
                ans->next = new ListNode();
            } else {
                break;
            }
            ans = ans->next;
            l2 = l2->next;
        }

        if (carry) {
            ans->next = new ListNode(1);
        } else if (l1) {
            ans->next = l1->next;
        } else if (l2) {
            ans->next = l2->next;
        }

        return _ans;
    }
};

ListNode *build(const vector<int> &v) {
    ListNode dummy;
    ListNode *cur = &dummy;
    for (int x: v) cur = cur->next = new ListNode(x);
    return dummy.next;
}

vector<int> toVector(ListNode *head) {
    vector<int> out;
    for (; head; head = head->next) out.push_back(head->val);
    return out;
}

void freeList(ListNode *head) {
    while (head) {
        ListNode *next = head->next;
        delete head;
        head = next;
    }
}

string str(const vector<int> &v) {
    string s = "[";
    for (size_t i = 0; i < v.size(); ++i) s += (i ? "," : "") + to_string(v[i]);
    return s + "]";
}

int main() {
    struct Case {
        vector<int> a, b, want;
    };
    vector<Case> cases = {
       {{2, 4, 3}, {5, 6, 4}, {7, 0, 8}}, // 342 + 465 = 807
       {{9, 9, 9, 9, 9, 9, 9}, {9, 9, 9, 9}, {8, 9, 9, 9, 0, 0, 0, 1}},
        {{5}, {5}, {0, 1}}
    };

    int failed = 0;
    for (auto &c: cases) {
        ListNode *l1 = build(c.a), *l2 = build(c.b);
        ListNode *res = Solution().addTwoNumbers(l1, l2);
        vector<int> got = toVector(res);
        bool ok = got == c.want;
        failed += !ok;
        cout << (ok ? "[PASS] " : "[FAIL] ") << str(c.a) << " + " << str(c.b)
                << " -> got " << str(got) << ", want " << str(c.want) << '\n';
        freeList(l1);
        freeList(l2);
        freeList(res);
    }
    cout << (failed ? to_string(failed) + " failed\n" : "All passed\n");
    return failed;
}
