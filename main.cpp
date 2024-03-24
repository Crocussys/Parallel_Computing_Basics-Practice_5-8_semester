#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

string abc = "абвгдеёжзийклмнопрстуфхцчшщъыьэюяabcdefghijklmnopqrstuvwxyz";
string ABC = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯABCDEFGHIJKLMNOPQRSTUVWXYZ";

void append_word(string str, vector<pair<string, int>>& arr){
    for (int j = 0; j < arr.size(); j++){
        if (arr[j].first == str){
            arr[j].second++;
            return;
        }
    }
    arr.push_back({str, 1});
}

int main()
{
    fstream file("../Parallel_Computing_Basics-Practice_5-8_semester/text.txt", ios::in);
    if (!file){
        cout << "FileError" << endl;
        return -1;
    }
    vector<pair<string, int>> words;
    string temp;
    for(file >> temp; !file.eof(); file >> temp) {
        string word = "";
        bool flag_w = false;
        for(int i = 0; i < temp.length(); i++){
            char letter = temp[i];
            bool flag_l = false;
            for (int j = 0; j < ABC.length(); j++){
                if (letter == ABC[j]){
                    letter = abc[j];
                    flag_l = true;
                    break;
                }
            }
            if (!flag_l){
                for (int j = 0; j < abc.length(); j++){
                    if (letter == abc[j]){
                        flag_l = true;
                        break;
                    }
                }
            }
            if (flag_l){
                word += letter;
                flag_w = true;
            }else if (flag_w){
                append_word(word, words);
                word = "";
                flag_w = false;
            }
        }
        if (flag_w){
            append_word(word, words);
        }
    }
    file.close();

    unordered_map<string, int> ans;
    for (int j = 0; j < words.size(); j++){
        ans.insert(words[j]);
    }

    for (auto& pair : ans){
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}
