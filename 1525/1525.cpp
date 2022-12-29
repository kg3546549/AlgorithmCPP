#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

void printState(string State) {
    int cnt=0;
    for(int i=0;i<3;i++) {
        cout<<"    ";
        for(int j=0;j<3;j++) {
            cout<<State[cnt++];
        }
        cout<<"\n";
    }
}

int main(void) {

    set<string> check;
    queue< pair<string,int> > que;
    string state;
    int answer = -1;
    for(int i=0;i<9;i++) {
        char input;
        cin>>input;
        state.push_back(input);
    }
    check.insert(state);
    que.push( make_pair(state,0) );

    int AAA=10;
    while(!que.empty()) {
        string curState = que.front().first;
        int tryCnt = que.front().second;
        que.pop();
        //완성 퍼즐이고 && 첫번째 완성이거나(answer이 변경되지 않았거나) || 전에 한것보다 빨리 한거라면.
        if(curState == "123456780" && (answer==-1 || answer>tryCnt) ) {
            answer = tryCnt;
        }
        
        #ifdef DEBUG
        cout<<"=====curState======"<<"\n";
        printState(curState);
        #endif

        //현재 string에서 0 찾기
        int index = curState.find("0");
        int cX = index/3;
        int cY = index%3;

        for(int i=0;i<4;i++) {
            int nX = dx[i]+cX;
            int nY = dy[i]+cY;
            
            //범위 벗어나면 패스
            
            // cout<<"nx"<<nX<<" ny"<<nY<<"\n";
            if(nX >= 3 || nX < 0 || nY >=3 || nY < 0) continue;

            string newState=curState;
            
            #ifdef DEBUG
            cout<<"    ======newState="<<i<<"==="<<"\n";
            printState(newState);
            cout<<"    ./././././././././."<<"\n";
            #endif

            //0과 다른놈을 바꾸고
            swap(newState[nX*3+nY],newState[index]);

            #ifdef DEBUG
            printState(newState);
            cout<<"    ==================="<<"\n";
            #endif
            //이미 한놈이라면
            if(check.count(newState) == 1) {
                #ifdef DEBUG
                cout<<"    continue"<<endl;
                #endif
                continue;
            }
            else {
                que.push( make_pair(newState,tryCnt+1) );
                //재탐색 안하게 set에 삽입
                check.insert(newState);
            }
        }
    }

    cout<<answer<<"\n";
    
    
    return 0;
}