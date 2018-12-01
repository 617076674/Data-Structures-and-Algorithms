#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct node{
	int v, len;
	node(int _v, int _len){
		v = _v;
		len = _len;
	}
};

int N, M, v1, v2, len, INF = 1000000000;
vector<node> graph[101];
int d[101], countInq[101];
bool inq[101];
int minIndex, minLen = INF;

bool spfa(int s);

int main(){
	scanf("%d %d", &N, &M);
	for(int i = 0; i < M; i++){
		scanf("%d %d %d", &v1, &v2, &len);
		graph[v1].push_back(node(v2, len));
		graph[v2].push_back(node(v1, len));
	}
	for(int i = 1; i <= N; i++){
		spfa(i);
		int maxLen = 0;
		for(int j = 1; j <= N; j++){
			if(d[j] > maxLen){
				maxLen = d[j];
			}
		}
		if(maxLen != INF){
			if(maxLen < minLen){
				minLen = maxLen;
				minIndex = i;
			}
		}
	}
	if(minLen == INF){
		printf("0\n");
		return 0;
	}
	printf("%d %d\n", minIndex, minLen);
	return 0;
}

bool spfa(int s){
	fill(d + 1, d + N + 1, INF);
	fill(countInq + 1, countInq + N + 1, 0);
	fill(inq + 1, inq + N + 1, false);
	d[s] = 0;
	queue<int> q;
	q.push(s);
	countInq[s]++;
	inq[s] = true;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		inq[u] = false;
		for(int i = 0; i < graph[u].size(); i++){
			int v = graph[u][i].v;
			int len = graph[u][i].len;
			if(d[u] + len < d[v]){
				d[v] = d[u] + len;
				if(!inq[v]){
					q.push(v);
					countInq[v]++;
					inq[v] = true;
					if(countInq[v] > N - 1){
						return false;
					}
				}
			}
		}
	}
	return true;
}
