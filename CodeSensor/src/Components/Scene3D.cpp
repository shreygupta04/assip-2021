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

#include "Components/Scene3D.hpp"

namespace Antipatrea
{
    void Scene3D::AddBoundaries( const double thick, const double h )
    {
	m_tmeshObstaclesCollision.AddBoundaries( m_grid.GetMin()[0],
						 m_grid.GetMin()[1],
						 m_grid.GetMin()[2],
						 m_grid.GetMax()[0],
						 m_grid.GetMax()[1],
						 m_grid.GetMin()[2] + h,
						 thick );
	
	m_tmeshObstaclesDraw.AddBoundaries( m_grid.GetMin()[0],
					    m_grid.GetMin()[1],
					    m_grid.GetMin()[2],
					    m_grid.GetMax()[0],
					    m_grid.GetMax()[1],
					    m_grid.GetMin()[2] + h,
					    thick );
    }
}
