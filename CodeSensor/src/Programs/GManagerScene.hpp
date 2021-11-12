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
 
#ifndef Antipatrea__GManagerScene_HPP_
#define Antipatrea__GManagerScene_HPP_

#include "Programs/GManagerSetup.hpp"

namespace Antipatrea
{
    
    class GManagerScene : public GManagerSetup
    {
    public:
	GManagerScene(void) : GManagerSetup()
	{
	    m_menuName = "Scene";
	}
	
	virtual ~GManagerScene(void)
	{
	}
	
	virtual void HandleEventOnDisplay(void);
		
	virtual int PrepareMenu(void);
	
    protected:
	int MENU_DRAW_OBSTACLES;
	int MENU_DRAW_OCCUPIED;	
	int MENU_DRAW_TERRAIN;
       
    };
    
    ClassContainer(GManagerScene, m_gManagerScene);
    
}

#endif
