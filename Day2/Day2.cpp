
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>

using namespace std;

const unsigned long powArray[12]={0, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000};

unsigned long part_1(vector<string>& ranges){

    unsigned long IdSum = 0;

    for(string r : ranges){
        string startString = r.substr(0,r.find('-'));
        string endString = r.substr(r.find('-') + 1, r.npos);
        unsigned long start = stol(startString);
        unsigned long end = stol(endString);

        unsigned long curNum = start;

        if(startString.length() % 2 !=0){
            if(endString.length() == startString.length()){
                continue;
            }
            curNum = powArray[startString.length()];
        }

        while(curNum <= end){
            string curNumString = to_string(curNum);
            unsigned long first = stol(curNumString.substr(0, curNumString.length() / 2));
            unsigned long sec = stol(curNumString.substr(curNumString.length() / 2, curNumString.npos));
            
            if(to_string(sec).length() != curNumString.length() / 2){
                sec = powArray[curNumString.length() / 2 - 1];
                curNum = stol(to_string(first) + to_string(sec));
                continue;
            }

            if(first == sec){
                IdSum = IdSum + curNum;
            }

            if(first > sec){
                sec++;
                if(stol(to_string(first) + to_string(first)) > start){
                    sec = first;
                }
                else{
                    sec++;
                }
                
            }
            else if(first < sec){
                if(stol(to_string(first) + to_string(first)) > start){
                    sec = first;
                }
                else{
                    first++;
                }
            }else{
                first++;
                sec++;
            }
            curNum = stol(to_string(first) + to_string(sec));
        }
    }

    return IdSum;
}

unsigned long part_2(vector<string>& ranges){

    unsigned long IdSum = 0;

    for(string r : ranges){
        int mid = r.find('-');
        string startString = r.substr(0,mid);
        string endString = r.substr(mid + 1, r.npos);
        unsigned long end = stol(endString);

        unsigned long curNum = stol(startString);
        regex reg("(.+)\\1+");

        while(curNum <= end){
            string curNumString = to_string(curNum);
            if(regex_match(curNumString, reg)){
                IdSum = IdSum + curNum;
            }
            curNum++;
        }
    }
    return IdSum;
}

int main(){

    ifstream f("input.txt");
    
    if(!f.is_open()){
        cout << "file read error" << endl;
        return 1;
    }

    string inpString;
    vector<string> ranges;

    while(getline(f, inpString)){
        string temp;
        stringstream ss(inpString);

        while(getline(ss, temp, ',')){
            ranges.push_back(temp);
        }
    }

    cout << "Answer to Part 1: " << part_1(ranges) << endl;
    cout << "Answer to Part 2: " << part_2(ranges) << endl;
    return 0;
}