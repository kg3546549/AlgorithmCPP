#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;

//지도 전체를 돌아다닌다.
//돌아다니면서 1. 단지인데 2. 아직 방문하지 않은 곳 이라면 dfs를 한다.
//dfs할때마다 cnt(단지 갯수)를 ++한다.
//dfs가 종료될 때 해당 단지의 건물 갯수를 return 한다.
//vector 만들어서 push한다.


int N;

pair<int,int> dxy[4] = {
    make_pair( 1,0),
    make_pair(-1,0),
    make_pair(0, 1),
    make_pair(0,-1)
};

vector< vector<int> >map;
vector< vector<bool> >visited;

void dfs(pair<int,int> curCoor , int * cnt) {
    visited[curCoor.second][curCoor.first] = true;
    // cout<<"X"<<curCoor.first<<"Y"<<curCoor.second<<endl;
    for(int i=0;i<4;i++) {
        int nx = curCoor.first + dxy[i].first;
        int ny = curCoor.second + dxy[i].second;
        //범위를 벗어난다면 
        if( nx < 0 || nx >= N ||  ny < 0 || ny >= N) continue;
        //4방을 둘러보았을 때 같은 단지인 집이 있고, 그 집을 방문하지 않았을 때.
        if( map[ny][nx] && !visited[ny][nx] ) {
            (*cnt)++;
            dfs(make_pair(nx,ny) , cnt);
        }
    }
}

int main(void) {
    vector<int> houseCnt;
    queue< pair<int,int> > apartCoor;
    cin>>N;

    map.assign(N , vector<int>(N,0));
    visited.assign(N , vector<bool>(N,false));

    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            scanf("%1d", &map[i][j]);
            if(map[i][j]==1) apartCoor.push( make_pair(j,i) );
        }
    }
    ///////input end/////////
    //아파트 위치 어디있는지 아는 큐가 빌때까지.
    while(!apartCoor.empty()) {
        int x = apartCoor.front().first;
        int y = apartCoor.front().second;
        apartCoor.pop();

        //이미 그 단지에 방문했었다면 넘긴다.
        if(visited[y][x] == true) continue;

        // cout<<"X : "<<x<<" Y : "<<y<<endl;
        int cntBlock = 1;
        // cout<<"dfs Start"<<endl;

        //방문한적이 없는 단지를 dfs하여 크기를 알아냄. cntblock에 크기가 출력되어 나올것임.
        dfs( make_pair(x,y) , &cntBlock );
        // cout<<"cntBlock : "<<cntBlock<<endl;
        houseCnt.push_back( cntBlock );
    }
    
    sort(houseCnt.begin(),houseCnt.end());

    cout<<houseCnt.size()<<endl;
    for(int i=0;i<houseCnt.size();i++) {
        cout<<houseCnt[i]<<endl;
    }

    return 0;
}