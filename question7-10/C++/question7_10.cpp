#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

struct situation{
	int x, y;
	bool visited;
};

int N, D;
situation situations[100];
bool flag = false;

double calculateDistance(situation s1, situation s2);
bool canReach(situation s1, situation s2);	//从s1位置能否到达s2位置
bool canEscape(situation s);	//从s位置能否逃出
void dfs(situation &nowVisited); 

int main(){
	scanf("%d %d", &N, &D);
	for(int i = 0; i < N; i++){
		scanf("%d %d", &situations[i].x, &situations[i].y);
		situations[i].visited = false;
	}
	vector<situation> first;
	situation start;
	start.x = 0;
	start.y = 0;
	for(int i = 0; i < N; i++){
		if(calculateDistance(situations[i], start) <= D * 1.0 + 7.5){
			first.push_back(situations[i]);
		}
	}
	for(int i = 0; i < first.size(); i++){
		dfs(first[i]);
	}
	if(flag){
		printf("Yes\n");
	}else{
		printf("No\n");
	}
	return 0;
}

double calculateDistance(situation s1, situation s2){
	return sqrt(pow(s1.x - s2.x, 2) + pow(s1.y - s2.y, 2));
}

bool canReach(situation s1, situation s2){
	if(calculateDistance(s1, s2) <= D){
		return true;
	}else{
		return false;
	}
}

bool canEscape(situation s){
	int len1, len2;
	if(s.y >= 0){
		len1 = 50 - s.y;
	}else{
		len1 = s.y + 50;
	}
	if(s.x >= 0){
		len2 = 50 - s.x;
	}else{
		len2 = s.x + 50;
	}
	if(min(len1, len2) <= D){
		return true;
	}else{
		return false;
	}
} 

void dfs(situation &nowVisited){
	nowVisited.visited = true;
	if(canEscape(nowVisited)){
		flag = true;
		return;
	}
	for(int i = 0; i < N; i++){
		if(!situations[i].visited && canReach(nowVisited, situations[i])){
			dfs(situations[i]);
		}
	}
}
