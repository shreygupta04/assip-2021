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
 
#include "Utils/ShapeSetup.hpp"
#include "Utils/Box2D.hpp"
#include "Utils/Polygon2D.hpp"
#include "Utils/Box3D.hpp"

namespace Antipatrea
{
    Shape* ShapeSetup::SetupFromParams(Params &p)
    {
	Shape *shape = NULL;
	
	auto data = p.GetData(Constants::KW_Box2D);	
	if(data)
	    shape = new Box2D();
	else
	{
	    data = p.GetData(Constants::KW_Polygon2D);
	    if(data)
		shape = new Polygon2D();
	    else
	    {
		data = p.GetData(Constants::KW_Box3D);
		if(data)
		    shape = new Box3D();		
	    }	    
	}

	if(shape )
	    shape->SetupFromParams(p);

	return shape;	
    }
}
