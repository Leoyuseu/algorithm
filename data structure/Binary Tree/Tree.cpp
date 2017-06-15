\chapter{树}

LeetCode 上二叉树的节点定义如下：
\begin{Code}
// 树的节点
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }
};
\end{Code}


\section{二叉树的遍历} %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

树的遍历有两类：深度优先遍历和宽度优先遍历。深度优先遍历又可分为两种：
先根（次序）遍历和后根（次序）遍历。

树的先根遍历是：先访问树的根结点，然后依次先根遍历根的各棵子树。
树的先跟遍历的结果与对应二叉树（孩子兄弟表示法）的先序遍历的结果相同。

树的后根遍历是：先依次后根遍历树根的各棵子树，然后访问根结点。
树的后跟遍历的结果与对应二叉树的中序遍历的结果相同。

二叉树的先根遍历有：\textbf{先序遍历}(root->left->right)，root->right->left；
后根遍历有：\textbf{后序遍历}(left->right->root)，right->left->root；
二叉树还有个一般的树没有的遍历次序，\textbf{中序遍历}(left->root->right)。


\subsection{Binary Tree Preorder Traversal}
\label{sec:binary-tree-preorder-traversal}


\subsubsection{描述}
Given a binary tree, return the \emph{preorder} traversal of its nodes' values.

