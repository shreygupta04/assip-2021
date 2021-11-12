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
 
#ifndef Antipatrea__ShapeSetup_HPP_
#define Antipatrea__ShapeSetup_HPP_

#include "Utils/Params.hpp"
#include "Utils/Shape.hpp"

namespace Antipatrea
{
    class ShapeSetup 
    {
    public:
	ShapeSetup(void)
	{
	}
	
	virtual ~ShapeSetup(void)
	{
	}

	static Shape* SetupFromParams(Params &p);

    };

}
#endif
