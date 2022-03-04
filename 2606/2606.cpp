#include <iostream>
#include <vector>

using namespace std;

int numOfComputer;
int numOfLine;

vector< vector<int> > map;
vector<int> visited;

static int result;

//dfs는 해당 노드가 들어갈 수 있는 노드인지 확인하고 바로 들어간다.
//해당 노드와 연결되어있는 노드인지 확인 후에 바로 들어감.
//전체 노드의 수만큼 훑어보면서 
int dfs(int curNode) {
    static int result;
    result++;
    visited[curNode] = 1;
    cout<<"visit : "<<curNode<< "  result : " << result <<endl;
    for(int i=1;i<numOfComputer+1;i++) {
        //방문하지 않았고, 연결되어있다면.
        if( map[curNode][i] && !visited[i] )
            dfs(i);
    }
    return result;
}

int main(void) {
    int result;
    cin>>numOfComputer;
    cin>>numOfLine;

    map.assign( numOfComputer+1 , vector<int>(numOfComputer+1,0) );
    visited.assign(numOfComputer+1,0);
    for(int i=0;i<numOfLine;i++) {
        int A, B;
        cin>>A>>B;

        map[A][B] = 1;
        map[B][A] = 1;
    }

    result = dfs(1);
    cout<<result-1<<endl;
}