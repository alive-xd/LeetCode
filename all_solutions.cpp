#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Problem 0001 - Two Sum
// Difficulty : Easy
// Time       : O(n)
// Space      : O(n)
// ============================================================
class Solution1 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> seen;
        for (int i = 0; i < (int)nums.size(); i++) {
            int complement = target - nums[i];
            if (seen.count(complement))
                return {seen[complement], i};
            seen[nums[i]] = i;
        }
        return {};
    }
};

// ============================================================
// Problem 0002 - Add Two Numbers
// Difficulty : Medium
// Time       : O(max(m, n))
// Space      : O(max(m, n))
// ============================================================
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* n) : val(x), next(n) {}
};

class Solution2 {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* curr = &dummy;
        int carry = 0;
        while (l1 || l2 || carry) {
            int sum = carry;
            if (l1) { sum += l1->val; l1 = l1->next; }
            if (l2) { sum += l2->val; l2 = l2->next; }
            carry = sum / 10;
            curr->next = new ListNode(sum % 10);
            curr = curr->next;
        }
        return dummy.next;
    }
};

// ============================================================
// Problem 0003 - Longest Substring Without Repeating Characters
// Difficulty : Medium
// Time       : O(n)
// Space      : O(min(n, m))
// ============================================================
class Solution3 {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> last;
        int maxLen = 0, left = 0;
        for (int right = 0; right < (int)s.size(); right++) {
            if (last.count(s[right]) && last[s[right]] >= left)
                left = last[s[right]] + 1;
            last[s[right]] = right;
            maxLen = max(maxLen, right - left + 1);
        }
        return maxLen;
    }
};

// ============================================================
// Problem 0004 - Median of Two Sorted Arrays
// Difficulty : Hard
// Time       : O(log(min(m, n)))
// Space      : O(1)
// ============================================================
class Solution4 {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) swap(nums1, nums2);
        int m = nums1.size(), n = nums2.size();
        int lo = 0, hi = m;
        while (lo <= hi) {
            int px = (lo + hi) / 2;
            int py = (m + n + 1) / 2 - px;
            int maxLX = (px == 0) ? INT_MIN : nums1[px - 1];
            int minRX = (px == m) ? INT_MAX : nums1[px];
            int maxLY = (py == 0) ? INT_MIN : nums2[py - 1];
            int minRY = (py == n) ? INT_MAX : nums2[py];
            if (maxLX <= minRY && maxLY <= minRX) {
                if ((m + n) % 2 == 0)
                    return (max(maxLX, maxLY) + min(minRX, minRY)) / 2.0;
                return max(maxLX, maxLY);
            } else if (maxLX > minRY) hi = px - 1;
            else lo = px + 1;
        }
        return 0.0;
    }
};

// ============================================================
// Problem 0005 - Longest Palindromic Substring
// Difficulty : Medium
// Time       : O(n^2)
// Space      : O(1)
// ============================================================
class Solution5 {
public:
    string longestPalindrome(string s) {
        int start = 0, maxLen = 1;
        auto expand = [&](int l, int r) {
            while (l >= 0 && r < (int)s.size() && s[l] == s[r]) { l--; r++; }
            if (r - l - 1 > maxLen) { maxLen = r - l - 1; start = l + 1; }
        };
        for (int i = 0; i < (int)s.size(); i++) {
            expand(i, i);
            expand(i, i + 1);
        }
        return s.substr(start, maxLen);
    }
};

// ============================================================
// Problem 0006 - Zigzag Conversion
// Difficulty : Medium
// Time       : O(n)
// Space      : O(n)
// ============================================================
class Solution6 {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;
        vector<string> rows(numRows);
        int row = 0, dir = -1;
        for (char c : s) {
            rows[row] += c;
            if (row == 0 || row == numRows - 1) dir = -dir;
            row += dir;
        }
        string result;
        for (auto& r : rows) result += r;
        return result;
    }
};

