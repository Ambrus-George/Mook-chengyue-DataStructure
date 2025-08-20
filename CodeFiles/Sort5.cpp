#include <iostream>
#include <vector>
#include <iomanip>

#define NoneSubmit -1

typedef int UserID;
typedef int ScoreType;
typedef int IndexType;
typedef int Rank;
typedef int NumType;

typedef struct StuNode* PtrToStuNode;
typedef struct StuNode {
	UserID user_id;
	Rank rank;
	ScoreType totalScore;
	NumType perfect_answer_num;
	std::vector<ScoreType> ProblemScore;
	StuNode(UserID uid, IndexType p, ScoreType s, IndexType pnum)
		: user_id(uid), rank(0), perfect_answer_num(0)
	{
		ProblemScore.resize(pnum + 1, NoneSubmit);
		ProblemScore.at(p) = s;
		if (-1 == s)
		{
			ProblemScore.at(p) = 0;
		}
	}

};

class PATJUDGE 
{
private:
	IndexType usr_num;
	IndexType problem_num;
	std::vector<ScoreType> PP;
	std::vector<PtrToStuNode> Data;
	std::vector<IndexType> table_rank;

	void writeHelper(UserID uid, IndexType pid, ScoreType s)
	{
		// 如果这个学生是第一次提交，还没有建档
		if (!Data.at(uid))
		{
			table_rank.at(uid) = uid;
			Data.at(uid) = new StuNode(uid, pid, s, problem_num);
			if (s == PP.at(pid))
			{
				Data.at(uid)->perfect_answer_num++;
			}
		}
		else {
			// 已经有档案了，题目得分初始化为 -1，所以不同的题目提交和同一个题目提交比较方式一致
			if (s >= Data.at(uid)->ProblemScore.at(pid))
			{
				if (s == PP.at(pid) && s > Data.at(uid)->ProblemScore.at(pid)) // 完美答案
				{
					Data.at(uid)->perfect_answer_num++;
				}
				Data.at(uid)->ProblemScore.at(pid) = s;
				if (-1 == s)
				{
					Data.at(uid)->ProblemScore.at(pid) = 0;
				}
			}
		}

		// 更新总成绩
		Data.at(uid)->totalScore = 0;
		for (auto item : Data.at(uid)->ProblemScore)
		{
			if (item != -1)
			{
				Data.at(uid)->totalScore += item;
			}
		}

	}

	

public:
	PATJUDGE(IndexType un, IndexType pn) : usr_num(un), problem_num(pn)
	{
		PP.resize(pn+1);
		Data.resize(un+1, nullptr);
		table_rank.resize(un + 1, 0);
	}

	~PATJUDGE()
	{}

	void init()
	{
		bool zeroflag = false;
		for (auto& item : PP)
		{
			if (!zeroflag)
			{
				zeroflag = true;
				continue;
			}
			std::cin >> item;
			
		}
	}

	void submit(UserID uid, IndexType pid, ScoreType s)
	{
		writeHelper(uid, pid, s);
		
	}

	void table_sort()
	{
		// 在第一次提交的时候已经初始化了
		// 未提交的人值为0
		for (IndexType i = 1; i < table_rank.size(); i++)
		{
			PtrToStuNode tmpptr = Data.at(i);

			if (!tmpptr)
			{
				continue;
			}

			IndexType j = i;
			while (j - 1 > 0 && !Data.at(j - 1))
			{
				Data.at(j) = Data.at(j - 1);
				j--;
			}
			Data.at(j) = tmpptr; // 找到了合适位置

			for (; j - 1 > 0 && Data.at(j - 1)->totalScore <= tmpptr->totalScore; j--)
			{
				// 总分一致
				if (Data.at(j - 1)->totalScore == tmpptr->totalScore)
				{
					// 因为最开始的数据就是从编号低到高排的，所以，当满分答案数都一致的时候，已经排好序了
					if (Data.at(j-1)->perfect_answer_num >= Data.at(j)->perfect_answer_num) // 需要考虑满分题目个数
					{
						break;
					}
				}

				Data.at(j) = Data.at(j - 1);
			}
			Data.at(j) = tmpptr; // 找到了合适位置
		}
	}

	void update_rank()
	{
		
		for (IndexType i = 1; i < Data.size(); i++)
		{
			if (!Data.at(i))
			{
				break;
			}
			
			if (i == 1)
			{
				Data.at(i)->rank = 1;
				continue;
			}

			if (Data.at(i)->totalScore == Data.at(i-1)->totalScore)
			{
				Data.at(i)->rank = Data.at(i - 1)->rank;
				continue;
			}

			// 针对一种情况，有没答的题，有0分的题，这种情况不输出
			if(Data.at(i)->totalScore == 0 && !noBlankAnswer(Data.at(i)))
			{
				continue;
			}

			Data.at(i)->rank = i;
		}
	}

	bool noBlankAnswer(PtrToStuNode tmpptr)
	{
		bool flag = true;

		for(IndexType i = 1; i < problem_num; i++)
		{
			if(tmpptr->ProblemScore.at(i) == -1)
			{
				flag = false;
				break;
			}
		}

		return flag;
	}

	void printResult()
	{
		bool zeroflag = false;

		for (auto tmpptr : Data)
		{
			if (!zeroflag)
			{
				zeroflag = true;
				continue;
			}

			if (!tmpptr || !tmpptr->rank) {
				break;
			}

			std::cout << tmpptr->rank << " ";
			std::cout << std::setfill('0') << std::setw(5) << tmpptr->user_id << " ";
			std::cout << tmpptr->totalScore;

			for (IndexType i = 1; i < tmpptr->ProblemScore.size(); i++)
			{
				if (-1 == tmpptr->ProblemScore.at(i))
				{
					std::cout << " -";
					continue;
				}

				std::cout << " " << tmpptr->ProblemScore.at(i);
			}

			std::cout << std::endl;
		}
	}
};

int main()
{
	// 读入学生总数，问题总数，建立PAT类
	int N, K, M;
	std::cin >> N >> K >> M;
	PATJUDGE PAT(N, K);

	// 类初始化，记录每道题的总分
	PAT.init();

	// 读入每次的提交
	for (IndexType i = 0; i < M; i++)
	{
		UserID usr_id;
		IndexType problem_id;
		ScoreType score;

		std::cin >> usr_id >> problem_id >> score;
		PAT.submit(usr_id, problem_id, score);
	}

	// 表排序
	PAT.table_sort();

	// 更新 rank 值
	PAT.update_rank();

	// 打印
	PAT.printResult();

	return 0;
}