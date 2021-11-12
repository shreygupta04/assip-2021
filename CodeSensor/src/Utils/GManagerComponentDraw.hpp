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

#ifndef Antipatrea__GManagerComponentDraw_HPP_
#define Antipatrea__GManagerComponentDraw_HPP_

#include "Utils/GManagerComponent.hpp"

namespace Antipatrea
{
    
    class GManagerComponentDraw : public GManagerComponent
    {
    public:
	GManagerComponentDraw(void) : GManagerComponent(),
				      MENU_DRAW_3D(Constants::ID_UNDEFINED),
				      MENU_DRAW_TEXTURES(Constants::ID_UNDEFINED),
				      MENU_DRAW_SAVE_FRAME(Constants::ID_UNDEFINED),
				      MENU_DRAW_SAVE_FRAMES(Constants::ID_UNDEFINED),
				      m_nrFrames(0)
	{
	    m_menuName = "Draw";	    	    
	}
	
	
	virtual ~GManagerComponentDraw(void)
	{
	}
	
	virtual int PrepareMenu(void);
	
	virtual bool HandleEventOnMenu(const int item);

	virtual void SaveFrameAsImage(void);
	
	virtual void SaveFrameAsImage(const char fname[]);
	
	int MENU_DRAW_3D;
	int MENU_DRAW_TEXTURES;
	int MENU_DRAW_SAVE_FRAME;
	int MENU_DRAW_SAVE_FRAMES;

    protected:
	int m_nrFrames;
	
    };
}

#endif
