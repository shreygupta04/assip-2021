# Multi-Robot Motion Planning in Unknown Environments
Worked with Dr. Erion Plaku under the Aspiring Scientists Summer Internship Program (ASSIP) at George Mason University. We researched how multi-agent pathfinding (MAPF) can be expanded into unknown environments. This code is a working framework that simulates multiple robots equipped with sensors that can conduct motion planning.

## Abstract
Multi-robot systems provide a viable venue to enhance automation, increase productivity, and reduce operational costs in transportation, surveillance, search-and-rescue, and other fields. Independent planning is no longer possible since the path of one robot can block another robot from reaching its goal. As a result, the robots often have to coordinate their motions to move around obstacles and travel without blocking each other.

While related work has assumed full knowledge of the environment and of the obstacles, our framework is able to plan in unknown environments. Each robot is equipped with a radial-based sensor which detects obstacles around them as the robots move. The robots share this information with one another to incrementally build a map of the environment. The framework uses the updated map to find paths that lead each robot to their goal. Path finding relies on advanced AI search techniques which reduces the distance traveled by each robot. To incentivize planning away from obstacles, a cost function is imposed that is higher near obstacles and smaller the further away the robots are.

The framework is evaluated in simulation using complex environments and an increasing number of robots (from 1 to 10). The results demonstrate the effectiveness of the framework for multi-robot motion planning in unknown environments, finding solutions in around 20s per planning cycle. In future work, we will apply these ideas on the field to carry out experiments with underwater vehicles inspecting harbors or offshore platforms.

## Acknowledgements
- Dr. Erion Plaku, Department of Computer Science, George Mason University
