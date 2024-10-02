#include<vector>
#include<string.h>
#include<iostream>
#include<filesystem>
#include<fstream>
#include<random>
#include<sstream>

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

    std::vector<fs::path> track_list;

    // iterate over song directory and store all filenames
    for (const auto& entry : fs::directory_iterator(vtol_music_dir)) {
        
        // store filenames ending in .mp3
        if (is_mp3(entry.path().filename().string())) {
            //std::cout << entry.path() << std::endl;
            track_list.push_back(entry.path());
        }
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, track_list.size()-1);
    int rand_index;
    fs::path temp;

    // shuffle track list
    for (int i=0; i < track_list.size(); i++) {
        rand_index = distrib(gen);
        if (rand_index != i) {
            temp = track_list[i];
            track_list[i] = track_list[rand_index];
            track_list[rand_index] = temp;
        }
    } 
    // rename files in their random order

    std::string track_name;
    fs::path new_path;
    std::ostringstream oss;

    for (int i = 0; i < track_list.size(); i++) {
        // get filename from path obj
        track_name = track_list[i].filename().string();
        // check if filename has prefix and remove it
        if (track_name.substr(0, 5) == PREFIX) { 

            // removes prefix from filenames that have it
            track_name = track_name.substr(9, track_name.size());
        }
        oss.str("");
        oss << vtol_music_dir << PREFIX << std::setfill('0') << std::setw(3) << (i + 1)
            << " " <<  track_name;
        new_path = oss.str();
        try {
            fs::rename(track_list[i], new_path);
        } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << e.what() << std::endl;
        }
    }
    return 0;
}