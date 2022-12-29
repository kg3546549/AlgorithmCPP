#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <algorithm>

#define DEBUG

using namespace std;

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
int bx[4] = {2,-2,0,0};
int by[4] = {0,0,2,-2};

int main(void) {

    int answer = -1;
    int N, M;
    cin>>N>>M;

    vector< vector<int> > map(N,vector<int>(M,0));
    vector< vector<int> > Svisited(N, vector<int>(M,0));

    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            scanf("%1d", &map[i][j]);
        }
    }

    //            x   y  cnt  벽
    queue< tuple<int,int,int,bool,vector< vector<int> > > > que;
    que.push( make_tuple(0,0,1,0,Svisited) );
    Svisited[0][0] = true;

    while(!que.empty()) {
        int curX = get<0>(que.front());
        int curY = get<1>(que.front());
        int cnt = get<2>(que.front());
        int breakFlag = get<3>(que.front());
        vector< vector<int> > visited = get<4>(que.front());
        que.pop();

        // cout<<"curXY : "<<curX<<" , "<<curY<<endl;

        if(curX == M-1 && curY == N-1) {
            if(answer==-1 || answer > cnt) answer = cnt;
        }
        
        for(int i=0;i<4;i++) {
            int nX = curX + dx[i];
            int nY = curY + dy[i];

            int bbX = curX + bx[i];
            int bbY = curY + by[i];

            

            if(nX < 0 || nX >= M || nY < 0 || nY >= N || visited[nY][nX]) continue;
            
            //벽 아직 안부쉈고, 범위에 벗어나지 않는다면,
            if( !breakFlag && (bbX > 0 && bbX < M && bbY > 0 && bbY < N) ) {
                
                //방문 안했고, 벽인지 확인
                if( !visited[bbY][bbX] && map[nY][nX] == 1  ) {
                    que.push( make_tuple(nX,nY,cnt+1,true, visited) );
                    visited[nY][nX] = 1;
                }
                
            }

            if( map[nY][nX] == 1 ) continue;
            
            // cout<<"    nXY : "<<nX<<" , "<<nY<<endl;
            // cout<<"    bbX : "<<bbX<<" , "<<bbY<<endl;
            que.push( make_tuple(nX,nY,cnt+1,breakFlag , visited ) );
            visited[nY][nX] = 1;
        }
    }
    cout<<answer<<endl;
    return 0;
}