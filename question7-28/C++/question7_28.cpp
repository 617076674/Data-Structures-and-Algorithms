#include<iostream>
#include<vector>

using namespace std;

int H, N, t0, totalMinutes, totalTime, INF = 1000000000;
char names[9][21];
int t[9], d[9];
bool solved[9];
vector<int> tempSolvedNumber, solvedNumber;	//分别存储dfs过程的当前路径和最优路径 
int minTime;	//记录最小时间 

int calculateFixTime(int currentTime);	//计算当前时刻对应的debug次数 
void dfs(int currentTime, int penaltyTime, int finalTime);	//当前时间currentTime，被拒绝次数penaltyTime，当前路径的花费时间finalTime 

int main() {
	while(true) {
		scanf("%d", &H);	//考试总小时数
		if(H < 0) {
			break;
		}
		scanf("%d %d", &N, &t0);
		for(int i = 0; i < N; i++) {
			scanf("%s %d %d", names[i], &t[i], &d[i]);
		}
		totalMinutes = H * 60;	//考试总分钟数
		minTime = INF; 
		solvedNumber.clear();
		fill(solved, solved + N, false);	//所有问题都没有被解决
		dfs(t0, 0, 0);	//初始时刻为t0，被拒绝次数为0次
		printf("Total Time = %d\n", minTime);
		for(int i = 0; i < solvedNumber.size(); i++) {
			printf("%s\n", names[solvedNumber[i]]);
		}
	}
	return 0;
}

int calculateFixTime(int currentTime) {
	if(currentTime <= 60) {
		return 0;
	} else if(currentTime > 60 && currentTime <= 120) {
		return 1;
	} else if(currentTime > 120 && currentTime <= 180) {
		return 2;
	} else if(currentTime > 180 && currentTime <= 240) {
		return 3;
	} else if(currentTime > 240 && currentTime <= 300) {
		return 4;
	}
}

void dfs(int currentTime, int penaltyTime, int finalTime) {
	//如果当前路径的解题数量比历史最优解题数量要多
	if((tempSolvedNumber.size() > solvedNumber.size()) ||
	        //或者当前路径的解题数量和历史最优解题数量相同，但是总时间花费比最小时间还要少
	        (tempSolvedNumber.size() == solvedNumber.size() && finalTime + penaltyTime * 20 < minTime)) {
		solvedNumber = tempSolvedNumber;	//更新历史最优解题数量
		minTime = finalTime + penaltyTime * 20;	//更新解题的最少时间
	}
	for(int i = 0; i < N; i++) {
		if(!solved[i]) {	//如果当前节点未被访问 
			int firstSubmit = currentTime + t[i];	//第一次提交的时间
			if(firstSubmit <= totalMinutes) {	//第一次提交的时间需要在考试时间内
				int fixTime = calculateFixTime(firstSubmit);
				if(firstSubmit + fixTime * d[i] <= totalMinutes) {	//AC时间需要在考试时间内
					solved[i] = true;
					tempSolvedNumber.push_back(i);
					dfs(firstSubmit + fixTime * d[i], penaltyTime + fixTime, finalTime + firstSubmit + fixTime * d[i]);
					solved[i] = false;	//变量的手动回溯 
					tempSolvedNumber.pop_back();	//变量的手动回溯 
				}
			}
		}
	}
}
