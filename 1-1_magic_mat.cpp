#include<iostream>
#include<iomanip>
#include<vector>
using namespace std;

int left_up(const int& w, int index){
    // left
    if (index % w == 0){
        index += (w-1);
    }
    else {
        index -= 1;
    }
    // up
    if (index < w){
        index += (w * (w-1));
    }
    else {
        index -= w;
    }
    return index;
}

void magic(const int& w){
    vector<int> arr(w*w); //TODO should use 2 dimension array
    int index = w / 2;
    for(int i=1; i<=w*w; i++){
        arr[index] = i;
        if (arr[left_up(w, index)] > 0){
            index += w;
        }
        else {
            index = left_up(w, index);
        }

        // for (int i=0; i<(w*w); i++){
        //     if (i % w ==0){
        //         cout << endl;
        //     }
        //     cout << setw(3) << arr[i];
        // }
        // cout << endl;
    }
    for (int i=0; i<(w*w); i++){
        if (i % w ==0 && i/w > 0){
            cout << endl;
        }
        cout << setw(3) << arr[i];
    }
    cout << endl;
}
int main(){
    // int w = 5;
    for (int i=1; i<=9; i+=2){
        magic(i);
        cout << endl;
    }
}