# array

## 1.[删除有序数组中的重复项](https://leetcode.cn/problems/remove-duplicates-from-sorted-array/)

### 1.1题目描述

给你一个 升序排列 的数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。元素的 相对顺序 应该保持 一致 。

由于在某些语言中不能改变数组的长度，所以必须将结果放在数组nums的第一部分。更规范地说，如果在删除重复项之后有 k 个元素，那么 nums 的前 k 个元素应该保存最终结果。

将最终结果插入 nums 的前 k 个位置后返回 k 。

不要使用额外的空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

判题标准:

系统会用下面的代码来测试你的题解:

int[] nums = [...]; // 输入数组
int[] expectedNums = [...]; // 长度正确的期望答案

int k = removeDuplicates(nums); // 调用

assert k == expectedNums.length;
for (int i = 0; i < k; i++) {
    assert nums[i] == expectedNums[i];
}
如果所有断言都通过，那么您的题解将被 通过。

### 1.2代码实现

```C++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int cnt = 1, size = nums.size(), i = 0;
        while(i < size) {
            // eg: a b b c c cnt指针始终指在最终结果的位置，i指针每次往后移动，并且判断其是否和cnt指针所指的内容一致，如果一致，直接往后走，不一致，cnt++，并将结果保存下来
            if(nums[i] != nums[cnt - 1]) {
                 nums[cnt] = nums[i];
                ++cnt;
            }
            ++i;
        }
        return cnt;
    }
};
```

时间复杂度为O(n)，空间复杂度为O(1)



## 2.[移除元素](https://leetcode.cn/problems/remove-element/)

### 2.1题目描述

给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。

不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。

元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。

示例 1：

输入：nums = [3,2,2,3], val = 3
输出：2, nums = [2,2]
解释：函数应该返回新的长度 2, 并且 nums 中的前两个元素均为 2。你不需要考虑数组中超出新长度后面的元素。例如，函数返回的新长度为 2 ，而 nums = [2,2,3,3] 或 nums = [2,2,0,0]，也会被视作正确答案。

### 2.2代码实现

```c++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int size = nums.size(), i = 0, cnt = 0;
        if(size == 0) {
            return 0;
        }

        while(i < size) {
            if(nums[i] != val) {
                nums[cnt] = nums[i];
                ++cnt;
            }
            ++i;
        }
        return cnt;
    }
};
```

时间复杂度为O(n)，空间复杂度为O(1)

## 3.[搜索插入位置](https://leetcode.cn/problems/search-insert-position/)

### 3.1题目描述

给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

请必须使用时间复杂度为 O(log n) 的算法。

示例 1:

输入: nums = [1,3,5,6], target = 5
输出: 2
示例 2:

输入: nums = [1,3,5,6], target = 2
输出: 1
示例 3:

输入: nums = [1,3,5,6], target = 7
输出: 4

### 3.2代码实现

```c++
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int lhs = 0, rhs = nums.size() - 1;

        /*
         if(target > nums[rhs]) {
            return rhs + 1;
        }

        if(target < nums[0]) {
            return lhs;
        }
        */

        while(lhs <= rhs) {
            int mid = (rhs + lhs) / 2;
            // int mid = (right - left) >> 1 + left
            if(target < nums[mid]) {
                rhs = mid - 1;
            }else if(target > nums[mid]){
                lhs = mid + 1;
            }else{
                return mid;
            }
        }

        return lhs;
    }
};
```

时间复杂度为O(logn)，空间复杂度为O(1)

## 4.[加一](https://leetcode.cn/problems/plus-one/)

### 4.1题目描述

给定一个由 整数 组成的 非空 数组所表示的非负整数，在该数的基础上加一。

最高位数字存放在数组的首位， 数组中每个元素只存储单个数字。

你可以假设除了整数 0 之外，这个整数不会以零开头。

示例 1：

输入：digits = [1,2,3]
输出：[1,2,4]
解释：输入数组表示数字 123。
示例 2：

