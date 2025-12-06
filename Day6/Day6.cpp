
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>

using namespace std;

unsigned long part_1(vector<vector<string>> lineList){
    unsigned long sum = 0;

    for(int i = 0; i < lineList[0].size(); i++){
        vector<unsigned long> problem;
        char oper;

        for(int j = 0; j < lineList.size(); j++){
            if(j == lineList.size() - 1){
                oper = lineList[j][i][0];
            }else{
                problem.push_back(stol(lineList[j][i]));
            }
        }

        unsigned long problemRes = (oper == '+') ? 0 : 1;
        for(auto d : problem){
            if(oper == '+'){
                problemRes = problemRes + d;
            }else{
                problemRes = problemRes * d;
            }
        }
        sum = sum + problemRes;
    }
    return sum;
}

unsigned long part_2(vector<vector<char>> dataArr){
    unsigned long sum = 0;
    
    vector<unsigned long> problem;
    char oper;

    for(int i = dataArr[0].size() - 1; i >= 0; i--){
        
        string num;
        for(int j = 0; j < dataArr.size(); j++){
            if(dataArr[j][i] == ' '){
                continue;
            }else{
                if(dataArr[j][i] == '+'){
                    oper = '+';
                }else if(dataArr[j][i] == '*'){
                    oper = '*';
                }else{
                    num = num + dataArr[j][i];
                }
            }
        }
        if(num == ""){
            unsigned long problemRes = (oper == '+') ? 0 : 1;
            for(auto d : problem){
                if(oper == '+'){
                    problemRes = problemRes + d;
                }else{
                    problemRes = problemRes * d;
                }
                
                
            }
            sum = sum + problemRes;
            problem.clear();
        }else{
            problem.push_back(stol(num));
        }
    }

    unsigned long problemRes = (oper == '+') ? 0 : 1;
    for(auto d : problem){
        if(oper == '+'){
            problemRes = problemRes + d;
        }else{
            problemRes = problemRes * d;
        }
        
        
    }
    sum = sum + problemRes;
    problem.clear();    

    return sum;
}

int main(){

    ifstream f("input.txt");
    
    if(!f.is_open()){
        cout << "file read error" << endl;
        return 1;
    }

    string inpString;

    vector<vector<string>> lineList;
    vector<vector<char>> dataArr;

    while(getline(f, inpString)){
        vector<char> charLine;
        for(char c : inpString){
            charLine.push_back(c);
        }
        dataArr.push_back(charLine);

        stringstream temp(inpString);
        vector<string> line;
        string elem;

        while( temp >> elem){
            line.push_back(elem);
        }
        lineList.push_back(line);
        
    }
    cout << "Answer to Part 1: " << part_1(lineList) << endl;
    cout << "Answer to Part 2: " << part_2(dataArr) << endl;

    return 0;
}