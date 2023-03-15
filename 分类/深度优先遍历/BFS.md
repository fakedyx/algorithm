# BFS

## 1.[岛屿的周长](https://leetcode.cn/problems/island-perimeter/)

### 1.1题目描述

给定一个 row x col 的二维网格地图 grid ，其中：grid[i][j] = 1 表示陆地， grid[i][j] = 0 表示水域。

网格中的格子 水平和垂直 方向相连（对角线方向不相连）。整个网格被水完全包围，但其中恰好有一个岛屿（或者说，一个或多个表示陆地的格子相连组成的岛屿）。

岛屿中没有“湖”（“湖” 指水域在岛屿内部且不和岛屿周围的水相连）。格子是边长为 1 的正方形。网格为长方形，且宽度和高度均不超过 100 。计算这个岛屿的周长。

 示例 1：

![image-20230111154809940](C:/Users/24991/AppData/Roaming/Typora/typora-user-images/image-20230111154809940.png)

输入：grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
输出：16
解释：它的周长是上面图片中的 16 个黄色的边
示例 2：

输入：grid = [[1]]
输出：4
示例 3：

输入：grid = [[1,0]]
输出：4

### 1.2题目分析

- 深度优先遍历。对于一个陆地格子的每条边，它被算作岛屿的周长当且仅当这条边为网格的边界或者相邻的另一个格子为水域。 因此，我们可以遍历每个陆地格子，看其四个方向是否为边界或者水域，如果是，将这条边的贡献+1。为了防止陆地格子在深度优先搜索中被重复遍历导致死循环，我们需要将遍历过的陆地格子标记为已经遍历过，下面的代码中我们设定值为-1。

```c++
class Solution {
    /*用来表示上下左右*/
    constexpr static int dx[4] {0, 0, 1, -1};
    constexpr static int dy[4] {1, -1, 0, 0};
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int res = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(grid[i][j] == 1) {
                    /*陆地*/
                    res = dfs(grid, i, j, n, m);
                }
            }//for j
        }//for i
        return res;
    }

    int dfs(vector<vector<int>>& grid, int i, int j, int n, int m) {
        if(i < 0 || i >= n || j < 0 || j >= m || grid[i][j] == 0) {
            /*四周为边界--周长加1*/
            return 1;
        }

        if(grid[i][j] == -1) {
            /*已经遍历过*/
            return 0;
        }
        grid[i][j] = -1;
        int res = 0;
        for(int k = 0; k < 4; ++k) {
            int tx = i + dx[k];
            int ty = j + dy[k];
            res += dfs(grid, tx, ty, n, m);
        }
        return res;
    }
};
/*
时间复杂度：O(nm)，其中 n 为网格的高度，m 为网格的宽度。每个格子至多会被遍历一次，因此总时间复杂度为 O(nm)。

空间复杂度：O(nm)。深度优先搜索复杂度取决于递归的栈空间，而栈空间最坏情况下会达到 O(nm)。
*/
```

## 2.[岛屿的最大面积](https://leetcode.cn/problems/max-area-of-island/)

### 2.1题目描述

给你一个大小为 m x n 的二进制矩阵 grid 。

岛屿 是由一些相邻的 1 (代表土地) 构成的组合，这里的「相邻」要求两个 1 必须在 水平或者竖直的四个方向上 相邻。你可以假设 grid 的四个边缘都被 0（代表水）包围着。

岛屿的面积是岛上值为 1 的单元格的数目。

计算并返回 grid 中最大的岛屿面积。如果没有岛屿，则返回面积为 0 。 

示例 1：

![image-20230111190354768](C:/Users/24991/AppData/Roaming/Typora/typora-user-images/image-20230111190354768.png)

输入：grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
输出：6
解释：答案不应该是 11 ，因为岛屿只能包含水平或垂直这四个方向上的 1 。

### 2.2题目分析

```c++
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int ans = 0;
        for(int i = 0; i < grid.size(); ++i){
            for(int j = 0; j < grid[0].size(); ++j){
                ans = max(ans, Island(grid, i, j));
            }
        }
        return ans;
    }

    int Island(vector<vector<int>>& grid, int i, int j){
        //递归终止条件
        if(i >= grid.size() || j >= grid[0].size() || i < 0 || j < 0){
            return 0;
        }
        if(grid[i][j] == 0) return 0;
        grid[i][j] = 0;
        return 1 + Island(grid, i + 1, j) + Island(grid, i - 1, j) + Island(grid, i, j + 1) + Island(grid, i, j -1);
    }
};
```

## 3.[岛屿数量](https://leetcode.cn/problems/number-of-islands/)

### 3.1题目描述

给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。

此外，你可以假设该网格的四条边均被水包围。

示例 1：

输入：grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
输出：1

示例 2：

输入：grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
输出：3

### 3.2题目分析

我们可以将二维网格看成一个无向图，竖直或水平相邻的 1之间有边相连。为了求出岛屿的数量，我们可以扫描整个二维网格。如果一个位置为 1，则以其为起始节点开始进行深度优先搜索。在深度优先搜索的过程中，每个搜索到的 1都会被重新标记为 0。最终岛屿的数量就是我们进行深度优先搜索的次数。

```c++
class Solution {
    constexpr static int dx[4] {0, 0, 1, -1};
    constexpr static int dy[4] {1, -1, 0, 0};
public:
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size();
        if(n == 0) return 0;
        int m = grid[0].size();
        int nums = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(grid[i][j] == '1') {
                    ++nums;
                    //返回dfs遍历与其相连的所有1，并将其置为0
                    dfs(grid, i, j, n, m);
                }
            }//for j
        }//for i
        return nums;
    }

    void dfs(vector<vector<char>>& grid, int i, int j, int n, int m) {
        if(i < 0 || i >= n || j < 0 || j >= m || grid[i][j] == '0') {
            return;
        }

        grid[i][j] = '0';
        for(int k = 0; k < 4; ++k) {
            dfs(grid, i+dx[k], j+dy[k], n, m);
        }
    }
};

/*
时间复杂度为O(nm)
空间复杂度为O(nm)
*/
```




