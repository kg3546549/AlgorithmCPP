#include <iostream>
#include <deque>
#include <queue>
#include <vector>
#include <utility>

//#define DEBUG 1

using namespace std;

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

int N;

vector< vector<char> > Map;

void printMap() {
	cout<<"==================================="<<endl;
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++) {
			cout<<Map[i][j];
		}
		cout<<"\n";
	}
	cout<<"==================================="<<endl;
}

typedef struct Coor {
	int x;
	int y;	
}coor;

class Snake {
public :	
	deque<coor> body;
	queue<pair<int,char> > turnQue;
	int curDir=0;
	
	Snake() {
		body.push_back(coor{0,0});
		Map[0][0] = 'S';
	}
	
	bool turn(char C) {
		
		if(C!='L' && C!='D') return false;
#ifdef DEBUG
		cout<<"Turn "<<C<<endl;
#endif
		if(C=='L') {
			curDir--;
			if(curDir==-1) curDir = 3;
			return true;
		}
		curDir++;
		if(curDir==4) curDir = 0;
		
		return true;
	}
	
	bool move() {
		int nx = body.front().x + dx[curDir];
		int ny = body.front().y + dy[curDir];
		
		//벽에 부댈 때 
		if(nx<0 || nx>=N || ny<0 || ny>=N) return false;
		//내 몸이 있을 떄 
		if(Map[ny][nx] == 'S') return false;
		
		body.push_front(coor{nx,ny});
		
		if(Map[ny][nx] != 'A') {
#ifdef DEBUG
			cout<<"no Apple"<<endl;
#endif
			Map[body.back().y][body.back().x] = '0';
			body.pop_back();
		}
		Map[ny][nx] = 'S';
		return true;
	}
	
	int getBodyLength() {
		return body.size();
	}
	
};

int main(void) {
	int K, L;
	int gameCnt=1;
	cin>>N;
	Map.assign(N, vector<char>(N,'0'));
	Snake s1;
	
	cin>>K;
	for(int i=0;i<K;i++) {
		int x, y;
		cin>>x>>y;
		Map[x-1][y-1] = 'A';
	}
	cin>>L;
	for(int i=0;i<L;i++) {
		int A; char B;
		cin>>A; cin>>B;
		s1.turnQue.push(make_pair(A,B));
	}
	
	while(true) {
#ifdef DEBUG
		cout<<"Game Time : "<<gameCnt<<endl;
		printMap();
#endif
		if(s1.move() == false) break;
#ifdef DEBUG
		cout<<"Current Direction "<<s1.curDir<<endl;
#endif
		pair<int,char> turnData = s1.turnQue.front();
		if(gameCnt == turnData.first) {
			
			s1.turn(turnData.second);
			s1.turnQue.pop();
#ifdef DEBUG
			cout<<"Current Direction "<<s1.curDir<<endl;
#endif
		}
		
		gameCnt++;
	}
	cout<<gameCnt<<endl;
	
}



