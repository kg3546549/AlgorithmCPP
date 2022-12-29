#include <iostream>
#include <queue>
#include <vector>
#include <utility>

// #define DEBUG 1

using namespace std;

pair<int,int> dxy[4] = {
    make_pair( 1,0),
    make_pair(-1,0),
    make_pair(0, 1),
    make_pair(0,-1),
};

int main(void) {
    int M, N;
    //토마토 전체 갯수
    int totalTomatoCnt=0;
    int unripedTomato=0;
    //익는 날짜 카운트
    int dayCnt=0;

    cin>>M>>N;
    //현재 익어있는 맵
    vector< vector<int> > curMap(N, vector<int>(M,0));
    //이번에 익을 놈들은 여기에 익힘.
    // vector< vector<int> > futureMap(N, vector<int>(M,0));
    //방문 맵
    vector< vector<int> > visited(N, vector<int>(M,0));
    queue<pair<int,int> > tomatoPosition;
    bool zeroFlag = false;
    //입력부
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            int input;
            cin>>input;
            curMap[i][j] = input;
            if(input == 1) {
                totalTomatoCnt++;
                tomatoPosition.push(make_pair(j,i));
            }
            else if(input == 0) {
                unripedTomato++;
            }
            if(!zeroFlag && input == 0) zeroFlag = true;
        }
    }

    if(!zeroFlag) {
        cout<<"0"<<endl; 
        return 0;
    }

    int curTomatoCnt=totalTomatoCnt;
    int futureTomatoCnt=totalTomatoCnt;

    queue< pair<int,int> > futureQue;
    

    //다 익거나, 더이상 익을 게 없다면 break되어 종료.
    while(1) {
        
        #ifdef DEBUG
        cout<<"+++++++++++++++++++++++++"<<"\n";
        cout<<"dayCnt : "<<dayCnt<<"\n";
        #endif
        
        curTomatoCnt = futureTomatoCnt;

        vector< vector<int> > futureMap(curMap);
        


        //전체탐색으로 하면 시간초과 남.

        //처음에 토마토 위치를 que에 삽입해서 해당 위치만 순회.
        //다음에는 que 초기화 후 이번에 futureMap에 추가된 애들을 다음 que에 삽입하여 해당 위치만 순회.x
        while(!tomatoPosition.empty()) {
            pair<int,int> qFront = tomatoPosition.front();
            tomatoPosition.pop();

            int i=qFront.second;
            int j=qFront.first;

            #ifdef DEBUG
            cout<<"  Located Tomato "<<j<<":"<<i<<"\n";
            #endif

            //방문
            visited[i][j] = 1;


            for(int i=0;i<4;i++) {
                int nX = qFront.first + dxy[i].first;
                int nY = qFront.second + dxy[i].second;
                
                //map 범위 벗어나지 않게 처리.
                if( nX < 0 || nX >= M || nY < 0 || nY >= N ) continue;

                // 0==안익은 토마토 익게 하자 (미래에)
                if( curMap[nY][nX] == 0 && futureMap[nY][nX] == 0 ) {
                    futureMap[nY][nX] = 1;
                    //익은 토마토 개수
                    futureTomatoCnt++;
                    unripedTomato--;
                    futureQue.push(make_pair(nX,nY));

                    #ifdef DEBUG
                    cout<<"    FutureQue Push : "<<nX<<":"<<nY<<"\n";
                    #endif
                }
            }
        }

        #ifdef DEBUG
        cout<<"  tomatoPositionSSIZZE : "<<tomatoPosition.size()<<endl;
        cout<<"  futureQueSSIZZE : "<<futureQue.size()<<endl;
        #endif

        dayCnt++;

        #ifdef DEBUG
        cout<<"    fTC : "<<futureTomatoCnt<<"  cTC : "<<curTomatoCnt<<"\n";
        
        for(int i=0;i<N;i++) {
            for(int j=0;j<M;j++) { 
                printf("%3d",curMap[i][j]);
            }
            cout<<"\n";
        }
        
        #endif

        //이번 탐색의 총 익은 토마토 수와 저번 토마토 수가 같다면 이젠 더이상 익힐수 있는게 없다.
        if(futureTomatoCnt == curTomatoCnt) {
            break;
        }

        for(int i=0;i<N;i++) {
            for(int j=0;j<M;j++) { 
                curMap[i][j] = futureMap[i][j];
            }
        }

        while(!futureQue.empty()) {
            tomatoPosition.push(futureQue.front());
            futureQue.pop();
        }
        #ifdef DEBUG
        cout<<"  tomatoPosition.size : "<<tomatoPosition.size()<<"\n";
        cout<<"  futureQue.size : "<<futureQue.size()<<"\n";
        cout<<"--------------------------"<<"\n";
        #endif 
        //방문 초기화.
        visited.clear();
        visited.assign(N, vector<int>(M,0));
        
    }
    //종료된 시점에서 안익은 토마토 있는지 전체탐색 후 결과 출력.

    // for(int i=0;i<N;i++) {
    //     for(int j=0;j<M;j++) { 
    //         if(curMap[i][j] == 0) {
    //             cout<<"-1"<<endl;
    //             return 0;
    //         }
    //     }
    // }
    if(unripedTomato != 0)
        cout<<"-1"<<endl;
    else {
        cout<<dayCnt-1<<endl;
    }
    
    
    return 0;

}