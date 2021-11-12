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
 
#ifndef Antipatrea__Shape2D_HPP_
#define Antipatrea__Shape2D_HPP_

#include "Utils/Shape.hpp"

namespace Antipatrea
{
    class Shape2D : public Shape
    {
    public:
	Shape2D(void) 
	{
	}
	
	virtual ~Shape2D(void)
	{
	}

	virtual int GetDim(void) const
	{
	    return 2;
	}	
    };

    ClassContainer(Shape2D, m_shape2D);
}
#endif
