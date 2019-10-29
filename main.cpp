#include <iostream>
#include "segment.h"
using namespace std;

int main(){
    int arr[11] = {65,2,96,63,46,73,72,64,92,36,7};
    SegmentTree<int> sumitas(arr,11);
    cout << sumitas.suma(2,9);
    return 0;
}