// ============================================================
// Problem 0007 - Reverse Integer
// Difficulty : Medium
// Time       : O(log x)
// Space      : O(1)
// ============================================================
class Solution7 {
public:
    int reverse(int x) {
        int result = 0;
        while (x != 0) {
            int digit = x % 10;
            x /= 10;
            if (result > INT_MAX / 10 || result < INT_MIN / 10) return 0;
            result = result * 10 + digit;
        }
        return result;
    }
};

// ============================================================
// Problem 0008 - String to Integer (atoi)
// Difficulty : Medium
// Time       : O(n)
// Space      : O(1)
// ============================================================
class Solution8 {
public:
    int myAtoi(string s) {
        int i = 0, sign = 1;
        long result = 0;
        while (i < (int)s.size() && s[i] == ' ') i++;
        if (i < (int)s.size() && (s[i] == '-' || s[i] == '+'))
            sign = (s[i++] == '-') ? -1 : 1;
        while (i < (int)s.size() && isdigit(s[i])) {
            result = result * 10 + (s[i++] - '0');
            if (result * sign > INT_MAX) return INT_MAX;
            if (result * sign < INT_MIN) return INT_MIN;
        }
        return (int)(result * sign);
    }
};

// ============================================================
// Problem 0009 - Palindrome Number
// Difficulty : Easy
// Time       : O(log x)
// Space      : O(1)
// ============================================================
class Solution9 {
public:
    bool isPalindrome(int x) {
        if (x < 0 || (x % 10 == 0 && x != 0)) return false;
        int reversed = 0;
        while (x > reversed) {
            reversed = reversed * 10 + x % 10;
            x /= 10;
        }
        return x == reversed || x == reversed / 10;
    }
};

// ============================================================
// Problem 0010 - Regular Expression Matching
// Difficulty : Hard
// Time       : O(m * n)
// Space      : O(m * n)
// ============================================================
class Solution10 {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp[0][0] = true;
        for (int j = 2; j <= n; j++)
            if (p[j - 1] == '*') dp[0][j] = dp[0][j - 2];
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j - 1] == '*') {
                    dp[i][j] = dp[i][j - 2] ||
                        ((p[j - 2] == '.' || p[j - 2] == s[i - 1]) && dp[i - 1][j]);
                } else if (p[j - 1] == '.' || p[j - 1] == s[i - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }
        return dp[m][n];
    }
};

// ============================================================
// Problem 0011 - Container With Most Water
// Difficulty : Medium
// Time       : O(n)
// Space      : O(1)
// ============================================================
class Solution11 {
public:
    int maxArea(vector<int>& height) {
        int left = 0, right = (int)height.size() - 1, maxWater = 0;
        while (left < right) {
            maxWater = max(maxWater, min(height[left], height[right]) * (right - left));
            if (height[left] < height[right]) left++;
            else right--;
        }
        return maxWater;
    }
};

// ============================================================
// Problem 0012 - Integer to Roman
// Difficulty : Medium
// Time       : O(1)
// Space      : O(1)
// ============================================================
class Solution12 {
public:
    string intToRoman(int num) {
        vector<pair<int, string>> table = {
            {1000,"M"},{900,"CM"},{500,"D"},{400,"CD"},
            {100,"C"},{90,"XC"},{50,"L"},{40,"XL"},
            {10,"X"},{9,"IX"},{5,"V"},{4,"IV"},{1,"I"}
        };
        string result;
        for (auto& [val, sym] : table)
            while (num >= val) { result += sym; num -= val; }
        return result;
    }
};

// ============================================================
// Problem 0013 - Roman to Integer
// Difficulty : Easy
// Time       : O(n)
// Space      : O(1)
// ============================================================
class Solution13 {
public:
    int romanToInt(string s) {
        unordered_map<char, int> val = {
            {'I',1},{'V',5},{'X',10},{'L',50},
            {'C',100},{'D',500},{'M',1000}
        };
        int result = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            if (i + 1 < (int)s.size() && val[s[i]] < val[s[i + 1]])
                result -= val[s[i]];
            else
                result += val[s[i]];
        }
        return result;
    }
};

