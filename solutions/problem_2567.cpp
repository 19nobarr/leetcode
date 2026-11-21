#include <algorithm>
#include <iostream>
#include <limits.h>
#include <vector>

using namespace std;

/**
 * 2567. Minimum Score by Changing Two Elements (Medium)
 * https://leetcode.com/problems/minimum-score-by-changing-two-elements/
 *
 * You are given an integer array nums.
 *
 *   - The low score of nums is the minimum absolute difference between any
 *     two integers.
 *   - The high score of nums is the maximum absolute difference between any
 *     two integers.
 *   - The score of nums is the sum of the high and low scores.
 *
 * Return the minimum score after changing two elements of nums.
 *
 * Example 1:
 *   Input:  nums = [1,4,7,8,5]
 *   Output: 3
 *   Explanation:
 *     - Change nums[0] and nums[1] to be 6 so that nums becomes [6,6,7,8,5].
 *     - The low score is the minimum absolute difference: |6 - 6| = 0.
 *     - The high score is the maximum absolute difference: |8 - 5| = 3.
 *     - The sum of high and low score is 3.
 *
 * Example 2:
 *   Input:  nums = [1,4,3]
 *   Output: 0
 *   Explanation:
 *     - Change nums[1] and nums[2] to 1 so that nums becomes [1,1,1].
 *     - The sum of maximum absolute difference and minimum absolute
 *       difference is 0.
 *
 * Constraints:
 *   - 3 <= nums.length <= 10^5
 *   - 1 <= num <= 10^9
 */
class Solution {
public:
    /**
     * This is the base solution which is about O(nlog(n)) time complexity and uses O(1) memory
     *
     * @param nums The input array
     * @return An integer which represents the optimal score based on the problem
     */
    int minimizeSum(vector<int> &nums) {
        // Check the invariant
        if (nums.size() < 3) return 0;

        // First, we sort the array
        sort(nums.begin(), nums.end());

        // We know that we can always make the closest pair = 0
        // So second, we just need to minimize the maximum
        return min(
            min(
                nums[size(nums) - 1] - nums[2],
                nums[size(nums) - 3] - nums[0]
            ),
            nums[size(nums) - 2] - nums[1]
        );
    }

    /**
     * This optimized solution has a runtime of O(n) and still a memory complexity of O(1)
     *
     * @param nums The input array
     * @return An integer which represents the optimal score based on the problem
     */
    int optimizedMinimizeSum(vector<int> &nums) {
        // Check the invariant
        if (nums.size() < 3) return 0;

        int s1 = INT_MAX;
        int s2 = INT_MAX;
        int s3 = INT_MAX;
        int l1 = 0;
        int l2 = 0;
        int l3 = 0;

        for (const auto num : nums) {

            // Search for smallest numbers
            if (num < s1) {
                s3 = s2;
                s2 = s1;
                s1 = num;
            } else if (num < s2) {
                s3 = s2;
                s2 = num;
            } else if (num < s3) {
                s3 = num;
            }

            // Search for largest numbers
            if (l1 < num) {
                l3 = l2;
                l2 = l1;
                l1 = num;
            } else if (l2 < num) {
                l3 = l2;
                l2 = num;
            } else if (l3 < num) {
                l3 = num;
            }
        }

        return min(min((l3-s1), (l2-s2)), (l1-s3));

    }
};

int main() {
    Solution s;
    vector<int> a = {1, 4, 7, 8, 5};
    vector<int> b = {1, 4, 3};

    cout << s.minimizeSum(a) << '\n'; // 3
    cout << s.minimizeSum(b) << '\n'; // 0

    cout << s.optimizedMinimizeSum(a) << '\n'; // 3
    cout << s.optimizedMinimizeSum(b) << '\n'; // 0

    return 0;
}
