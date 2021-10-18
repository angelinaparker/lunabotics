import numpy as np


class Node:
    """
    Node class for A* Pathfinding
    parent is parent of the current Node
    position is current position of the Node in the maze
    g is cost from start to current Node
    h is heuristic based estimated cost for current Node to end Node
    f is total cost of present node, f = g + h
    """
    def __init__(self, parent=None, position=None):
        self.parent = parent
        self.position = position

        self.g = 0
        self.h = 0
        self.f = 0

    def __eq__(self, other):
        return self.position == other.position

    # returns the path of the search
    def return_path(self, current_node, maze):
        path = []
        no_rows, no_columns = np.shape(maze)        # return shape of array maze
        result = [[-1 for i in range(no_columns)] for j in range(no_rows)]      # initialize result maze with -1
        current = current_node

        while current is not None:
            path.append(current.position)
            current = current.parent

        # return reversed path to show from start to end of path
        path = path[::-1]       # starts from the end towards the first taking each node
        start_value = 0

        # update the path of start to end found by A-star search with every step incremented by 1
        for i in range(len(path)):
            result[path[i][0]][path[i][1]] = start_value
            start_value += 1

        return result

    def search(self, maze, cost, start, end):
        """
        Returns a list of tuples as a path from the given start to the given end in the given maze
        :param cost:
        :param start:
        :param end:
        :return:
        """
        # create start and end node with initialized values for g, h, and f
        start_node = Node(None, tuple(start))
        start_node.g = start_node.h = start_node.f = 0

        # create end node with initialized values for g, h, and f
        end_node = Node(None, tuple(end))
        end_node.g = end_node.h = end_node.f = 0

        # initialize yet_to_visit and visited list
        yet_to_visit_list = []      # nodes that are yet_to_visit for exploring, to find the lowest cost node to expand
        visited_list = []       # nodes already explored

        yet_to_visit_list.append(start_node)        # add start node

        outer_iterations = 0        # counter
        max_iterations = (len(maze) // 2) ** 10     # reasonable number of steps

        # search movement is left-right-top-bottom, 4 movements from every position
        move = [[-1, 0],    # go up
                [0, -1],    # go left
                [1, 0],     # go down
                [0, 1]]     # go right

        # use current node to compare all f costs and select lowest cost node for further expansion
        no_rows, no_columns = np.shape(maze)        # find rows and columns in maze

        while len(yet_to_visit_list) > 0:
            outer_iterations += 1       # when node is referred from yet_to_visit list, increment counter
            current_node = yet_to_visit_list[0]     # get current node
            current_index = 0       # initialize index

            for index, item in enumerate(yet_to_visit_list):
                if item.f < current_node.f:     # compare cost of first node in yet_to_visit_list to current node cost
                    current_node = item
                    current_index = index

            if outer_iterations > max_iterations:       # no solution or computation cost is too high
                print("giving up on pathfinding due to too many iterations")
                return self.return_path(current_node, maze)

            yet_to_visit_list.pop(current_index)        # pop current node off
            visited_list.append(current_node)           # add current node to visited list

            if current_node == end_node:        # if goal is reached, return path
                return self.return_path(current_node, maze)

            children = []

            for new_position in move:
                node_position = (current_node.position[0] + new_position[0],        # get node position
                                 current_node.position[1] + new_position[1])

                if (node_position[0] > (no_rows - 1) or             # check if within maze boundary
                    node_position[0] < 0 or
                    node_position[1] > (no_columns - 1) or
                    node_position[1] < 0):
                    continue

                if maze[node_position[0]][node_position[1]] != 0:
                    continue

                if maze[node_position[0]][node_position[1]] != 0:   # check if terrain is walkable
                    continue

                new_node = Node(current_node, node_position)        # create new node
                children.append(new_node)                           # append new_node to children

            for child in children:          # loop through children

                # if child is on visited list
                if len([visited_child for visited_child in visited_list if visited_child == child]) > 0:
                    continue

                # calculate f, g, and h values. Hueristic cost calculated using Eucledian distance
                child.g = current_node.g + cost
                child.h = (((child.position[0] - end_node.position[0]) ** 2) +
                           ((child.position[1] - end_node.position[1]) ** 2))
                child.f = child.g + child.h

                # check if child is already in the yet_to_visit list and g cost is already lower
                if len([i for i in yet_to_visit_list if child == i and child.g > i.g]) > 0:
                    continue

                yet_to_visit_list.append(child)     # add child to the yet_to_visit list


if __name__ == '__main__':
    maze = [[0, 1, 0, 0, 0, 0],
            [0, 1, 0, 0, 0, 0],
            [0, 0, 0, 1, 0, 0],
            [0, 1, 0, 0, 1, 0],
            [0, 0, 0, 0, 1, 0]]

    start = [0, 0]
    end = [4, 5]
    cost = 1

    ex = Node()
    path = ex.search(maze, cost, start, end)
    print(path)
    print('\n')
    print('Counting steps taken where -1 = nodes untraveled:')
    print('\n')
    print('\n'.join([''.join(["{:" ">3d}".format(item) for item in row]) for row in path]))
