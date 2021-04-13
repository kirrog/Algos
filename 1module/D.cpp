#include "iostream"

int main(){
    int a;
    std::cin >> a;
    int b;
    std::cin >> b;
    int c;
    std::cin >> c;
    int d;
    std::cin >> d;
    int k;
    std::cin >> k;

    int prev = a;

    for (int i = 0; i < k; ++i) {
        int between = a*b;
        if(between > c){
            between -= c;
        } else{
            between=0;
        }
        if(between >= d){
            a = d;
        } else{
            a = between;
        }
        if(prev == a){
            break;
        } else{
            prev = a;
        }
    }

    printf("%d", a);

    return 0;
}