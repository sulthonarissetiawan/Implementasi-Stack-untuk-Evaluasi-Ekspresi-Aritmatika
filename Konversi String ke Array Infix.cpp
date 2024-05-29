#include <cmath>
#include <cstdio>
#include <stack>
#include<iostream>
#include<algorithm>
#include<vector>
bool apakahItuOperator(char a){
    return(a=='+'||a=='/'||a=='*'||a=='%'||a=='-');
}

bool apakahItukurung(char a){
    return (a=='('||a==')');
}
std::string infixParsing(std::string infix){
    std::string result;
    int length = infix.length();
    std::stack<char> stackInfix;
    if(infix[0]=='-'&&infix[1]=='('){
        stackInfix.push('-');
        stackInfix.push('1');
        stackInfix.push(' ');
        stackInfix.push('*');
        stackInfix.push(' ');
        
    }
    else stackInfix.push(infix[0]);
    for(int i = 1; i <length;i++){
        char c = infix[i];
        if(c==' ')continue;
        else if(c=='-'&&(apakahItuOperator(infix[i-1]))){
            stackInfix.push('-');
            stackInfix.push('1');
            stackInfix.push(' ');
            stackInfix.push('*');
            stackInfix.push(' ');
        }
        else if(c>'0' && c<'9')stackInfix.push(c);
        else if(infix[i-1]=='('&&c=='-')stackInfix.push(c);
        else if(c=='('){stackInfix.push(c);stackInfix.push(' ');}
        else if(c==')'){stackInfix.push(' ');stackInfix.push(c);}
        else{
            stackInfix.push(' ');
            stackInfix.push(c);
            stackInfix.push(' ');
        };
        
    }
    while(!stackInfix.empty()){
        char c = stackInfix.top();
        result +=c;
        stackInfix.pop();
    }
    std::reverse(result.begin(),result.end());
    return result;
}
int main(){
    std::string infi,infix,result;
    std::getline(std::cin,infi);
    for(char c:infi)if(c!=' ')infix+=c;
    result = infixParsing(infix);
    std::cout<<result<<'\n';
    return 0;
}
