#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

/*
    22.05.30
    처음에 해쉬를 써야하나 했던 그 직감을 믿었어야했다...
    하지만 머릿속에 대충 어느정도 구현이 끝나있었던 상태이므로 해쉬형 배열로 바꾸는데에는 그렇게 오래걸리지 않았다...
*/


vector<int> map;
vector<int> visited;

//그래프로 연결되어있는 놈들을 전부 다 방문한다.
//최대 간선 수 (N), 전체탐색 중 만난 탐색 시작 노드 i, 
void bfs(int N, int startNode) {
    queue<int> que;
    que.push(startNode);

    while(!que.empty()) {
        int curNode = que.front();
        // cout<<"curNode : "<<curNode<<endl;
        que.pop();
        visited[curNode] = 1;
        
        if(!visited[map[curNode]]) {
            que.push(map[curNode]);
        }
    }
    // cout<<"BFS END"<<endl;
}



int main(void) {

    int T;

    cin>>T;

    while(T--) {
        int N;
        cin>>N;
        // cout<<endl;
        queue<int> memoryNode;
        map.assign( N+1 , 0 );
        visited.assign( N+1 , 0 );

        for(int i=1;i<=N;i++) {
            int input;
            cin>>input;
            map[i] = input;
            // memoryNode.push();
        }

        int cnt=0;
        //그래프를 다 돌면서 1이 나왔을 때 bfs로 전부 다 방문처리 하고 cnt++
        for(int i=1;i<=N;i++) {
            if(!visited[map[i]]) {
                bfs(N,i);
                cnt++;
                continue;
            }
        }
        cout<<cnt<<endl;
        
        map.clear();
        visited.clear();
    }
    return 0;
}