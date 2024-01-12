#include<iostream>
using namespace std;

class Arr{
    private:
        int length;
    public:
        int *data;

        Arr(const int& length)
        :length(length)
        {
            //init to all 0
            // data = new int; // has a bug due to occupying system memory
            data = new int[10];
            for (int i=0; i<length; i++){
                data[i] = 0;
            }
        }

        ~Arr(){
            delete []data;
        }

        int &operator[] (int i){
            if (i<0 || i>length)
                throw out_of_range( "Subscript out of range" );
            return *(data+i);
        }

        void operator*= (int t){
            for (int i=0; i<length; i++){
                *(data+i) *= t;
            }
            // carry
            for (int i=1; i<length; i++){
                *(data+i) += *(data+i-1) / 10;
                *(data+i-1) %= 10;
            }
            // add length
            while (data[length-1] >= 10){
                data[length] = data[length-1] / 10;
                data[length-1] %= 10;
                length++;
            }
        }

        void print(){
            for (int i=(length-1); i>=0; i--){
                cout << data[i] << " ";
            }
            cout << endl;
        }
};

void factorial(int n){
    int ret = 1;
    for (int i=1; i<=n; i++){
        ret *= i;
    }
    cout << ret << endl;
}

void arr_factorial(int n){
    Arr arr(1);
    arr[0] = 1;
    for (int i=1; i<=n; i++){
        arr *= i;
        arr.print();
    }

}
int main(){
    arr_factorial(13);
}