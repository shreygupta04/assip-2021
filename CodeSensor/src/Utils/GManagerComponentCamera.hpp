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

#ifndef Antipatrea__GManagerComponentCamera_HPP_
#define Antipatrea__GManagerComponentCamera_HPP_

#include "Utils/GManagerComponent.hpp"
#include "Utils/GCamera.hpp"

namespace Antipatrea
{
    
    class GManagerComponentCamera : public GManagerComponent
    {
    public:
	GManagerComponentCamera(void) : GManagerComponent(),
					MENU_CAMERA_ROTATE_X(Constants::ID_UNDEFINED),
					MENU_CAMERA_ROTATE_Y(Constants::ID_UNDEFINED),
					MENU_CAMERA_ROTATE_Z(Constants::ID_UNDEFINED),
					MENU_CAMERA_ROTATE_CENTER(Constants::ID_UNDEFINED),
					MENU_CAMERA_ROTATE_GLOBAL_AXIS(Constants::ID_UNDEFINED),
					MENU_CAMERA_INFO(Constants::ID_UNDEFINED)
	{
	    	    m_menuName = "Camera";	    
	}
	
	
	virtual ~GManagerComponentCamera(void)
	{
	}
	

	virtual void SetupFromParams(Params &params);
		
	virtual bool HandleEventOnActiveMouseMove(const int x, const int y);
	
	virtual bool HandleEventOnNormalKeyPress(const int key);
		
	virtual bool HandleEventOnSpecialKeyPress(const int key);
		
	virtual bool HandleEventOnMenu(const int item);
	
	virtual int PrepareMenu(void);

	virtual const GCamera* GetCamera(void) const
	{
	    return &m_gCamera;
	}

	virtual GCamera* GetCamera(void)
	{
	    return &m_gCamera;
	}
	
    protected:
	virtual bool HandleEventOnCameraRotation(const double thetax, const double thetay, const double thetaz);
	
	GCamera m_gCamera;
	
	int MENU_CAMERA_ROTATE_X;
	int MENU_CAMERA_ROTATE_Y;
	int MENU_CAMERA_ROTATE_Z;
	int MENU_CAMERA_ROTATE_CENTER;
	int MENU_CAMERA_ROTATE_GLOBAL_AXIS;
	int MENU_CAMERA_INFO;
    };
}

#endif
