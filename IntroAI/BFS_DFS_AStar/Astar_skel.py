"""
CS 331 Fall 2025
This is a skeleton code for A* search algorithm. You need to fill in the missing lines (indicated by `...`) to complete the implementation.
 """

import time

def a_star_search_simple(graph, start, goal, h):
    """
    Implements the A* search algorithm.

    Args:
        graph (dict): The graph connections and costs.
        start (str): The starting node.
        goal (str): The goal node.
        h (dict): A dictionary of heuristic values for each node.

    Returns:
        tuple: A tuple containing the path, cost, expanded_nodes, and elapsed_time.
    """
    start_time = time.perf_counter()

    # --- 1. Initialize Data Structures ---

    # open_set: A list of nodes we need to visit. We start with just the start node, because we don't know any others yet.
    open_set = [start]

    # closed_set: A set of nodes we have already visited and finished with. Starts empty.
    closed_set = set()

    # came_from: A dictionary to reconstruct the path once we find the goal.
    # It will store for each node, which node it came from, in our shortest path. e.g., came_from['G'] = '4'
    came_from = {}

    # g_score: The cost of the cheapest path from the start node to another node.
    # We initialize all costs to infinity, except for the start node, which is 0.
    g_score = {}
    g_score[start] = 0

    # f_score: The estimated total cost from the start to the goal, going through a specific node.
    # f_score = g_score (actual cost so far) + h_score (estimated cost to goal)
    # We initialize all to infinity, except for the start node.
    f_score = {}
    f_score[start] = 0

    nodes_expanded = 0

    # --- 2. Main Algorithm Loop ---

    # The loop continues as long as there are nodes in our 'to-visit' list (open_set).
    while open_set:

        # --- Find the best node to visit next ---
        # we manually search for the node in the open_set that has the lowest f_score.
        # current: The node we are currently visiting.
        current = None
        current_f_score = float('inf')
        for node in open_set:
            f = f_score.get(node, float('inf'))

            if f < current_f_score:
                current_f_score = f
                current = node
        
        # --- Check if we've reached the goal ---
        if current == goal:
            # If so, we're done! Reconstruct the path and return the results.
            path = [current]

            while current in came_from:
                current = came_from[current]
                path.append(current)

            path.reverse()

            # Add the goal node as a expanded node
            nodes_expanded += 1

            # Record the end time and calculate elapsed time
            end_time = time.perf_counter()
            elapsed_time = end_time - start_time

            return path, g_score[goal], nodes_expanded, elapsed_time

        # --- Prepare for the next loop iteration ---
        # Move the current node from the 'to-visit' list to the 'visited' list.
        open_set.remove(current)
        closed_set.add(current)
        nodes_expanded += 1

        print(open_set)
            
        # --- Explore Neighbors of the Current Node ---
        # Because we have visited this node, now we can get the costs to its neighbors.
        # Look at all the nodes connected to the current one.
        for neighbor, cost in graph[current].items():
            # If we've already visited this neighbor, skip it.
            if neighbor in closed_set:
                continue

            # Calculate the cost to reach this neighbor through the current node.
            tentative_g_score = g_score[current] + cost

            # --- Check if this is a better path ---
            # If the new path to the neighbor is shorter than any previous path we've found... then update our records to reflect this new, better path.
            if tentative_g_score < g_score.get(neighbor, float('inf')):
                g_score[neighbor] = tentative_g_score 
                f_score[neighbor] = g_score[neighbor] + h.get(neighbor, float('inf'))
                came_from[neighbor] = current

                if neighbor not in open_set:
                    open_set.append(neighbor)

    # If the loop finishes and we haven't found the goal, it means there's no path.
    end_time = time.perf_counter()
    elapsed_time = (end_time - start_time) * 1000
    return None, float('inf'), nodes_expanded, elapsed_time


# --- Main execution block ---
if __name__ == '__main__':
    # Define the graph
    graph = {
        'S': {'1': 6, '2': 5},
        '1': {'S': 6, '3': 3, '4': 4},
        '2': {'S': 5, '4': 6, '5': 5},
        '3': {'1': 3, '4': 5},
        '4': {'1': 4, '2': 6, '3': 5, '5': 8, 'G': 4},
        '5': {'2': 5, '4': 8},
        'G': {'4': 4}
    }

    # Heuristic values
    heuristic = {
        'S': 10,
        '1': 6,
        '2': 1,
        '3': 8,
        '4': 2,
        '5': 1,
        'G': 0
    }

    start_node = 'S'
    goal_node = 'G'

    path, cost, expanded_nodes, time_taken = a_star_search_simple(graph, start_node, goal_node, heuristic)

    print("--- Simplified A* Search Results ---")
    if path:
        print(f"(ii) Shortest path found: {' -> '.join(path)}")
        print(f"(iii) Solution cost: {cost}")
        print(f"(iv) Number of nodes expanded: {expanded_nodes}")
        print(f"(v) Time taken to solve: {time_taken:.4f} ms")
    else:
        print("No path found from S to G.")
    print("------------------------------------")