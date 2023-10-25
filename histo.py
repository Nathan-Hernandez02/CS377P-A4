import matplotlib.pyplot as plt

# Read the data from the text file
data = []
with open('histo_wiki.dimacs.txt', 'r') as file:
    for line in file:
        parts = line.split()
        if len(parts) == 5:
            node_id = int(parts[1])
            num_outgoing_edges = int(parts[4])
            data.append((node_id, num_outgoing_edges))

# Separate the data into node IDs and the number of outgoing edges
node_ids, outgoing_edges = zip(*data)

# Create a bar chart
plt.bar(node_ids, outgoing_edges, color='skyblue')
plt.xlabel('Node ID')
plt.ylabel('Number of Outgoing Edges')
plt.title('Outgoing Edges Histogram')

# Save the plot to a file (e.g., outgoing_edges.png)
plt.savefig('outgoing_edges.png')

# Show the plot (optional)
plt.show()
