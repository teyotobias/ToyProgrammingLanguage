#include "Parse.h"
#include "Heart.h"
#include <map>
#include <vector>
#include <string>
using namespace std;
#include <iostream>
map<string,int> vars;
vector<string> equats;



int ProcessEquation(int arg1, int arg2, string op){
    if(op == "+"){
        return arg1 + arg2;
    }
    else if(op == "-"){
        return arg1 -arg2;
    }
    else if(op == "*"){
        return arg1 *arg2;
    }
    else if(op == "/"){
        return arg1/arg2;
    }
    else if(op == "%"){
        return arg1%arg2;
    }
    else if(op == "&&"){
        return arg1 && arg2;
    }
    else if(op == "||"){
        return arg1 || arg2;
    }
    else if(op == ">"){
        return arg1 > arg2;
    }
    else if(op == "<"){
        return arg1 < arg2;
    }
    else if(op == "=="){
        return arg1 == arg2;
    }
    else if(op == "!="){
        return arg1 != arg2;
    }
    else if(op == "<="){
        return arg1 <= arg2;
    }
    else if(op == ">="){
        return arg1 >= arg2;
    }
    else {
        exit(1); //for invalid input

    }

}

int parse(vector<string>& expr) {
    string first = expr[0];
    expr.erase(expr.begin());
    if(first.compare("+") != 0 && first.compare("-") != 0 && first.compare("/") != 0 && first.compare("*")!= 0
    && first.compare("%") != 0 && first.compare("&&") != 0 && first.compare(">") != 0 && first.compare("<") != 0 &&
    first.compare("==") != 0 && first.compare("!=") != 0 && first.compare("<=") != 0 &&
    first.compare(">=") != 0 && first.compare("!") != 0 && first.compare("~") != 0){
        if(vars.find(first) != vars.end()){
            return vars[first];
        }
        return stoi(first); //stoi is string to integer -> base case
    }
    if(first == "~"){
        int arg = parse(expr);
        return -1 * arg;
    }
    if(first == "!"){
        int arg = parse(expr);
        return ! arg;
    }

    int arg1 = parse(expr);
    int arg2 = parse(expr);
    return ProcessEquation(arg1, arg2, first);
}


void ProcessText(){
    string temp;
    read_next_token();
    temp = next_token();
    cout << temp;
}

void ProcessVar(){
    string holdStr;
    string holdString;
    int holdInt;
    read_next_token();
    holdStr = next_token();
    if(vars.find(holdStr) == vars.end()){
        read_next_token();
        if(next_token_type == NUMBER){
            vars[holdStr] = token_number_value;
        }
        else {
            while(holdString != "text" && holdString != "output" && holdString != "set" && holdString != "var" && next_token_type != END){
                equats.push_back(next_token());
                read_next_token();
                holdString = next_token();
            }
            holdInt = parse(equats);
            vars[holdStr] = holdInt;
        }
    }
    else {
        cout << "variable " << holdStr << " incorrectly re-initialized";
    }

}


void ProcessOutput(){
    int holdInt = 0;
    string holdStr;
    string holdString;
    read_next_token();
    if(next_token_type == NUMBER){
        cout << token_number_value;
    }
    else {
        if(next_token_type == NAME){
            holdStr = next_token();
            cout << vars[holdStr];
            return;
        }
        while(holdString != "text" && holdString != "output" && holdString != "set" && holdString != "var"){
            equats.push_back(next_token());
            read_next_token();
            holdString = next_token();
        }
        holdInt = parse(equats);
        equats.clear();
        cout << holdInt;
    }

}

void ProcessSet(){
    string holdStr;
    string holdString;
    int holdInt;
    read_next_token();
    holdStr = next_token();
    if(vars.find(holdStr) == vars.end()){
        cout << "variable " << holdStr << "not declared" << endl;
    }
    else {
        read_next_token();
        if(next_token_type == NUMBER){
            vars[holdStr] = token_number_value;
        }
        else {
            while(holdString != "text" && holdString != "output" && holdString != "set" && holdString != "var"){
                equats.push_back(next_token());
                read_next_token();
                holdString = next_token();
            }
            holdInt = parse(equats);
        }
        vars[holdStr] = holdInt;
    }

}



void run() {
    string holdStr;
    int i = 0;
    next_token_type = NAME;
    while(next_token_type != END) {
        if(i != 1){
            read_next_token();
        }
        i = 0;
        holdStr = next_token();
        if (holdStr == "text") {
            ProcessText();
        }
        else if (holdStr == "var") {
            ProcessVar();
        }
        else if(holdStr == "output"){
            ProcessOutput();
            i = 1;
        }
        else if(holdStr == "set"){
            ProcessSet();
            i = 1;
        }
        else if(holdStr == "//"){
            skip_line();
        }

    }

}
