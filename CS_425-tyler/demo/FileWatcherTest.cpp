#include <iostream>

#include "FileWatcher.h"

int main() {

	using namespace std;

	FileWatcher fw("./assets/scripts", chrono::milliseconds(1000));


    fw.start([](std::string path_to_watch, FileStatus status) -> void {
        // Process only regular files, all other file types are ignored
        if (!std::filesystem::is_regular_file(std::filesystem::path(path_to_watch)) && status != FileStatus::erased) {

            return;
        }


        switch (status) {
            case FileStatus::created:
                std::cout << "File created: " << path_to_watch << '\n';
                break;
            case FileStatus::modified:
                std::cout << "File modified: " << path_to_watch << '\n';
                break;
            case FileStatus::erased:
                std::cout << "File erased: " << path_to_watch << '\n';
                break;
            default:
                std::cout << "Error! Unknown file status.\n";
            }
        });

}