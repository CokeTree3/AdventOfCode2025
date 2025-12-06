
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

unsigned long part_1(vector<pair<unsigned long, unsigned long>> ranges, vector<unsigned long> ids){
    unsigned long sum = 0;

    for(unsigned long id : ids){
        for(auto range : ranges){
            if(id >= range.first && id <= range.second){
                sum++;
                break;
            }
        }
    }

    return sum;
}

unsigned long part_2(vector<pair<unsigned long, unsigned long>> inputRanges){
    unsigned long sum = 0;
    bool changeDone = true;

    while(changeDone){
        for(int i = 0; i < inputRanges.size(); i++){

            pair<unsigned long, unsigned long> range = inputRanges[i];
            changeDone = false;

            for(int j = 1; j < inputRanges.size(); j++){
                if(j == i){
                    continue;
                }

                if(range.second < inputRanges[j].first){        // completely in front
                    continue;

                }else if(range.first < inputRanges[j].first && range.second >= inputRanges[j].first){ // starts in front, overlaps(possibly fully)

                    if(range.second > inputRanges[j].second){       // fully surrounds

                        inputRanges.erase(inputRanges.begin() + j);
                        j--;
                        changeDone = true;
                        continue;
                        
                    }else{                                  // ends inside of
                        inputRanges[j].first = range.first;
                        changeDone = true;
                    }

                }else if(range.first >= inputRanges[j].first && range.first <=  inputRanges[j].second) {  // starts inside of, ends inside of or after

                    if(range.second > inputRanges[j].second){       // ends after

                        inputRanges[j].second = range.second;
                        changeDone = true;
                        
                    }else{                                          // completely inside of
                        inputRanges.erase(inputRanges.begin() + i);
                        i--;
                        changeDone = true;
                        break;
                    }

                }else if(range.first > inputRanges[j].second){ // completely after
                    continue;
                }else{
                    cout << "miss" << endl;
                }
            }
        }
    }

    for(auto r : inputRanges){
        sum = sum + (r.second - r.first + 1);
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
    vector<pair<unsigned long, unsigned long>> ranges;
    vector<unsigned long> ids;

    while(getline(f, inpString)){
        string tempLine;

        if(inpString.find('-') != inpString.npos){
            string start = inpString.substr(0, inpString.find("-"));
            string end = inpString.substr(inpString.find("-") + 1, inpString.npos);

            pair<unsigned long, unsigned long> range = {stol(start), stol(end)};

            ranges.push_back(range);
        }
        else if(inpString == ""){
            continue;
        }else{
            ids.push_back(stol(inpString));
        }
        
    }
    cout << "Answer to Part 1: " << part_1(ranges, ids) << endl;
    cout << "Answer to Part 2: " << part_2(ranges) << endl;

    return 0;
}