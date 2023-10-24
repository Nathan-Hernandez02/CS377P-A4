#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;


struct node
    {
        double node_label[2];
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
    
    edge(int s, int d, int w) {
        sourceNode = s;
        destNode = d;
        weight = w;
    }
};

class graph {
    public:
        int nums_nodes; // total nodes
        int nums_edges; // total edges
        std::vector<edge> connect; // edge consists of source, destination, and weight
        struct node * graph_node;
        int * rp;
        int * ci;
        int * ai;
};



void handle_arrays(vector<edge> non_dups, graph fin) {
    int num_edges = non_dups.size() + 2;
    int num_nodes = fin.nums_nodes + 2;

    fin.rp = new int[num_nodes];
    fin.ci = new int[num_edges];
    fin.ai = new int[num_edges];
    fin.graph_node = new node[num_nodes];

    fin.rp[0] = 1;
    fin.ci[0] = 1;
    fin.ai[0] = 1;

    non_dups.insert(non_dups.begin(), edge(fin.rp[0], fin.ci[0], fin.ai[0]));

    int cur_node = 0;

    for(int i = 1; i <= num_edges; i++) {
        //const?
        edge cur_edge = non_dups[i];
        if (cur_node < cur_edge.sourceNode) {
            cur_node += 1;
            fin.rp[cur_node] = i;
        }
        else{
            fin.ai[i] = cur_edge.weight;
            fin.ci[i] = cur_edge.destNode;
            i++;
        }
    }

    int fin_edges = num_edges + 1;
    int fin_nodes = num_edges + 1;

    for(int i = cur_node + 1; i <= fin_nodes; i++) {
        fin.rp[i] = fin_edges;
    }

    fin.ai[fin_edges] = 0;
    fin.ci[fin_edges] = fin_nodes;
}


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
        } else {
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
        // int x = 0;
        //     while (x < non_dups.size()) {
        //         cout << non_dups[x].sourceNode << " " << 
        //             non_dups[x].destNode << " " << non_dups[x].weight << "\n";
        //         x++;
        //     }
    handle_arrays(non_dups, fin);
    return fin.connect;
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
            }
        }
        fin.connect = sort_graph(fin);
        fin.connect = handle_dups(fin);
    }

    return;
}

void pagerank(graph graph){
    double thresh_hold = 1.0e-4;
    double damping = 0.85;

    int num_nodes = graph.nums_nodes;
    int num_edges = graph.nums_edges;
    vector<edge> current = graph.connect;

    bool is_converged = false;
    bool first_time = true;

    while (!is_converged || first_time) {

        // reset_next_level

        for (int i = 0; i < num_nodes; i++) {
        }

        for (int s = 1; s < num_nodes; s++) {
            // get label
            // get label
            // if
                // false
            // else
                // true
        }


        first_time = false;
    }
}

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