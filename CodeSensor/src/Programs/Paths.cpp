/*
 * Copyright (C) 2021 Erion Plaku
 * All Rights Reserved
 *
 *   Created by Erion Plaku
 *   www.robotmotionplanning.org
 *
 * Code should not be distributed or used without written permission from the
 * copyright holder.
 */

#include "Programs/Setup.hpp"
#include <fstream>
#include "Utils/Heap.hpp"
#include <unordered_set>

namespace Antipatrea
{
    class GraphSearchNode
    {
    public:
	GraphSearchNode(void) : m_parent(NULL),
				m_gCost(0.0),
				m_hCost(0.0),
				m_id(Constants::ID_UNDEFINED)
	{
	}
	
	virtual ~GraphSearchNode(void)
	{
	}
	
	virtual GraphSearchNode* NewNode(void) const
	{
	    return new GraphSearchNode();
	}
	
	
	Id m_id;
	GraphSearchNode *m_parent;
	double m_gCost;
	double m_hCost;
    };
    
    class GraphSearchNodeCompare
    {
    public:
	GraphSearchNodeCompare() 
	{
	}
	
	virtual ~GraphSearchNodeCompare(void)
	{
	}
	
	typedef GraphSearchNode* NodePtr;
	
	virtual bool operator()(NodePtr u, NodePtr v)
	{
	    return (u->m_gCost + u->m_hCost) < (v->m_gCost + v->m_hCost);
	}
    };
    
    
    class ProcessPaths
    {
    public:
	ProcessPaths(void)
	{
	}
	
	virtual ~ProcessPaths(void)
	{
	}
	
	virtual void Clear(void)
	{
	    m_heap.Clear();
	    
	    for(auto & iter : m_map)
		if(iter.second)
		    delete iter.second;
	    m_map.clear();
	}
	
	virtual void Search(const int goal)
	{
	    Clear();
	    
	    std::vector<int> neighs;
	    
	    GraphSearchNode *u;
	    GraphSearchNode *v;
	    
	    u = new GraphSearchNode();
	    u->m_id = goal;
	    m_heap.Insert(u);
	    m_map.insert(std::make_pair(u->m_id, u));
	    
	    while(m_heap.IsEmpty() == false)
	    {
		u  = m_heap.RemoveTop();
		m_grid.GetNeighbors(u->m_id, neighs);
		for(auto neigh : neighs)
		    if(m_cellsBlocked.find(neigh) == m_cellsBlocked.end())
		    {
			auto cur = m_map.find(neigh);
			if(cur == m_map.end())
			{
			    v = new GraphSearchNode();
			    v->m_id = neigh;
			    v->m_parent = u;
			    v->m_gCost = u->m_gCost + 1;
			    m_heap.Insert(v);
			    m_map.insert(std::make_pair(v->m_id, v));
			}
			else
			{
			    v = cur->second;
			    if(v->m_gCost > (u->m_gCost + 1))
			    {
				v->m_gCost = u->m_gCost + 1;
				v->m_parent = u;
				m_heap.Update(v);
				
			    }			
			}
		    }
	    }
	}
	
	void ReadScene(const char fname[])
	{
	    std::string s;
	    int dims[2];	    
	    int coords[2];
	    
	    
	    std::ifstream in(fname);
	    if(!in)
		return;
	    
	    in >> s >> s >> s >> dims[0] >> s >> dims[1] >> s;
	    m_grid.Setup2D(dims[0], dims[1], 0.0, 0.0, dims[0], dims[1]);
	    
	    Logger::m_out
		<< "reading scene from <" << fname << ">" << std::endl
		<< "...grid dims = " << dims[0] << " x " << dims[1] << std::endl;
	    while(in >> s)
	    {
		in >> s >> s >> coords[0] >> s >> coords[1];
		m_cellsBlocked.insert(m_grid.GetCellIdFromCoords(coords));
	    }
	    in.close();
	    
	    Logger::m_out << "...number of blocked cells = " << m_cellsBlocked.size() << std::endl;
	    
	}
	
	void ReadGoals(const char fname[])
	{
	    Logger::m_out << "reading goals from <" << fname << ">" << std::endl;
	    
	    std::ifstream in(fname);
	    int coords[2];
	    while(in >> coords[0] >> coords[1])
		m_goals.push_back(m_grid.GetCellIdFromCoords(coords));
	    
	    
	    Logger::m_out << "...number of goals = " << m_goals.size() << std::endl;
	    
	    in.close();
	}
	
	void Execute(const char fname[])
	{
	    std::ofstream out(fname);
	    int coords1[2];
	    int coords2[2];
	    
	    
	    Logger::m_out << "writing results to <" << fname << ">" << std::endl;
	    
	    for(auto & goal : m_goals)
	    {
		m_grid.GetCoordsFromCellId(goal, coords1);
		
		Logger::m_out << "...searching for goal " << goal << " with coords " << coords1[0] << " " << coords1[1] << std::endl;
		Search(goal);
		for(auto  & iter : m_map)
		{
		    m_grid.GetCoordsFromCellId(iter.first, coords2);
		    
		    
		    out << coords1[0] << " " << coords1[1]  << " " << coords2[0] << " " << coords2[1] << " " << iter.second->m_gCost << std::endl;
		}
	    }
	    
	    out.close();
	    
	}
	
	
	Grid m_grid;
	std::unordered_set<int> m_cellsBlocked;
	
	Heap<GraphSearchNode*, GraphSearchNodeCompare> m_heap;
	std::unordered_map<Id, GraphSearchNode*> m_map;
	std::vector<int> m_goals;
	
    };
    
    
};


using namespace Antipatrea;

extern "C" int Paths( int argc, char **argv )
{
//./bin/Runner Paths sceneFile goalFile outFile
    
    
    ProcessPaths pp;
    
    pp.ReadScene(argv[1]);
    pp.ReadGoals(argv[2]);
    pp.Execute(argv[3]);
    
    return 0;
}
