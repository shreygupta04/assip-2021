import os
import yaml
import time

from planner.cbs import returnSolutionData
from visualize import Animation

class CBSClass:
    positionCache = []

    @staticmethod
    def collectData(pathToinputFile):
        with open(f'{pathToinputFile}', 'r') as file:
            info = yaml.load(file, Loader=yaml.FullLoader)
            positions = []
            goalPositions = []
            for agent in info['agents']:
                positions.append(tuple(agent['start']))
                goalPositions.append(tuple(agent['goal']))

            obstacles = []
            for obstacle in info['map']['obstacles']:
                obstacles.append(obstacle)

            freeCells = set()
            n, m = info['map']['dimensions'][0], info['map']['dimensions'][1]
            for i in range(n):
                for j in range(m):
                    if (i, j) in obstacles: continue
                    freeCells.add((i, j))
            return positions, goalPositions, obstacles, freeCells, n, m, int(info['radius'])


    def senseObstacles(currentPositions, obstacles, radius):
        obstaclesSensed = set()
        for pos in currentPositions:
            if pos in CBSClass.positionCache: continue
            for obs in obstacles:
                wrongObstacle = False
                if (obs[1] - pos[1])**2 + (obs[0] - pos[0])**2 <= radius**2:
                    if obs[0] > pos[0]:
                        x = obs[0]
                        while x >= pos[0]:
                            y = (pos[1] - obs[1])/(pos[0] - obs[0])*(x - pos[0]) + pos[1]
                            if (round(x), round(y)) in set(obstacles) - {obs}:
                                wrongObstacle = True
                                break
                            x -= 0.5
                    elif obs[0] < pos[0]:
                        x = obs[0]
                        while x <= pos[0]:
                            y = (pos[1] - obs[1])/(pos[0] - obs[0])*(x - pos[0]) + pos[1]
                            if (round(x), round(y)) in set(obstacles) - {obs}:
                                wrongObstacle = True
                                break
                            x += 0.5
                    else:
                        if obs[1] > pos[1]:
                            for y in range(obs[1] - 1, pos[1], -1):
                                if (pos[0], round(y)) in obstacles:
                                    wrongObstacle = True
                                    break
                        else:
                            for y in range(obs[1] + 1, pos[1]):
                                if (pos[0], round(y)) in obstacles:
                                    wrongObstacle = True
                                    break
                        # obstacle and position are vertically aligned case
                    if wrongObstacle == False:
                        obstaclesSensed.add(obs)
        return obstaclesSensed
            

    def senseFreeCells(currentPositions, obstacles, freeCells, radius):
        freeCellsSensed = set()
        for pos in currentPositions:
            if pos in CBSClass.positionCache: continue
            for fc in freeCells:
                if (fc[1] - pos[1])**2 + (fc[0] - pos[0])**2 <= radius**2:
                    if fc[0] > pos[0]:
                        x = fc[0]
                        while x >= pos[0]:
                            y = (pos[1] - fc[1])/(pos[0] - fc[0])*(x - pos[0]) + pos[1]
                            if (round(x), round(y)) in obstacles:
                                break
                            else:
                                freeCellsSensed.add(fc)
                            x -= 0.5
                    elif fc[0] < pos[0]:
                        x = fc[0]
                        while x <= pos[0]:
                            y = (pos[1] - fc[1])/(pos[0] - fc[0])*(x - pos[0]) + pos[1]
                            if (round(x), round(y)) in obstacles:
                                break
                            else:
                                freeCellsSensed.add(fc)
                            x += 0.5
                    else:
                        wrongSensedFc = False
                        if fc[1] > pos[1]:
                            for y in range(fc[1] - 1, pos[1], -1):
                                if (pos[0], round(y)) in obstacles:
                                    wrongSensedFc = True
                                break
                        else:
                            for y in range(fc[1] + 1, pos[1], 1):
                                if (pos[0], round(y)) in obstacles:
                                    wrongSensedFc = True
                                break
                        if wrongSensedFc == False:
                            freeCellsSensed.add(fc)
        return freeCellsSensed
        

    @staticmethod
    def solve(pathToInputFile):
        startTime = time.time()

        positions, goalPositions, obstacles, freeCells, n, m, radius = CBSClass.collectData(pathToInputFile)
        print(freeCells)
        print(f'Agents: {len(positions)}')
        print(f'Grid: {n}x{m}')
        print(f'Obstacle coverage: {str(len(obstacles)/(n*m)*100)[:4]}%')

        currentPositions = [*positions]
        allSensedObstacles, allSensedFreeCells = set(), set()
        t, distance = 0, 0

        outputAgentPaths = {}
        obstacleSchedule = {}
        
        orgMap = {
                'agents':[{'start': list(positions[i]),'goal': list(goalPositions[i]), 'name': f'agent{i}'} for i in range(len(positions))],
                'map': {'dimensions':[n, m], 'obstacles':obstacles}
        }
        while currentPositions != goalPositions:
            numNewObstaclesSensed = len(allSensedObstacles)
            allSensedObstacles |= CBSClass.senseObstacles(currentPositions, obstacles, radius)
            numNewObstaclesSensed = len(allSensedObstacles) - numNewObstaclesSensed

            numNewFreeCellsSensed = len(allSensedFreeCells)
            allSensedFreeCells |= CBSClass.senseFreeCells(currentPositions, obstacles, freeCells, radius)
            numNewFreeCellsSensed = len(allSensedFreeCells) - numNewFreeCellsSensed

            CBSClass.positionCache += currentPositions

            print(f'New obstacles sensed: {numNewObstaclesSensed}')
            print(f'New free cells sensed: {numNewFreeCellsSensed}')
            
            obstacleSchedule[t] = [*allSensedObstacles]

            map = {
                'agents':[{'start': list(currentPositions[i]),'goal': list(goalPositions[i]), 'name': f'agent{i}'} for i in range(len(currentPositions))],
                'map': {'dimensions':[n, m], 'obstacles':allSensedObstacles}
            }

            # costDict = run C++ code that creates this CostDict
            ### TODO: fix this temporary solution
            f = open('CodeSensor/data/scene.txt', 'w')
            f.write(f"{map['map']['dimensions'][0]} {map['map']['dimensions'][1]}")
            for obs in allSensedObstacles:
                f.write(f"{obs[0]} {obs[1]} 0")
            for fc in allSensedFreeCells:
                f.write(f"{fc[0]} {fc[1]} 1")
            os.system('./CodeSensor/bin/Runner Distances data/scene.txt data/dists.txt')
            ###
            costDict = {}
            solution = returnSolutionData(map, len(goalPositions), costDict)
            for idx, agent in enumerate(solution):
                # adding the position that each robot moved to
                if agent in outputAgentPaths:
                    outputAgentPaths[agent].append({'t':t, 'x':currentPositions[idx][0], 'y':currentPositions[idx][1]})
                else:
                    outputAgentPaths[agent] = [{'t':t, 'x':currentPositions[idx][0], 'y':currentPositions[idx][1]}]

                # updating current positions of the robots
                if currentPositions[idx][0] != solution[agent]['x']:
                    distance += 1
                if currentPositions[idx][1] != solution[agent]['y']:
                    distance += 1
                currentPositions[idx] = (solution[agent]['x'], solution[agent]['y'])
            t += 1
        
        # adding goal positions to agent paths
        for idx, agent in enumerate(outputAgentPaths):
            outputAgentPaths[agent].append({'t':t, 'x':currentPositions[idx][0], 'y':currentPositions[idx][1]})
        return orgMap, {'schedule': outputAgentPaths, 'obstacles': obstacleSchedule}, time.time() - startTime
    
    @staticmethod
    def animate(map, outputAgentPaths, saveOutput=False):
        
        animation = Animation(map, outputAgentPaths)
        animation.show()