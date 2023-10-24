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

class graph {
    public:
        int nums_nodes; // total nodes
        int nums_edges; // total edges
        std::vector<edge> connect; // edge consists of source, destination, and weight
};


void sort_graph(graph fin) {
    sort(fin.connect.begin(), fin.connect.end(), [] (const edge& e1, const edge& e2) { 
        if(e1.sourceNode < e2.sourceNode) {
        return true;
        } else if (e1.sourceNode == e2.sourceNode) {
        if(e1.destNode < e2.destNode) {
            return true;
        } else if (e1.destNode == e2.destNode) {
            return e1.weight < e2.weight;
        }
        }
    });
}

void handle_dups(graph fin) {
    vector<edge> non_dups;
    int num_edges = fin.connect.size();
    int node1 = fin.connect[0].sourceNode;
    int node2 = fin.connect[0].destNode;
    int weight = fin.connect[0].weight;
    for (int i = 1; i < num_edges; i++) {
        if (fin.connect[i].sourceNode == fin.connect[i - 1].sourceNode && fin.connect[i].destNode == fin.connect[i - 1].destNode) {
            // duplicate edge
            weight = fin.connect[i].weight > weight ? fin.connect[i].weight : weight;
        } 
            else {
                // add the edge with max_weight to good_edges
                edge curEdge;
                curEdge.sourceNode = fin.connect[i - 1].sourceNode;
                curEdge.destNode = fin.connect[i - 1].destNode;
                curEdge.weight = weight;
                            non_dups.push_back(curEdge);
                            // initialize max_weight
                weight = fin.connect[i].weight;
            }
        }
        // deal with the last edge
    non_dups.push_back(edge(fin.connect[num_edges - 1].sourceNode, fin.connect[num_edges - 1].destNode, weight));
}
//
void read_file(string choice, graph Graph) { // we need to read from the file
    std::ifstream file (choice);
    // if file is opened close it
    graph fin; // only one graph needed

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
        sort_graph(fin);
        handle_dups(fin);
    }

    return;
}

void pagerank(graph graph){

    double thresh_hold = 1.0e-4;
    double damping = 0.85;

    int num_nodes = graph.nums_nodes;
    int num_edges = graph.nums_edges;
    vector<edges> current = graph.connect;
}

int main (int argc, char* argv[]) {

    string text_con[] = {"rmat15.dimacs", "road-NY.dimacs", "wiki.dimacs"};

    int choice;

    while(choice != 1 || choice != 2 || choice != 3) {
        cout << "Choose Between: rmat15 == 1, road_ny == 2 or wiki == 3 : ";

        cin >> choice;
    }

    graph Graph; // uninitialized graph

    // enters the data into graph
    read_file(text_con[choice - 1], Graph);

    // pagerank
    pagerank(Graph);

    // prints

}