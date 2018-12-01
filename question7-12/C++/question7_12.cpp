#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct node {
	int v;
	int len;
	node(int _v, int _len) {
		v = _v;
		len = _len;
	}
};

int N, M, INF = 1000000000;
vector<node> graph[100];
int d[100], countInq[100], inDegree[100];
bool inq[100], visited[100];
int maxLen = 0;

bool spfa(int s);

int main() {
	scanf("%d %d", &N, &M);
	fill(inDegree, inDegree + N, 0);
	int v1, v2, len;
	for(int i = 0; i < M; i++) {
		scanf("%d %d %d", &v1, &v2, &len);
		graph[v1].push_back(node(v2, -len));
		inDegree[v2]++;
	}
	bool flag = false;
	for(int i = 0; i < N; i++) {
		if(inDegree[i] == 0) {
			flag = true;
		}
	}
	if(!flag) {
		printf("Impossible\n");
		return 0;
	}
	for(int j = 0; j < N; j++) {
		if(inDegree[j] != 0) {	//SPFA的起点应该是入度为0的点 
			continue;
		}
		fill(visited, visited + N, false);	
		bool flag = spfa(j);
		if(!flag) {
			printf("Impossible\n");
			return 0;
		}
		int tempMaxLen = 0;
		for(int i = 0; i < N; i++) {
			if(!visited[i]){	//如果没被访问过，说明不属于当前连通分量 
				continue;
			}
			if(tempMaxLen < -d[i]) {
				tempMaxLen = -d[i];
			}
		}
		maxLen = max(tempMaxLen, maxLen);
	}
	printf("%d\n", maxLen);
	return 0;
}

bool spfa(int s) {
	fill(d, d + 100, INF);
	fill(countInq, countInq + 100, 0);
	fill(inq, inq + 100, false);
	d[s] = 0;
	queue<int> q;
	q.push(s);
	visited[s] = true;
	inq[s] = true;
	countInq[s]++;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inq[u] = false;
		for(int i = 0; i < graph[u].size(); i++) {
			int v = graph[u][i].v;
			int len = graph[u][i].len;
			if(d[u] + len < d[v]) {
				d[v] = d[u] + len;
				if(!inq[v]) {
					q.push(v);
					visited[v] = true;
					inq[v] = true;
					countInq[v]++;
					if(countInq[v] > N - 1) {
						return false;
					}
				}
			}
		}
	}
	return true;
}

