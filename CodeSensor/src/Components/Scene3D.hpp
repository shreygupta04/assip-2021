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

#ifndef Antipatrea__Scene3D_HPP_
#define Antipatrea__Scene3D_HPP_

#include "Components/Scene.hpp"


namespace Antipatrea
{
    class Scene3D : public Scene
    {
    public:
	Scene3D( void ) : Scene()
	{
	    m_allocatorPosition.SetDim(3);	    
	}
	
	
	virtual ~Scene3D( void )
	{
	}
	
	virtual void AddBoundaries(const double thick, const double h);

	
	virtual void DrawPoint(const double p[]) const
	{
	    GDrawSphere3D(p, GDrawGetParam(GDRAW_POINT_SIZE));	    
	}
	
	virtual void DrawSegment(const double p1[], const double p2[]) const
	{
	    GDrawSegment3D(p1, p2);
	}
	
    };
}

#endif
