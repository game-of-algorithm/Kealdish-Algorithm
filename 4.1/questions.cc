/**
 * 4.1.4 如果用栈代替队列来实现广度优先搜索，我们还能得到最短路径吗？
 * 
 * 可以
 */

/**
 * 4.1.32 奇环。证明一幅图能够用两种颜色着色（二分图）当且仅当它不含有长度为奇数的环。
 * 
 * 反证法。三角形。
 * 
 */

/**
 * 4.1.35 边的连通性。在一幅连通图中，如果一条边被删除后图会被分为两个独立的连通分量，
 * 这条边就被称为桥。没有桥的图称为边连通图。开发一种基于深度优先搜索算法的数据类型，
 * 判断一个图是否是边连通图。
 * 
 * 
 */

struct vexNode {
    int val;
    vexNode *disableNode; // 是否有断开的连接的结点
    GraphNode *firstNode; // 指向的第一个结点
};

struct GraphNode {
    int val; // 当前结点的值
    GraphNode *next; // 连接的下一个结点
    vexNode *self;
};

/**
 * 括号生成。
 * 
 * 每一次对左右括号进行穷举，并且使用数组进行迭代。
 * 如果检查到某位出现左括号小于右括号数时，此时必定不合法。
 */