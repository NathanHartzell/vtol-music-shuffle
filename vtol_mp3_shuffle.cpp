#include<vector>
#include<string.h>
#include<iostream>
#include<filesystem>
#include<fstream>

using namespace std;

namespace fs = std::filesystem;

#define FILEPATH "/Users/nathanhartzell/Desktop/vtol_mp3_stream copy"
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

    std::string line;
    if (std::getline(file, line)) {
        std::cout << "Read line: " << line << std::endl;
    } else {
        std::cerr << "Could not read a line from the file." << std::endl;
    }

    file.close();

    std::vector<std::string> track_list;

    // iterate over song directory and store all filenames
    for (const auto& entry : fs::directory_iterator(FILEPATH)) {
        track_list.push_back(entry.path().filename().string());
    }

    // iterate over stored list of filenames, removing non-mp3s
    for (int i = 0; i < track_list.size();) {
        if (is_mp3(track_list[i])){

            // check if file has prepended "vtol_" prefix
            // allows user to add new files without manually adding prefix
            if (track_list[i].substr(0, 5) == PREFIX) { 

                // removes prefix from filenames that have it
                track_list[i] = track_list[i].substr(8, track_list[i].size()); 
                std::cout << track_list[i] << std::endl;
            } 
            ++i;
        } else { track_list.erase(track_list.begin() + i); }
    }

    // shuffle track list



    return 0;
}