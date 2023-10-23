#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;


struct edge { // single edge must have a source, weight, and dest
    int sourceNode;
    int destNode;
    int weight;
};

class CSR_graph {
    public:
        int nums_nodes; // total nodes
        int nums_edges; // total edges
        std::vector<edge> connect; // edge consists of source, destination, and weight
};

void read_file(string choice) { // we need to read from the file
    std::ifstream file (choice);
    // if file is opened close it
    CSR_graph fin; // only one graph needed

    std::string curline;

    if (file.is_open()) { 
        
        while(getline(file, curline)) {
            
            if (curline[0] == 'p') {
                // setting total nodes and edges
                sscanf(curline.c_str(), "p sp %d %d", &fin.nums_nodes, &fin.nums_edges); // get total edges and nodes
                // cout << fin.nums_edges << '\n';
            } else if (curline[0] == 'a') {
                edge curEdge;
                
                // adds edges, even duplicates (considering n1 and n2), will sort later
                sscanf(curline.c_str(), "a %d %d %d", &curEdge.sourceNode, &curEdge.destNode, &curEdge.weight);
                
                fin.connect.push_back(curEdge);

                // cout << curEdge.sourceNode << " " << curEdge.destNode << " " << curEdge.weight << '\n';
            }
        }
        // sort the edges (doesn't get rid of duplicates yet)
        sort(fin.connect.begin(), fin.connect.end(), 
        [] (const edge& e1, const edge& e2) { 
          return (e1.sourceNode < e2.sourceNode) ? true : (e1.sourceNode == e2.sourceNode) ? (e1.destNode < e2.destNode) : false; // needs to modified to sort weights too
        });

        if (e1.sourceNode < e2.sourceNode) {
            return true;
        } else if (e1.sourceNode == e2.sourceNode) {
            if (e1.destNode < e2.destNode) {
                false
            }
        }
        
        // handle duplicate in the edges
        // vector<edge> non_dups;
        // int num_edges = fin.connect.size();
        // node1 = fin.connect[0].sourceNode;
        // node2 = fin.connect[0].destNode;
        // weight = fin.connect[0].weight;
        // for (int i = 1; i < num_edges; i++) {
        //     if (fin.connect[i].sourceNode == fin.connect[i - 1].sourceNode && fin.connect[i].destNode == fin.connect[i - 1].destNode) {
        //         // duplicate edge
        //         weight = fin.connect[i].weight > weight ? fin.connect[i].weight : weight;
        //     } 
        //     else {
        //         // add the edge with max_weight to good_edges
        //         edge curEdge;
        //         curEdge.sourceNode = fin.connect[i - 1].sourceNode;
        //         curEdge.destNode = fin.connect[i - 1].destNode;
        //         curEdge.weight = weight;

        //         non_dups.push_back(curEdge);

        //         // initialize max_weight
        //         weight = fin.connect[i].weight;
        //     }
        // }
        // // deal with the last edge
        // good_edges.push_back(Edge(edges[edge_size - 1].src, edges[edge_size - 1].dst, max_weight));

        // // get the actual number of edges
        // num_edges = good_edges.size();

        // int x = fin.connect.size();
        // for (int i = 0; i < x; i++) {
        //     cout << fin.connect[i].sourceNode << " " << fin.connect[i].destNode << " " << fin.connect[i].weight << '\n';
        // }
    }

    return;
}



// void sort_edges(vector<edge> &) {
    
//     return;
// }


int main (int argc, char* argv[]) {

    string text_con[] = {"rmat15.dimacs", "road-NY.dimacs", "wiki.dimacs"};

    int choice;

    while(choice != 1 || choice != 2 || choice != 3) {
        cout << "Choose Between: rmat15 == 1, road_ny == 2 or wiki == 3 : ";

        cin >> choice;
    }

    read_file(text_con[choice - 1]);
}


// private:
//     int numNodes;
//     int numEdges;


//     // Function to read DIMACS file and construct CSR representation
//     void readDIMACS(std::ifstream& input) {
//         std::string line;
//         while (std::getline(input, line)) {
//             if (line[0] == 'p') {
//                 // Parse problem line to get the number of nodes and edges
//                 sscanf(line.c_str(), "p sp %d %d", &numNodes, &numEdges);

//                 // Initialize CSR data structures
//                 rowPointers.assign(numNodes + 1, 0);
//                 columnIndices.resize(numEdges);

//             } else if (line[0] == 'a') {
//                 // Parse edge information and construct CSR representation
//                 int source, target, weight;
//                 sscanf(line.c_str(), "a %d %d %d", &source, &target, &weight);
//                 columnIndices[rowPointers[source - 1]] = target - 1;
//                 rowPointers[source - 1]++;
//             }
//         }

//         // Update row pointers to store the correct offsets
//         int prefixSum = 0;
//         for (int i = 0; i <= numNodes; i++) {
//             int tmp = rowPointers[i];
//             rowPointers[i] = prefixSum;
//             prefixSum += tmp;
//         }
//     }
// };

// int main() {
//     std::string filename = "your_dimacs_graph_file.dimacs"; // Replace with your file's name
//     CSRGraph csrGraph(filename);
//     csrGraph.printCSR();
//     return 0;
// }