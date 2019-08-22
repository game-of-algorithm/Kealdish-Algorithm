// 负载均衡。接受一个整数 M 作为命令行参数，从标准输入中读取任务的名称和所需的运行时间，用最长处理时间优先原则打印出一份调度计划，将所有任务分配给 M 个处理器并使得所有任务完成所需的总时间最少。

/*
 将输入任务按照执行时间从大到小进行排列，如果输入任务的数目小于 M，则直接将任务分配给处理器即可。
 如果输入任务的数目大于 M，则先建立小根堆，处理 M 个任务，当根结点任务结束时，读入下个任务，放在根结点，
 然后将剩余结点的数值都减去根结点的数值，再重新进行堆化。
 如此循环，直到等待执行的任务梳数为 0.
*/

#include <algorithm>
#include <queue>
#include <string>
#include <vector>
using std::priority_queue;
using std::string;
using std::vector;
using std::sort;

struct Task {
    string name;
    int cost;

    bool operator<(const Task& a) const
    {
        return cost > a.cost; // 小顶堆
    }
};

struct {
    bool operator()(int a, int b) const
    {   
        return a > b;
    }   
} customLess;

int M = 8;

void updateNodes(priority_queue<Task, vector<Task> > &pq, int cost) {
    vector<Task> vt;
    while (!pq.empty()) {
        vt.push_back(pq.top());
        pq.pop();
    }

    for (int i; i < vt.size(); i++) {
        vt[i].cost = vt[i].cost - cost;
        pq.push(vt[i]);
    }

}

int calculate_total_cost(vector<Task> tasks) {

    sort(tasks.begin(), tasks.end(), customLess);

    if (M >= tasks.size())
    {
        return tasks[0].cost;
    }

    priority_queue<Task, vector<Task> > pq;

    int cost = 0;
    int cur = 0;
    for (int i = M; i > 0; i--)
    {
        pq.push(tasks[cur]);
        cur++;
    }
    
    while (cur < tasks.size()) {
        Task minTask = pq.top();
        cost += minTask.cost;
        pq.pop();

        updateNodes(pq, minTask.cost);

        pq.push(tasks[cur]);
        cur++;
    }
    
    return cost;
}

