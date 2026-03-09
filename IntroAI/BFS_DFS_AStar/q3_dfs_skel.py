"""
IMPORTANT NOTE:
---------------
The provided code is based on the general implementation of Depth-First Search (DFS) 
using recursion. This is the most common and standard way of implementing DFS. 
However, you are welcome to try your own approach or other variations of DFS as long as 
they produce correct results.
"""

def dfs(
    graph: dict[str, list[str]], 
    start: str, 
    end: str, 
    path: list[str] = None, 
    expansion_order: list[str] = None
) -> tuple[dict[str] | None, list[str]]:
    """
    Perform a Depth-First Search (DFS) on a graph to find a path 
    from the start node to the end node and record the expansion order.

    Parameters:
    ----------
    graph : dict[str, list[str]]
        A dictionary representing the adjacency list of the graph. 
        Keys are node labels, and values are lists of directly connected nodes.
    start : str
        The starting node of the search.
    end : str
        The goal node to reach.
    path : list[str], optional
        A list storing the current path being explored (default is None).
    expansion_order : list[str], optional
        A list to record the order in which nodes are visited (default is None).

    Returns:
    -------
    tuple
        path : list[str] | None
            A list of nodes representing the path from start to goal if a path exists, otherwise None.
        expansion_order : list[str]
            The list of nodes in the order they were expanded (visited).
    """

    if path is None:
        path = [start]
    if expansion_order is None:
        expansion_order = []

    parent_map = {start: None} # track parent map too for path

    children = graph[start] # root's child list

    # expansion order: S -> 1 -> 4 -> 10 -> 11 -> 5
    # so we will add the children to the list reversed, pop the front as current node, if there are children then we append the children and pop the leftmost

    while end not in path:      
        current_node = path.pop() # pop the last node to be current node
        for child in reversed(children): # add children in reverse order
           path.append(child)
           if child not in parent_map:
               parent_map[child] = current_node
        if current_node not in expansion_order:
            expansion_order.append(current_node)
             # if we find the right node break
            break
        children = graph[current_node] # travel down the last node's children

    #print(parent_map)

    return parent_map, expansion_order  

# from bfs file
def backtracking(parent_map: dict[str, str | None], goal_node: str = 'G') -> list[str]:
    """
    Reconstruct the path from the start node to the goal node using the parent map.

    Parameters
    ----------
    parent_map : dict[str, str | None]
        Dictionary mapping child -> parent node created by BFS.
    goal_node : str, optional
        The goal node (default is 'G').

    Variables
    ----------
    path : list[str]
        List of nodes representing the reconstructed path from goal to start.
    node : str
        Current node during backtracking.

    Returns
    -------
    list[str]
        Ordered list of nodes from start to goal.
    """
    path = []
    node = goal_node
    while node is not None:
        path.append(node)
        node = parent_map[node]
    return path[::-1]


def display(list_of_nodes: list[str]) -> None:
    """
    Print a sequence of nodes in arrow-separated format.
    
    Parameters:
    ----------
    list_of_nodes : list[str]
        The list of nodes representing the path from start to goal.

    Returns:
    -------
    None
    """
    print(" -> ".join(list_of_nodes))


def main() -> None:
    """
    Main function to define the graph, call DFS, and print the result.

    Variables:
    ---------
    graph : dict[str, list[str]]
        The adjacency list representing the graph structure.
    path : list[str] | None
        The result path from DFS (list of nodes) or None if not found.
    expansion_order : list[str]
        The order in which nodes were expanded during DFS.

    Returns:
    -------
    None
    """
    graph = {
        'S': ['1', '2', '3'],
        '1': ['4', '5'],
        '2': ['6', '7', '8'],
        '3': ['9'],
        '4': ['10', '11'],
        '5': ['G', '12'],
        '6': ['13', '14'],
        '7': ['15', '16'],
        '8': ['17', '18'],
        '9': ['19'],
        'G': [],
        '10': [], '11': [], '12': [], '13': [], '14': [],
        '15': [], '16': [], '17': [], '18': [], '19': []
    }

    # Perform DFS on the graph
    parent_map, expansion_order = dfs(graph, 'S', 'G')
    
    if 'G' in parent_map:
        path = backtracking(parent_map, 'G')
    else:
        path = None

    # Print the expansion order
    print("DFS Expansion Order:")
    display(expansion_order)

    # Print the path
    if path:
        print("DFS Path Found:")
        display(path)
    else:
        print("No path found.")


if __name__ == "__main__":
    main()