输入：digits = [4,3,2,1]
输出：[4,3,2,2]
解释：输入数组表示数字 4321。

### 4.2思想描述

找出最长的后缀9

当我们对数组+1时，只需要关注数组末尾出现了多少个9，然后再分类讨论:

- 如果末尾没有9，直接对末尾数加1；
- 如果末尾有若干9，从末尾开始找到第一个不为9的数，让其++，后面位全部置0
- 如果全都是9，只需要构造一个长度+1的数组，然后将首个元素置为1，其余元素置为0

### 4.3代码实现

```C++
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int size = digits.size();
        //从个位开始查找第一个不为9的数
        for(int i = size - 1; i >= 0; i--) {
            if(digits[i] != 9) {
                //先让这一位++
                ++digits[i];
                //让后面的位全变成0
                for(int j = i + 1; j <= size - 1; ++j) {
                    digits[j] = 0;
                }
                return digits;
            }
        }

        //全部为9
        vector<int> ans(size+1);
        ans[0] = 1;
        return ans;
    }
};
```

时间复杂度为O(n)，空间复杂度为O(1)



## 5.[将有序数组转换为二叉搜索树](https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/)

### 5.1题目描述

给你一个整数数组 nums ，其中元素已经按 升序 排列，请你将其转换为一棵 高度平衡 二叉搜索树。

高度平衡 二叉树是一棵满足「每个节点的左右两个子树的高度差的绝对值不超过 1 」的二叉树。

示例 1：

输入：nums = [-10,-3,0,5,9]
输出：[0,-3,9,-10,null,5]
解释：[0,-10,5,null,-3,null,9] 也将被视为正确答案：



### 5.2代码实现

```C++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return helper(nums, 0, nums.size() - 1);
    }

    TreeNode* helper(vector<int>& nums, int lhs, int rhs) {
        if(lhs > rhs) {
            return nullptr;
        }

        // 将中间的值构造为根结点
        int mid = (rhs + lhs) >> 1;
        //int mid = (rhs + lhs) / 2;
        TreeNode* root = new TreeNode(nums[mid]);
        //root->val = nums[mid];
        root->left = helper(nums, lhs, mid - 1);
        root->right = helper(nums, mid + 1, rhs);
        return root;

    }
};
```

## 6.[ 多数元素](https://leetcode.cn/problems/majority-element/)

### 6.1题目描述

给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。

示例 1：

输入：nums = [3,2,3]
输出：3
示例 2：

输入：nums = [2,2,1,1,1,2,2]
输出：2



### 6.2题目分析

- 方法1：hash table

```c++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> coll;
        int cnt = 0, ans = nums[0];
        for(auto & elem : nums) {
            coll[elem]++;
            if(cnt < coll[elem]) {
                ans = elem;
                cnt = coll[elem];
            }
        }
        return ans;
    }
};
```

- 方法2：排序后返回[n/2]

```C++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];
    }
};
```

- 方法3：摩尔投票法

Boyer-Moore 算法的本质和方法四中的分治十分类似。我们首先给出 Boyer-Moore 算法的详细步骤：

我们维护一个候选众数 candidate 和它出现的次数 count。初始时 candidate 可以为任意值，count 为 0；

我们遍历数组 nums 中的所有元素，对于每个元素 x，在判断 x 之前，如果 count 的值为 0，我们先将 x 的值赋予 candidate，随后我们判断 x：

如果 x 与 candidate 相等，那么计数器 count 的值增加 1；

如果 x 与 candidate 不等，那么计数器 count 的值减少 1。

在遍历完成后，candidate 即为整个数组的众数。	

```c++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
       int candiate = nums[0], cnt = 1;
       for(int i = 1; i < nums.size(); ++i) {
           if(nums[i] == candiate) {
               cnt++;
           }else{
               cnt--;
               if(cnt == 0){
                   candiate = nums[i];
                   cnt = 1;
               }
           }
       }
       return candiate;
    }
};
```

## 7.[存在重复元素 II](https://leetcode.cn/problems/contains-duplicate-ii/)

