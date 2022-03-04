#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N,M,V;

vector< vector<int> > graph;
vector<int> visited;

void bfs() {
    queue<int> que;
    que.push(V);

    while(!que.empty()) {
        int pop = que.front();
        que.pop();
        cout<<pop<<" ";

        for(int i=1;i<=N;i++) {
            //현재 노드와 탐색 노드가 같다면 건너뛴다.
            if(i==pop) continue;
            //방문하지 않은 노드가 연결되어있다면
            if(visited[i] == 0 && graph[pop][i] == 1) {
                visited[i] = 1;
                que.push(i);
            }
        }
    }
}

void dfs(int V) {
    //dfs는 보이는 죽시 들어간다.
    cout<<V<<" ";
    //나이거나 이미 갔다온장소면 안감.
    //방문하지 않았고 내가 아니라면 바로 방문.
    //연결된 노드 탐색
    for(int i=1;i<=N;i++) {
        //나라면 건너뛴다.
        if(V == i) continue;
        //현재 노드 V와 연결되어 있고, 방문하지 않았따면 
        if(visited[i] == 0 && graph[V][i] == 1) {
            visited[i] = 1;
            dfs(i);
        }
    }
    
}

int main(void) {
    cin>>N>>M>>V;

    graph.assign( N+1 , vector<int>(N+1,0) );
    visited.assign( N+1 , 0);

    for(int i=0;i<M;i++) {
        int A, B;
        cin>>A>>B;
        graph[A][B] = graph[B][A] = 1;
    }

    // for(int i=0;i<N;i++) {
    //     for(int j=0;j<N;j++) {
    //         cout<<graph[i][j];
    //     }
    //     cout<<"\n";
    // }

    //깊이 우선 탑색.
    //보통 재귀를 사용하여 구현함.
    visited[V] = 1;
    dfs(V);
    cout<<endl;
    visited.clear();
    visited.assign( N+1 , 0);
    visited[V] = 1;
    bfs();
    cout<<endl;

    return 0;
}