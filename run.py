from time import time
from planner.cbs import CBS
from cbsclass import CBSClass

map, outputAgentPaths, totalTime = CBSClass.solve('data/input10_32x32_0.2_0.yaml')
print(f'Time: {str(totalTime)[:5]}')
CBSClass.animate(map, outputAgentPaths)
