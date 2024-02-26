#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <bitset>
using namespace std;

unordered_map<string,pair<string,string>> mp = {
    {"add",{"0000000","000"}},
    {"sub",{"0100000","000"}},
    {"or",{"0000000","110"}},
    {"and",{"0000000","111"}},
    {"ld",{"0000000","100"}},
    {"sd",{"0000000","010"}},
    {"beq",{"0000000","000"}}
};


vector<string> separator(string st){
    string inputString = st;
    transform(inputString.begin(),inputString.end(),inputString.begin(),::tolower);
    vector<string> words;

    stringstream ss(inputString);
    string word;
    while (getline(ss, word, ' ')) {
        stringstream wordStream(word);
        string subWord;
        while (getline(wordStream, subWord, ',')) {
            stringstream char1(subWord);
            string ssword;
            while(getline(char1,ssword,'(')){
                stringstream char2(ssword);
                string sssword;
                while(getline(char2,sssword,')')){
                    words.push_back(sssword);
                }
            }
        }
    }

    return words;
}

string transformRegToBi(string st){
    string s = "";
    for(int i=1;i<st.length();i++){
        s+=st[i];
    }
    int x = stoi(s);
    return bitset<5>(x).to_string();
}

vector<string> converterRT(vector<string> v){
    vector<string> vret(6);
    vret[0] = mp[v[0]].first;
    vret[3] = mp[v[0]].second;
    vret[5] = "0110011";
    vret[1] = transformRegToBi(v[3]);
    vret[2] = transformRegToBi(v[2]);
    vret[4] = transformRegToBi(v[1]);
    return vret;
}

vector<string> converterLW(vector<string> v){
    vector<string> vter(5);
    vter[0] = bitset<12>(stoi(v[2])).to_string();
    vter[1] = transformRegToBi(v[3]);
    vter[2] = mp[v[0]].second;
    vter[3] = transformRegToBi(v[1]);
    vter[4] = "0000011";
    return vter;
}

vector<string> converterSD(vector<string> v){
    vector<string> vter(6);
    string s = bitset<12>(stoi(v[2])).to_string();
    vter[1] = transformRegToBi(v[1]);
    vter[2] = transformRegToBi(v[3]);
    vter[3] = mp[v[0]].second;
    vter[5] = "0100011";
    vter[0] = s.substr(0,7);
    vter[4] = s.substr(7,5);
    return vter;
}

vector<string> converterBR(vector<string> v){
    vector<string> vter(6);
    string s = bitset<12>(stoi(v[3])).to_string();
    vter[1] = transformRegToBi(v[2]);
    vter[2] = transformRegToBi(v[1]);
    vter[3] = mp[v[0]].second;
    vter[5] = "1100011";
    vter[0] = s.substr(0,1)+s.substr(2,6);
    vter[4] = s.substr(1,1)+s.substr(8,4);
    return vter;
}

vector<string> convertToBinary(vector<string> v){
    if(v[0]=="add" || v[0]=="sub" || v[0]=="and" || v[0]=="or"){
        return converterRT(v);
    }
    else if(v[0]=="beq"){
        return converterBR(v);
    }
    else if(v[0]=="sd"){
        return converterSD(v);
    }
    return converterLW(v);
}

int main() {
    fstream f;
    f.open("Assembley.asm",ios::in);
    if(!f){
        cout<<"Error loading the file"<<endl;
        return 1;
    }

    
    ofstream outFile("Output.exeFile",ios::app);
    if(!outFile){
            cout<<"Error creating file"<<endl;
            return 1;
    }

    string line;
    while(getline(f,line)){
        vector<string> words = separator(line);
        vector<string> binaryForm = convertToBinary(words);
        
        for(int i=0;i<binaryForm.size();i++){
            outFile<<binaryForm[i]<<" ";
        }
        outFile<<endl;
    }

    outFile.close();
    cout<<endl;
    f.close();
    return 0;
}