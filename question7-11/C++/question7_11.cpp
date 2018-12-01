#include<iostream>
#include<vector>
#include<queue>
#include<set>

using namespace std;

struct situation {
	int x, y;
};

int N, D, INF = 1000000000;
situation situations[101];
int graph[101][101];	//无向图graph[i][j]代表situations[i]与situations[j]之间存在的路径长度的平方
int d[101];
int countInq[101];
bool inq[101];
set<int> pre[101];
vector<int> tempPath;
vector<int> path;
int minSteps = INF;	//最少跳跃步数 
int minFirstJump = INF;	//第一步跳的距离最短 

int calculateDistance(situation s1, situation s2);
bool canEscape(situation s);	//从s位置能否逃出
bool spfa(int s);
void dfs(int nowVisit);

int main() {
	situations[0].x = situations[0].y = 0;	//situations[0]是原点，坐标为(0, 0)
	scanf("%d %d", &N, &D);
	for(int i = 1; i <= N; i++) {
		scanf("%d %d", &situations[i].x, &situations[i].y);
	}
	if((D + 7.5) * (D + 7.5) >= 50 * 50) {	//如果一步就能跳出去 
		printf("1\n");
		return 0;
	}
	for(int i = 0; i < N + 1; i++) {
		for(int j = i + 1; j < N + 1; j++) {
			graph[i][j] = graph[j][i] = INF;
		}
	}
	for(int i = 1; i < N + 1; i++) {
		int distance = calculateDistance(situations[0], situations[i]);
		if(distance <= (D + 7.5) * (D + 7.5)) {
			graph[0][i] = graph[i][0] = distance;
		}
	}
	for(int i = 1; i < N + 1; i++) {
		for(int j = i + 1; j < N + 1; j++) {
			int distance = calculateDistance(situations[i], situations[j]);
			if(distance <= D * D) {
				graph[i][j] = graph[j][i] = distance;
			}
		}
	}
	spfa(0);
	for(int i = 1; i < N + 1; i++) {
		if(!canEscape(situations[i])) {
			continue;
		}
		dfs(i);
	}
	printf("%d\n", path.size());
	for(int i = path.size() - 2; i >= 0; i--) {
		printf("%d %d\n", situations[path[i]].x, situations[path[i]].y);
	}
	return 0;
}

int calculateDistance(situation s1, situation s2) {
	return (s1.x - s2.x) * (s1.x - s2.x) + (s1.y - s2.y) * (s1.y - s2.y);
}

bool canEscape(situation s) {
	int len1, len2;
	if(s.y >= 0) {
		len1 = 50 - s.y;
	} else {
		len1 = s.y + 50;
	}
	if(s.x >= 0) {
		len2 = 50 - s.x;
	} else {
		len2 = s.x + 50;
	}
	if(min(len1, len2) <= D) {
		return true;
	} else {
		return false;
	}
}

bool spfa(int s) {
	fill(d, d + N + 1, INF);
	fill(countInq, countInq + N + 1, 0);
	fill(inq, inq + N + 1, false);
	d[s] = 0;
	queue<int> q;
	q.push(s);
	countInq[s]++;
	inq[s] = true;
	while(!q.empty()) {
		int now = q.front();
		q.pop();
		inq[now] = false;
		for(int i = 0; i < N + 1; i++) {
			if(graph[now][i] < INF) {
				if(d[now] + 1 < d[i]) {
					d[i] = d[now] + 1;
					pre[i].clear();
					pre[i].insert(now);
					if(!inq[i]) {
						q.push(i);
						countInq[i]++;
						inq[i] = true;
						if(countInq[i] > N) {
							return false;
						}
					}
				} else if(d[now] + 1 == d[i]) {
					pre[i].insert(now);
					if(!inq[i]) {
						q.push(i);
						countInq[i]++;
						inq[i] = true;
						if(countInq[i] > N) {
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}

void dfs(int nowVisit) {
	tempPath.push_back(nowVisit);
	if(nowVisit == 0) {
		if(tempPath.size() < minSteps) {
			path = tempPath;
			minSteps = tempPath.size();
			minFirstJump = graph[0][tempPath[tempPath.size() - 2]];
		} else if(tempPath.size() == minSteps && graph[0][tempPath[tempPath.size() - 2]] < minFirstJump) {
			path = tempPath;
			minFirstJump = graph[0][tempPath[tempPath.size() - 2]];
		} 
		tempPath.pop_back();
		return;
	}
	for(set<int>::iterator it = pre[nowVisit].begin(); it != pre[nowVisit].end(); it++) {
		dfs(*it);
	}
	tempPath.pop_back();
}
