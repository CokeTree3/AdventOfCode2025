
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int findLargestValInString(string inp, char baseVal = '0'){
    char largestValue = baseVal;
    int topValueLocation = -1;

    if(inp.length() == 1){
        return 0;
    }

    for(int i = 0; i < inp.length(); i++){
            
        if(inp[i] > largestValue){
            largestValue = inp[i];
            topValueLocation = i;
        }
    }
    return topValueLocation;
}

unsigned long part_1(vector<string>& banks){
    unsigned long sum = 0;

    for(string battBank : banks){
        
        int firstLoc = findLargestValInString(battBank.substr(0, battBank.length() - 1 ));
        int secLoc = findLargestValInString(battBank.substr(firstLoc + 1, battBank.npos));

        int resultVal = stoi(std::string() + battBank[firstLoc] + battBank[firstLoc + 1 + secLoc]);

        sum = sum + resultVal;
    }

    return sum;
}

unsigned long part_2(vector<string>& banks){
    unsigned long sum = 0;

    for(string battBank : banks){

        int indexList[12];
        int startPos = 0;
        int endPos = battBank.length() - 11;

        for(int i = 0; i < 12 ; i++){
            int ret = findLargestValInString(battBank.substr(startPos, endPos - startPos));
            indexList[i] = ret + startPos;
            endPos++;
            startPos = startPos + ret + 1;
        }
        
        string resultString;

        for(int i = 0; i < 12 ; i++){
            resultString = resultString + battBank[indexList[i]];
        }

        unsigned long resultVal = stol(resultString);
        
        sum = sum + resultVal;
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
        banks.push_back(inpString);
    }

    cout << "Answer to Part 1: " << part_1(banks) << endl;
    cout << "Answer to Part 2: " << part_2(banks) << endl;

    return 0;
}