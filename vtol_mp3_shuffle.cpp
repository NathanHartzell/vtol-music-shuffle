#include<vector>
#include<string.h>
#include<iostream>
#include<filesystem>
#include<fstream>
#include<random>

using namespace std;

namespace fs = std::filesystem;

#define IMPORT_PATH "dir_path.txt"
#define PREFIX "vtol_"

// @return true if file ends with .mp3
bool is_mp3(std::string filename) {
    return filename.size() >= 4 && filename.substr(filename.size() - 4) == ".mp3";
}

int main() {

    std::ifstream file(IMPORT_PATH);
    if (!file) {
        std::cerr << "Could not open the file: " << IMPORT_PATH << std::endl;
        return 1;
    }

    std::string vtol_music_dir;
    if (std::getline(file, vtol_music_dir)) {
    } else {
        std::cerr << "Could not read a line from the file." << std::endl;
    }

    file.close();

    std::vector<std::string> track_list;

    // iterate over song directory and store all filenames
    for (const auto& entry : fs::directory_iterator(vtol_music_dir)) {
        
        // store filenames ending in .mp3
        if (is_mp3(entry.path().filename().string()))
            track_list.push_back(entry.path().filename().string());
    }

    // iterate over stored list of filenames, removing non-mp3s
    for (int i = 0; i < track_list.size(); i++) {
        // check if file has prepended "vtol_" prefix
        // allows user to add new files without manually adding prefix
        if (track_list[i].substr(0, 5) == PREFIX) { 

            // removes prefix from filenames that have it
            track_list[i] = track_list[i].substr(8, track_list[i].size()); 
            
        }
        std::cout << track_list[i] << std::endl; // remove me
    }

    std::cout << std::endl << std::endl << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, track_list.size()-1);
    int rand_index;
    std::string temp;

    // TODO: shuffle track list
    for (int i=0; i < track_list.size(); i++) {
        rand_index = distrib(gen);
        if (rand_index != i) {
            temp = track_list[i];
            track_list[i] = track_list[rand_index];
            track_list[rand_index] = temp;
        }
    }
    
    for (const std::string& song : track_list) {
        std::cout << song << std::endl;
    }
    // TODO: rename files in their random order


    return 0;
}