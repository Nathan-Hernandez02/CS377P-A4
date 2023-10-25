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

    for (int i = 0; i < num_edges + 1; i++)
    {
        cout << fin->ai[i] << " " << fin->ci[i] << " " << fin->rp[i] << "\n";
    }
}

bool compare_edges(const edge &e1, const edge &e2)
{
    if (e1.sourceNode != e2.sourceNode) {
        return e1.sourceNode < e2.sourceNode;
    }
    return e1.destNode < e2.destNode;
}


// @TO:DO chnage style of this method!!!!!
///////////////////////////////////////////////////////////////////////////////////
void handle_dups(graph *fin)
{
    vector<edge> edges = fin->connect;
    vector<edge> good_edges;
    int edge_size = edges.size();

    // Sort the edges by source and destination nodes
    sort(edges.begin(), edges.end(), compare_edges);

    int max_weight = edges[0].weight;

    for (int i = 1; i < edge_size; i++)
    {
        if (edges[i].sourceNode == edges[i - 1].sourceNode && edges[i].destNode == edges[i - 1].destNode)
        {
            // Duplicate edge
            max_weight = max(max_weight, edges[i].weight);
        }
        else
        {
            // Add the edge with max_weight to good_edges
            good_edges.push_back(edge(edges[i - 1].sourceNode, edges[i - 1].destNode, max_weight));
            max_weight = edges[i].weight;
        }
    }

    // Deal with the last edge
    good_edges.push_back(edge(edges[edge_size - 1].sourceNode, edges[edge_size - 1].destNode, max_weight));

    // cout << "For non-duplicates:\n";
    // for (const edge &good_edge : good_edges)
    // {
    //     cout << good_edge.sourceNode << " " << good_edge.destNode << " " << good_edge.weight << "\n";
    // }

    handle_arrays(good_edges, fin);
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
        sort(fin->connect.begin(), fin->connect.end(), compare_edges);
        handle_dups(fin);
    }
}

void set_nodes(graph *graph, int num_nodes, double damping)
{
    for (int i = 0; i < num_nodes; i++)
    {
        double damp = damping * graph->graph_node[i].node_label[0];
        double rp_arr = graph->rp[i + 1] - graph->rp[i];

        double converge_equation = damp / rp_arr;

        for (int k = graph->rp[i]; k < graph->rp[i + 1]; k++)
        {
            int get_dst = graph->ci[k];
            graph->graph_node[get_dst].node_label[1] = graph->graph_node[get_dst].node_label[1] + converge_equation;
        }
    }
}

void pagerank(graph *graph)
{
    // from slides and assignment page.
    double convergence = 1.0e-4;
    double damping = 0.85;

    int num_nodes = graph->nums_nodes;
    // int num_edges = graph.nums_edges;
    vector<edge> current = graph->connect;

    bool is_converged = false;
    bool first_time = true;

    // sets current label
    for (int i = 1; i < num_nodes; i++)
    {
        graph->graph_node[i].node_label[0] = 1 / num_nodes;
    }

    while (!is_converged || first_time)
    {

        // sets next level
        for (int n = 1; n <= num_nodes; n++)
        {
            graph->graph_node[n].node_label[1] = (1.0 - damping) / (double)num_nodes;
        }

        set_nodes(graph, num_nodes, damping);

        for (int c = 1; c <= num_nodes; c++)
        {
            double cur = graph->graph_node[c].node_label[0];
            double next = graph->graph_node[c].node_label[1];

            if (fabs(next - cur) > convergence)
            {
                is_converged = false;
            }

            if (c == num_nodes)
            {
                is_converged = true;
            }
        }

        for (int l = 1; l <= num_nodes; l++)
        {
            graph->graph_node[l].node_label[0] = graph->graph_node[l].node_label[1];
        }

        double sum = 0.0;

        for (int i = 1; i <= num_nodes; i++)
        {
            sum += graph->graph_node[i].node_label[0];
        }
        for (int j = 1; j <= num_nodes; j++)
        {
            graph->graph_node[j].node_label[0] = graph->graph_node[j].node_label[0] / sum;
        }

        first_time = false;
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

    // ofstream out_stream(out_file);
    // for (const pair<int, double> &v : label)
    // {
    //     out_stream << v.first << " " << fixed << setprecision(6) << v.second << endl;
    // }
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

    pagerank(g);

    std::vector<std::pair<int, double>> pairs = pair_sort(g);

    print_pairs(pairs);

}