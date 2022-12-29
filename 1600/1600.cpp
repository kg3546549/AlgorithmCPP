#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main(void) {
    int K , W , H;
    pair<int,int> curPos = make_pair(0,0);
    cin>>K>>W>>H;
    vector< vector<int> > board( W , vector<int>(H,0) );
    for(int i=0;i<W;i++) {
        for(int j=0;j<H;j++) {
            cin>>board[i][j];
        }
    }
    
}