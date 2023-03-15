# string

## 1.[Excel表列名称](https://leetcode.cn/problems/excel-sheet-column-title/)

### 1.1题目描述

给你一个整数 columnNumber ，返回它在 Excel 表中相对应的列名称。

例如：

A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28 
...


示例 1：

输入：columnNumber = 1
输出："A"
示例 2：

输入：columnNumber = 28
输出："AB"

### 1.2思想分析

$$
利用性质0 \le a_0 - 1 \le 25
$$

### 1.3代码实现

```C++
class Solution {
public:
    string convertToTitle(int columnNumber) {
        string ans;
        while(columnNumber > 0) {
            --columnNumber;
            ans += columnNumber % 26 + 'A';
            columnNumber /= 26;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
```

时间复杂度O($log_{26}n$),空间复杂度为O(1)



## 2.[Excel 表列序号](https://leetcode.cn/problems/excel-sheet-column-number/)

### 2.1题目描述

给你一个字符串 columnTitle ，表示 Excel 表格中的列名称。返回 该列名称对应的列序号 。

例如：

A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28 
...


示例 1:

输入: columnTitle = "A"
输出: 1
示例 2:

输入: columnTitle = "AB"
输出: 28

### 2.2代码实现

```c++
class Solution {
public:
    int titleToNumber(string columnTitle) {
        int ans = 0, i = 0, size = columnTitle.size() - 1;
        int base = pow(26, size);
        while(i <= size) {
            ans += (columnTitle[i] - 'A' + 1) * base;
            base /= 26;
            ++i;
        }
        return ans;
    }
};

//倒着算
class Solution {
public:
    int titleToNumber(string columnTitle) {
        int ans = 0, i = columnTitle.size() - 1;
        long base = 1;
        while(i >= 0) {
            ans += (columnTitle[i] - 'A' + 1) * base;
            base *= 26;
            --i;
        }
        return ans;
    }
};
```

时间复杂度O(n),空间复杂度为O(1)

## 3.[单词规律](https://leetcode.cn/problems/word-pattern/)

### 3.1题目描述

给定一种规律 pattern 和一个字符串 s ，判断 s 是否遵循相同的规律。

这里的 遵循 指完全匹配，例如， pattern 里的每个字母和字符串 s 中的每个非空单词之间存在着双向连接的对应规律。

示例1:

输入: pattern = "abba", s = "dog cat cat dog"
输出: true
示例 2:

输入:pattern = "abba", s = "dog cat cat fish"
输出: false
示例 3:

输入: pattern = "aaaa", s = "dog cat cat dog"
输出: false



### 3.2思想分析

在本题中，我们需要判断字符与字符串之间是否恰好一一对应。即任意一个字符都对应着唯一的字符串，任意一个字符串也只被唯一的一个字符对应。在集合论中，这种关系被称为「双射」。

想要解决本题，我们可以利用哈希表记录每一个字符对应的字符串，以及每一个字符串对应的字符。然后我们枚举每一对字符与字符串的配对过程，不断更新哈希表，如果发生了冲突，则说明给定的输入不满足双射关系。

在实际代码中，我们枚举 $\textit{pattern}$ 中的每一个字符，利用双指针来均摊线性地找到该字符在 $\textit{str}$  中对应的字符串。每次确定一个字符与字符串的组合，我们就检查是否出现冲突，最后我们再检查两字符串是否比较完毕即可。

### 3.3代码实现

```c++
class Solution {
public:
    bool wordPattern(string pattern, string s) {
        unordered_map<string, char> str2ch;
        unordered_map<char, string> ch2str;
        int i = 0, n = s.length();
        for(auto ch : pattern) {
            if(i >= n){
                return false;
            }

            //截取一个单词
            int j = i;
            while(j < n && s[j] != ' ') {
                j++;
            }
            string tmp = s.substr(i, j - i);
            if(str2ch.count(tmp) && str2ch[tmp] != ch) {
                //此处必须要.count()，否则在开始的时候直接return false
                return false;
            }

            if(ch2str.count(ch) && ch2str[ch] != tmp) {
                return false;
            }
			
            
            //不管前面的匹配规则，直接按现在的修改，如果遇到冲突就return false
            ch2str[ch] = tmp;
            str2ch[tmp] = ch;
            i = j+1;
        }
        return i >= n;  //pattern数小于word个数

    }
};

///////测试

#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <numeric>
#include <algorithm>
#include <iterator>
using namespace std;


void test01() {
	unordered_map<char, string> ch2str;
	if (ch2str.count('a') && ch2str['a'] != "str") {
		cout << "test1" << endl;
	}
	//不会输出

	if (ch2str['a'] != "str") {
		cout << "test2" << endl;
	}
	//输出

	if (ch2str.count('a') && ch2str['a'] != "str") {
		cout << "test3" << endl;
	}
	//输出
}

int main()
{
	test01();
	return 0;
}
```

