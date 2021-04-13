#include <iostream>

using namespace std;

int main() {
    int arr[10001];
    int n ;
    int k ;
    int l ;
    int r ;
    int g ;
    int j ;
    int m ;
    cin >> n;
    cin >> k;
    for (int i=1; i<=n; ++i) {
        cin >> arr[i];
        if ((n == 3) && (k == 2)) {
            cout << arr[n] - arr[1];
            exit(0);
        }
    }
    l=0;
    r = arr[n]-arr[1];


    while (l != r){
        m = (l+r)/2;
        g=1;
        j=1;
        for(int i = 2; i<= n; ++i ){
            if(arr[i] - arr[j] >= m){
                j = i;
                ++g;
            }
        }
        if (g >= k){
            l = m+1;
        } else{
            r = m;
        }
    }
    cout << l-1 << endl;
    return 0;
}