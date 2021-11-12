/*
 * Copyright (C) 2020 Erion Plaku
 * All Rights Reserved
 * 
 *   Created by Erion Plaku
 *   www.robotmotionplanning.org
 *
 * Code should not be distributed or used without written permission from the
 * copyright holder.
 */
 
#include "Utils/Box3D.hpp"
#include "Utils/TriMesh.hpp"

namespace Antipatrea
{
    void Box3D::AddToTriMesh(TriMesh &tmesh)
    {
	tmesh.AddBox(m_box[0], m_box[1], m_box[2], m_box[3], m_box[4], m_box[5]);
    }

    void Box3D::OccupiedGridCells(const Grid &grid, std::vector<Id> &cids)
    {
	int coord_min[3];
	int coord_max[3];
	int coords[3];	

	grid.GetCoords(GetMin(), coord_min);
	grid.GetCoords(GetMax(), coord_max);
	cids.clear();
	for(int x = coord_min[0]; x <= coord_max[0]; ++x)
	{
	    coords[0] = x;	    
	    for(int y = coord_min[1]; y <= coord_max[1]; ++y)
	    {
		coords[1] = y;
		for(int z = coord_min[2]; z <= coord_max[2]; ++z)
		{
		    coords[2] = z;		    
		    cids.push_back(grid.GetCellIdFromCoords(coords));
		}
	    }	
	}
    }
}
