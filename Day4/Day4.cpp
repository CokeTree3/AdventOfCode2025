
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<vector<char>> map;

bool check_roll(int rowNr, int colNr){

    bool res;
    int neighborCount = 0;

    if(map.empty() || rowNr < 0 || colNr < 0) return false;

    if(rowNr >= map.size() || colNr >= map[0].size()) return false;

    for(int i = -1; i < 2; i++){
        if(rowNr + i < 0 || rowNr + i >= map.size()) continue;

        for(int j = -1; j < 2; j++){
            if(colNr + j < 0 || colNr + j >= map[rowNr].size()) continue;

            if(i==0 && j == 0) continue;

            if(map[rowNr + i][colNr + j] == '@' || map[rowNr + i][colNr + j] == 'x'){
                neighborCount++;
            }
        }
    }

    if(neighborCount >= 4) return false;
    else return true;
}



unsigned long part_1(vector<string>& banks){
    unsigned long sum = 0;

    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[i].size(); j++){
            if(map[i][j] == '@'){
                if(check_roll(i, j)){
                    sum++;
                }
            }
        }
    }

    return sum;
}

unsigned long part_2(vector<string>& banks){
    unsigned long sum = 0;
    int loopChange = 0;
    while(true){
        loopChange = 0;

        for(int i = 0; i < map.size(); i++){
            for(int j = 0; j < map[i].size(); j++){
                if(map[i][j] == '@' && check_roll(i, j)){
                    loopChange++;
                    map[i][j] = 'x';
                }
            }
        }

        for(int i = 0; i < map.size(); i++){
            for(int j = 0; j < map[i].size(); j++){
                if(map[i][j] == 'x'){
                    map[i][j] = '.';
                }
            }
        }
        if(loopChange > 0){
            sum = sum + loopChange;
        }else{
            break;
        }
    }

    return sum;
}

int main(){

    ifstream f("input.txt");
    
    if(!f.is_open()){
        cout << "file read error" << endl;
        return 1;
    }

    string inpString;
    vector<string> banks;

    while(getline(f, inpString)){
        vector<char> temp;
        for(char loc : inpString){
            temp.push_back(loc);
        }
        map.push_back(temp);
    }
    
    cout << "Answer to Part 1: " << part_1(banks) << endl;
    cout << "Answer to Part 2: " << part_2(banks) << endl;

    return 0;
}