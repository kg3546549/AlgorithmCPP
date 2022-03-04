#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int N, M;
vector< vector<int> > miro;
vector< vector<int> > visited;

int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

/*
    1은 이동할 수 있는 칸. 0은 벽.
    0,0에서 시작해서 N-1,M-1으로 도착할 수 있는 최소한의 거리를 출력하라.
    거리의 길이를 숫자로출력하라.

    dfs로 하면 모든 경우의 수를 다 따져보고 최솟값을 찾아내야 하기 때문에 효율이 좋지 않고.
    bfs로 해서 가장 빨리 도달한 수가 최솟값이기 때문에 bfs로 해결한다.

    0,0에서 bfs를 시작해서 4방을 다 둘러 본 후, 갈 수 있는 곳이면 큐에 삽입한다. 큐에 삽입할 때 몇번쨰 이동인지 같이 넣는다.
    4방 둘러볼 떄 세그멘테이션 에러 주의한다.
    N이 Y고 M이 X다.
    pair<int , pair<int,int> > (횟수, pair(x,y) );

    N-1 M-1에 도착하면 해당 pair의 cnt를 return한다.


*/

void printMiro() {
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            cout<<miro[i][j];
        }
        cout<<endl;
    }
}

int bfs() {
    queue< pair< int , pair<int,int> > > que;
    //                  cnt            X,Y
    que.push( make_pair( 0 , make_pair(0,0) ) );

    while(!que.empty()) {
        int cnt , X, Y;
        cnt = que.front().first;
        X = que.front().second.first;
        Y = que.front().second.second;
        que.pop();

        cout<<"X : "<<X<<" Y : "<<Y<<" cnt : "<<cnt<<endl;

        if(X == M-1 && Y == N-1) return cnt;

        //4방 둘러보기
        for(int i=0;i<4;i++) {
            int sx = X+dx[i]; int sy = Y+dy[i];
            //segmentation 에러 잡기
            //N과 M의 범위를 벗어나는 탐색 하지않게
            //범위가 0보다 작거나, N,M이랑 같거나 더 커서 지도 밖을 벗어나려고 하면 continue, 벽이라면 continue, 이미 방문한 곳이라면 continue
            if(sx < 0 || sx >= M || 
               sy < 0 || sy >= N ||
               miro[Y][X] == 0 ||
               visited[Y][X] == 1)
                continue;
            
            //여기까지 왔으면 탐색할 수 있는 곳임.
 
            cout<<"sX : "<<sx<<" sY : "<<sy<<" cnt : "<<cnt<<endl;

            visited[sy][sx] = 1;
            que.push( make_pair( cnt+1 , make_pair(sx , sy) ) );

        }

    }
}

int main(void) {

    cin>>N>>M;

    miro.assign( N , vector<int>(M , 0) );
    visited.assign( N , vector<int>(M , 0) );

    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            scanf("%1d" ,&miro[i][j]);
        }
    }
    
    cout<<bfs()<<endl;

    return 0;
}