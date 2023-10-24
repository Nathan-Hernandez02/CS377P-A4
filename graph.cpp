#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;


struct node
    {
        
        double curNode;
        double nextNode;
    };

struct edge { // single edge must have a source, weight, and dest
    int sourceNode;
    int destNode;
    int weight;
    
    edge() {
        sourceNode = 0;
        destNode = 0;
        weight = 0;
    }
    
    edge(int src, int dest, int whey) : sourceNode(src), destNode(dest), weight(whey) {} // change the formatting on this later
};

class graph {
    public:
        int nums_nodes; // total nodes
        int nums_edges; // total edges
        std::vector<edge> connect; // edge consists of source, destination, and weight
};


vector<edge> sort_graph(graph fin) {
    sort(fin.connect.begin(), fin.connect.end(), [] (const edge& e1, const edge& e2) { 
        if(e1.sourceNode < e2.sourceNode) {
            return true;
        } else if (e1.sourceNode == e2.sourceNode) {
            if(e1.destNode < e2.destNode) {
                return true;
            } else {
                return false;
            } 
        } 
        return false;
    });
    return fin.connect;
}

vector<edge> handle_dups(graph fin) {
    vector<edge> non_dups;
    int num_edges = fin.connect.size();
    int node1 = fin.connect[0].sourceNode;
    int node2 = fin.connect[0].destNode;
    int weight = fin.connect[0].weight;
    
    for (int i = 1; i < num_edges; i++) {
        if (fin.connect[i].sourceNode == fin.connect[i - 1].sourceNode && fin.connect[i].destNode == fin.connect[i - 1].destNode) {
            // duplicate edge
            // cout << "yo pierre you wanna come out 'ere" << "\n";
            weight = fin.connect[i].weight > weight ? fin.connect[i].weight : weight;
        } 
            else {
                // cout << "there's no time for hesitation, that only leads to incarceration" << "\n";
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

    non_dups.push_back(edge(fin.connect[num_edges - 1].sourceNode, fin.connect[num_edges - 1].destNode, weight)); // change this to look like lines 68-64
    
    // cout << " for non dups \n";
    int x = 0;
        while (x < non_dups.size()) {
            cout << non_dups[x].sourceNode << " " << 
                non_dups[x].destNode << " " << non_dups[x].weight << "\n";
            x++;
        }

    return fin.connect;
    // // get the actual number of edges
    // num_edges = non_dups.size();

    // // allocate space for dynamic arrays
    // node = new Node[num_nodes + 2];
    // rp = new int[num_nodes + 2];
    // ci = new int[num_edges + 2];
    // ai = new int[num_edges + 2];

    // // rp[0] = 1 to be consistent with rp[1] = 1 (This affects the number of edges we get for node 1)
    // rp[0] = 1;
    // ci[0] = 0;
    // ai[0] = 0;
    // good_edges.insert(good_edges.begin(), Edge(rp[0], ci[0], ai[0]));

    // // loop through each edge in COO and construct CSR representation
    // int cur_node = 0;
    // int cur_edge = 1;
    // while (cur_edge <= num_edges)
    // {
    //     const Edge &e = good_edges[cur_edge];
    //     // update cur_node and its coresponding rp when current source node is larger than current node
    //     if (e.src > cur_node)
    //     {
    //         cur_node++;
    //         rp[cur_node] = cur_edge;
    //     }
    //     // copy the destination and weight to ci and ai otherwise
    //     else
    //     {
    //         ci[cur_edge] = e.dst;
    //         ai[cur_edge] = e.weight;
    //         cur_edge++;
    //     }
    // }

    // // set the remaining nodes without edges
    // for (int i = cur_node + 1; i <= num_nodes + 1; i++)
    // {
    //     rp[i] = num_edges + 1;
    // }
    // ci[num_edges + 1] = num_nodes + 1;
    // ai[num_edges + 1] = 0;
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
        fin.connect = sort_graph(fin);
        // sort(fin.connect.begin(), fin.connect.end(), [] (const edge& e1, const edge& e2) { 
            
        //     if(e1.sourceNode < e2.sourceNode) {
        //         return true;
        //     } else if (e1.sourceNode == e2.sourceNode) {
        //         if(e1.destNode < e2.destNode) {
        //             return true;
        //         } else {
        //             return false;
        //         } 
        //     } 
        //     return false;
        // });

        // int x = 0;
        // while (x < fin.connect.size()) {
        //     cout << fin.connect[x].sourceNode << " " << 
        //         fin.connect[x].destNode << " " << fin.connect[x].weight << "\n";
        //     x++;
        // }

        fin.connect = handle_dups(fin);
    }

    return;
}

// void pagerank(graph graph){

//     double thresh_hold = 1.0e-4;
//     double damping = 0.85;

//     int num_nodes = graph.nums_nodes;
//     int num_edges = graph.nums_edges;
//     vector<edges> current = graph.connect;
// }

int main (int argc, char* argv[]) {

    string text_con[] = {"rmat15.dimacs", "road-NY.dimacs", "wiki.dimacs"}; // wiki.dimacs

    int choice;

    while(choice != 1 && choice != 2 && choice != 3) {
        cout << "Choose Between: rmat15 == 1, road_ny == 2 or wiki == 3 : ";

        cin >> choice;
    }

    graph Graph; // uninitialized graph

    // enters the data into graph
    read_file(text_con[choice - 1], Graph);

    // pagerank
    // pagerank(Graph);

    // prints

}