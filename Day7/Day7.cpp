
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fo;
vector<vector<char>> dataArr;

int make_beam(int row, int col){
    int splitCount = 0;
    if(row >= dataArr.size() || row < 0)     return 0;
    if(col >= dataArr[0].size() || col < 0)  return 0;
    if(dataArr[row][col] == '|')            return 0;

    int curRow = row;

    while(dataArr[curRow][col] == '.'){
        if(dataArr[curRow][col] == '.'){
            dataArr[curRow][col] = '|';
            curRow++;
        }
        if(curRow >= dataArr.size()) return splitCount;
    }

    if(dataArr[curRow][col] == '^'){
        splitCount++;
        splitCount = splitCount + make_beam(curRow,col - 1);
        splitCount = splitCount + make_beam(curRow, col + 1);
    }
    return splitCount;
}

unsigned long make_beam_2(int row, int col){
    unsigned long splitCount = 1;
    int curRow = row;

    while(dataArr[curRow][col] == '.'){
        curRow++;
        if(curRow >= dataArr.size()) return 1;
    }
    fo << curRow << "   " <<  col << endl;
    if(dataArr[curRow][col] == '^'){
        splitCount = splitCount + make_beam_2(curRow,col - 1) - 1;
        splitCount = splitCount + make_beam_2(curRow, col + 1);
    }
    
    return splitCount;
}

unsigned long part_1(){
    unsigned long sum = 0;

    int startPos;
    for(int i = 0; i < dataArr[0].size(); i++){
        if(dataArr[0][i] == 'S'){
            startPos = i;
            break;
        }
    }

    sum = make_beam(1, startPos);
    for(int i = 0; i < dataArr.size(); i++){
        for(int j = 0; j < dataArr[0].size(); j++){
           cout << dataArr[i][j];
        }
        cout << endl;
    }
    return sum;
}

unsigned long part_2(){
    unsigned long sum = 0;
    cout << endl;

    int startPos;
    for(int i = 0; i < dataArr[0].size(); i++){
        if(dataArr[0][i] == 'S'){
            startPos = i;
            break;
        }
    }

    //sum = make_beam_2(1, startPos);
    vector<int>colTotal(dataArr[0].size(), 0);

    for(int i = 0; i < dataArr.size(); i++){
        for(int j = 0; j < dataArr[0].size(); j++){
            if(dataArr[i][j] == 'S') colTotal[j] = 1;
            if(dataArr[i][j] == '^'){
                colTotal[j-1] = colTotal[j-1] + colTotal[j];
                colTotal[j+1] = colTotal[j+1] + colTotal[j];

                colTotal[j] = 0;
            }
        }
    }

    for(int s : colTotal){
        sum = sum + s;
    }

    return sum;
}

int main(){

    ifstream f("input.txt");
    fo.open("o.txt");
    
    if(!f.is_open()){
        cout << "file read error" << endl;
        return 1;
    }

    string inpString;
    vector<vector<char>> dataArrCopy;
    int counts;

    while(getline(f, inpString)){
        vector<char> charLine;
        
        for(char c : inpString){
            charLine.push_back(c);
        }
        dataArr.push_back(charLine);
        if(std::count(charLine.begin(), charLine.end(), '.') != charLine.size()){
            dataArrCopy.push_back(charLine);
        }
        
        
    }
    //cout << "Answer to Part 1: " << part_1() << endl;

    //dataArr = dataArrCopy;
    cout << "Answer to Part 2: " << part_2() << endl;


    return 0;
}
