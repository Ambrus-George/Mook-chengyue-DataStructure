#include <iostream>
#include <vector>
#include <queue>

typedef struct ANode* PtrToANode;
struct ANode
{
	int startPoint;
	int endPoint;
	int workload;
	int maneuveringTime;
	PtrToANode Next;
	ANode(int start, int end, int lastingTime) : startPoint(start),
		endPoint(end), workload(lastingTime), maneuveringTime(0),
		Next(nullptr) {}
};

struct CNode
{
	int vertex;
	int inDegree;
	int outDegree;
	int earliestTime;
	int deadLine;
};

class ProjectSchedule
{
public:
	ProjectSchedule() {}
	ProjectSchedule(int cnum, int anum);
	~ProjectSchedule();

	void init();
	int culculateEarliestTime();

private:
	int checkPointsNum;
	int activitiesNum;
	std::vector<PtrToANode> activities;
	std::vector<CNode> checkpoints;
	std::vector<bool> Visited;
};

ProjectSchedule::ProjectSchedule(int cnum, int anum)
{
	checkPointsNum = cnum;
	activitiesNum = anum;
	activities.resize(cnum, nullptr);
	checkpoints.resize(cnum);
	Visited.resize(cnum, false);

	// 给每个检查点建立一个空结点，保存当前检查点的入度和出度
	for (size_t i = 0; i < cnum; i++)
	{
		checkpoints.at(i).vertex = i;
		checkpoints.at(i).deadLine = 0;
		checkpoints.at(i).earliestTime = 0;
		checkpoints.at(i).inDegree = 0;
		checkpoints.at(i).outDegree = 0;
		//activities.at(i) = new ANode(0, 0, 0);	// startPoint--入度  endPoint--出度
	}
}

ProjectSchedule::~ProjectSchedule()
{
	for (size_t i = 0; i < checkPointsNum; i++)
	{
		PtrToANode itemptr = activities.at(i);
		while (itemptr)
		{
			PtrToANode deteptr = itemptr;
			itemptr = itemptr->Next;
			delete(deteptr);
		}
	}
}

void ProjectSchedule::init()
{
	for (size_t i = 0; i < activitiesNum; i++)
	{
		int startP, endP, workl;
		std::cin >> startP >> endP >> workl;
		PtrToANode newNode = new ANode(startP, endP, workl);
		newNode->Next = activities.at(startP);
		activities.at(startP) = newNode;

		// 这个检查点的出度+1
		checkpoints.at(startP).outDegree++;

		// 下一个检查点的入度+1
		checkpoints.at(endP).inDegree++;
	}
}

int ProjectSchedule::culculateEarliestTime()
{
	// 挑选入度为0的检查点入队列
	// 使用队列对图进行广度优先遍历
	// 如果没有入度为0的点且没有访问过全部的点证明有圈形结构

	std::queue<int> Que;		// 队列用来存放检查点
	int popcount = 0;			// 记录访问了几个检查点
	int maxtime = 0;			// 记录最快完成的时间

	while (true)
	{
		// 入度为0的检查点入队列
		bool hadPush = false;
		for (size_t i = 0; i < checkPointsNum; i++)
		{
			if ((checkpoints.at(i).inDegree == 0) && !Visited.at(i))
			{
				Que.push(i);
				hadPush = true;
				Visited.at(i) = true;
			}
		}

		// 没有新入队列的两种情况：访问完了；有循环结构
		if (!hadPush)
		{
			if (popcount < checkPointsNum)
			{
				return -1;
			}
			return maxtime;
		}

		// 出队列，访问
		while (!Que.empty())
		{
			int vertexItem = Que.front();
			Que.pop();
			maxtime = (maxtime > checkpoints.at(vertexItem).earliestTime) ? maxtime : checkpoints.at(vertexItem).earliestTime;

			PtrToANode ptr = activities.at(vertexItem);

			while (ptr)
			{
				int time = ptr->workload + checkpoints.at(ptr->startPoint).earliestTime;
				checkpoints.at(ptr->endPoint).earliestTime = (checkpoints.at(ptr->endPoint).earliestTime > time) ?
					checkpoints.at(ptr->endPoint).earliestTime : time;

				/*checkpoints.at(ptr->startPoint).outDegree--;*/
				checkpoints.at(ptr->endPoint).inDegree--;

				ptr = ptr->Next;
			}
			
			popcount++;
		}
	}

}

int main()
{
	int N = 0, M = 0;
	std::cin >> N >> M;
	ProjectSchedule Project(N, M);

	// 读入活动数据，也就是边的数据
	Project.init();

	int earliestTime = Project.culculateEarliestTime();
	if (earliestTime == -1)
	{
		std::cout << "Impossible";
	}
	else {
		std::cout << earliestTime;
	}

	return 0;
}