# 动态规划

## 1.[最大子数组和](https://leetcode.cn/problems/maximum-subarray/)

### 1.1题目描述

给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

子数组 是数组中的一个连续部分。

示例 1：

输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
输出：6
解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。

示例 2：

输入：nums = [1]
输出：1

示例 3：

输入：nums = [5,4,-1,7,8]
输出：23

### 1.2题目分析

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ans = nums[0], sum = 0;
        for(int& elem : nums) {
            if(sum > 0) {
                sum += elem;
            }else{
                sum = elem;
            }
            ans = max(ans, sum);
        }
        return ans;
    }
};
```

## 2.[不同路径](https://leetcode.cn/problems/unique-paths/)

### 2.1题目描述

一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。

问总共有多少条不同的路径？

 ![image-20230120184004601](C:/Users/24991/AppData/Roaming/Typora/typora-user-images/image-20230120184004601.png)

示例 1：

输入：m = 3, n = 7
输出：28

示例 2：

输入：m = 3, n = 2
输出：3
解释：
从左上角开始，总共有 3 条路径可以到达右下角。

1. 向右 -> 向下 -> 向下
2. 向下 -> 向下 -> 向右
3. 向下 -> 向右 -> 向下

### 2.2题目分析

- 组合数学。求一个阶乘！
- 动态规划

```c++
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> ans(m, vector<int>(n));

        for(int i= 0; i < m; ++i) {
            ans[i][0] = 1;
        }

        for(int j = 0; j < n; ++j) {
            ans[0][j] = 1;
        }

        for(int i = 1; i < m; ++i) {
            for(int j = 1; j < n; ++j) {
                ans[i][j] = ans[i-1][j] + ans[i][j-1];
            }
        }
        return ans[m-1][n-1];
    }
};
```

## 3.[判断子序列](https://leetcode.cn/problems/is-subsequence/)

### 3.1题目描述

给定字符串 s 和 t ，判断 s 是否为 t 的子序列。

字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。（例如，"ace"是"abcde"的一个子序列，而"aec"不是）。

进阶：

如果有大量输入的 S，称作 S1, S2, ... , Sk 其中 k >= 10亿，你需要依次检查它们是否为 T 的子序列。在这种情况下，你会怎样改变代码？

示例 1：

输入：s = "abc", t = "ahbgdc"
输出：true

示例 2：

输入：s = "axc", t = "ahbgdc"
输出：false

### 3.2题目分析

- 双指针

```c++
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int n = s.length(), m = t.length();
        int i = 0, j = 0;
        while(i < n && j < m) {
            if(s[i] == t[j]) {
                ++i;
            }
            ++j;
        }
        return i == n;
    }
};
```

- 动态规划

```c++
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int n = s.size(), m = t.size();

        vector<vector<int> > f(m + 1, vector<int>(26, 0));
        for (int i = 0; i < 26; i++) {
            f[m][i] = m;
        }

        for (int i = m - 1; i >= 0; i--) {
            for (int j = 0; j < 26; j++) {
                if (t[i] == j + 'a')
                    f[i][j] = i;
                else
                    f[i][j] = f[i + 1][j];
            }
        }
        int add = 0;
        for (int i = 0; i < n; i++) {
            if (f[add][s[i] - 'a'] == m) {
                return false;
            }
            add = f[add][s[i] - 'a'] + 1;
        }
        return true;
    }
};
```

