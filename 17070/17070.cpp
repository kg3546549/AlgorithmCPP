#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> Map;

void printMap() { 
    int N = Map.size();
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            cout<<Map[i][j];
        }
        cout<<"\n";
    }
}

int RangeOfMotion[3] = {2,2,3};

class Pipes {

private : 
    // 가로 : 1, 세로 : 2, 대각 : 3
    int status;
    pair<pair<int,int>,pair<int,int>> Coor;
        
public : 
    Pipes() {
        this->Coor.first.first = 0;
        this->Coor.first.second = 0;

        this->Coor.second.first = 1;
        this->Coor.second.second = 0;

        //가로
        status = 1;
    }

    int getStatus() {
        return status;
    }

    pair<int,int> getFirst () {
        return Coor.first;
    }

    pair<int,int> getSecond () {
        return Coor.second;
    }

    bool isCan(int dx,int dy) {
        int N = Map.size();
        if(dx >= N || dy >= N || dx < 0 || dy < 0) return false;
        if(Map[dy][dx] == 1) return false;
    }

    void realMove(int dx,int dy) {
        this->Coor.first.first = this->Coor.second.first;
        this->Coor.first.second = this->Coor.second.second;

        this->Coor.second.first = dx;
        this->Coor.second.second = dy;
    }

    bool Move(int direction) {
        int N = Map.size();
        int dx;
        int dy;
        //가로
        if(this->status == 1) {
            if(direction == 0) { //오른쪽으로 한칸 밀 때
                dx = this->Coor.second.first+1;
                dy = this->Coor.second.second;
                isCan(dx,dy);
                //갈 수 있는곳이라고 인식
                realMove(dx,dy);
                //상태 변경 없음
                return true;
            }
            else if(direction == 1) { //가로에서 대각선으로 밀 때

                dx = this->Coor.second.first+1;
                dy = this->Coor.second.second;
                isCan(dx,dy);

                dx--;
                dy++;
                isCan(dx,dy);

                dx++;
                isCan(dx,dy);

                //갈 수 있는곳이라고 인식
                //위치 이동
                realMove(dx,dy);
                //대각선으로 상태 변경
                this->status = 3;
                return true;
            }
        }

        //세로        
        if(this->status == 2) {
            
            if(direction == 0) {
                dx = this->Coor.second.first;
                dy = this->Coor.second.second++;
                isCan(dx,dy);

                //갈 수 있는곳이라고 인식
                //위치 이동
                realMove(dx,dy);
                //상태 변경 없음
                return true;
            }
            else if(direction == 1) {
                dx = this->Coor.second.first+1;
                dy = this->Coor.second.second;
                isCan(dx,dy);

                dx--;
                dy++;
                isCan(dx,dy);

                dx++;
                isCan(dx,dy);

                //갈 수 있는곳이라고 인식
                //위치 이동
                realMove(dx,dy);
                //대각선으로 상태 변경
                this->status = 3;
                return true;
            }
        }

        //Cross
        if(this->status == 3) {
            if(direction == 0) {
                dx = this->Coor.second.first+1;
                dy = this->Coor.second.second;
                isCan(dx,dy);

                //갈 수 있는곳이라고 인식
                //위치 이동
                realMove(dx,dy);
                //가로로 상태 변경
                this->status = 1;
                return true;
            }
            else if(direction == 1) {
                dx = this->Coor.second.first;
                dy = this->Coor.second.second+1;
                isCan(dx,dy);

                //갈 수 있는곳이라고 인식
                //위치 이동
                realMove(dx,dy);
                //세로로 상태 변경
                this->status = 3;
                return true;
            }
            else if(direction == 2) {
                dx = this->Coor.second.first+1;
                dy = this->Coor.second.second;
                isCan(dx,dy);

                dx--;
                dy++;
                isCan(dx,dy);

                dx++;
                isCan(dx,dy);

                //갈 수 있는곳이라고 인식
                //위치 이동
                realMove(dx,dy);
                //상태 변경 없음
                return true;
            }
        }
    }
};


int main() {
    
    int N;
    int result = 0;
    cin>>N;
    Map.assign(N,vector<int>(N,0));
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            cin>>Map[i][j];
        }
    }
    Pipes pipe1;

    /*================Input END================*/

    /*
    이동을 해야하는데...
    Pair로 현재 위치를 만든다.
    현재 위치를 이동시키는 함수를 만든다.
        현재 상태에 맞게 이동할수 있는 방법이 제한적이기 때문에
        파이프Class로 이동하게 만듬.
        bfs로 해서 pair.second가 도착했을 때 
    */

   //BFS실시해아하는디

   queue<Pipes> que;
   que.push(pipe1);

    while(!que.empty()) {
        Pipes nPipe = que.front();
        que.pop();

        //도착 했을 때
        if(nPipe.getSecond().first == N-1 || nPipe.getSecond().second == N-1) {
            result++;
        }

        for(int i=0;i<RangeOfMotion[nPipe.getStatus()];i++) {
            Pipes newPipe = nPipe;
            newPipe.Move(i);
            que.push(newPipe);
        }
    }
    cout<<result<<endl;
}