### 7.1题目描述

给你一个整数数组 nums 和一个整数 k ，判断数组中是否存在两个 不同的索引 i 和 j ，满足 nums[i] == nums[j] 且 abs(i - j) <= k 。如果存在，返回 true ；否则，返回 false 。

 

示例 1：

输入：nums = [1,2,3,1], k = 3
输出：true
示例 2：

输入：nums = [1,0,1,1], k = 1
输出：true
示例 3：

输入：nums = [1,2,3,1,2,3], k = 2
输出：false

### 7.2题目分析

- 方法1：hash表[nums[i]， i]表示某个数上次出现的索引位置

```c++
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> coll;
        int n = nums.size();
        for(int i = 0; i < n; ++i) {
            if(coll.count(nums[i]) && i - coll[nums[i]] <= k) {
                return true;
            }
            //更新coll中的距离
            coll[nums[i]] = i;
        }
        return false;
    }
};
```

时间复杂度为O(n)，空间复杂度为O(n)

- 方法2：滑动窗口

考虑数组 $\textit{nums}$ 中的每个长度不超过 k + 1 的滑动窗口，同一个滑动窗口中的任意两个下标差的绝对值不超过 k。如果存在一个滑动窗口，其中有重复元素，则存在两个不同的下标 i 和 j 满足 $\textit{nums}[i] = \textit{nums}[j] 且 |i - j| \le k$。如果所有滑动窗口中都没有重复元素，则不存在符合要求的下标。因此，只要遍历每个滑动窗口，判断滑动窗口中是否有重复元素即可。

```c++
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> s;
        int n = nums.size();
        for(int i = 0; i < n; ++i) {
            if(i > k) {
                 s.erase(nums[i - k - 1]);
            }
             
            //此时还没有插入nums[i]，如果其数量已经等于1，说明插入之后就等于2了
            if(s.count(nums[i])) {
                return true;
            }

            s.emplace(nums[i]);
           
        }
        return false;
    }
};
```

## 8.[汇总区间](https://leetcode.cn/problems/summary-ranges/)

### 8.1题目描述

给定一个  无重复元素 的 有序 整数数组 nums 。

返回 恰好覆盖数组中所有数字 的 最小有序 区间范围列表 。也就是说，nums 的每个元素都恰好被某个区间范围所覆盖，并且不存在属于某个范围但不属于 nums 的数字 x 。

列表中的每个区间范围 [a,b] 应该按如下格式输出：

"a->b" ，如果 a != b
"a" ，如果 a == b


示例 1：

输入：nums = [0,1,2,4,5,7]
输出：["0->2","4->5","7"]
解释：区间范围是：
[0,2] --> "0->2"
[4,5] --> "4->5"
[7,7] --> "7"
示例 2：

输入：nums = [0,2,3,4,6,8,9]
输出：["0","2->4","6","8->9"]
解释：区间范围是：
[0,0] --> "0"
[2,4] --> "2->4"
[6,6] --> "6"
[8,9] --> "8->9"

### 8.2代码实现

```	C++
class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        int n = nums.size();
        vector<string> vec;
        long num;
        int j;
        for (int i = 0; i < n; ) {
            string s;
            num = nums[i];
            j = i;
            while (j < n && num == nums[j]) {
                num++;
                j++;
            }

            s += to_string(nums[i]);
            if (j - i > 1) {
                s += "->";
                s += to_string(nums[j - 1]);
            }

            i = j;
            vec.push_back(s);
        }
        return vec;
    }
};
```

时间复杂度为O(n)，空间复杂度为O(1)。

***注意to_string()函数***

## 9.[移动零](https://leetcode.cn/problems/move-zeroes/)

### 9.1题目描述

给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

请注意 ，必须在不复制数组的情况下原地对数组进行操作。

示例 1:

输入: nums = [0,1,0,3,12]
输出: [1,3,12,0,0]
示例 2:

输入: nums = [0]
输出: [0]

