/*
	空闲时间。假设有一台计算机能够并行处理 N 个任务。编写一段程序并给定一系列任务的起始时间
	和结束时间，找出这台机器最长的空闲时间和最长的繁忙时间。
*/

/*
	把所有事件的开始时间和结束时间按照从小到大的顺序进行排序，用一个栈来记录当前时间点正在执行的任务数目。
*/

#include <stack>
#include <vector>
#include <algorithm>
using std::stack;
using std::vector;
using std::sort;
using std::max;

struct task
{
	int startTime;
	int endTime;
};

// sort using a custom function object
struct {
	bool operator()(int a, int b) const
	{   
		return abs(a) < abs(b);
	}   
} customLess;

vector<int> sort_task_time(vector<struct task *> taskList) {
	vector<int> vt;
	for (auto &&i : taskList)
	{
		vt.push_back(i->startTime);
		vt.push_back(-(i->endTime));
	}
	
	sort(vt.begin(), vt.end(), customLess);

	return vt;
}

void calculate_idle_and_busy(vector<struct task *> taskList) {
	stack<int> stack;
	
	vector<int> vt = sort_task_time(taskList);
	int tmpTime = 0;
	int maxIdle = 0;
	int maxBusy = 0;

	for (int i = 0; i < vt.size(); i++)
	{
		int curTime = vt[i];
		if (curTime > 0)
		{
			if (stack.empty() && i > 0)
			{
				if (i > 0)
				{
					maxIdle = max(maxIdle, curTime - tmpTime);
				} 
				
				tmpTime = curTime;
			}

			stack.push(curTime);
		} else {
			int time = stack.top();
			
			stack.pop();

			if (stack.empty())
			{
				maxBusy = max(maxBusy, (abs(time) - tmpTime));
				tmpTime = abs(time);
			}
			
		}
		
	}
	
	printf("Max idle time: %d , Max busy time: %d", maxIdle, maxBusy);

}