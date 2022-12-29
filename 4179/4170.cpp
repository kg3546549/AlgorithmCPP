#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <deque>

#define MV_FAIL 0
#define MV_SUCC 1

using namespace std;

typedef struct Position {
    int x;
    int y;
} Position;

//           상 하 좌 우
const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

int R, C;


/*
    지훈 : J
    불 : F
    x=j , y=i

    불은 항상 같은 범위로 번진다.
    불은 겉에만 번지기 때문에 불 위치를 Queue로 만들어서 번진 불 주변만 또 다시 번지게 한다.
    현재 불 위치의 사방으로 불이 번질 수 있는지 확인하고(벽인지, 이미 불인지) 불이 번지면서 큐에 번지는 불 위치를 넣는다.

    지훈이가 먼저 이동하고 불이 번져야 한다.
    
    
*/

class MAPS {
    private : 
        vector< vector<char> > MAP;
        Position JIHUN; //맵 내 지훈의 위치
        queue<Position> FIRE; //맵 내 불의 위치

    public : 
        MAPS( vector< vector<char> > input , Position Jihun, Position Fire) {
            MAP = input;
            JIHUN = Jihun;
            FIRE.push(Fire);
        }

        MAPS(const MAPS& origin) {
            MAP = origin.MAP;
            JIHUN.x = origin.JIHUN.x;
            JIHUN.y = origin.JIHUN.y;
            FIRE = origin.FIRE;
        }

        //상1하2좌3우4
        int move(int dir) {
            //지훈이가 먼저 이동하고
            int nx = dx[dir-1]+JIHUN.x;
            int ny = dy[dir-1]+JIHUN.y;
            if(nx<0 || nx>=C || ny<0 || ny>=R || MAP[ny][nx] == 'F' || MAP[ny][nx] == '#' ) {
                return MV_FAIL;
            }

            MAP[ny][nx] = 'J';
            MAP[JIHUN.y][JIHUN.x] = '.'; 
            JIHUN.x = nx; JIHUN.y = ny;

            //불이 그 다음으로 이동해야 함
            queue<Position> nFIRE;
            while(!FIRE.empty()) {
                Position A = FIRE.front();
                FIRE.pop();

                for(int i=0;i<4;i++) {
                    int nx = A.x + dx[i];
                    int ny = A.y + dy[i];
                    
                    if(nx<0 || nx>=C || ny<0 || ny>=R ) continue;
                    //불이 번지면서 얘를 죽였다. 그럼 여기는 못가는 통로인것
                    if(MAP[ny][nx] == 'J') {
                        return MV_FAIL;
                    }
                    if(MAP[ny][nx] == '#') continue;
                    MAP[ny][nx] = 'F';

                    //새로운 불이 번지는 곳을 큐에 삽입
                    Position N;
                    N.x = nx; N.y = ny;
                    nFIRE.push(N);
                }
            }
            //새로운 불을 다시 넣음
            FIRE = nFIRE;
            return MV_SUCC;
        }

        vector< vector<char> > getMAP() {
            return MAP;
        }

        Position getJIHUN() {
            return JIHUN;
        }

        queue<Position> getFIRE() {
            return FIRE;
        }
};

int main(void) {
    
    vector< vector<char> > MAP;
    Position fJIHUN;
    Position fFIRE;

    cin>>R>>C;
    MAP.assign(R,vector<char>(C,0));

    for(int i=0;i<R;i++) {
        for(int j=0;j<C;j++) {
            cin>>MAP[i][j];
            if(MAP[i][j] == 'J') {
                fJIHUN.x = j;
                fJIHUN.y = i;
            }
            else if(MAP[i][j]=='F') {
                fFIRE.x = j;
                fFIRE.y = i;
            }
        }
    }
    MAPS MAP1(MAP,fJIHUN,fFIRE);

    //==============END INPUT==============//

    // cout<<"x : "<<MAP1.getJIHUN().x<<"  y : "<<MAP1.getJIHUN().y<<endl;
    // cout<<"move : "<<MAP1.move(2)<<endl;
    // cout<<"x : "<<MAP1.getJIHUN().x<<"  y : "<<MAP1.getJIHUN().y<<endl;
    
    queue<MAPS> q;
    q.push(MAP1);
    while(!q.empty()) {
        MAPS Map1 = q.front();

        for(int i=1;i<=4;i++) {
            
        }
    }

    
}