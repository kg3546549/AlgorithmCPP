#include <iostream>
#include <tuple>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

int main(void) {

    int N, M;

    cin>>N>>M;

    vector< vector<int> > MAP(N, vector<int>(M,0));
    vector< vector<int> > visited(N, vector<int>(M,0));
    int pictureNumCnt=0;
    int biggestSize=0;
    
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            cin>>MAP[i][j];
        }
    }

    //입력시 que로 설정하여 풀 수도있는데 겨우 500 * 500짜리에서 2초나 줌.

    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            
            //만났을 때 bfs 시전.
            if(MAP[i][j]==1 && !visited[i][j] ) {
                pictureNumCnt++;
                queue< pair<int,int> > que;
                int sizeCnt = 1;
                que.push( make_pair(j,i) );
                visited[i][j] = 1;

                while(!que.empty()) {
                    int cX = que.front().first;
                    int cY = que.front().second;
                    que.pop();

                    for(int AA=0;AA<4;AA++) {
                        int nX = cX + dx[AA];
                        int nY = cY + dy[AA];
                        
                        if(nX >= M || nX < 0 || nY >= N || nY < 0) continue;
                        if(visited[nY][nX]) continue;
                        
                        if(MAP[nY][nX]) {
                            que.push( make_pair(nX,nY) );
                            sizeCnt++;
                            visited[nY][nX]=1;
                        }
                    }
                }
                
                if(biggestSize < sizeCnt ) {
                    biggestSize=sizeCnt;
                }
                

            }

        }
    }
    
    cout<<pictureNumCnt<<endl<<biggestSize<<endl;

}