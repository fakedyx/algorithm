# 树的深度

## 1.[N 叉树的最大深度](https://leetcode.cn/problems/maximum-depth-of-n-ary-tree/)

### 1.1题目描述

给定一个 N 叉树，找到其最大深度。

最大深度是指从根节点到最远叶子节点的最长路径上的节点总数。

N 叉树输入按层序遍历序列化表示，每组子节点由空值分隔（请参见示例）。

![image-20230112185027610](C:/Users/24991/AppData/Roaming/Typora/typora-user-images/image-20230112185027610.png)

### 1.2题目分析

- **BFS**

```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    int maxDepth(Node* root) {
        if(root == nullptr) {
            return 0;
        }
        
        int n = root->children.size();
        if(n == 0) {
            return 1;
        }
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            ans = max(ans, maxDepth(root->children[i]) + 1);
        }
        return ans;
    }
};



//重构
class Solution {
public:
    int maxDepth(Node* root) {
        if(root == nullptr) {
            return 0;
        }
        
        vector<Node*> children = root->children;
        int maxChildrenDepth = 0;
        for(auto child : children) {
            int childDepth = maxDepth(child);
            maxChildrenDepth = max(maxChildrenDepth, childDepth);
        }
        return maxChildrenDepth + 1;
    }
};
```

- **DFS**。通过层次遍历判断一共有多少层，即可得到最大深度。

```c++
class Solution {
public:
    int maxDepth(Node* root) {
        if(root == nullptr) {
            return 0;
        }
        
        queue<Node*> q;
        q.push(root);
        int ans = 0;
        while(!q.empty()) {
            int size = q.size();
            while(size > 0) {
                /*将该层所有的元素都取弹出*/
                Node* child = q.front();
                q.pop();
                for(auto c : child->children) {
                    /*将该结点的孩子结点放入队列*/
                    q.push(c);
                }
                --size;
            }
            ++ans;
        }
        return ans;
    }
};
```

## 2.[二叉树的最大深度](https://leetcode.cn/problems/maximum-depth-of-binary-tree/)

### 2.1题目描述

给定一个二叉树，找出其最大深度。

二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。

说明: 叶子节点是指没有子节点的节点。

示例：
给定二叉树 [3,9,20,null,null,15,7]，

​    3

   / \
  9  20
    /  \
   15   7
返回它的最大深度 3 。

### 2.2题目分析

```c++
class Solution {
public:
    int maxDepth(TreeNode* root) {
        return root ? max(maxDepth(root->left), maxDepth(root->right)) + 1 : 0;
    }
};
```

## 3.[二叉树的最小深度](https://leetcode.cn/problems/minimum-depth-of-binary-tree/)

### 3.1题目描述

给定一个二叉树，找出其最小深度。

最小深度是从根节点到最近叶子节点的最短路径上的节点数量。

**说明：**叶子节点是指没有子节点的节点。

![image-20230112195152779](C:/Users/24991/AppData/Roaming/Typora/typora-user-images/image-20230112195152779.png)

### 3.2题目分析

- BFS

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
    int minDepth(TreeNode* root) {
        if(root == nullptr) {
            return 0;
        }else if(root->left == nullptr && root->right == nullptr) {
            //叶子结点
            return 1;
        }else if(root->left == nullptr) {
            return 1 + minDepth(root->right);
        }else if(root->right == nullptr)
            return 1 + minDepth(root->left);
        else{
            return 1 + min(minDepth(root->left), minDepth(root->right));
        }
    }
};
```

