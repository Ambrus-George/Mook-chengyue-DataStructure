#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <stack>

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
	void updateDeadline();
	void updateManeuveringTime();
	int getLastOne();
	int getFirstOne();
	PtrToANode findPtr(int startC, int endC);

private:
	int checkPointsNum;
	int activitiesNum;
	int firstone;
	int lastone;
	int earliestTime;
	std::vector<PtrToANode> activities;
	std::vector<CNode> checkpoints;
	std::vector<bool> Visited;
	void refleshVisited();
	std::stack<int> StackPop;
	/*std::vector<std::queue<int>> inDegreeGroup;*/

	/*PtrToANode activitiesList;
	PtrToANode rearPtr;*/
};

void ProjectSchedule::refleshVisited()
{
	std::fill(Visited.begin(), Visited.end(), false);
}

ProjectSchedule::ProjectSchedule(int cnum, int anum)
{
	checkPointsNum = cnum;
	activitiesNum = anum;
	lastone = 0;
	activities.resize(cnum+1, nullptr);
	checkpoints.resize(cnum + 1);
	Visited.resize(cnum + 1, false);
	/*activitiesList = new ANode(0, 0, 0);
	rearPtr = activitiesList;*/

	// 给每个检查点建立一个空结点，保存当前检查点的入度和出度
	for (size_t i = 0; i < cnum; i++)
	{
		checkpoints.at(i).vertex = i;
		checkpoints.at(i).deadLine = std::numeric_limits<int>::max();
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

		/*PtrToANode newNode_List = new ANode(startP, endP, workl);
		rearPtr->Next = newNode_List;
		rearPtr = rearPtr->Next;*/

		// 这个检查点的出度+1
		checkpoints.at(startP).outDegree++;

		// 下一个检查点的入度+1
		checkpoints.at(endP).inDegree++;
		/*inDegreeGroup.at(endP).push(startP);*/	// 父节点入队列
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
	int vertexItem = 0;
	bool getfirstone = false;


	while (true)
	{
		// 入度为0的检查点入队列
		bool hadPush = false;
		for (size_t i = 1; i <= checkPointsNum; i++)
		{
			if ((checkpoints.at(i).inDegree == 0) && !Visited.at(i))
			{
				if (!getfirstone)
				{
					firstone = i;
					getfirstone = true;
				}
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
			lastone = vertexItem;
			checkpoints.at(lastone).deadLine = maxtime;
			earliestTime = maxtime;
			refleshVisited();
			return maxtime;
		}

		// 出队列，访问
		while (!Que.empty())
		{
			vertexItem = Que.front();
			StackPop.push(vertexItem);
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

PtrToANode ProjectSchedule::findPtr(int startC, int endC)
{
	PtrToANode itemptr = activities.at(startC);
	while (itemptr)
	{
		if ((itemptr->startPoint == startC) && (itemptr->endPoint == endC))
		{
			return itemptr;
		}
		itemptr = itemptr->Next;
	}
	return nullptr;
}

void ProjectSchedule::updateDeadline()
{
	/*while (!inDegreeGroup.at(a).empty())
	{
		int startC = inDegreeGroup.at(a).front();
		inDegreeGroup.at(a).pop();
		int endC = a;

		PtrToANode itemptr = findPtr(startC, endC);
		int newdeadline = checkpoints.at(endC).deadLine - itemptr->workload;

		if (newdeadline < checkpoints.at(startC).deadLine)
		{
			checkpoints.at(startC).deadLine = newdeadline;
			PtrToANode ptr = activities.at(startC);
			while (ptr)
			{
				ptr->maneuveringTime = checkpoints.at(ptr->endPoint).deadLine - checkpoints.at(ptr->startPoint).earliestTime - ptr->workload;
				ptr = ptr->Next;
			}
		}
	}*/

	while (!StackPop.empty())
	{
		int a = StackPop.top();
		StackPop.pop();

		PtrToANode ptr = activities.at(a);
		if (!ptr)
		{
			checkpoints.at(a).deadLine = earliestTime;
		}
		while (ptr)
		{
			/*if (!Visited.at(ptr->endPoint))
			{
				updateDeadline(ptr->endPoint);
			}*/

			int newdeadline = checkpoints.at(ptr->endPoint).deadLine - ptr->workload;
			checkpoints.at(a).deadLine = (newdeadline < checkpoints.at(a).deadLine) ? newdeadline : checkpoints.at(a).deadLine;
			ptr = ptr->Next;
		}
	}

	
}

int ProjectSchedule::getLastOne()
{
	return lastone;
}

int ProjectSchedule::getFirstOne()
{
	return firstone;
}

void ProjectSchedule::updateManeuveringTime()
{
	for (size_t i = 1; i <= checkPointsNum; i++)
	{
		PtrToANode ptr = activities.at(i);
		while (ptr)
		{
			ptr->maneuveringTime = checkpoints.at(ptr->endPoint).deadLine - checkpoints.at(ptr->startPoint).earliestTime - ptr->workload;
			if (!ptr->maneuveringTime)
			{
				std::cout << ptr->startPoint << "->" << ptr->endPoint << std::endl;
			}
			ptr = ptr->Next;
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
		std::cout << "0";
	}
	else {
		std::cout << earliestTime << std::endl;

		Project.updateDeadline();
		Project.updateManeuveringTime();
	}

	

	return 0;
}