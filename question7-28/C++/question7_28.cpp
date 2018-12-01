#include<iostream>
#include<vector>

using namespace std;

int H, N, t0, totalMinutes, totalTime, INF = 1000000000;
char names[9][21];
int t[9], d[9];
bool solved[9];
vector<int> tempSolvedNumber, solvedNumber;	//�ֱ�洢dfs���̵ĵ�ǰ·��������·�� 
int minTime;	//��¼��Сʱ�� 

int calculateFixTime(int currentTime);	//���㵱ǰʱ�̶�Ӧ��debug���� 
void dfs(int currentTime, int penaltyTime, int finalTime);	//��ǰʱ��currentTime�����ܾ�����penaltyTime����ǰ·���Ļ���ʱ��finalTime 

int main() {
	while(true) {
		scanf("%d", &H);	//������Сʱ��
		if(H < 0) {
			break;
		}
		scanf("%d %d", &N, &t0);
		for(int i = 0; i < N; i++) {
			scanf("%s %d %d", names[i], &t[i], &d[i]);
		}
		totalMinutes = H * 60;	//�����ܷ�����
		minTime = INF; 
		solvedNumber.clear();
		fill(solved, solved + N, false);	//�������ⶼû�б����
		dfs(t0, 0, 0);	//��ʼʱ��Ϊt0�����ܾ�����Ϊ0��
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
	//�����ǰ·���Ľ�����������ʷ���Ž�������Ҫ��
	if((tempSolvedNumber.size() > solvedNumber.size()) ||
	        //���ߵ�ǰ·���Ľ�����������ʷ���Ž���������ͬ��������ʱ�仨�ѱ���Сʱ�仹Ҫ��
	        (tempSolvedNumber.size() == solvedNumber.size() && finalTime + penaltyTime * 20 < minTime)) {
		solvedNumber = tempSolvedNumber;	//������ʷ���Ž�������
		minTime = finalTime + penaltyTime * 20;	//���½��������ʱ��
	}
	for(int i = 0; i < N; i++) {
		if(!solved[i]) {	//�����ǰ�ڵ�δ������ 
			int firstSubmit = currentTime + t[i];	//��һ���ύ��ʱ��
			if(firstSubmit <= totalMinutes) {	//��һ���ύ��ʱ����Ҫ�ڿ���ʱ����
				int fixTime = calculateFixTime(firstSubmit);
				if(firstSubmit + fixTime * d[i] <= totalMinutes) {	//ACʱ����Ҫ�ڿ���ʱ����
					solved[i] = true;
					tempSolvedNumber.push_back(i);
					dfs(firstSubmit + fixTime * d[i], penaltyTime + fixTime, finalTime + firstSubmit + fixTime * d[i]);
					solved[i] = false;	//�������ֶ����� 
					tempSolvedNumber.pop_back();	//�������ֶ����� 
				}
			}
		}
	}
}
