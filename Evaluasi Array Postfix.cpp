#include <cmath>
#include <cstdio>
#include <stack>
#include <iostream>
#include <algorithm>
#include <vector>
bool apakahItuOperator(char a){
    return (a=='+'||a=='/'||a=='*'||a=='%'||a=='-');
}

bool apakahItuKurung(char a){
    return (a=='('||a==')');
}

int Precedence(char a){
    if(a=='+'||a=='-')return 1;
    if(a=='/'||a=='*'||a=='%')return 2;
    if(a=='^')return 3;
    return -1;
}

bool apakahItuAngka(char a){
    return (a<='9'&&a>='0');
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
    for(int i = 1;i < length;i++){
        char c = infix[i];
        if(c==' ')continue;
        else if(c=='-'&&(apakahItuOperator(infix[i-1]))){
            stackInfix.push('-');
            stackInfix.push('1');
            stackInfix.push(' ');
            stackInfix.push('*');
            stackInfix.push(' ');
        }
        else if(apakahItuAngka(c))stackInfix.push(c);
        else if(infix[i-1]=='('&&c=='-')stackInfix.push(c);
        else if(c=='('){stackInfix.push(c);stackInfix.push(' ');}
        else if(c==')'){stackInfix.push(' ');stackInfix.push(c);}
        else {
            stackInfix.push(' ');
            stackInfix.push(c);
            stackInfix.push(' ');
        };
    }
    while(!stackInfix.empty()){
        char c = stackInfix.top();
        result+=c;
        stackInfix.pop();
    }
    std::reverse(result.begin(),result.end());
    return result;
}
std::string infixPostfix(std::string infix){
    std::stack<char> operat;
    std::string res;
    int length = infix.length();
    for(int i =0; i<length;i++){
        char c=infix[i];
        if(c!=' '){
            if(c=='-'&&apakahItuAngka(infix[i+1])){
                res+=c;
            }
            else if(c=='('){
                if(!res.empty())res.pop_back();
                operat.push(c);
            }
            else if(c==')'){
                while(!operat.empty()&&operat.top()!='('){
                    res+=operat.top();
                    operat.pop();
                }
                operat.pop();
            }
            else if(apakahItuOperator(c)){
                res.pop_back();
                if(operat.empty()||operat.top()=='('){
                    operat.push(c);
                }
                else{
                    while(!operat.empty()&&operat.top()!='('&&Precedence(c)<=Precedence(operat.top())){
                        res+=" ";
                        res+=operat.top();
                        operat.pop();
                    }
                    operat.push(c);
                }
                
            }
            else res+=c;
        }
        else res+=" ";
    }
    while(!operat.empty()){
        res+=" ";
        res+=operat.top();  
        operat.pop();
    }
    //naroh spasi
    int leng = res.length();
    std::string L,R,temp;
    for(int i = 0; i<leng; i++){
        if(apakahItuOperator(res[i])&&apakahItuOperator(res[i+1])){
            L = res.substr(0, i);
            R = res.substr(i+1, res.length());
            leng++;
            temp+=L;
            temp+=R;
            res = temp;
        }
    }
    return res;
}
double evaluatePostfix(std::string postfix){
    std::stack<double> wadah;
    int length = postfix.length();
    std::string temp;
    for(int i = 0; i<length;i++){
        char c = postfix[i];
        if((c=='-'&&postfix[i+1]!=' '&&i+1!=length)||(c<='9'&&c>='0')){
            temp+=c;
        }
        else if(apakahItuOperator(c)){
            double right = wadah.top();
            wadah.pop();
            double left = wadah.top();
            wadah.pop();
            if(c=='+')wadah.push(left+right);
            else if(c=='-')wadah.push(left-right);
            else if(c=='*')wadah.push(left*right);
            else if(c=='/')wadah.push(left/right);
            else if(c=='%')wadah.push(fmod(left,right));
        }
        if(c==' '&&temp.length()!=0){
            wadah.push(stol(temp));
            temp = "";
        }
        //if(!wadah.empty())std::cout<<"c ku adalah "<<c<<" AKu adalah .top = "<<wadah.top()<<'\n';

    }
    return wadah.top();
}
int main() {
    std::string infi,infix,result;
    std::getline(std::cin,infi);
    for(char c:infi)if(c!=' ')infix+=c;
    result = infixParsing(infix);
    //std::cout<<result<<'\n';
    std::string postfix = infixPostfix(result);
    //std::cout<<postfix<<'\n';
    std::cout<<evaluatePostfix(postfix);
    return 0;
}