For example:
Given binary tree \code{\{1,\#,2,3\}},
\begin{Code}
 1
  \
   2
  /
 3
\end{Code}
return \code{[1,2,3]}.

Note: Recursive solution is trivial, could you do it iteratively?


\subsubsection{分析}
用栈或者Morris遍历。


subsubsection{栈}
begin{Code}
// LeetCode, Binary Tree Preorder Traversal
// 使用栈，时间复杂度O(n)，空间复杂度O(n)
class Solution {
public:
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> result;
        const TreeNode *p;
        stack<const TreeNode *> s;

        p = root;
        if (p != nullptr) s.push(p);

        while (!s.empty()) {
            p = s.top();
            s.pop();
            result.push_back(p->val);

            if (p->right != nullptr) s.push(p->right);
            if (p->left != nullptr) s.push(p->left);
        }
        return result;
    }
};
end{Code}


\subsubsection{Morris先序遍历}
\begin{Code}
// LeetCode, Binary Tree Preorder Traversal
// Morris先序遍历，时间复杂度O(n)，空间复杂度O(1)
class Solution {
public:
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> result;
        TreeNode *cur, *prev;

        cur = root;
        while (cur != nullptr) {
            if (cur->left == nullptr) {
                result.push_back(cur->val);
                prev = cur; /* cur刚刚被访问过 */
                cur = cur->right;
            } else {
                /* 查找前驱 */
                TreeNode *node = cur->left;
                while (node->right != nullptr && node->right != cur)
                    node = node->right;

                if (node->right == nullptr) { /* 还没线索化，则建立线索 */
                    result.push_back(cur->val); /* 仅这一行的位置与中序不同 */
                    node->right = cur;
                    prev = cur; /* cur刚刚被访问过 */
                    cur = cur->left;
                } else {    /* 已经线索化，则删除线索  */
                    node->right = nullptr;
                    /* prev = cur; 不能有这句，cur已经被访问 */
                    cur = cur->right;
                }
            }
        }
        return result;
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item Binary Tree Inorder Traversal，见 \S \ref{sec:binary-tree-inorder-traversal}
\item Binary Tree Postorder Traversal，见 \S \ref{sec:binary-tree-postorder-traversal}
\item Recover Binary Search Tree，见 \S \ref{sec:recover-binary-search-tree}
\myenddot


\subsection{Binary Tree Inorder Traversal}
\label{sec:binary-tree-inorder-traversal}


\subsubsection{描述}
Given a binary tree, return the \emph{inorder} traversal of its nodes' values.

For example:
Given binary tree \code{\{1,\#,2,3\}},
\begin{Code}
 1
  \
   2
  /
 3
\end{Code}
return \code{[1,3,2]}.

Note: Recursive solution is trivial, could you do it iteratively?


\subsubsection{分析}
用栈或者Morris遍历。


\subsubsection{栈}
\begin{Code}
// LeetCode, Binary Tree Inorder Traversal
// 使用栈，时间复杂度O(n)，空间复杂度O(n)
class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> result;
        const TreeNode *p = root;
        stack<const TreeNode *> s;

        while (!s.empty() || p != nullptr) {
            if (p != nullptr) {
                s.push(p);
                p = p->left;
            } else {
                p = s.top();
                s.pop();
                result.push_back(p->val);
                p = p->right;
            }
        }
        return result;
    }
};
\end{Code}


\subsubsection{Morris中序遍历}
\begin{Code}
// LeetCode, Binary Tree Inorder Traversal
// Morris中序遍历，时间复杂度O(n)，空间复杂度O(1)
class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> result;
        TreeNode *cur, *prev;

        cur = root;
        while (cur != nullptr) {
            if (cur->left == nullptr) {
                result.push_back(cur->val);
                prev = cur;
                cur = cur->right;
            } else {
                /* 查找前驱 */
                TreeNode *node = cur->left;
                while (node->right != nullptr && node->right != cur)
                    node = node->right;

                if (node->right == nullptr) { /* 还没线索化，则建立线索 */
                    node->right = cur;
                    /* prev = cur; 不能有这句，cur还没有被访问 */
                    cur = cur->left;
                } else {    /* 已经线索化，则访问节点，并删除线索  */
                    result.push_back(cur->val);
                    node->right = nullptr;
                    prev = cur;
                    cur = cur->right;
                }
            }
        }
        return result;
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item Binary Tree Preorder Traversal，见 \S \ref{sec:binary-tree-preorder-traversal}
\item Binary Tree Postorder Traversal，见 \S \ref{sec:binary-tree-postorder-traversal}
\item Recover Binary Search Tree，见 \S \ref{sec:recover-binary-search-tree}
\myenddot


\subsection{Binary Tree Postorder Traversal}
\label{sec:binary-tree-postorder-traversal}


\subsubsection{描述}
Given a binary tree, return the \emph{postorder} traversal of its nodes' values.

For example:
Given binary tree \code{\{1,\#,2,3\}},
\begin{Code}
 1
  \
   2
  /
 3
\end{Code}
return \code{[3,2,1]}.

Note: Recursive solution is trivial, could you do it iteratively?


\subsubsection{分析}
用栈或者Morris遍历。


\subsubsection{栈}
\begin{Code}
// LeetCode, Binary Tree Postorder Traversal
// 使用栈，时间复杂度O(n)，空间复杂度O(n)
class Solution {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> result;
        /* p，正在访问的结点，q，刚刚访问过的结点*/
        const TreeNode *p, *q;
        stack<const TreeNode *> s;

        p = root;

        do {
            while (p != nullptr) { /* 往左下走*/
                s.push(p);
                p = p->left;
            }
            q = nullptr;
            while (!s.empty()) {
                p = s.top();
                s.pop();
                /* 右孩子不存在或已被访问，访问之*/
                if (p->right == q) {
                    result.push_back(p->val);
                    q = p; /* 保存刚访问过的结点*/
                } else {
                    /* 当前结点不能访问，需第二次进栈*/
                    s.push(p);
                    /* 先处理右子树*/
                    p = p->right;
                    break;
                }
            }
        } while (!s.empty());

        return result;
    }
};
\end{Code}


\subsubsection{Morris后序遍历}
\begin{Code}
// LeetCode, Binary Tree Postorder Traversal
// Morris后序遍历，时间复杂度O(n)，空间复杂度O(1)
class Solution {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> result;
        TreeNode dummy(-1);
        TreeNode *cur, *prev = nullptr;
        std::function < void(const TreeNode*)> visit = 
            [&result](const TreeNode *node){
            result.push_back(node->val); 
        };

        dummy.left = root;
        cur = &dummy;
        while (cur != nullptr) {
            if (cur->left == nullptr) {
                prev = cur; /* 必须要有 */
                cur = cur->right;
            } else {
                TreeNode *node = cur->left;
                while (node->right != nullptr && node->right != cur)
                    node = node->right;

                if (node->right == nullptr) { /* 还没线索化，则建立线索 */
                    node->right = cur;
                    prev = cur; /* 必须要有 */
                    cur = cur->left;
                } else { /* 已经线索化，则访问节点，并删除线索  */
                    visit_reverse(cur->left, prev, visit);
                    prev->right = nullptr;
                    prev = cur; /* 必须要有 */
                    cur = cur->right;
                }
            }
        }
        return result;
    }
private:
    // 逆转路径
    static void reverse(TreeNode *from, TreeNode *to) {
        TreeNode *x = from, *y = from->right, *z;
        if (from == to) return;

        while (x != to) {
            z = y->right;
            y->right = x;
            x = y;
            y = z;
        }
    }

    // 访问逆转后的路径上的所有结点
    static void visit_reverse(TreeNode* from, TreeNode *to, 
                     std::function< void(const TreeNode*) >& visit) {
        TreeNode *p = to;
        reverse(from, to);

        while (true) {
            visit(p);
            if (p == from)
                break;
            p = p->right;
        }

        reverse(to, from);
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item Binary Tree Preorder Traversal，见 \S \ref{sec:binary-tree-preorder-traversal}
\item Binary Tree Inorder Traversal，见 \S \ref{sec:binary-tree-inorder-traversal}
\item Recover Binary Search Tree，见 \S \ref{sec:recover-binary-search-tree}
\myenddot


\subsection{Binary Tree Level Order Traversal}
\label{sec:binary-tree-tevel-order-traversal}


\subsubsection{描述}
Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree \code{\{3,9,20,\#,\#,15,7\}},
\begin{Code}
    3
   / \
  9  20
    /  \
   15   7
\end{Code}
return its level order traversal as:
\begin{Code}
[
  [3],
  [9,20],
  [15,7]
]
\end{Code}


\subsubsection{分析}
无


\subsubsection{递归版}
\begin{Code}
// LeetCode, Binary Tree Level Order Traversal
// 递归版，时间复杂度O(n)，空间复杂度O(n)
class Solution {
public:
    vector<vector<int> > levelOrder(TreeNode *root) {
        vector<vector<int>> result;
        traverse(root, 1, result);
        return result;
    }

    void traverse(TreeNode *root, size_t level, vector<vector<int>> &result) {
        if (!root) return;

        if (level > result.size())
            result.push_back(vector<int>());

        result[level-1].push_back(root->val);
        traverse(root->left, level+1, result);
        traverse(root->right, level+1, result);
    }
};
\end{Code}


\subsubsection{迭代版}
\begin{Code}
// LeetCode, Binary Tree Level Order Traversal
// 迭代版，时间复杂度O(n)，空间复杂度O(1)
class Solution {
public:
    vector<vector<int> > levelOrder(TreeNode *root) {
        vector<vector<int> > result;
        if(root == nullptr) return result;

        queue<TreeNode*> current, next;
        vector<int> level; // elments in level level

        current.push(root);
        while (!current.empty()) {
            while (!current.empty()) {
                TreeNode* node = current.front();
                current.pop();
                level.push_back(node->val);
                if (node->left != nullptr) next.push(node->left);
                if (node->right != nullptr) next.push(node->right);
            }
            result.push_back(level);
            level.clear();
            swap(next, current);
        }
        return result;
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item Binary Tree Level Order Traversal II，见 \S \ref{sec:binary-tree-tevel-order-traversal-ii}
\item Binary Tree Zigzag Level Order Traversal，见 \S \ref{sec:binary-tree-zigzag-level-order-traversal}
\myenddot


\subsection{Binary Tree Level Order Traversal II}
\label{sec:binary-tree-tevel-order-traversal-ii}


\subsubsection{描述}
Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

For example:
Given binary tree \code{\{3,9,20,\#,\#,15,7\}},
\begin{Code}
    3
   / \
  9  20
    /  \
   15   7
\end{Code}
return its bottom-up level order traversal as:
\begin{Code}
[
  [15,7]
  [9,20],
  [3],
]
\end{Code}


\subsubsection{分析}
在上一题（见\S \ref{sec:binary-tree-tevel-order-traversal}）的基础上，\fn{reverse()}一下即可。


\subsubsection{递归版}
\begin{Code}
// LeetCode, Binary Tree Level Order Traversal II
// 递归版，时间复杂度O(n)，空间复杂度O(n)
class Solution {
public:
    vector<vector<int> > levelOrderBottom(TreeNode *root) {
        vector<vector<int>> result;
        traverse(root, 1, result);
        std::reverse(result.begin(), result.end()); // 比上一题多此一行
        return result;
    }

    void traverse(TreeNode *root, size_t level, vector<vector<int>> &result) {
        if (!root) return;

        if (level > result.size())
            result.push_back(vector<int>());

        result[level-1].push_back(root->val);
        traverse(root->left, level+1, result);
        traverse(root->right, level+1, result);
    }
};
\end{Code}


\subsubsection{迭代版}
\begin{Code}
// LeetCode, Binary Tree Level Order Traversal II
// 迭代版，时间复杂度O(n)，空间复杂度O(1)
class Solution {
public:
    vector<vector<int> > levelOrderBottom(TreeNode *root) {
        vector<vector<int> > result;
        if(root == nullptr) return result;

        queue<TreeNode*> current, next;
        vector<int> level; // elments in level level

        current.push(root);
        while (!current.empty()) {
            while (!current.empty()) {
                TreeNode* node = current.front();
                current.pop();
                level.push_back(node->val);
                if (node->left != nullptr) next.push(node->left);
                if (node->right != nullptr) next.push(node->right);
            }
            result.push_back(level);
            level.clear();
            swap(next, current);
        }
        reverse(result.begin(), result.end()); // 比上一题多此一行
        return result;
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item Binary Tree Level Order Traversal，见 \S \ref{sec:binary-tree-tevel-order-traversal}
\item Binary Tree Zigzag Level Order Traversal，见 \S \ref{sec:binary-tree-zigzag-level-order-traversal}
\myenddot


\subsection{Binary Tree Zigzag Level Order Traversal}
\label{sec:binary-tree-zigzag-level-order-traversal}


\subsubsection{描述}
Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree \code{{3,9,20,\#,\#,15,7}},
\begin{Code}
    3
   / \
  9  20
    /  \
   15   7
\end{Code}
return its zigzag level order traversal as:
\begin{Code}
[
  [3],
  [20,9],
  [15,7]
]
\end{Code}


\subsubsection{分析}
广度优先遍历，用一个bool记录是从左到右还是从右到左，每一层结束就翻转一下。


\subsubsection{递归版}
\begin{Code}
// LeetCode, Binary Tree Zigzag Level Order Traversal
// 递归版，时间复杂度O(n)，空间复杂度O(n)
class Solution {
public:
    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
        vector<vector<int>> result;
        traverse(root, 1, result, true);
        return result;
    }

    void traverse(TreeNode *root, size_t level, vector<vector<int>> &result,
            bool left_to_right) {
        if (!root) return;

        if (level > result.size())
            result.push_back(vector<int>());

        if (left_to_right)
            result[level-1].push_back(root->val);
        else
            result[level-1].insert(result[level-1].begin(), root->val);

        traverse(root->left, level+1, result, !left_to_right);
        traverse(root->right, level+1, result, !left_to_right);
    }
};
\end{Code}

\subsubsection{迭代版}
\begin{Code}
//LeetCode, Binary Tree Zigzag Level Order Traversal
//广度优先遍历，用一个bool记录是从左到右还是从右到左，每一层结束就翻转一下。
// 迭代版，时间复杂度O(n)，空间复杂度O(n)
class Solution {
public:
    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
        vector<vector<int> > result;
        if (nullptr == root) return result;

        queue<TreeNode*> q;
        bool left_to_right = true;  //left to right
        vector<int> level;  // one level's elements

        q.push(root);
        q.push(nullptr);  // level separator
        while (!q.empty()) {
            TreeNode *cur = q.front();
            q.pop();
            if (cur) {
                level.push_back(cur->val);
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            } else {
                if (left_to_right) {
                    result.push_back(level);
                } else {
                    reverse(level.begin(), level.end());
                    result.push_back(level);
                }
                level.clear();
                left_to_right = !left_to_right;

                if (q.size() > 0) q.push(nullptr);
            }
        }

        return result;
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item Binary Tree Level Order Traversal，见 \S \ref{sec:binary-tree-tevel-order-traversal}
\item Binary Tree Level Order Traversal II，见 \S \ref{sec:binary-tree-tevel-order-traversal-ii}
\myenddot


\subsection{Recover Binary Search Tree}
\label{sec:recover-binary-search-tree}


\subsubsection{描述}
Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Note: A solution using $O(n)$ space is pretty straight forward. Could you devise a constant space solution?


\subsubsection{分析}
$O(n)$空间的解法是，开一个指针数组，中序遍历，将节点指针依次存放到数组里，然后寻找两处逆向的位置，先从前往后找第一个逆序的位置，然后从后往前找第二个逆序的位置，交换这两个指针的值。

中序遍历一般需要用到栈，空间也是$O(n)$的，如何才能不使用栈？Morris中序遍历。


\subsubsection{代码}

\begin{Code}
// LeetCode, Recover Binary Search Tree
// Morris中序遍历，时间复杂度O(n)，空间复杂度O(1)
class Solution {
public:
    void recoverTree(TreeNode* root) {
        pair<TreeNode*, TreeNode*> broken;
        TreeNode* prev = nullptr;
        TreeNode* cur = root;

        while (cur != nullptr) {
            if (cur->left == nullptr) {
                detect(broken, prev, cur);
                prev = cur;
                cur = cur->right;
            } else {
                auto node = cur->left;

                while (node->right != nullptr && node->right != cur)
                    node = node->right;

                if (node->right == nullptr) {
                    node->right = cur;
                    //prev = cur; 不能有这句！因为cur还没有被访问
                    cur = cur->left;
                } else {
                    detect(broken, prev, cur);
                    node->right = nullptr;
                    prev = cur;
                    cur = cur->right;
                }
            }
        }

        swap(broken.first->val, broken.second->val);
    }

    void detect(pair<TreeNode*, TreeNode*>& broken, TreeNode* prev,
            TreeNode* current) {
        if (prev != nullptr && prev->val > current->val) {
            if (broken.first == nullptr) {
                broken.first = prev;
            } //不能用else，例如 {0,1}，会导致最后 swap时second为nullptr，
              //会 Runtime Error
            broken.second = current;
        }
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item Binary Tree Inorder Traversal，见 \S \ref{sec:binary-tree-inorder-traversal}
\myenddot


\subsection{Same Tree}
\label{sec:same-tree}


\subsubsection{描述}
Given two binary trees, write a function to check if they are equal or not.

Two binary trees are considered equal if they are structurally identical and the nodes have the same value.


\subsubsection{分析}
无


\subsubsection{递归版}
递归版
\begin{Code}
// LeetCode, Same Tree
// 递归版，时间复杂度O(n)，空间复杂度O(logn)
class Solution {
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        if (!p && !q) return true;   // 终止条件
        if (!p || !q) return false;  // 剪枝
        return p->val == q->val      // 三方合并
                && isSameTree(p->left, q->left)
                && isSameTree(p->right, q->right);
    }
};
\end{Code}


\subsubsection{迭代版}
\begin{Code}
// LeetCode, Same Tree
// 迭代版，时间复杂度O(n)，空间复杂度O(logn)
class Solution {
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        stack<TreeNode*> s;
        s.push(p);
        s.push(q);

        while(!s.empty()) {
            p = s.top(); s.pop();
            q = s.top(); s.pop();

            if (!p && !q) continue;
            if (!p || !q) return false;
            if (p->val != q->val) return false;

            s.push(p->left);
            s.push(q->left);

            s.push(p->right);
            s.push(q->right);
        }
        return true;
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item Symmetric Tree，见 \S \ref{sec:symmetric-tree}
\myenddot


\subsection{Symmetric Tree}
\label{sec:symmetric-tree}


\subsubsection{描述}
Given two binary trees, write a function to check if they are equal or not.

Two binary trees are considered equal if they are structurally identical and the nodes have the same value.


\subsubsection{分析}
无


\subsubsection{递归版}
\begin{Code}
// LeetCode, Symmetric Tree
// 递归版，时间复杂度O(n)，空间复杂度O(logn)
class Solution {
public:
    bool isSymmetric(TreeNode *root) {
        return root ? isSymmetric(root->left, root->right) : true;
    }
    bool isSymmetric(TreeNode *left, TreeNode *right) {
        if (!left && !right) return true;   // 终止条件
        if (!left || !right) return false;  // 终止条件
        return left->val == right->val      // 三方合并
                && isSymmetric(left->left, right->right)
                && isSymmetric(left->right, right->left);
    }
};
\end{Code}


\subsubsection{迭代版}
\begin{Code}
// LeetCode, Symmetric Tree
// 迭代版，时间复杂度O(n)，空间复杂度O(logn)
class Solution {
public:
    bool isSymmetric (TreeNode* root) {
        if (!root) return true;

        stack<TreeNode*> s;
        s.push(root->left);
        s.push(root->right);

        while (!s.empty ()) {
            auto p = s.top (); s.pop();
            auto q = s.top (); s.pop();

            if (!p && !q) continue;
            if (!p || !q) return false;
            if (p->val != q->val) return false;

            s.push(p->left);
            s.push(q->right);

            s.push(p->right);
            s.push(q->left);
        }

        return true;
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item Same Tree，见 \S \ref{sec:same-tree}
\myenddot


\subsection{Balanced Binary Tree}
\label{sec:balanced-binary-tree}


\subsubsection{描述}
Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.


\subsubsection{分析}
无


\subsubsection{代码}
\begin{Code}
// LeetCode, Balanced Binary Tree
// 时间复杂度O(n)，空间复杂度O(logn)
class Solution {
public:
    bool isBalanced (TreeNode* root) {
        return balancedHeight (root) >= 0;
    }

    /**
     * Returns the height of `root` if `root` is a balanced tree,
     * otherwise, returns `-1`.
     */
    int balancedHeight (TreeNode* root) {
        if (root == nullptr) return 0;  // 终止条件

        int left = balancedHeight (root->left);
        int right = balancedHeight (root->right);

        if (left < 0 || right < 0 || abs(left - right) > 1) return -1;  // 剪枝

        return max(left, right) + 1; // 三方合并
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item 无
\myenddot


\subsection{Flatten Binary Tree to Linked List}
\label{sec:flatten-binary-tree-to-linked-list}


\subsubsection{描述}
Given a binary tree, flatten it to a linked list in-place.

For example, Given
\begin{Code}
         1
        / \
       2   5
      / \   \
     3   4   6
\end{Code}

The flattened tree should look like:
\begin{Code}
   1
    \
     2
      \
       3
        \
         4
          \
           5
            \
             6
\end{Code}

\subsubsection{分析}
无


\subsubsection{递归版1}
\begin{Code}
// LeetCode, Flatten Binary Tree to Linked List
// 递归版1，时间复杂度O(n)，空间复杂度O(logn)
class Solution {
public:
    void flatten(TreeNode *root) {
        if (root == nullptr) return;  // 终止条件

        flatten(root->left);
        flatten(root->right);

        if (nullptr == root->left) return;

        // 三方合并，将左子树所形成的链表插入到root和root->right之间
        TreeNode *p = root->left;
        while(p->right) p = p->right; //寻找左链表最后一个节点
        p->right = root->right;
        root->right = root->left;
        root->left = nullptr;
    }
};
\end{Code}


\subsubsection{递归版2}
\begin{Code}
// LeetCode, Flatten Binary Tree to Linked List
// 递归版2
// @author 王顺达(http://weibo.com/u/1234984145)
// 时间复杂度O(n)，空间复杂度O(logn)
class Solution {
public:
    void flatten(TreeNode *root) {
        flatten(root, NULL);
    }
private:
    // 把root所代表树变成链表后，tail跟在该链表后面
    TreeNode *flatten(TreeNode *root, TreeNode *tail) {
        if (NULL == root) return tail;

        root->right = flatten(root->left, flatten(root->right, tail));
        root->left = NULL;
        return root;
    }
};
\end{Code}


\subsubsection{迭代版}
\begin{Code}
// LeetCode, Flatten Binary Tree to Linked List
// 迭代版，时间复杂度O(n)，空间复杂度O(logn)
class Solution {
public:
    void flatten(TreeNode* root) {
        if (root == nullptr) return;

        stack<TreeNode*> s;
        s.push(root);

        while (!s.empty()) {
            auto p = s.top();
            s.pop();

            if (p->right)
                s.push(p->right);
            if (p->left)
                s.push(p->left);

            p->left = nullptr;
            if (!s.empty())
                p->right = s.top();
        }
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item 无
\myenddot


\subsection{Populating Next Right Pointers in Each Node II} %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\label{sec:populating-next-right-pointers-in-each-node-ii}


\subsubsection{描述}
Follow up for problem "Populating Next Right Pointers in Each Node".

What if the given tree could be any binary tree? Would your previous solution still work?

Note: You may only use constant extra space.

For example,
Given the following binary tree,
\begin{Code}
         1
       /  \
      2    3
     / \    \
    4   5    7
\end{Code}

After calling your function, the tree should look like:
\begin{Code}
         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \    \
    4-> 5 -> 7 -> NULL
\end{Code}


\subsubsection{分析}
要处理一个节点，可能需要最右边的兄弟节点，首先想到用广搜。但广搜不是常数空间的，本题要求常数空间。

注意，这题的代码原封不动，也可以解决 Populating Next Right Pointers in Each Node I.


\subsubsection{递归版}
\begin{Code}
// LeetCode, Populating Next Right Pointers in Each Node II
// 时间复杂度O(n)，空间复杂度O(1)
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if (root == nullptr) return;

        TreeLinkNode dummy(-1);
        for (TreeLinkNode *curr = root, *prev = &dummy; 
                curr; curr = curr->next) {
            if (curr->left != nullptr){
                prev->next = curr->left;
                prev = prev->next;
            }
            if (curr->right != nullptr){
                prev->next = curr->right;
                prev = prev->next;
            }
        }
        connect(dummy.next);
    }
};
\end{Code}


\subsubsection{迭代版}
\begin{Code}
// LeetCode, Populating Next Right Pointers in Each Node II
// 时间复杂度O(n)，空间复杂度O(1)
class Solution {
public:
    void connect(TreeLinkNode *root) {
        while (root) {
            TreeLinkNode * next = nullptr; // the first node of next level
            TreeLinkNode * prev = nullptr; // previous node on the same level
            for (; root; root = root->next) {
                if (!next) next = root->left ? root->left : root->right;

                if (root->left) {
                    if (prev) prev->next = root->left;
                    prev = root->left;
                }
                if (root->right) {
                    if (prev) prev->next = root->right;
                    prev = root->right;
                }
            }
            root = next; // turn to next level
        }
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item Populating Next Right Pointers in Each Node，见 \S \ref{sec:populating-next-right-pointers-in-each-node}
\myenddot


\section{二叉树的构建} %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


\subsection{Construct Binary Tree from Preorder and Inorder Traversal}
\label{sec:construct-binary-tree-from-preorder-and-inorder-traversal}


\subsubsection{描述}
Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.


\subsubsection{分析}
无


\subsubsection{代码}
\begin{Code}
// LeetCode, Construct Binary Tree from Preorder and Inorder Traversal
// 递归，时间复杂度O(n)，空间复杂度O(\logn)
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return buildTree(begin(preorder), end(preorder),
                begin(inorder), end(inorder));
    }

    template<typename InputIterator>
    TreeNode* buildTree(InputIterator pre_first, InputIterator pre_last,
            InputIterator in_first, InputIterator in_last) {
        if (pre_first == pre_last) return nullptr;
        if (in_first == in_last) return nullptr;

        auto root = new TreeNode(*pre_first);

        auto inRootPos = find(in_first, in_last, *pre_first);
        auto leftSize = distance(in_first, inRootPos);

        root->left = buildTree(next(pre_first), next(pre_first,
                leftSize + 1), in_first, next(in_first, leftSize));
        root->right = buildTree(next(pre_first, leftSize + 1), pre_last,
                next(inRootPos), in_last);

        return root;
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item Construct Binary Tree from Inorder and Postorder Traversal，见 \S \ref{sec:construct-binary-tree-from-inorder-and-postorder-traversal}
\myenddot


\subsection{Construct Binary Tree from Inorder and Postorder Traversal}
\label{sec:construct-binary-tree-from-inorder-and-postorder-traversal}


\subsubsection{描述}
Given inorder and postorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.


\subsubsection{分析}
无


\subsubsection{代码}
\begin{Code}
// LeetCode, Construct Binary Tree from Inorder and Postorder Traversal
// 递归，时间复杂度O(n)，空间复杂度O(\logn)
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return buildTree(begin(inorder), end(inorder),
                begin(postorder), end(postorder));
    }

    template<typename BidiIt>
    TreeNode* buildTree(BidiIt in_first, BidiIt in_last,
            BidiIt post_first, BidiIt post_last) {
        if (in_first ==in_last) return nullptr;
        if (post_first == post_last) return nullptr;

        const auto val = *prev(post_last);
        TreeNode* root = new TreeNode(val);

        auto in_root_pos = find(in_first, in_last, val);
        auto left_size = distance(in_first, in_root_pos);
        auto post_left_last = next(post_first, left_size);

        root->left = buildTree(in_first, in_root_pos, post_first, post_left_last);
        root->right = buildTree(next(in_root_pos), in_last, post_left_last,
                prev(post_last));

        return root;
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item Construct Binary Tree from Preorder and Inorder Traversal，见 \S \ref{sec:construct-binary-tree-from-preorder-and-inorder-traversal}
\myenddot


\section{二叉查找树} %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


\subsection{Unique Binary Search Trees}
\label{sec:unique-binary-search-trees}


\subsubsection{描述}
Given $n$, how many structurally unique BST's (binary search trees) that store values $1...n$?

For example,
Given $n = 3$, there are a total of 5 unique BST's.
\begin{Code}
   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
\end{Code}

\subsubsection{分析}
如果把上例的顺序改一下，就可以看出规律了。
\begin{Code}
 1       1           2          3       3
  \       \         / \        /       / 
   3       2       1   3      2       1
  /         \                /         \
2            3              1           2
\end{Code}

比如，以1为根的树的个数，等于左子树的个数乘以右子树的个数，左子树是0个元素的树，右子树是2个元素的树。以2为根的树的个数，等于左子树的个数乘以右子树的个数，左子树是1个元素的树，右子树也是1个元素的树。依此类推。

当数组为 $1,2,3,...,n$时，基于以下原则的构建的BST树具有唯一性：
\textbf{以i为根节点的树，其左子树由[1, i-1]构成， 其右子树由[i+1, n]构成。}

定义$f(i)$为以$[1,i]$能产生的Unique Binary Search Tree的数目，则

如果数组为空，毫无疑问，只有一种BST，即空树，$f(0)=1$。

如果数组仅有一个元素{1}，只有一种BST，单个节点，$f(1)=1$。

如果数组有两个元素{1,2}， 那么有如下两种可能
\begin{Code}
1             2
  \          /
    2      1
\end{Code}

\begin{eqnarray}
f(2) &=& f(0) * f(1)   \text{ ，1为根的情况} \nonumber \\
     &+& f(1) * f(0)   \text{ ，2为根的情况} \nonumber
\end{eqnarray}

再看一看3个元素的数组，可以发现BST的取值方式如下：
\begin{eqnarray}
f(3) &=& f(0) * f(2)   \text{ ，1为根的情况} \nonumber \\
     &+& f(1) * f(1)   \text{ ，2为根的情况} \nonumber \\
     &+& f(2) * f(0)   \text{ ，3为根的情况} \nonumber
\end{eqnarray}

所以，由此观察，可以得出$f$的递推公式为
$$
f(i) = \sum_{k=1}^{i} f(k-1) \times f(i-k)
$$
至此，问题划归为一维动态规划。


\subsubsection{代码}

\begin{Code}
// LeetCode, Unique Binary Search Trees
// 时间复杂度O(n^2)，空间复杂度O(n)
class Solution {
public:
    int numTrees(int n) {
        vector<int> f(n + 1, 0);

        f[0] = 1;
        f[1] = 1;
        for (int i = 2; i <= n; ++i) {
            for (int k = 1; k <= i; ++k)
                f[i] += f[k-1] * f[i - k];
        }

        return f[n];
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item Unique Binary Search Trees II，见 \S \ref{sec:unique-binary-search-trees-ii}
\myenddot


\subsection{Unique Binary Search Trees II}
\label{sec:unique-binary-search-trees-ii}


\subsubsection{描述}
Given $n$, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given $n = 3$, your program should return all 5 unique BST's shown below.
\begin{Code}
   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
\end{Code}


\subsubsection{分析}
见前面一题。


\subsubsection{代码}

\begin{Code}
// LeetCode, Unique Binary Search Trees II
// 时间复杂度TODO，空间复杂度TODO
class Solution {
public:
    vector<TreeNode *> generateTrees(int n) {
        if (n == 0) return generate(1, 0);
        return generate(1, n);
    }
private:
    vector<TreeNode *> generate(int start, int end) {
        vector<TreeNode*> subTree;
        if (start > end) {
            subTree.push_back(nullptr);
            return subTree;
        }
        for (int k = start; k <= end; k++) {
            vector<TreeNode*> leftSubs = generate(start, k - 1);
            vector<TreeNode*> rightSubs = generate(k + 1, end);
            for (auto i : leftSubs) {
                for (auto j : rightSubs) {
                    TreeNode *node = new TreeNode(k);
                    node->left = i;
                    node->right = j;
                    subTree.push_back(node);
                }
            }
        }
        return subTree;
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item Unique Binary Search Trees，见 \S \ref{sec:unique-binary-search-trees}
\myenddot


\subsection{Validate Binary Search Tree}
\label{sec:validate-binary-search-tree}


\subsubsection{描述}
Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:
\begindot
\item The left subtree of a node contains only nodes with keys less than the node's key.
\item The right subtree of a node contains only nodes with keys greater than the node's key.
\item Both the left and right subtrees must also be binary search trees.
\myenddot


\subsubsection{分析}


\subsubsection{代码}

\begin{Code}
// LeetCode, Validate Binary Search Tree
// 时间复杂度O(n)，空间复杂度O(\logn)
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return isValidBST(root, INT_MIN, INT_MAX);
    }

    bool isValidBST(TreeNode* root, int lower, int upper) {
        if (root == nullptr) return true;

        return root->val > lower && root->val < upper
                && isValidBST(root->left, lower, root->val)
                && isValidBST(root->right, root->val, upper);
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item Validate Binary Search Tree，见 \S \ref{sec:validate-binary-search-tree}
\myenddot


\subsection{Convert Sorted Array to Binary Search Tree}
\label{sec:convert-sorted-array-to-binary-search-tree}


\subsubsection{描述}
Given an array where elements are sorted in ascending order, convert it to a height balanced BST.


\subsubsection{分析}
二分法。


\subsubsection{代码}

\begin{Code}
// LeetCode, Convert Sorted Array to Binary Search Tree
// 分治法，时间复杂度O(n)，空间复杂度O(logn)
class Solution {
public:
    TreeNode* sortedArrayToBST (vector<int>& num) {
        return sortedArrayToBST(num.begin(), num.end());
    }

    template<typename RandomAccessIterator>
    TreeNode* sortedArrayToBST (RandomAccessIterator first,
            RandomAccessIterator last) {
        const auto length = distance(first, last);

        if (length <= 0) return nullptr;  // 终止条件

        // 三方合并
        auto mid = first + length / 2;
        TreeNode* root = new TreeNode (*mid);
        root->left = sortedArrayToBST(first, mid);
        root->right = sortedArrayToBST(mid + 1, last);

        return root;
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item Convert Sorted List to Binary Search Tree，见 \S \ref{sec:convert-sorted-list-to-binary-search-tree}
\myenddot


\subsection{Convert Sorted List to Binary Search Tree}
\label{sec:convert-sorted-list-to-binary-search-tree}


\subsubsection{描述}
Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.


\subsubsection{分析}
这题与上一题类似，但是单链表不能随机访问，而自顶向下的二分法必须需要RandomAccessIterator，因此前面的方法不适用本题。

存在一种自底向上(bottom-up)的方法，见\myurl{http://leetcode.com/2010/11/convert-sorted-list-to-balanced-binary.html}


\subsubsection{分治法，自顶向下}
分治法，类似于 Convert Sorted Array to Binary Search Tree，自顶向下，复杂度$O(n\log n)$。
\begin{Code}
// LeetCode, Convert Sorted List to Binary Search Tree
// 分治法，类似于 Convert Sorted Array to Binary Search Tree，
// 自顶向下，时间复杂度O(n^2)，空间复杂度O(logn)
class Solution {
public:
    TreeNode* sortedListToBST (ListNode* head) {
        return sortedListToBST (head, listLength (head));
    }

    TreeNode* sortedListToBST (ListNode* head, int len) {
        if (len == 0) return nullptr;
        if (len == 1) return new TreeNode (head->val);

        TreeNode* root = new TreeNode (nth_node (head, len / 2 + 1)->val);
        root->left = sortedListToBST (head, len / 2);
        root->right = sortedListToBST (nth_node (head, len / 2 + 2), 
                (len - 1) / 2);

        return root;
    }

    int listLength (ListNode* node) {
        int n = 0;

        while(node) {
            ++n;
            node = node->next;
        }

        return n;
    }

    ListNode* nth_node (ListNode* node, int n) {
        while (--n)
            node = node->next;

        return node;
    }
};
\end{Code}


\subsubsection{自底向上}
\begin{Code}
// LeetCode, Convert Sorted List to Binary Search Tree
// bottom-up，时间复杂度O(n)，空间复杂度O(logn)
class Solution {
public:
    TreeNode *sortedListToBST(ListNode *head) {
        int len = 0;
        ListNode *p = head;
        while (p) {
            len++;
            p = p->next;
        }
        return sortedListToBST(head, 0, len - 1);
    }
private:
    TreeNode* sortedListToBST(ListNode*& list, int start, int end) {
        if (start > end) return nullptr;

        int mid = start + (end - start) / 2;
        TreeNode *leftChild = sortedListToBST(list, start, mid - 1);
        TreeNode *parent = new TreeNode(list->val);
        parent->left = leftChild;
        list = list->next;
        parent->right = sortedListToBST(list, mid + 1, end);
        return parent;
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item Convert Sorted Array to Binary Search Tree，见 \S \ref{sec:convert-sorted-array-to-binary-search-tree}
\myenddot


\section{二叉树的递归} %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
二叉树是一个递归的数据结构，因此是一个用来考察递归思维能力的绝佳数据结构。

递归一定是深搜（见 \S \ref{sec:dfs-vs-recursion}节 “深搜与递归的区别”），由于在二叉树上，递归的味道更浓些，因此本节用“二叉树的递归”作为标题，而不是“二叉树的深搜”，尽管本节所有的算法都属于深搜。

二叉树的先序、中序、后序遍历都可以看做是DFS，此外还有其他顺序的深度优先遍历，共有$3!=6$种。其他3种顺序是 \fn{root->r->l，r->root->l, r->l->root}。


\subsection{Minimum Depth of Binary Tree}
\label{sec:minimum-depth-of-binary-tree}


\subsubsection{描述}
Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.


\subsubsection{分析}
无


\subsubsection{递归版}
\begin{Code}
// LeetCode, Minimum Depth of Binary Tree
// 递归版，时间复杂度O(n)，空间复杂度O(logn)
class Solution {
public:
    int minDepth(const TreeNode *root) {
        return minDepth(root, false);
    }
private:
    static int minDepth(const TreeNode *root, bool hasbrother) {
        if (!root) return hasbrother ? INT_MAX : 0;

        return 1 + min(minDepth(root->left, root->right != NULL),
                minDepth(root->right, root->left != NULL));
    }
};
\end{Code}


\subsubsection{迭代版}
\begin{Code}
// LeetCode, Minimum Depth of Binary Tree
// 迭代版，时间复杂度O(n)，空间复杂度O(logn)
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root == nullptr)
            return 0;

        int result = INT_MAX;

        stack<pair<TreeNode*, int>> s;
        s.push(make_pair(root, 1));

        while (!s.empty()) {
            auto node = s.top().first;
            auto depth = s.top().second;
            s.pop();

            if (node->left == nullptr && node->right == nullptr)
                result = min(result, depth);

            if (node->left && result > depth) // 深度控制，剪枝
                s.push(make_pair(node->left, depth + 1));

            if (node->right && result > depth) // 深度控制，剪枝
                s.push(make_pair(node->right, depth + 1));
        }

        return result;
    }
};
\end{Code}

\subsubsection{相关题目}
\begindot
\item Maximum Depth of Binary Tree，见 \S \ref{sec:maximum-depth-of-binary-tree}
\myenddot


\subsection{Maximum Depth of Binary Tree}
\label{sec:maximum-depth-of-binary-tree}


\subsubsection{描述}
Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.


\subsubsection{分析}
无

\subsubsection{代码}

\begin{Code}
// LeetCode, Maximum Depth of Binary Tree
// 时间复杂度O(n)，空间复杂度O(logn)
class Solution {
public:
    int maxDepth(TreeNode *root) {
        if (root == nullptr) return 0;

        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item Minimum Depth of Binary Tree，见 \S \ref{sec:minimum-depth-of-binary-tree}
\myenddot


\subsection{Path Sum}
\label{sec:path-sum}


\subsubsection{描述}
Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.

For example:
Given the below binary tree and \code{sum = 22},
\begin{Code}
          5
         / \
        4   8
       /   / \
      11  13  4
     /  \      \
    7    2      1
\end{Code}
return true, as there exist a root-to-leaf path \code{5->4->11->2} which sum is 22.


\subsubsection{分析}
题目只要求返回\fn{true}或者\fn{false}，因此不需要记录路径。

由于只需要求出一个结果，因此，当左、右任意一棵子树求到了满意结果，都可以及时return。

由于题目没有说节点的数据一定是正整数，必须要走到叶子节点才能判断，因此中途没法剪枝，只能进行朴素深搜。

\subsubsection{代码}

\begin{Code}
// LeetCode, Path Sum
// 时间复杂度O(n)，空间复杂度O(logn)
class Solution {
public:
    bool hasPathSum(TreeNode *root, int sum) {
        if (root == nullptr) return false;

        if (root->left == nullptr && root->right == nullptr) // leaf
            return sum == root->val;

        return hasPathSum(root->left, sum - root->val)
                || hasPathSum(root->right, sum - root->val);
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item Path Sum II，见 \S \ref{sec:path-sum-ii}
\myenddot


\subsection{Path Sum II}
\label{sec:path-sum-ii}


\subsubsection{描述}
Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

For example:
Given the below binary tree and \code{sum = 22},
\begin{Code}
          5
         / \
        4   8
       /   / \
      11  13  4
     /  \    / \
    7    2  5   1
\end{Code}
return
\begin{Code}
[
   [5,4,11,2],
   [5,8,4,5]
]
\end{Code}


\subsubsection{分析}
跟上一题相比，本题是求路径本身。且要求出所有结果，左子树求到了满意结果，不能return，要接着求右子树。

\subsubsection{代码}

\begin{Code}
// LeetCode, Path Sum II
// 时间复杂度O(n)，空间复杂度O(logn)
class Solution {
public:
    vector<vector<int> > pathSum(TreeNode *root, int sum) {
        vector<vector<int> > result;
        vector<int> cur; // 中间结果
        pathSum(root, sum, cur, result);
        return result;
    }
private:
    void pathSum(TreeNode *root, int gap, vector<int> &cur,
            vector<vector<int> > &result) {
        if (root == nullptr) return;

        cur.push_back(root->val);

        if (root->left == nullptr && root->right == nullptr) { // leaf
            if (gap == root->val)
                result.push_back(cur);
        }
        pathSum(root->left, gap - root->val, cur, result);
        pathSum(root->right, gap - root->val, cur, result);

        cur.pop_back();
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item Path Sum，见 \S \ref{sec:path-sum}
\myenddot


\subsection{Binary Tree Maximum Path Sum}
\label{sec:binary-tree-maximum-path-sum}


\subsubsection{描述}
Given a binary tree, find the maximum path sum.

The path may start and end at any node in the tree.
For example:
Given the below binary tree,
\begin{Code}
  1
 / \
2   3
\end{Code}
Return $6$.


\subsubsection{分析}
这题很难，路径可以从任意节点开始，到任意节点结束。

可以利用“最大连续子序列和”问题的思路，见第\S \ref{sec:maximum-subarray}节。如果说Array只有一个方向的话，那么Binary Tree其实只是左、右两个方向而已，我们需要比较两个方向上的值。

不过，Array可以从头到尾遍历，那么Binary Tree怎么办呢，我们可以采用Binary Tree最常用的dfs来进行遍历。先算出左右子树的结果L和R，如果L大于0，那么对后续结果是有利的，我们加上L，如果R大于0，对后续结果也是有利的，继续加上R。

\subsubsection{代码}

\begin{Code}
// LeetCode, Binary Tree Maximum Path Sum
// 时间复杂度O(n)，空间复杂度O(logn)
class Solution {
public:
    int maxPathSum(TreeNode *root) {
        max_sum = INT_MIN;
        dfs(root);
        return max_sum;
    }
private:
    int max_sum;
    int dfs(const TreeNode *root) {
        if (root == nullptr) return 0;
        int l = dfs(root->left);
        int r = dfs(root->right);
        int sum = root->val;
        if (l > 0) sum += l;
        if (r > 0) sum += r;
        max_sum = max(max_sum, sum);
        return max(r, l) > 0 ? max(r, l) + root->val : root->val;
    }
};
\end{Code}

注意，最后return的时候，只返回一个方向上的值，为什么？这是因为在递归中，只能向父节点返回，不可能存在L->root->R的路径，只可能是L->root或R->root。


\subsubsection{相关题目}
\begindot
\item Maximum Subarray，见 \S \ref{sec:maximum-subarray}
\myenddot


\subsection{Populating Next Right Pointers in Each Node} %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\label{sec:populating-next-right-pointers-in-each-node}


\subsubsection{描述}
Given a binary tree
\begin{Code}
struct TreeLinkNode {
   int val;
   TreeLinkNode *left, *right, *next;
   TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};
\end{Code}

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to \fn{NULL}.

Initially, all next pointers are set to \fn{NULL}.

Note:
\begindot
\item You may only use constant extra space.
\item You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).
\myenddot

For example,
Given the following perfect binary tree,
\begin{Code}
         1
       /  \
      2    3
     / \  / \
    4  5  6  7
\end{Code}

After calling your function, the tree should look like:
\begin{Code}
         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL
\end{Code}


\subsubsection{分析}
无

\subsubsection{代码}

\begin{Code}
// LeetCode, Populating Next Right Pointers in Each Node
// 时间复杂度O(n)，空间复杂度O(logn)
class Solution {
public:
    void connect(TreeLinkNode *root) {
        connect(root, NULL);
    }
private:
    void connect(TreeLinkNode *root, TreeLinkNode *sibling) {
        if (root == nullptr)
            return;
        else
            root->next = sibling;

        connect(root->left, root->right);
        if (sibling)
            connect(root->right, sibling->left);
        else
            connect(root->right, nullptr);
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item Populating Next Right Pointers in Each Node II，见 \S \ref{sec:populating-next-right-pointers-in-each-node-ii}
\myenddot


\subsection{Sum Root to Leaf Numbers} %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\label{sec:sum-root-to-leaf-numbers}


\subsubsection{描述}
Given a binary tree containing digits from \fn{0-9} only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path \fn{1->2->3} which represents the number \fn{123}.

Find the total sum of all root-to-leaf numbers.

For example,
\begin{Code}
    1
   / \
  2   3
\end{Code}

The root-to-leaf path \fn{1->2} represents the number \fn{12}.
The root-to-leaf path \fn{1->3} represents the number \fn{13}.

Return the sum = \fn{12 + 13 = 25}.


\subsubsection{分析}
无

\subsubsection{代码}

\begin{Code}
// LeetCode, Decode Ways
// 时间复杂度O(n)，空间复杂度O(logn)
class Solution {
public:
    int sumNumbers(TreeNode *root) {
        return dfs(root, 0);
    }
private:
    int dfs(TreeNode *root, int sum) {
        if (root == nullptr) return 0;
        if (root->left == nullptr && root->right == nullptr)
            return sum * 10 + root->val;

        return dfs(root->left, sum * 10 + root->val) +
                dfs(root->right, sum * 10 + root->val);
    }
};
\end{Code}


\subsubsection{相关题目}
\begindot
\item 无
\myenddot