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
 
#ifndef Antipatrea__Shape3D_HPP_
#define Antipatrea__Shape3D_HPP_

#include "Utils/Shape.hpp"

namespace Antipatrea
{
    class Shape3D : public Shape
    {
    public:
	Shape3D(void) 
	{
	}
	
	virtual ~Shape3D(void)
	{
	}

	virtual int GetDim(void) const
	{
	    return 3;
	}	
    };

    ClassContainer(Shape3D, m_shape3D);

}
#endif