### 9.2题目分析

- 方法1：交换法

```c++
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
       int n = nums.size(), i = 0, j = 0;  //i指针用来寻找非0数，j指针用来寻找0
       while(i < n) {
            if(nums[i]) {
                swap(nums[i], nums[j]);
                ++j; //加完依旧指向0
            }
            ++i;
        }

        // while (i < n && j < n) {
        //     while (i < n && nums[i] == 0) {
        //         ++i;
        //     }
        //     while (j < n && nums[j] != 0) {
        //         ++j;
        //     }
        //     if (i < n && j < n && i > j) {
        //         swap(nums[i], nums[j]);
        //         ++i;
        //         ++j;
        //     }
        // }   
    }
};

/*
T = O(n)
R = O(1)
*/
```

- 方法2：统计非0数，然后直接覆盖然后补0

```c++
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
       int n = nums.size(), i = 0, j = 0;  //i指针用来寻找非0数，j指针用来寻找0
       while(i < n) {
           if(nums[i]) {
               nums[j] = nums[i];
               ++j;
           }
           ++i;
       }
       while(j < n) {
           nums[j] = 0;
           ++j;
       } 
    }
};
```

## 10.[杨辉三角 II](https://leetcode.cn/problems/pascals-triangle-ii/)

### 10.1题目描述

给定一个非负索引 rowIndex，返回「杨辉三角」的第 rowIndex 行。

在「杨辉三角」中，每个数是它左上方和右上方的数的和。

示例 1:

输入: rowIndex = 3
输出: [1,3,3,1]

示例 2:

输入: rowIndex = 0
输出: [1]

示例 3:

输入: rowIndex = 1
输出: [1,1]

### 10.2题目分析

![image-20230116145609672](C:/Users/24991/AppData/Roaming/Typora/typora-user-images/image-20230116145609672.png)

```c++
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> ans(rowIndex + 1);
        ans[0] = 1;
        for(int i = 1; i <= rowIndex; ++i) {
            for(int j = i; j > 0; --j) {
                //倒着算
                ans[j] += ans[j-1];
            }
        }
        return ans;
    }
};
```

## 11.[键盘行](https://leetcode.cn/problems/keyboard-row/)

### 11.1题目描述

给你一个字符串数组 words ，只返回可以使用在 美式键盘 同一行的字母打印出来的单词。键盘如下图所示。

美式键盘 中：

第一行由字符 "qwertyuiop" 组成。
第二行由字符 "asdfghjkl" 组成。
第三行由字符 "zxcvbnm" 组成。

**示例 1：**

输入：words = ["Hello","Alaska","Dad","Peace"]
输出：["Alaska","Dad"]

**示例 2：**

输入：words = ["omk"]
输出：[]

**示例 3：**

输入：words = ["adsdf","sfd"]
输出：["adsdf","sfd"]

### 11.2题目分析

- 遍历。我们为每一个英文字母标记其对应键盘上的行号，然后检测字符串中所有字符对应的行号是否相同。

  我们可以预处理计算出每个字符对应的行号。

  遍历字符串时，统一将大写字母转化为小写字母方便计算。

```c++
class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        vector<string> ans;
        string rowIdx = "12210111011122000010020202";  //妙！
        for(auto& word : words) {
            bool isValid = true;
            char idx = rowIdx[tolower(word[0]) - 'a'];
            //然后去遍历word中其他的字符，判断是否为idx
            for(int i = 1; i < word.size(); ++i) {
                if(rowIdx[tolower(word[i]) - 'a'] != idx) {
                    isValid = false;
                    break;
                }
            }
            if(isValid) {
                ans.push_back(word);
            }
        }
        return ans;
    }
};
```

## 12.[ 最长和谐子序列](https://leetcode.cn/problems/longest-harmonious-subsequence/)

### 12.1题目描述

和谐数组是指一个数组里元素的最大值和最小值之间的差别 正好是 1 。

现在，给你一个整数数组 nums ，请你在所有可能的子序列中找到最长的和谐子序列的长度。

