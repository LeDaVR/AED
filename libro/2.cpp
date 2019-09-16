#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<int> a;
    a.push_back(5);
    a.push_back(10);
    auto it = a.begin();
    //a.erase(it);
    //a.push_back(15);
    for(;it!=a.end();it++)
        cout << *it << " ";
}
