#include <iostream>
#include <tuple>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

//


int main(void) {

    int N;

    cin>>N;
    vector< vector<char> > map(N,vector<char>(N,'N'));
    vector< vector<int> > visited1(N,vector<int>(N,0));
    vector< vector<int> > visited2(N,vector<int>(N,0));
    int normalPersonCnt=0;
    int colorBlindPersonCnt=0;

    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            cin>>map[i][j];
        }
    }

    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            if(map[i][j]!='N' && !visited1[i][j]) {
                
                char selectChar = map[i][j];
                normalPersonCnt++;
                visited1[i][j] = 1;
                queue< pair<int,int> > que;
                que.push( make_pair(j,i) );

                while(!que.empty()) {
                    int cX = que.front().first;
                    int cY = que.front().second;
                    que.pop();

                    for(int A=0;A<4;A++) {
                        int nX = cX+dx[A];
                        int nY = cY+dy[A];
                        
                        if(nX < 0 || nX >= N || nY < 0 || nY >= N) continue;
                        if( visited1[nY][nX] ) continue;

                        if(map[nY][nX]==selectChar) {
                            que.push( make_pair(nX,nY) );
                            visited1[nY][nX] = 1;
                        }
                    }
                }
            }

            if(map[i][j]!='N' && !visited2[i][j]) {
                char selectChar = map[i][j];
                

                // cout<<"X : "<<j<<"  Y : "<<i<<endl;
                // cout<<"selectChar : "<<map[i][j]<<"  convertChar : "<<selectChar<<endl;
                

                colorBlindPersonCnt++;
                visited2[i][j] = 1;
                queue< pair<int,int> > que;
                que.push( make_pair(j,i) );

                while(!que.empty()) {
                    int cX = que.front().first;
                    int cY = que.front().second;
                    que.pop();

                    for(int A=0;A<4;A++) {
                        int nX = cX+dx[A];
                        int nY = cY+dy[A];
                        
                        if(nX < 0 || nX >= N || nY < 0 || nY >= N) continue;
                        if( visited2[nY][nX] ) continue;
                        

                        if(selectChar == 'G' || selectChar == 'R')
                        {    
                            if(map[nY][nX]=='G' || map[nY][nX]=='R') {
                                // cout<<"    selectChar : "<<map[nY][nX]<<"  convertChar : "<<selectChar<<endl;
                                que.push( make_pair(nX,nY) );
                                visited2[nY][nX] = 1;
                            }
                        }
                        else if(map[nY][nX]=='B') {
                            // cout<<"    selectChar : "<<map[nY][nX]<<"  convertChar : "<<selectChar<<endl;
                            que.push( make_pair(nX,nY) );
                            visited2[nY][nX] = 1;
                        }
                    }
                }

                // for(int ii=0;ii<N;ii++) {
                //     cout<<"    ";
                //     for(int jj=0;jj<N;jj++) {
                //         cout<<visited2[ii][jj];
                //     }
                //     cout<<endl;
                // }
            }
        }
    }

    cout<<normalPersonCnt<<" "<<colorBlindPersonCnt<<endl;

    

}