数组的子序列是一个由数组派生出来的序列，它可以通过删除一些元素或不删除元素、且不改变其余元素的顺序而得到。

示例 1：

输入：nums = [1,3,2,2,5,2,3,7]
输出：5
解释：最长的和谐子序列是 [3,2,2,2,3]

示例 2：

输入：nums = [1,2,3,4]
输出：2

示例 3：

输入：nums = [1,1,1,1]
输出：0

### 12.2题目分析

- 方法1：枚举。先进行排序然后再统计
- 方法2：使用hashmap

```c++
class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> coll;
        for(auto& elem : nums) {
            coll[elem]++;
        }
        int ans = 0;
        // for(auto[key, val] : coll) {
        //     if(coll.count(key+1)) {
        //         ans = max(ans, val + coll[key+1]);
        //     }
        // }
        for(auto& elem : coll) {
            if(coll.count(elem.first + 1)) {
                ans = max(ans, elem.second + coll[elem.first+1]);
            }
        }
        return ans;
    }
};
```



## 13.数组的度

### 13.1题目分析

给定一个非空且只包含非负数的整数数组 nums，数组的 度 的定义是指数组里任一元素出现频数的最大值。

你的任务是在 nums 中找到与 nums 拥有相同大小的度的最短连续子数组，返回其长度。

示例 1：

