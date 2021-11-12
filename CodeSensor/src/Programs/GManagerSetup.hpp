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
 
#ifndef Antipatrea__GManagerSetup_HPP_
#define Antipatrea__GManagerSetup_HPP_

#include "Programs/Setup.hpp"
#include "Utils/GManagerComponent.hpp"

namespace Antipatrea
{
    
    class GManagerSetup : public GManagerComponent,
			  public SetupContainer
    {
    public:
	GManagerSetup(void) : GManagerComponent(),
			      SetupContainer()
	{
	}
	
	virtual ~GManagerSetup(void)
	{
	}
	
	virtual void SetupFromParams(Params &params)
	{
	    GManagerComponent::SetupFromParams(params);
	}
    };
    
    ClassContainer(GManagerSetup, m_gManagerSetup);
    
}

#endif
