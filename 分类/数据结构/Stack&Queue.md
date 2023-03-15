# Stack&Queue

## 1.[用队列实现栈](https://leetcode.cn/problems/implement-stack-using-queues/)

### 1.1题目描述

请你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作（push、top、pop 和 empty）。

实现 MyStack 类：

void push(int x) 将元素 x 压入栈顶。
int pop() 移除并返回栈顶元素。
int top() 返回栈顶元素。
boolean empty() 如果栈是空的，返回 true ；否则，返回 false 。


注意：

你只能使用队列的基本操作 —— 也就是 push to back、peek/pop from front、size 和 is empty 这些操作。
你所使用的语言也许不支持队列。 你可以使用 list （列表）或者 deque（双端队列）来模拟一个队列 , 只要是标准的队列操作即可。


示例：

输入：
["MyStack", "push", "push", "top", "pop", "empty"]
[[], [1], [2], [], [], []]
输出：
[null, null, null, 2, 2, false]

解释：
MyStack myStack = new MyStack();
myStack.push(1);
myStack.push(2);
myStack.top(); // 返回 2
myStack.pop(); // 返回 2
myStack.empty(); // 返回 False

### 1.2题目分析

- 双队列模拟。使用两个队列q1和q2，q1为保存最终结果的队列，q2是辅助入栈的队列。在入栈的时候，先将新元素入q2，然后将q1中的元素依次出队后入队q2，最后交换q1和q2。

```c++
class MyStack {
public:
    queue<int> q1;
    queue<int> q2;
    MyStack() {

    }
    
    void push(int x) {
        q2.push(x);
        int n = q1.size();
        for(int i = 0; i < n; ++i) {
            q2.push(q1.front());
            q1.pop();
        }
        swap(q1, q2);
    }
    
    int pop() {
        int elem = q1.front();
        q1.pop();
        return elem;
    }
    
    int top() {
        return q1.front();
    }
    
    bool empty() {
        return q1.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
```

- 单队列模拟。核心操作依旧在入栈操作，思想是将队列在逻辑上等效循环队列。我们先记录queue之前的size，然后将元素插入，再将新插入元素之前的元素依次入队再入队，即可以正确完成入栈操作。

```c++
class MyStack {
public:
    queue<int> q;
    MyStack() {

    }
    
    void push(int x) {
        int n = q.size();
        q.push(x);
        for(int i = 0; i < n; ++i) {
            q.push(q.front());
            q.pop();
        }
    }
    
    int pop() {
        int elem = q.front();
        q.pop();
        return elem;
    }
    
    int top() {
        return q.front();
    }
    
    bool empty() {
        return q.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
```

## 2[用栈实现队列](https://leetcode.cn/problems/implement-queue-using-stacks/)

### 2.1题目描述

请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（push、pop、peek、empty）：

实现 MyQueue 类：

void push(int x) 将元素 x 推到队列的末尾
int pop() 从队列的开头移除并返回元素
int peek() 返回队列开头的元素
boolean empty() 如果队列为空，返回 true ；否则，返回 false
说明：

你 只能 使用标准的栈操作 —— 也就是只有 push to top, peek/pop from top, size, 和 is empty 操作是合法的。
你所使用的语言也许不支持栈。你可以使用 list 或者 deque（双端队列）来模拟一个栈，只要是标准的栈操作即可。


示例 1：

输入：
["MyQueue", "push", "push", "peek", "pop", "empty"]
[[], [1], [2], [], [], []]
输出：
[null, null, null, 1, 1, false]

解释：
MyQueue myQueue = new MyQueue();
myQueue.push(1); // queue is: [1]
myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
myQueue.peek(); // return 1
myQueue.pop(); // return 1, queue is [2]
myQueue.empty(); // return false

### 2.2题目分析

- 错误做法

```c++
class MyQueue {
public:
    stack<int> s1;
    stack<int> s2;
    MyQueue() {

    }
    
    void push(int x) {
        s2.push(x);
        int n = s1.size();
        for(int i = 0; i < n; ++i) {
            s2.push(s1.top());
            s1.pop();
        }
        swap(s1, s2);
    }
    
    int pop() {
        int elem = s1.top();
        s1.pop();
        return elem;
    }
    
    int peek() {
        return s1.top();
    }
    
    bool empty() {
        return s1.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
```

- 双栈模拟输入输出

```c++
class MyQueue {
    void in2out() {
        while(!sin.empty()) {
            sout.push(sin.top());
            sin.pop();
        }
    }
public:
    stack<int> sin;
    stack<int> sout;
    MyQueue() {

    }
    
    void push(int x) {
        sin.push(x);
    }
    
    int pop() {
        if(sout.empty()) {
            in2out();  //将输入栈中数据放到输出栈中
        }
        int elem = sout.top();
        sout.pop();
        return elem;
    }
    
    int peek() {
        if(sout.empty()) {
            in2out();  //将输入栈中数据放到输出栈中
        }
        return sout.top();
    }
    
    bool empty() {
        return sin.empty() && sout.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
```



