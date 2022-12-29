#include <iostream>
#include <vector>
#include <cstdlib>

//#define DEBUG 1

using namespace std;

int N, L;

enum CODE {
	SUCCESS = 1,
	FAIL = 0,
	DOWNFAIL = -1,
	UPFAIL = -2,
	OVERRAMP = -3,
	LENGTH_SHORT = -4,
	RAMP_EXIST = -5,
	OVERLOW = -6,
	OVERHIGH = -7,
};

CODE isPossible(vector<int> line) {
	int prevHeight = line[0];
	int flag = 0;
	int flag_cnt = L;
	vector<int> ramp;
	ramp.assign(line.size(),0);
	for(int i=1;i<line.size();i++) {
		#ifdef DEBUG
		cout<<"    ======== i : "<<i<<" ========"<<endl;
		#endif
		if(prevHeight != line[i]) { //단차가 생겼을 떄 
			#ifdef DEBUG
			cout<<"        PrevHeight : "<<prevHeight<<"  Line[i] : "<<line[i]<<endl;
			#endif
			
			if(ramp[i] == 1) return OVERRAMP;
			
			if(prevHeight > line[i]) { //내려가는 단차일 때 
				if(prevHeight-1 != line[i]) return OVERLOW;
				if(i+L-1 > line.size()) return LENGTH_SHORT;
				int std = line[i];
				#ifdef DEBUG
				cout<<"            std : "<<std<<endl;
				#endif
				for(int j=i;j<i+L;j++) {
					#ifdef DEBUG
					cout<<"             -line[j] : "<<line[j]<<endl;
					#endif
					if(std != line[j]) return DOWNFAIL; //경사로의 길이만큼 같은 높이가 지속되지 않는다면 FAIL 
				}
				for(int j=i;j<i+L;j++) {
					ramp[j] = 1;
				}
				i+=L-1; // i위치를 i+L-1로 i 변경 (이미 경사로가 가능한지 보면서 순회했기 때문.)
			}
			else if(prevHeight < line[i]) { //올라가는 단차일 때
				if(prevHeight+1 != line[i]) return OVERHIGH;
				if(i-L < 0) return LENGTH_SHORT;
				int std = line[i-1];
				#ifdef DEBUG
				cout<<"            std : "<<std<<endl;
				#endif
				for(int j=i-1;j>=i-L;j--) {
					#ifdef DEBUG
					cout<<"             -j:"<<j<<"line[j] : "<<line[j]<< "  ramp[j] : " << ramp[j]<<endl;
					#endif
					if(std != line[j]) return UPFAIL;
					if(ramp[j] == 1) return RAMP_EXIST; //뒤를 탐색할때 이미 경사로가 존재할 때 
				}
			}
		}
		prevHeight = line[i];
	}
	return SUCCESS;
}

int main(void) {
	int result=0;
	cin>>N>>L;
	vector< vector<int> > board;
	board.assign(N,vector<int>(N,0));
	
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++) {
			cin>>board[i][j];
		}
	}
	
	for(int i=0;i<N;i++) {
		#ifdef DEBUG
		cout<< "//////////////////" <<"X : " << i << "//////////////////" << endl;
		#endif
		CODE doit=isPossible(board[i]);
		#ifdef DEBUG
		cout << "Search Error Code : " << doit << endl;
		#endif
		if(doit==1) result++;
		#ifdef DEBUG
		cout<< "//////////////////" <<"X : " << i << "//////////////////" << endl << endl;
		#endif
	}
	
	for(int i=0;i<N;i++) {
		vector<int> column2row;
		for(int j=0;j<N;j++) {
			column2row.push_back(board[j][i]);
		}
		#ifdef DEBUG
		cout<< "//////////////////" <<"Y : " << i << "//////////////////" << endl;
		#endif
		CODE doit=isPossible(column2row);
		#ifdef DEBUG
		cout << "Search Error Code : " << doit << endl;
		#endif
		if(doit==1) result++;
		#ifdef DEBUG
		cout<< "//////////////////" <<"Y : " << i << "//////////////////" << endl << endl;
		#endif
	}
	#ifdef DEBUG
	cout<<endl<<endl<<endl;
	#endif
	cout<<result<<endl;
}
