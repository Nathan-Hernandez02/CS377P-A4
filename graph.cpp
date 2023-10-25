#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;


struct node
    {
        double node_label[2];
    };

struct edge { // single edge must have a source, weight, and dest
    int sourceNode;
    int destNode;
    int weight;
    
    edge(int s, int d, int w) {
        sourceNode = s;
        destNode = d;
        weight = w;
    }
};

struct PairHash
{
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const
    {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
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
        bool is_allocated;

    graph() {
        is_allocated = true;
    }

    ~graph() {
        if(is_allocated) {
            delete[] rp;
            delete[] ci;
            delete[] ai;
            delete[] graph_node;
        }
    }
};

void handle_arrays(vector<edge> non_dups, graph *fin)
{
    int num_edges = non_dups.size();
    int num_nodes = fin->nums_nodes;

    // Deallocate previously allocated memory (if any)
    delete[] fin->rp;
    delete[] fin->ci;
    delete[] fin->ai;
    delete[] fin->graph_node;

    // Allocate memory for the arrays
    fin->rp = new int[num_nodes + 2];
    fin->ci = new int[num_edges + 2];
    fin->ai = new int[num_edges + 2];
    fin->graph_node = new node[num_nodes + 2];

    // Initialize arrays
    fin->rp[0] = 1;
    fin->ci[0] = 1;
    fin->ai[0] = 1;

    int cur_node = 0;

    for (int i = 0; i < num_edges; i++) {
        edge cur_edge = non_dups[i];
        if (cur_node < cur_edge.sourceNode)
        {
            cur_node = cur_edge.sourceNode;
            fin->rp[cur_node] = i + 1; // Adjust the index by 1
        }

        fin->ai[i + 1] = cur_edge.weight;
        fin->ci[i + 1] = cur_edge.destNode;
    }

    // Set final edges and nodes
    int fin_edges = num_edges + 1;
    int fin_nodes = num_nodes + 1;

    for (int i = cur_node + 1; i <= fin_nodes; i++) {
        fin->rp[i] = fin_edges;
    }

    fin->ai[fin_edges] = 0;
    fin->ci[fin_edges] = fin_nodes;
}

bool compare_edge(const edge &e1, const edge &e2)
{
    if (e1.sourceNode != e2.sourceNode) {
        return e1.sourceNode < e2.sourceNode;
    }
    return e1.destNode < e2.destNode;
}

void sort_graph(graph *fin)
{
    sort(fin->connect.begin(), fin->connect.end(), compare_edge);
}

vector<edge> handle_dups(graph *fin)
{
    vector<edge> non_dups;
    unordered_map<pair<int, int>, int, PairHash> edgeMap; // Use the custom hasher

    for (const edge &curEdge : fin->connect)
    {
        pair<int, int> edgeKey(curEdge.sourceNode, curEdge.destNode);
        if (edgeMap.find(edgeKey) != edgeMap.end())
        {
            // Edge already exists, update the weight if needed
            edgeMap[edgeKey] = max(edgeMap[edgeKey], curEdge.weight);
        }
        else
        {
            // Not a duplicate, add it to the map
            edgeMap[edgeKey] = curEdge.weight;
        }
    }

    for (const auto &entry : edgeMap)
    {
        int sourceNode = entry.first.first;
        int destNode = entry.first.second;
        int weight = entry.second;
        non_dups.push_back(edge(sourceNode, destNode, weight));
    }

    // cout << " for non dups \n";
    // for (const edge &nonDupEdge : non_dups)
    // {
    //     cout << nonDupEdge.sourceNode << " " << nonDupEdge.destNode << " " << nonDupEdge.weight << "\n";
    // }

    handle_arrays(non_dups, fin);

    return non_dups;
}

//
void read_file(string choice, graph *fin) {
    ifstream file(choice);
    if (file.is_open())
    {
        string curline;
        while (getline(file, curline))
        {
            if (curline[0] == 'p')
            {
                sscanf(curline.c_str(), "p sp %d %d", &fin->nums_nodes, &fin->nums_edges);
            }
            else if (curline[0] == 'a')
            {
                int sourceNode, destNode, weight;
                sscanf(curline.c_str(), "a %d %d %d", &sourceNode, &destNode, &weight);
                edge curEdge = edge(sourceNode, destNode, weight);
                fin->connect.push_back(curEdge);
            }
        }
        sort_graph(fin);
        fin->connect = handle_dups(fin);
    }
}

int main (int argc, char* argv[]) {

    string text_con[] = {"rmat15.dimacs", "road-NY.dimacs", "wiki.dimacs"}; // wiki.dimacs

    int choice = 0;

    while(choice != 1 && choice != 2 && choice != 3) {
        cout << "Choose Between: rmat15 == 1, road_ny == 2 or wiki == 3 : ";

        cin >> choice;
    }

    graph * g = new graph(); // uninitialized graph

    // enters the data into graph
    read_file(text_con[choice - 1], g);

}

// cout << " for non dups \n";
// std::vector<edge>::size_type x = 0;
// while (x < non_dups.size())
// {
//     cout << non_dups[x].sourceNode << " " << non_dups[x].destNode << " " << non_dups[x].weight << "\n";
//     x++;
// }