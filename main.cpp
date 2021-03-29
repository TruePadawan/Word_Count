/* THIS PROGRAM LISTS OUT THE INDIVIDUAL WORDS IN THE WORDS.TXT FILE
 * AND STATES HOW MANY TIME THEY OCCUR AND ALSO WHAT LINE THEY APPEAR ON
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <string>
#include <iomanip>
#include <vector>
//DISPLAYS THE LINES WHERE EACH WORD APPEARS ON
void display_line(std::set<int> a){
    std::cout << "[ ";
    for(auto b: a)
        std::cout << b << " ";
    std::cout << "]\n";
}
//DISPLAYS THE WORD, HOW MANY TIMES IT APPEARS AND THE LINES IT APPEARS ON
void display_words(const std::map<std::string, int> &words, const std::map<std::string, std::set<int>> &occur) {
    std::cout << std::setw(18) << std::left << "\nWord"
                << std::setw(14) << std::right << "Count"<< std::setw(26)<< "Occurrences(lines)" << std::endl;
    std::cout << std::setw(96) << std::setfill('=') << "" << std::setfill(' ') << std::endl;
    for (auto pair: words){
        std::cout << std::setw(18) << std::left << pair.first 
                       << std::setw(13) << std::right << pair.second << std::setw(10);
                display_line(occur.at(pair.first));
    }
}

// This function removes periods, commas, semicolons and colon in 
// a string and returns the clean version
std::string clean_string(const std::string &s) {
    std::string result;
    for (char c: s) {
        if (c == '.' || c == ',' || c == ';' || c == ':')
            continue;
        else
            result += c;
    }
    return result;
}

// word_count process the file and builds a map of words, the 
// number of times they occur in the file and the lines they appear on
void word_count() {
    std::map<std::string, int> words;
    std::string line;       
    std::string word;
    int num{0};
    std::map<std::string, std::set<int>> occur;
    std::ifstream in_file {"words.txt"};
    if (in_file) {
        while(!in_file.eof()){
            std::getline(in_file, line);
            num += 1;
            std::stringstream ss{line};
            
            while(!ss.eof()){
                std::vector<int> temp;
                ss >> word;
                word = clean_string(word);
                if(words.count(word)){ //CHECKS TO SEE IF THE WORD IS ALREADY IN THE SET
                    words[word] += 1;
                    occur.at(word).insert(num);
                }else{
                    words.insert(std::make_pair(word, 1));
                    occur.insert(std::make_pair(word, std::set<int>{num}));
                }
            }
            
        }
        
        in_file.close();
        display_words(words, occur);
    } else {
        std::cerr << "Error opening input file" << std::endl;
    }
}

int main() {
    word_count();
    return 0;
}

