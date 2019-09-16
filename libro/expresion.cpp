#include <iostream>
#include <vector>

using namespace std;

bool isletter(char a){
    return (a>='a'&& a<='z') || (a>='1' && a<='9') || (a>='A' && a<='Z');
}

bool isprimarysymbol(char a){
    return a =='*' || a == '/';
}

bool issecondarysymbol(char a){
    return a == '+' || a == '-';
}

bool issymbol(char a){
    return isprimarysymbol(a) || issecondarysymbol(a);
}

void analize(char& a,char& b){
    if(issymbol(a)&&isletter(b))
        swap(a,b);
    if(issecondarysymbol(a)&&isprimarysymbol(b))
        swap(a,b);
}


void toPostFix(string infix){
    vector<string> posfix;
    for(int j=0;j<infix.size()-1;j++){
        if(isprimarysymbol(infix[j])&&isletter(infix[j+1])){
            swap(infix[j],infix[j+1]);
            posfix.pop_back();
            string temp=infix[j-1];
            posfix.push_back(temp);
            j+=2;
            continue;
        }
        string temp=infix[j]+'\0';
        posfix.push_back(temp);
    }
    for(int i=0;i<posfix.size();i++)
        cout<<posfix[i];
}

int main(){
    string a;
    cin>>a;
    toPostFix(a);
    return 0;
}