输入：nums = [1,2,2,3,1]
输出：2
解释：
输入数组的度是 2 ，因为元素 1 和 2 的出现频数最大，均为 2 。
连续子数组里面拥有相同度的有如下所示：
[1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
最短连续子数组 [2, 2] 的长度为 2 ，所以返回 2 。

示例 2：

输入：nums = [1,2,2,3,1,4,2]
输出：6
解释：
数组的度是 3 ，因为元素 2 重复出现 3 次。
所以 [2,2,3,1,4,2] 是最短子数组，因此返回 6 。

### 13.2题目分析

```c++
class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        unordered_map<int, vector<int>> mp; //vector<int>{次数，第一次出现的下标，最短的下一次出现的下标}
        int n = nums.size();
        for(int i = 0; i < n; ++i) {
            if(mp.count(nums[i])) {
                //不是首次出现
                mp[nums[i]][0]++;
                mp[nums[i]][2] = i;
            }else {
                mp[nums[i]] = {1, i, i};
            }
        }
        int maxNum = 0, minLen = 0;
        for(auto& [_, vec] : mp) {
            if(maxNum < vec[0]) {
                maxNum = vec[0];
                minLen = vec[2] - vec[1] + 1;
            }else if(maxNum == vec[0]) {
                if(minLen > vec[2] - vec[1] + 1) {
                    minLen = vec[2] - vec[1] + 1;
                }
            }
        }//for
        return minLen;
    }
};
```

## 14.[删除有序数组中的重复项 II](https://leetcode.cn/problems/remove-duplicates-from-sorted-array-ii/)

### 14.1题目描述

给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使得出现次数超过两次的元素只出现两次 ，返回删除后数组的新长度。

不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

说明：

为什么返回数值是整数，但输出的答案是数组呢？

请注意，输入数组是以「引用」方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。

你可以想象内部操作如下:

// nums 是以“引用”方式传递的。也就是说，不对实参做任何拷贝
int len = removeDuplicates(nums);

// 在函数里修改输入数组对于调用者是可见的。
// 根据你的函数返回的长度, 它会打印出数组中 该长度范围内 的所有元素。
for (int i = 0; i < len; i++) {
    print(nums[i]);
}


示例 1：

输入：nums = [1,1,1,2,2,3]
输出：5, nums = [1,1,2,2,3]
解释：函数应返回新长度 length = 5, 并且原数组的前五个元素被修改为 1, 1, 2, 2, 3 。 不需要考虑数组中超出新长度后面的元素。

示例 2：

输入：nums = [0,0,1,1,1,1,2,3,3]
输出：7, nums = [0,0,1,1,2,3,3]
解释：函数应返回新长度 length = 7, 并且原数组的前五个元素被修改为 0, 0, 1, 1, 2, 3, 3 。 不需要考虑数组中超出新长度后面的元素。



### 14.2题目分析

- 双指针

```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if(n <= 2) return n;
        int index = 2;
        for(int i = 2; i < n; ++i) {
            //非常巧妙的一步，我的最开始思路是增加一个计数器，太笨重了
            if(nums[i] != nums[index-2]) {
                nums[index++] = nums[i];
            }
        }
        return index;
    }
};
```

## 15.[只出现一次的数字 II](https://leetcode.cn/problems/single-number-ii/)

### 15.1题目描述

给你一个整数数组 nums ，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次 。请你找出并返回那个只出现了一次的元素。

**你必须设计并实现线性时间复杂度的算法且不使用额外空间来解决此问题。**

示例 1：

输入：nums = [2,2,3,2]

输出：3

示例 2：

输入：nums = [0,1,0,1,0,1,99]
输出：99

### 15.2题目分析

- hash_table

```c++
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_map<int, int> coll;
        for(auto& elem : nums) {
            coll[elem]++;
        }

        int val = 0;
        for(auto& elem : nums) {
            if(coll[elem] == 1) {
                val = elem;
            }
        }
        return val;
    }
};
```



- 位运算

## 16.[完全二叉树的节点个数](https://leetcode.cn/problems/count-complete-tree-nodes/)

### 16.1题目描述

给你一棵 完全二叉树 的根节点 root ，求出该树的节点个数。

完全二叉树 的定义如下：在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第 h 层，则该层包含 1~ 2h 个节点。

示例 1：

输入：root = [1,2,3,4,5,6]
输出：6

示例 2：

输入：root = []
输出：0

示例 3：

输入：root = [1]
输出：1

### 16.2题目分析

- 中序遍历

```c++
class Solution {
    int cnt = 0;
public:
    int countNodes(TreeNode* root) {
        dfs(root);
        return cnt;
    }

    void dfs(TreeNode* root) {
        if(root == nullptr) {
            return;
        }
        dfs(root->left);
        ++cnt;
        dfs(root->right);
    }
};
```

- 利用完全二叉树的性质

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int countNodes(TreeNode* root) {
        /*
        *完全二叉树的高度可以通过不断地访问左子树就可以获取
        *判断左右子树的高度：
        *如果相等说明左右子树是满二叉树，然后进一步判断右子树的节点数
        *如果不等，...
        */
        if(root == nullptr) return 0;
        int lhs = getDepth(root->left);
        int rhs = getDepth(root->right);
        if(lhs == rhs) return (1 << lhs) + countNodes(root->right);
        else return (1 << rhs) + countNodes(root->left);
    }

    int getDepth(TreeNode* root) {
        int depth = 0;
        while(root != nullptr) {
            root = root->left;
            ++depth;
        }
        return depth;
    }
};
```

## 17.[只出现一次的数字 III](https://leetcode.cn/problems/single-number-iii/)

### 17.1题目描述

给你一个整数数组 nums，其中恰好有两个元素只出现一次，其余所有元素均出现两次。 找出只出现一次的那两个元素。你可以按 任意顺序 返回答案。

你必须设计并实现线性时间复杂度的算法且仅使用常量额外空间来解决此问题。

示例 1：

输入：nums = [1,2,1,3,2,5]
输出：[3,5]
解释：[5, 3] 也是有效的答案。

示例 2：

输入：nums = [-1,0]
输出：[-1,0]

示例 3：

输入：nums = [0,1]
输出：[1,0]

### 17.2题目分析

- hash_table

```c++
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        unordered_map<int, int> coll;
        for(int num : nums) {
            ++coll[num];
        }

        vector<int> ans;
        for(const auto& [num, occ] : coll) {
            if(occ == 1) {
                ans.push_back(num);
            }
        }
        return ans;
    }
};
```

- 位运算

```c++

```

