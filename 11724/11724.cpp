#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

vector<vector<bool> > graph;
vector<bool> visited;
int N, M;
int nodeCnt;

void bfs(int startNode) {
    queue<int> que;
    que.push(startNode);
    visited[startNode] = true;

    while(!que.empty()) {
        nodeCnt++;
        int curNode = que.front();
        que.pop();
        
        //해당 노드에 연결되어있는 노드들을 탐색.
        for(int i=1;i<=N;i++) {
            //현재 노드와 연결되어있고 && 아직 방문하지 않았다면
            if(graph[curNode][i] && !visited[i]) {
                //방문처리 후,
                visited[i] = true;
                
                //해당 놈을 큐에 추가하여 방문할 수 있게 한다.
                que.push(i);
            }
        }
    }
}

int main(void) {
    
    cin>>N>>M;

    graph.assign( N+1 , vector<bool>(N,false) );
    visited.assign(N+1,false);

    for(int i=0;i<M;i++) {
        int u, v;
        cin>>u>>v;
        graph[u][v] = true;
        graph[v][u] = true;
    }

    int cnt=0;
    //노드들을 탐색한다. (그래프에서 1로되어있는 부분이 노드인데, 노드가 존재한다는 뜻이고 그 노드고 어딘가에 연결되어있다는 뜻)
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=N;j++) {
            //노드를 발견했을 떄 아직 방문하지 않은 노드라면
            if(graph[i][j] && !visited[i]) {
                //bfs를 통해서 해당 노드와 연결된 모든 노드를 방문하고,
                bfs(i);
                //cnt++함으로써 연결 요소의 갯수를 센다.
                cnt++;
            }
        }
    }
    if(nodeCnt != N) {
        if(nodeCnt>N) {
            cnt = (nodeCnt-N)+cnt;
        }
        else if(nodeCnt<N) {
            cnt = (N-nodeCnt)+cnt;
        }
    }
    // cout<<"nodeCnt : "<<nodeCnt<<endl;

    cout<<cnt<<endl;

}