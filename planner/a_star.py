"""

AStar search

author: Ashwin Bose (@atb033)

"""

import random
import time

class AStar():
    def __init__(self, env, dimension, costDict):
        self.agent_dict = env.agent_dict
        self.admissible_heuristic = env.admissible_heuristic
        self.is_at_goal = env.is_at_goal
        self.get_neighbors = env.get_neighbors
        self.dimension = dimension
        self.costDict = self.readCostDict('dists.txt') #costDict
        

    def readCostDict(self, costDictFile):
        cd = {}
        with open(f'./CodeSensor/data/{costDictFile}', 'r') as f:
            for line in f.read().splitlines():
                l = line.split()
                l[1] = self.dimension[0] - 1 - int(l[1])
                l[3] = self.dimension[1] - 1 - int(l[3])
                lStr = ' '.join(str(item) for item in l[:-1])
                cd[lStr] = l[-1]
        return cd

    def reconstruct_path(self, came_from, current):
        total_path = [current]
        while current in came_from.keys():
            current = came_from[current]
            total_path.append(current)
        return total_path[::-1]

    def search(self, agent_name):
        """
        low level search 
        """
        initial_state = self.agent_dict[agent_name]["start"]
        step_cost = 1
        
        closed_set = set()
        open_set = {initial_state}

        came_from = {}

        g_score = {} 
        g_score[initial_state] = 0

        f_score = {} 

        f_score[initial_state] = self.admissible_heuristic(initial_state, agent_name)

        startTime = time.time()
      
        while open_set:
            if time.time() - startTime > 120:
                print('Timed out')
                return False
      
            temp_dict = {open_item:f_score.setdefault(open_item, float("inf")) for open_item in open_set}
            current = min(temp_dict, key=temp_dict.get)

            if self.is_at_goal(current, agent_name):
                return self.reconstruct_path(came_from, current)

            open_set -= {current}
            closed_set |= {current}

            
            neighbor_list = self.get_neighbors(current)
            for neighbor in neighbor_list:
                if neighbor in closed_set:
                    continue
                
                if f'{current.location.x} {current.location.y} {neighbor.location.x} {neighbor.location.y}' not in self.costDict:
                    step_cost = 1
                else:
                    step_cost = int(self.costDict[f'{current.location.x} {current.location.y} {neighbor.location.x} {neighbor.location.y}'])                
                tentative_g_score = g_score.setdefault(current, float("inf")) + int(step_cost)

                #print(f'open = {len(open_set)} closed = {len(closed_set)} edge = {current} -> {neighbor} cost  = {step_cost}')
                if neighbor not in open_set:
                    open_set |= {neighbor}
                elif tentative_g_score >= g_score.setdefault(neighbor, float("inf")):
                    continue

                came_from[neighbor] = current

                g_score[neighbor] = tentative_g_score
                f_score[neighbor] = g_score[neighbor] + self.admissible_heuristic(neighbor, agent_name)
        return False
