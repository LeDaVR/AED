#include <bits/stdc++.h> 
using namespace std; 

//verifica si es un operando
bool isOperand(char x) 
{ 
   return (x >= 'a' && x <= 'z') || 
          (x >= 'A' && x <= 'Z'); 
} 
  
// Get Infix for a given postfix 
// expression 
string getInfix(string exp) 
{ 
    stack<string> s; 
  
    for (int i=0; exp[i]!='\0'; i++) // recorre toda la cadena
    { 
        if (isOperand(exp[i])) 
        { 
           string op(1, exp[i]); 
           s.push(op); 
        } 
  
        else // si es operador retirara el ultimo elemento
        { 
            string op1 = s.top(); 
            s.pop(); // toma el primer operando
            string op2 = s.top(); 
            s.pop(); //tome el segundo operando
            s.push("(" + op2 + exp[i] + 
                   op1 + ")");  // los coloca con el operador en medio
        } 
    } 
  
    // There must be a single element 
    // in stack now which is the required 
    // infix. 
    return s.top(); 
} 
  
// Driver code 
int main() 
{ 
    string exp = "ab+"; 
    cout << getInfix(exp); 
    return 0; 
} 