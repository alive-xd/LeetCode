# LeetCode C++ Solutions

Structured C++ solutions for LeetCode problems 1–700, organized problem-wise for clarity, consistency, and quick reference.

---

## Key Features

- Solutions organized strictly by problem number
- Optimized approaches with attention to time and space complexity
- Consistent file and code structure across all problems
- Self-contained problem folders for easy navigation and isolation

---

## Folder Structure

```
leetcode-cpp/
│
├── README.md
│
├── problems/
│   ├── 0001-two-sum/
│   │   ├── solution.cpp
│   │   └── README.md
│   ├── 0002-add-two-numbers/
│   │   ├── solution.cpp
│   │   └── README.md
│   └── ...
│
└── scripts/
    └── scaffold.sh
```

---

## Problems Index

| Number | Problem | Difficulty | LeetCode |
|--------|---------|------------|----------|
| 0001 | Two Sum | Easy | [Link](https://leetcode.com/problems/two-sum/) |
| 0002 | Add Two Numbers | Medium | [Link](https://leetcode.com/problems/add-two-numbers/) |
| 0003 | Longest Substring Without Repeating Characters | Medium | [Link](https://leetcode.com/problems/longest-substring-without-repeating-characters/) |
| 0004 | Median of Two Sorted Arrays | Hard | [Link](https://leetcode.com/problems/median-of-two-sorted-arrays/) |
| 0005 | Longest Palindromic Substring | Medium | [Link](https://leetcode.com/problems/longest-palindromic-substring/) |
| 0006 | Zigzag Conversion | Medium | [Link](https://leetcode.com/problems/zigzag-conversion/) |
| 0007 | Reverse Integer | Medium | [Link](https://leetcode.com/problems/reverse-integer/) |
| 0008 | String to Integer (atoi) | Medium | [Link](https://leetcode.com/problems/string-to-integer-atoi/) |
| 0009 | Palindrome Number | Easy | [Link](https://leetcode.com/problems/palindrome-number/) |
| 0010 | Regular Expression Matching | Hard | [Link](https://leetcode.com/problems/regular-expression-matching/) |
| 0011 | Container With Most Water | Medium | [Link](https://leetcode.com/problems/container-with-most-water/) |
| 0012 | Integer to Roman | Medium | [Link](https://leetcode.com/problems/integer-to-roman/) |
| 0013 | Roman to Integer | Easy | [Link](https://leetcode.com/problems/roman-to-integer/) |
| 0014 | Longest Common Prefix | Easy | [Link](https://leetcode.com/problems/longest-common-prefix/) |
| 0015 | 3Sum | Medium | [Link](https://leetcode.com/problems/3sum/) |
| 0016 | 3Sum Closest | Medium | [Link](https://leetcode.com/problems/3sum-closest/) |
| 0017 | Letter Combinations of a Phone Number | Medium | [Link](https://leetcode.com/problems/letter-combinations-of-a-phone-number/) |
| 0018 | 4Sum | Medium | [Link](https://leetcode.com/problems/4sum/) |
| 0019 | Remove Nth Node From End of List | Medium | [Link](https://leetcode.com/problems/remove-nth-node-from-end-of-list/) |
| 0020 | Valid Parentheses | Easy | [Link](https://leetcode.com/problems/valid-parentheses/) |

---

## Solutions

---

### 0001 - Two Sum

**Difficulty:** Easy
**Time:** O(n) | **Space:** O(n)
**Approach:** Single-pass hash map. For each element, check if its complement already exists in the map.

```cpp
// Problem    : 0001 - Two Sum
// Difficulty : Easy
// Time       : O(n)
// Space      : O(n)

class Solution {
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
```

---

### 0002 - Add Two Numbers

**Difficulty:** Medium
**Time:** O(max(m, n)) | **Space:** O(max(m, n))
**Approach:** Traverse both linked lists simultaneously, carry the overflow digit forward.

```cpp
// Problem    : 0002 - Add Two Numbers
// Difficulty : Medium
// Time       : O(max(m, n))
// Space      : O(max(m, n))

class Solution {
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
```

---

### 0003 - Longest Substring Without Repeating Characters

**Difficulty:** Medium
**Time:** O(n) | **Space:** O(min(n, m))
**Approach:** Sliding window with a hash map tracking the last seen index of each character.

```cpp
// Problem    : 0003 - Longest Substring Without Repeating Characters
// Difficulty : Medium
// Time       : O(n)
// Space      : O(min(n, m))

class Solution {
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
```

---

### 0004 - Median of Two Sorted Arrays

**Difficulty:** Hard
**Time:** O(log(min(m, n))) | **Space:** O(1)
**Approach:** Binary search on the smaller array to find the correct partition point.

```cpp
// Problem    : 0004 - Median of Two Sorted Arrays
// Difficulty : Hard
// Time       : O(log(min(m, n)))
// Space      : O(1)

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) swap(nums1, nums2);
        int m = nums1.size(), n = nums2.size();
        int lo = 0, hi = m;
        while (lo <= hi) {
            int px = (lo + hi) / 2;
            int py = (m + n + 1) / 2 - px;
            int maxLeftX  = (px == 0) ? INT_MIN : nums1[px - 1];
            int minRightX = (px == m) ? INT_MAX : nums1[px];
            int maxLeftY  = (py == 0) ? INT_MIN : nums2[py - 1];
            int minRightY = (py == n) ? INT_MAX : nums2[py];
            if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
                if ((m + n) % 2 == 0)
                    return (max(maxLeftX, maxLeftY) + min(minRightX, minRightY)) / 2.0;
                return max(maxLeftX, maxLeftY);
            } else if (maxLeftX > minRightY) {
                hi = px - 1;
            } else {
                lo = px + 1;
            }
        }
        return 0.0;
    }
};
```

---

### 0005 - Longest Palindromic Substring

**Difficulty:** Medium
**Time:** O(n²) | **Space:** O(1)
**Approach:** Expand around each center (both odd and even length) and track the longest result.

```cpp
// Problem    : 0005 - Longest Palindromic Substring
// Difficulty : Medium
// Time       : O(n^2)
// Space      : O(1)

class Solution {
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
```

---

### 0006 - Zigzag Conversion

**Difficulty:** Medium
**Time:** O(n) | **Space:** O(n)
**Approach:** Simulate row assignment using a direction flag that flips at top and bottom rows.

```cpp
// Problem    : 0006 - Zigzag Conversion
// Difficulty : Medium
// Time       : O(n)
// Space      : O(n)

class Solution {
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
```

---

### 0007 - Reverse Integer

**Difficulty:** Medium
**Time:** O(log x) | **Space:** O(1)
**Approach:** Pop digits one by one and push onto the result, checking for 32-bit overflow before each step.

```cpp
// Problem    : 0007 - Reverse Integer
// Difficulty : Medium
// Time       : O(log x)
// Space      : O(1)

class Solution {
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
```

---

### 0008 - String to Integer (atoi)

**Difficulty:** Medium
**Time:** O(n) | **Space:** O(1)
**Approach:** Strip whitespace, handle sign, parse digits while checking for 32-bit integer overflow.

```cpp
// Problem    : 0008 - String to Integer (atoi)
// Difficulty : Medium
// Time       : O(n)
// Space      : O(1)

class Solution {
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
```

---

### 0009 - Palindrome Number

**Difficulty:** Easy
**Time:** O(log x) | **Space:** O(1)
**Approach:** Reverse only the second half of the number and compare with the first half. No string conversion.

```cpp
// Problem    : 0009 - Palindrome Number
// Difficulty : Easy
// Time       : O(log x)
// Space      : O(1)

class Solution {
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
```

---

### 0010 - Regular Expression Matching

**Difficulty:** Hard
**Time:** O(m * n) | **Space:** O(m * n)
**Approach:** Bottom-up dynamic programming. `dp[i][j]` is true if `s[0..i-1]` matches `p[0..j-1]`.

```cpp
// Problem    : 0010 - Regular Expression Matching
// Difficulty : Hard
// Time       : O(m * n)
// Space      : O(m * n)

class Solution {
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
```

---

### 0011 - Container With Most Water

**Difficulty:** Medium
**Time:** O(n) | **Space:** O(1)
**Approach:** Two pointers from both ends. Move the pointer at the shorter height inward to maximize area.

```cpp
// Problem    : 0011 - Container With Most Water
// Difficulty : Medium
// Time       : O(n)
// Space      : O(1)

class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0, right = (int)height.size() - 1, maxWater = 0;
        while (left < right) {
            int water = min(height[left], height[right]) * (right - left);
            maxWater = max(maxWater, water);
            if (height[left] < height[right]) left++;
            else right--;
        }
        return maxWater;
    }
};
```

---

### 0012 - Integer to Roman

**Difficulty:** Medium
**Time:** O(1) | **Space:** O(1)
**Approach:** Greedy subtraction using a value-symbol table ordered from largest to smallest.

```cpp
// Problem    : 0012 - Integer to Roman
// Difficulty : Medium
// Time       : O(1)
// Space      : O(1)

class Solution {
public:
    string intToRoman(int num) {
        vector<pair<int, string>> table = {
            {1000,"M"},{900,"CM"},{500,"D"},{400,"CD"},
            {100,"C"},{90,"XC"},{50,"L"},{40,"XL"},
            {10,"X"},{9,"IX"},{5,"V"},{4,"IV"},{1,"I"}
        };
        string result;
        for (auto& [val, sym] : table) {
            while (num >= val) { result += sym; num -= val; }
        }
        return result;
    }
};
```

---

### 0013 - Roman to Integer

**Difficulty:** Easy
**Time:** O(n) | **Space:** O(1)
**Approach:** Traverse left to right. Subtract current value if the next symbol is larger, otherwise add.

```cpp
// Problem    : 0013 - Roman to Integer
// Difficulty : Easy
// Time       : O(n)
// Space      : O(1)

class Solution {
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
```

---

### 0014 - Longest Common Prefix

**Difficulty:** Easy
**Time:** O(n * m) | **Space:** O(1)
**Approach:** Use the first string as the reference prefix. Trim it character by character against every other string.

```cpp
// Problem    : 0014 - Longest Common Prefix
// Difficulty : Easy
// Time       : O(n * m)
// Space      : O(1)

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string prefix = strs[0];
        for (int i = 1; i < (int)strs.size(); i++)
            while (strs[i].find(prefix) != 0)
                prefix = prefix.substr(0, prefix.size() - 1);
        return prefix;
    }
};
```

---

### 0015 - 3Sum

**Difficulty:** Medium
**Time:** O(n²) | **Space:** O(1)
**Approach:** Sort the array, fix one element, then use two pointers to find pairs that sum to zero. Skip duplicates.

```cpp
// Problem    : 0015 - 3Sum
// Difficulty : Medium
// Time       : O(n^2)
// Space      : O(1)

class Solution {
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
```

---

### 0016 - 3Sum Closest

**Difficulty:** Medium
**Time:** O(n²) | **Space:** O(1)
**Approach:** Sort the array, fix one element, use two pointers. Track the closest sum to target seen so far.

```cpp
// Problem    : 0016 - 3Sum Closest
// Difficulty : Medium
// Time       : O(n^2)
// Space      : O(1)

class Solution {
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
```

---

### 0017 - Letter Combinations of a Phone Number

**Difficulty:** Medium
**Time:** O(4^n * n) | **Space:** O(n)
**Approach:** Backtracking. Build combinations character by character using a digit-to-letters map.

```cpp
// Problem    : 0017 - Letter Combinations of a Phone Number
// Difficulty : Medium
// Time       : O(4^n * n)
// Space      : O(n)

class Solution {
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
```

---

### 0018 - 4Sum

**Difficulty:** Medium
**Time:** O(n³) | **Space:** O(1)
**Approach:** Sort, fix two elements with nested loops, then apply two pointers on the remaining range. Skip duplicates at each level.

```cpp
// Problem    : 0018 - 4Sum
// Difficulty : Medium
// Time       : O(n^3)
// Space      : O(1)

class Solution {
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
```

---

### 0019 - Remove Nth Node From End of List

**Difficulty:** Medium
**Time:** O(n) | **Space:** O(1)
**Approach:** Two pointers with a gap of n. When the fast pointer reaches the end, slow is just before the target node.

```cpp
// Problem    : 0019 - Remove Nth Node From End of List
// Difficulty : Medium
// Time       : O(n)
// Space      : O(1)

class Solution {
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
```

---

### 0020 - Valid Parentheses

**Difficulty:** Easy
**Time:** O(n) | **Space:** O(n)
**Approach:** Use a stack. Push open brackets; for close brackets, check if the top of the stack is the matching opener.

```cpp
// Problem    : 0020 - Valid Parentheses
// Difficulty : Easy
// Time       : O(n)
// Space      : O(n)

class Solution {
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
```

---

## Code Standards

**Language:** C++17
**STL:** `vector`, `unordered_map`, `stack`, `queue`, `set`, `string`, `algorithm` as appropriate.
**Complexity:** Every solution documents time and space complexity in the header comment.
**Formatting:** 4-space indentation, descriptive variable names, single-responsibility functions.

---

## Notes

- Each problem lives in its own isolated folder under `problems/`.
- Every folder contains two files: `solution.cpp` (implementation) and `README.md` (problem statement, constraints, approach notes).
- Folder names follow the format `NNNN-problem-slug` for consistent lexicographic ordering.
- The `scripts/scaffold.sh` utility generates a blank problem folder with the correct structure.

---

## License

MIT
