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

    fin->graph_node = new node[num_nodes + 2];
    fin->rp = new int[num_nodes + 2];
    fin->ci = new int[num_edges + 2];
    fin->ai = new int[num_edges + 2];

    // rp[0] = 1 to be consistent with rp[1] = 1 (This affects the number of edges we get for node 1)
    fin->rp[0] = 1;
    fin->ci[0] = 0;
    fin->ai[0] = 0;
    non_dups.insert(non_dups.begin(), edge(fin->rp[0], fin->ci[0], fin->ai[0]));

    int cur_node = 0;
    int cur_edge = 1;
    while (cur_edge <= num_edges) {
        const edge &e = non_dups[cur_edge];
        
        if (e.sourceNode > cur_node) {
            cur_node++;
            fin->rp[cur_node] = cur_edge;
        }
        else {
            fin->ci[cur_edge] = e.destNode;
            fin->ai[cur_edge] = e.weight;
            cur_edge++;
        }
    }
    for (int i = cur_node + 1; i <= num_nodes + 1; i++)
    {
        fin->rp[i] = num_edges + 1;
    }
    fin->ci[num_edges + 1] = num_nodes + 1;
    fin->ai[num_edges + 1] = 0;
}

bool compare_label(const edge &e1, const edge &e2)
{
    if (e1.sourceNode != e2.sourceNode) {
        return e1.sourceNode < e2.sourceNode;
    }
    return e1.destNode < e2.destNode;
}

void handle_dups(graph *fin) {
    std::vector<edge> &edges = fin->connect;
    std::sort(edges.begin(), edges.end(), compare_label);

    std::vector<edge> non_dups;
    edge current_edge = edges[0];

    for (int i = 1; i < edges.size(); i++) {
        const edge &next_edge = edges[i];

        if (current_edge.sourceNode == next_edge.sourceNode && current_edge.destNode == next_edge.destNode) {
            current_edge.weight = std::max(current_edge.weight, next_edge.weight);
        }
        else {
            non_dups.push_back(current_edge);
            current_edge = next_edge;
        }
    }
    non_dups.push_back(current_edge);

    handle_arrays(non_dups, fin);
}

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
        sort(fin->connect.begin(), fin->connect.end(), compare_label);
        handle_dups(fin);
    }
}

bool converged(graph *g)
{
    double con = 1.0e-4;
    for (int n = 1; n <= g->nums_nodes; n++)
    {
        const double cur = g->graph_node[n].node_label[0];

        const double next = g->graph_node[n].node_label[1];
        if (fabs(next - cur) > con)
        {
            return false;
        }
    }
    return true;
}


void pagerank(graph *g)
{
    double damp = 0.85;
    int num_nodes = g->nums_nodes;
    for (int n = 1; n <= num_nodes; n++)
    {
        g->graph_node[n].node_label[0] = 1.0 / num_nodes;
    }

    bool convergence = false;

    while (!convergence) {
        
        for (int n = 1; n <= num_nodes; n++) {
            g->graph_node[n].node_label[1] = (1.0 - damp) / (double)num_nodes;
        }

        for (int n = 1; n <= num_nodes; n++) {
            int out_degree = g->rp[n + 1] - g->rp[n];
            double equation = damp * g->graph_node[n].node_label[0] / (double)out_degree;
            for (int e = g->rp[n]; e < g->rp[n + 1]; e++) {
                int dst = g->ci[e];
                g->graph_node[dst].node_label[1] = g->graph_node[dst].node_label[1] + equation;
            }
        }
        convergence = converged(g);

        for (int n = 1; n <= num_nodes; n++) {
            g->graph_node[n].node_label[0] = g->graph_node[n].node_label[1];
        }
    }

    // scale the sum to 1
    double sum = 0.0;
    int nodes = g->nums_nodes;
    for (int n = 1; n <= nodes; n++) {
        sum += g->graph_node[n].node_label[0];
    }
    for (int n = 1; n <= nodes; n++) {
        double i = g->graph_node[n].node_label[0] / sum;
        g->graph_node[n].node_label[0] = i;
    }
}

bool compare_pair(const std::pair<int, double> &v1, const std::pair<int, double> &v2)
{
    if (v1.second > v2.second)
    {
        return true;
    }
    else if (v1.second == v2.second)
    {
        return v1.first < v2.first;
    }
    return false;
}

std::vector<std::pair<int, double>> pair_sort(graph *graph)
{
    std::vector<std::pair<int, double>> pairs;

    for (int i = 1; i <= graph->nums_nodes; i++)
    {
        pairs.push_back(std::make_pair(i, graph->graph_node[i].node_label[0]));
    }

    std::sort(pairs.begin(), pairs.end(), compare_pair);

    return pairs;
}

void print_pairs(std::vector<std::pair<int, double>> &pairs)
{
    ofstream out_stream("output.txt");
    for (const auto &pair : pairs)
    {
        out_stream << pair.first << " " << fixed << setprecision(6) << pair.second << endl;
    }
}

int main (int argc, char* argv[]) {

    string text_con[] = {"rmat15.dimacs", "road-NY.dimacs", "wiki.dimacs"}; // wiki.dimacs

    int choice = 0;

    while(choice != 1 && choice != 2 && choice != 3) {
        cout << "Choose Between: rmat15 == 1, road_ny == 2 or wiki == 3 : ";

        cin >> choice;
    }

    graph * g = new graph();

    // enters the data into graph
    read_file(text_con[choice - 1], g);

    // performs page rank
    pagerank(g);

    // sorts
    std::vector<std::pair<int, double>> pairs = pair_sort(g);

    // prints
    print_pairs(pairs);

    // cout << "new value 1 \n";

    return 0;
}