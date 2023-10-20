#include <iostream>
#include <fstream>
using namespace std;

int nums_nodes;
int nums_edges;



void read_file() { // we need to read from the file
    std::ifstream file ("rmat15.dimacs");
    // we need to get the edges and the nodes from the file

    std::string curWord;

    if (file.is_open()) {
        while(file.good()) {
            file >> curWord;
            std::cout << curWord;
        }
    }

    return;
}


int main () {
    read_file();
}