// ============================================================
// Problem 0014 - Longest Common Prefix
// Difficulty : Easy
// Time       : O(n * m)
// Space      : O(1)
// ============================================================
class Solution14 {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string prefix = strs[0];
        for (int i = 1; i < (int)strs.size(); i++)
            while (strs[i].find(prefix) != 0)
                prefix = prefix.substr(0, prefix.size() - 1);
        return prefix;
    }
};

// ============================================================
// Problem 0015 - 3Sum
// Difficulty : Medium
// Time       : O(n^2)
// Space      : O(1)
// ============================================================
class Solution15 {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        for (int i = 0; i < (int)nums.size() - 2; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            int left = i + 1, right = (int)nums.size() - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum == 0) {
                    result.push_back({nums[i], nums[left], nums[right]});
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    left++; right--;
                } else if (sum < 0) left++;
                else right--;
            }
        }
        return result;
    }
};

// ============================================================
// Problem 0016 - 3Sum Closest
// Difficulty : Medium
// Time       : O(n^2)
// Space      : O(1)
// ============================================================
class Solution16 {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int closest = nums[0] + nums[1] + nums[2];
        for (int i = 0; i < (int)nums.size() - 2; i++) {
            int left = i + 1, right = (int)nums.size() - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (abs(sum - target) < abs(closest - target)) closest = sum;
                if (sum < target) left++;
                else if (sum > target) right--;
                else return sum;
            }
        }
        return closest;
    }
};

// ============================================================
// Problem 0017 - Letter Combinations of a Phone Number
// Difficulty : Medium
// Time       : O(4^n * n)
// Space      : O(n)
// ============================================================
class Solution17 {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        unordered_map<char, string> phone = {
            {'2',"abc"},{'3',"def"},{'4',"ghi"},{'5',"jkl"},
            {'6',"mno"},{'7',"pqrs"},{'8',"tuv"},{'9',"wxyz"}
        };
        vector<string> result;
        string current;
        function<void(int)> backtrack = [&](int index) {
            if (index == (int)digits.size()) { result.push_back(current); return; }
            for (char c : phone[digits[index]]) {
                current.push_back(c);
                backtrack(index + 1);
                current.pop_back();
            }
        };
        backtrack(0);
        return result;
    }
};

// ============================================================
// Problem 0018 - 4Sum
// Difficulty : Medium
// Time       : O(n^3)
// Space      : O(1)
// ============================================================
class Solution18 {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        int n = nums.size();
        for (int i = 0; i < n - 3; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < n - 2; j++) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;
                int left = j + 1, right = n - 1;
                while (left < right) {
                    long long sum = (long long)nums[i] + nums[j] + nums[left] + nums[right];
                    if (sum == target) {
                        result.push_back({nums[i], nums[j], nums[left], nums[right]});
                        while (left < right && nums[left] == nums[left + 1]) left++;
                        while (left < right && nums[right] == nums[right - 1]) right--;
                        left++; right--;
                    } else if (sum < target) left++;
                    else right--;
                }
            }
        }
        return result;
    }
};

// ============================================================
// Problem 0019 - Remove Nth Node From End of List
// Difficulty : Medium
// Time       : O(n)
// Space      : O(1)
// ============================================================
class Solution19 {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0, head);
        ListNode* fast = &dummy;
        ListNode* slow = &dummy;
        for (int i = 0; i <= n; i++) fast = fast->next;
        while (fast) { fast = fast->next; slow = slow->next; }
        ListNode* toDelete = slow->next;
        slow->next = slow->next->next;
        delete toDelete;
        return dummy.next;
    }
};

// ============================================================
// Problem 0020 - Valid Parentheses
// Difficulty : Easy
// Time       : O(n)
// Space      : O(n)
// ============================================================
class Solution20 {
public:
    bool isValid(string s) {
        stack<char> st;
        unordered_map<char, char> match = {{')', '('}, {']', '['}, {'}', '{'}};
        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') {
                st.push(c);
            } else {
                if (st.empty() || st.top() != match[c]) return false;
                st.pop();
            }
        }
        return st.empty();
    }
};
