import networkx as nx
import matplotlib.pyplot as plt
my_list = []
my_nums = []
# Function to read a DIMACS file and create a NetworkX graph
def readDIMACSFile(filename):
    global my_list
    global my_nums
    graph = nx.Graph()
    with open(filename, 'r') as file:
        for line in file:
            line = line.strip()
            if line.startswith('c'):
                # Skip comments
                continue
            elif line.startswith('p'):
                _, _, numVertices, numEdges = line.split()
                my_list = [0 for i in range(int(numVertices))] 
                my_nums = [i for i in range(int(numVertices))] 
            elif line.startswith('a'):
                _, nodeA, nodeB, _ = line.split()
                G.add_edge(int(nodeA), int(nodeB))
                my_list[int(nodeA) - 1] =  my_list[int(nodeA) - 1] + 1
    return graph

# Function to read weights from a separate file
def readWeightsFile(filename):
    node_weights = {}
    with open(filename, 'r') as file:
        for line in file:
            _, node, _, weight = line.split()
            node_weights[int(node)] = float(weight)
    return node_weights

# Function to visualize the graph with node sizes based on weights
def visualizeGraph(graph, node_weights, weights_filename):
    pos = nx.random_layout(graph)
    scaled_sizes = [50000 * node_weights[node] for node in graph.nodes]
    node_colors = [node_weights[node]  for node in graph.nodes]
    node_labels = {}
    with open(weights_filename, "r") as file:
        for line in file:
            node_id, label = line.strip().split()
            node_labels[int(node_id)] = label

    plt.figure(figsize=(10, 6))
    nx.draw(graph, pos, node_size=scaled_sizes, with_labels=False, font_size=10, font_color='black', node_color=node_colors, edge_color='black')
    nx.draw_networkx_labels(G, pos, node_labels, font_size=10, font_color='black')

    plt.title(f'Graph Visualization with Node Sizes Based on Weights')
    plt.show()


if __name__ == "__main__":
    filename = "wiki.dimacs"  # Change this to your DIMACS file
    weights_filename = "pagerank_wiki.dimacs"  # Change this to the separate weights file
    G = readDIMACSFile(filename)
    node_weights = readWeightsFile(weights_filename)

    # Visualize the graph
    visualizeGraph(G, node_weights, weights_filename)