## 4.[反转字符串中的元音字母](https://leetcode.cn/problems/reverse-vowels-of-a-string/)

### 4.1题目描述

给你一个字符串 s ，仅反转字符串中的所有元音字母，并返回结果字符串。

元音字母包括 'a'、'e'、'i'、'o'、'u'，且可能以大小写两种形式出现不止一次。

示例 1：

输入：s = "hello"
输出："holle"
示例 2：

输入：s = "leetcode"
输出："leotcede"

### 4.2代码实现

```c++
class Solution {
public:
    string reverseVowels(string s) {
        auto isVowel = [vowels = "aeiouAEIOU"s](char ch) {
            return vowels.find(ch) != string::npos;//npos是字符串的最后一个空字符
        };

        int n = s.size();
        int i = 0, j = n - 1;
        while(i < j) {
            while(i < n && !isVowel(s[i])) {
                ++i;
            }
            while(j > 0 && !isVowel(s[j])) {
                --j;
            }
            if(i < j) {
                swap(s[i], s[j]);
                ++i;
                --j;
            }
        }
        return s;
    }
};
```

### 4.3知识扩充

**C++中的字符串**

1. string。string的接口比较复杂，除了字符串的操作，还有类似于容器的操作，比如size()、begin()、end()、push_back()注意：字符串和容器完全是两个不同的概念。using string = std::basic_string; // string其实是一个类型别名。基于各种原因：在涉及 [Unicode](https://so.csdn.net/so/search?q=Unicode&spm=1001.2101.3001.7020)、编码转换的时候，尽量不要用 C++，一般只用string就好。如果只是存储字符，没有string其他不必要的操作，可以使用vector来代替。

```c++
使用技巧：
using namespace std::literals::string_literals;  //必须打开名字空间

auto str = "std string"s;      // 后缀s，表示是标准字符串，直接类型推导

assert("time"s.size() == 4);   // 标准字符串可以直接调用成员函数

C++14中的新增，字符串后面+s，表示：它是string字符串类型，不是C字符串，可以用auto自动类型推导，而且在其他用到字符串的地方，也可以省去声明临时字符串变量的麻烦，效率也会更高。
注意：为了避免与用户自定义字面量的冲突，后缀“s”不能直接使用，必须用 using 打开名字空间才行
```

2. 原始字符串R"()"
   C++11新增原始字符串内容，将具有转义的字符表达出来。

```c++
auto str1 = R"(char""'')";    // 原样输出：char""''
auto str2 = R"(\r\n\t\")";    // 原样输出：\r\n\t\"
auto str3 = R"(\\\$)";        // 原样输出：\\\$
auto str4 = "\\\\\\$";         // 转义后输出：\\\$

如上述表示**R"()"**里括号的内容里放具有转义语义的字符可以直接输出，可轻松表达正则式，或者类似的回车、空格等不可打印的字符\n \r之类的。
但如果表示R"()"呢？
解决办法如下：
auto str5 = R"==(R"(xxx)")==";// 原样输出：R"(xxx)"
```

3. 字符串转换函数。C++11新增如下转换函数：
stoi()、stol()、stoll() 等把字符串转换成整数；
stof()、stod() 等把字符串转换成浮点数；
to_string() 把整数、浮点数转换成字符串。

```c++
assert(stoi("42") == 42);          // 字符串转整数
assert(stol("253") == 253L);       // 字符串转长整数
assert(stod("2.0") == 2.0);       // 字符串转浮点数
assert(to_string(1984) == "1984");       // 整数转字符串
C语言中有atoi()、atol()函数，但是针对的是C语言中的字符串，而不是string，用起来麻烦。
```