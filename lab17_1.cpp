#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<cstring>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string fn,vector<string> &names,vector<int> &scores,vector<char> &grades){
    ifstream op;
    op.open("name_score.txt");
    string text;
    char name[100];
    char format[] = "%[^:]:%i %i %i";
    while(getline(op,text)){
        int a=0,b=0,c=0;
        char textx[100];
        strcpy(textx,text.c_str());
        sscanf(textx,format,name,&a,&b,&c);
        names.push_back(name);
        scores.push_back(a+b+c);
        grades.push_back(score2grade(a+b+c));
    }
    op.close();
}

void getCommand(string &command,string &key){
    string text;
    cout << "Please input your command: ";
    getline(cin,text);
    int lo = text.find_first_of(" ");
    command = text.substr(0,lo);
    key = text.substr(lo+1);
}

void searchName(vector<string> &names,vector<int> &scores,vector<char> &grades,string key){
    int N = names.size();
    int status = 0;
    cout << "---------------------------------\n";
    for(int i = 0 ; i < N ; i++){
        if(key == toUpperStr(names[i])){
            cout << names[i] << "'s score = " << scores[i] << endl << names[i] << "'s grade = " << grades[i] << endl;
            status = 1;
        }
    }
    if(status != 1) cout << "Cannot found." << endl;
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &names,vector<int> &scores,vector<char> &grades,string key){
    int N = grades.size();
    int status = 0;
    char ikey[100];
    strcpy(ikey,key.c_str());
    cout << "---------------------------------\n";
    for(int i = 0 ; i < N ; i++){
        if(*ikey == grades[i]){
        cout << names[i] << " (" << scores[i] << ")" << endl;
        status = 1;
        }
    }
    if(status != 1) cout << "Cannot found." << endl;
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
