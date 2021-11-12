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
#include <unordered_set>
#include <queue>

namespace Antipatrea
{
    
    class ProcessDistances
    {
    public:
	ProcessDistances(void)
	{
	}
	
	virtual ~ProcessDistances(void)
	{
	}
	
	void ReadScene(const char fname[])
	{
	    std::string s;
	    int dims[2];	    
	    int coords[2];
	    int val;
	    
	    
	    
	    std::ifstream in(fname);
	    if(!in)
		return;
	    
	    in >> dims[0]  >> dims[1] ;
	    m_grid.Setup2D(dims[0], dims[1], 0.0, 0.0, dims[0], dims[1]);
	   	    
	    Logger::m_out
		<< "reading scene from <" << fname << ">" << std::endl
		<< "...grid dims = " << dims[0] << " x " << dims[1] << std::endl;
	    while(in >> coords[0] >> coords[1] >> val)
		if(val == 0)
		    m_cellsBlocked.insert(m_grid.GetCellIdFromCoords(coords));
		else
		    m_cellsFree.insert(m_grid.GetCellIdFromCoords(coords));
		    
	    Logger::m_out
		<< "...number of blocked cells = " << m_cellsBlocked.size() << std::endl
		<< "...number of free cells = " << m_cellsFree.size() << std::endl
		<< "...number of unknown cells = " << (m_grid.GetNrCells() - m_cellsBlocked.size() - m_cellsFree.size()) << std::endl;
	    

		in.close();
	}

	void ComputeDistances(void)
	{
	    m_dmax = 0;	    
	    m_dists.resize(m_grid.GetNrCells());
	    std::fill(m_dists.begin(), m_dists.end(), -1);
	    for(auto & cell : m_cellsBlocked)
	    {
		m_dists[cell] = 0;
		m_remain.push(cell);		
	    }
	    
	    for(int x = 0; x < m_grid.GetDims()[0]; ++x)
	    {
		UpdateValue(x, 0);
		UpdateValue(x, m_grid.GetDims()[1] - 1);		
	    }

	    for(int y = 0; y < m_grid.GetDims()[1]; ++y)
	    {
		UpdateValue(0, y);
		UpdateValue(m_grid.GetDims()[0] - 1, y);		
	    }

	    ProcessRemain();	    
	}

	void ProcessRemain(void)
	{
	    std::vector<int> neighs;
	    
	    while(m_remain.empty() == false)
	    {
		auto cid = m_remain.front();
		m_remain.pop();
		m_grid.GetNeighbors(cid, neighs);
		for(auto & neigh : neighs)
		    if(m_dists[neigh] == -1)
		    {
			m_dists[neigh] = m_dists[cid] + 1;
			m_remain.push(neigh);

			if(m_dists[neigh] > m_dmax)
			    m_dmax = m_dists[neigh];			
		    }
		
	    }
	    
	}
	

	void UpdateValue(const int x, const int y)
	{
	    const int coords[] = {x, y};
	    auto id = m_grid.GetCellIdFromCoords(coords);
	    if(m_dists[id] == -1)
	    {
		m_dists[id] = 1;
		m_remain.push(id);
		if(m_dists[id] > m_dmax)
		    m_dmax = m_dists[id];		
	    }
	    
	}
	
	void Execute(const char fname[])
	{
	    ComputeDistances();
	    
	    std::ofstream out(fname);
	    int coords[2];
	    int coords1[2];
	    int coords2[2];
	    
	    Logger::m_out << "writing results to <" << fname << ">" << std::endl;
	    /*for(int i = 0; i < m_grid.GetDims()[0]; ++i)
	    {
		for(int j = 0;  j < m_grid.GetDims()[1] ; --j)
		{
		    coords[0] = i;
		    coords[1] = j;
		    out << m_dists[m_grid.GetCellIdFromCoords(coords)] << " ";
		}
		out << std::endl;
		}*/
	    
	    
	    std::vector<int> neighs;
	    double cost;
	    
	    for(int i = 0; i < m_dists.size(); ++i)
		if(m_dists[i] > 0) //unknown or free
		{
		    
		    auto isFree1 = m_cellsFree.find(i) != m_cellsFree.end();
		    
		    m_grid.GetCoordsFromCellId(i, coords1);
		    
		    m_grid.GetNeighbors(i, neighs);
		    neighs.push_back(i);
		    
		    for(auto & neigh : neighs)
			if(m_dists[neigh] > 0)
			{
			    auto d = m_dists[neigh]  + m_dists[i];
			    if(d > 16)
				cost = 1;
			    else if(d > 12)
				cost = 2;
			    else if(d > 8)
				cost = 4;
			    else if (d > 4)
				cost = 8;			    
			    else 
				cost = 16;
			    
			    
			    //cost = 2 * m_dmax + 1 - m_dists[neigh] - m_dists[i];
			      //cost = pow(cost, 3);
			    
			    auto isFree2 = m_cellsFree.find(i) != m_cellsFree.end();

			    if(isFree1 == false)
				cost *= 2;
			    if(isFree2 == false)
				cost *= 2;
		    
			    m_grid.GetCoordsFromCellId(neigh, coords2);

			    
			    out << coords1[0] << " " << coords1[1]  << " " << coords2[0] << " " << coords2[1] << " " << (int) cost << std::endl;

			    
			}		    
		}
	    
	    
	    
	    out.close();

	    Logger::m_out << "...done writing results" << std::endl;
	    
	}
	
	
	Grid m_grid;
	std::unordered_set<int> m_cellsBlocked;
	std::unordered_set<int> m_cellsFree;
	
	std::vector<int> m_dists;
	std::queue<int> m_remain;
	int m_dmax;
	
    };
    
    
};


using namespace Antipatrea;

extern "C" int Distances( int argc, char **argv )
{
//./bin/Runner Distances sceneFile  outFile
    
    
    ProcessDistances pd;
    
    pd.ReadScene(argv[1]);
    pd.Execute(argv[2]);
    
    return 0;
}
