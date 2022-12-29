#include <iostream>
#include <vector>
#include <utility>

using namespace std;

/*
*/

const pair<int,int> Tetromino[4][4] = {
    { make_pair(0,0),make_pair(0,1),make_pair(0,-1),make_pair(-1,0) },
    { make_pair(0,0),make_pair(0,1),make_pair(0,-1),make_pair(1,0) },
    { make_pair(0,0),make_pair(-1,0),make_pair(1,0),make_pair(0,1) },
    { make_pair(0,0),make_pair(-1,0),make_pair(1,0),make_pair(0,-1) }
};

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

int Max = 0;
vector< vector<int> > board;
vector< vector<int> > visited;
int N, M;

void dfs(int cnt, int sum, int x, int y) {

    // cout<<"visit ["<<x<<":"<<y<<"] - "<<board[y][x]<<" - "<<sum<<endl;

    visited[y][x] = cnt;
    if(cnt==4) {
        // cout<<"sum : "<<sum<<endl;
        if(Max < sum) {
            int checkSum = 0;
            Max = sum;
            /*
                Max 교체 시에 현재 선택된 애들 Debug Print
            */
            // cout<<"MAX Found!! : "<<Max<<endl;
            // for(int i=0;i<N;i++) {
            //     cout<<"    ";
            //     for(int j=0;j<M;j++) {
            //         cout<<visited[i][j]<<" ";
            //     }
            //     cout<<endl;
            // }
        }
        visited[y][x] = 0;
        return;
    }

    for(int i=0;i<4;i++) {
        int nx = dx[i]+x;
        int ny = dy[i]+y;
        if(nx < 0 || nx >= M || ny < 0 || ny >= N) continue;
        if(visited[ny][nx] >= 1) continue;

        dfs(cnt+1, sum+board[ny][nx],x+dx[i],y+dy[i]);
    }
    visited[y][x] = 0;
}

int shape(int x, int y) {
    int max = 0;
    for(int i=0;i<4;i++) {
        int sum = 0;

        for(int j=0;j<4;j++) {
            int nx = x+Tetromino[i][j].first;
            int ny = y+Tetromino[i][j].second;
            if(nx < 0 || nx >= M || ny < 0 || ny >= N) break;

            sum += board[ny][nx];
        }
        if(max < sum) max = sum;
    }
    return max;
}

int main(void) {
    ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    
    cin>>N>>M;
    board.assign(N,vector<int>(M,0));
    visited.assign(N,vector<int>(M,0));

    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            cin>>board[i][j];
        }
    }


    //한 포인트에 대해서 Depths 4의 DFS를 실시하면 ㅗ 모양의 테트로미노를 제외한 모든 테트로미노를 탐색할 수 있다.
    //한 선에 모두 연결되어있기 때문임.

    // visited[2][2] = 1;
    //         dfs(1, board[2][2], 2, 2);
    //         visited[2][2] = 0;

    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {

            visited[i][j] = 1;
            dfs(1, board[i][j], j, i);
            visited[i][j] = 0;

            int shape1 = shape(j,i);
            Max = Max<shape1?shape1:Max;
        }
    }

    
    cout<<Max<<endl;
}