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

#include "Components/Sensor.hpp"

namespace Antipatrea
{
    void Sensor::Clear(void)
    {
	for(auto & iter : m_sensorReadings)
	    if(iter.second)
		delete iter.second;
	m_sensorReadings.clear();

	m_sensedCellsFree.clear();
	m_sensedCellsOccupied.clear();
	
    }
    
    const Sensor::Data* Sensor::Sense(const Id cid1)
    {
	auto iter = m_sensorReadings.find(cid1);
	if(iter != m_sensorReadings.end())
	    return iter->second;	
	else
	{
	     std::vector<int> candidates;
	     auto grid = GetScene()->GetGrid();	     
	     std::vector<double> p1(grid->GetNrDims());
	     std::vector<double> p2(grid->GetNrDims());
	     std::vector<double> p3(grid->GetNrDims());
	     Id cid3;
	     
	     grid->GetCellCenterFromId(cid1, &p1[0]);
	   
	     auto data = new Data();	    
	     m_sensorReadings.insert(std::make_pair(cid1, data));
	     grid->GetCellsInsideBall(&p1[0], GetRadius(), candidates);
	     for(auto & cid2 : candidates)
	     {
		 grid->GetCellCenterFromId(cid2, &p2[0]);

		 auto d = Algebra::PointDistance(grid->GetNrDims(), &p1[0], &p2[0]);	
		 auto step = grid->GetMinUnit();
		 auto nrSteps = std::ceil(d / step);
			 
		 for(int i = 0; i <= nrSteps; ++i)
		 {
		     auto t = (i + 0.0) / nrSteps;	    
		     Algebra::VecLinearInterpolation(grid->GetNrDims(), &p1[0], (1 - t), &p2[0], t, &p3[0]);
		     cid3 = grid->GetCellId(&p3[0]);		     
		     if(GetScene()->IsCellInCollision(cid3) )
		     {
			 data->m_cellsOccupied.insert(cid3);
			 m_sensedCellsOccupied.insert(cid3);			 
			 break;
		     }
		     else
		     {
			 data->m_cellsFree.insert(cid3);
			 m_sensedCellsFree.insert(cid3);			 
		     }
		 }
	     }
	     
	     return data;	    
	}
    };
    
    

}
