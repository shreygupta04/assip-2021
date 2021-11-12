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
 
#ifndef Antipatrea__GManagerSensor_HPP_
#define Antipatrea__GManagerSensor_HPP_

#include "Programs/GManagerSetup.hpp"

namespace Antipatrea
{
    
    class GManagerSensor : public GManagerSetup
    {
    public:
	GManagerSensor(void) : GManagerSetup()
	{
	    m_menuName = "Sensor";
	}
	
	virtual ~GManagerSensor(void)
	{
	}

	virtual bool HandleEventOnMouseLeftBtnDown(const int x, const int y);
		
	virtual void HandleEventOnDisplay(void);
		
	virtual int PrepareMenu(void);
	
    protected:
	Sensor::Data m_sensed;
	
	
	int MENU_SENSOR_ACTIVATE;
    };
    
    ClassContainer(GManagerSensor, m_gManagerSensor);
    
}

#endif
