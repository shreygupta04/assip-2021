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

#include "Utils/GManagerComponentCamera.hpp"
#include "Utils/GManager.hpp"

namespace Antipatrea
{
    void GManagerComponentCamera::SetupFromParams(Params &p)
    {
	auto data = p.GetData(Constants::KW_Camera);
	if (data && data->m_params)
	    m_gCamera.SetupFromParams(*(data->m_params));
    }
    
    
    int GManagerComponentCamera::PrepareMenu(void)
    {
	GManagerComponent::PrepareMenu();
	
	auto items = GetManager()->GetMenuItems();
	
	MENU_CAMERA_ROTATE_X = items->size();
	items->push_back(new GMenuItem("rotate x", GMenuItem::FLAG_ON | GMenuItem::FLAG_TOGGLES));
	MENU_CAMERA_ROTATE_Y = items->size();
	items->push_back(new GMenuItem("rotate y", GMenuItem::FLAG_ON | GMenuItem::FLAG_TOGGLES));
	MENU_CAMERA_ROTATE_Z = items->size();
	items->push_back(new GMenuItem("rotate z", GMenuItem::FLAG_ON | GMenuItem::FLAG_TOGGLES));
	MENU_CAMERA_ROTATE_CENTER = items->size();
	items->push_back(new GMenuItem("rotate center", GMenuItem::FLAG_ON | GMenuItem::FLAG_TOGGLES));
	MENU_CAMERA_ROTATE_GLOBAL_AXIS = items->size();
	items->push_back(new GMenuItem("rotate global axis", GMenuItem::FLAG_ON | GMenuItem::FLAG_TOGGLES));
	MENU_CAMERA_INFO = items->size();
	items->push_back(new GMenuItem("info", GMenuItem::FLAG_OFF));
	
	m_menuLastItem =  MENU_CAMERA_INFO;
	
	for(int i = MENU_CAMERA_ROTATE_X; i <= MENU_CAMERA_INFO; ++i)
	    GetManager()->AddMenuEntry((*items)[i]->GetExtendedName(), i);
	
	return m_menu;	
    }
    
    bool GManagerComponentCamera::HandleEventOnActiveMouseMove(const int x, const int y)
    {
	const double thetax = 0.25 * 2 * M_PI * (y - GetManager()->GetMousePrevY()) / glutGet(GLUT_WINDOW_HEIGHT);
	const double thetay = 0.25 * 2 * M_PI * (x - GetManager()->GetMousePrevX()) / glutGet(GLUT_WINDOW_WIDTH);
	const double thetaz = thetay;
	
	return
	    HandleEventOnCameraRotation(thetax, thetay, thetaz) ||
	    GManagerComponent::HandleEventOnActiveMouseMove(x, y);
    }
    
    bool GManagerComponentCamera::HandleEventOnNormalKeyPress(const int key)
    {
	switch (key)
	{
	case Constants::KEY_CAMERA_ROTATE_X:
	    return HandleEventOnCameraRotation(Constants::DEG2RAD, 0, 0);
	case Constants::KEY_CAMERA_ROTATE_Y:
	    return HandleEventOnCameraRotation(0, Constants::DEG2RAD, 0);
	case Constants::KEY_CAMERA_ROTATE_Z:
	    return HandleEventOnCameraRotation(0, 0, Constants::DEG2RAD);
	case Constants::KEY_CAMERA_ROTATE_XNEG:
	    return HandleEventOnCameraRotation(-Constants::DEG2RAD, 0, 0);
	case Constants::KEY_CAMERA_ROTATE_YNEG:
	    return HandleEventOnCameraRotation(0, -Constants::DEG2RAD, 0);
	case Constants::KEY_CAMERA_ROTATE_ZNEG:
	    return HandleEventOnCameraRotation(0, 0, -Constants::DEG2RAD);
	};
	
	return GManagerComponent::HandleEventOnNormalKeyPress(key);	
    }
    
    bool GManagerComponentCamera::HandleEventOnSpecialKeyPress(const int key)
    {
	auto d = GetCamera()->GetMoveDistance();
	
	switch (key)
	{
	case GLUT_KEY_UP:           m_gCamera.MoveForward(d);   return true;
	case GLUT_KEY_DOWN:  m_gCamera.MoveForward(-d);  return true;
	case GLUT_KEY_RIGHT:   m_gCamera.MoveRight(d);   return true;
	case GLUT_KEY_LEFT:       m_gCamera.MoveRight(-d);  return true;
	case GLUT_KEY_PAGE_DOWN:  m_gCamera.MoveUp(d);  return true;
	case GLUT_KEY_PAGE_UP:  m_gCamera.MoveUp(-d);   return true;
	}
	
	return GManagerComponentCamera::HandleEventOnSpecialKeyPress(key);	
    }
    
    
    bool GManagerComponentCamera::HandleEventOnMenu(const int item)
    {
	if (item == MENU_CAMERA_INFO)
	    m_gCamera.Print(Logger::m_out);
	
	return GManagerComponent::HandleEventOnMenu(item);
    }
    
    bool GManagerComponentCamera::HandleEventOnCameraRotation(const double thetax, const double thetay, const double thetaz)
    {
	auto items = GetManager()->GetMenuItems();
	
	const double *p = HasAllFlags((*items)[MENU_CAMERA_ROTATE_CENTER]->GetFlags(), GMenuItem::FLAG_ON) ? m_gCamera.GetCenter() : m_gCamera.GetEye();
	bool event = false;
	
	if (HasAllFlags((*items)[MENU_CAMERA_ROTATE_X]->GetFlags(), GMenuItem::FLAG_ON) && thetax != 0)
	{
	    if (HasAllFlags((*items)[MENU_CAMERA_ROTATE_GLOBAL_AXIS]->GetFlags(), GMenuItem::FLAG_ON))
		m_gCamera.RotateAroundAxisAtPoint(thetax, 1, 0, 0, p[0], p[1], p[2]);
	    else
		m_gCamera.RotateAroundRightAxisAtPoint(thetax, p[0], p[1], p[2]);
	    event = true;
	}
	
	if (HasAllFlags((*items)[MENU_CAMERA_ROTATE_Y]->GetFlags(), GMenuItem::FLAG_ON) && thetay != 0)
	{
	    if (HasAllFlags((*items)[MENU_CAMERA_ROTATE_GLOBAL_AXIS]->GetFlags(), GMenuItem::FLAG_ON))
		m_gCamera.RotateAroundAxisAtPoint(thetay, 0, 1, 0, p[0], p[1], p[2]);
	    else
		m_gCamera.RotateAroundUpAxisAtPoint(thetay, p[0], p[1], p[2]);
	    event = true;
	}
	
	if (HasAllFlags((*items)[MENU_CAMERA_ROTATE_Z]->GetFlags(), GMenuItem::FLAG_ON) && thetaz != 0)
	{
	    if (HasAllFlags((*items)[MENU_CAMERA_ROTATE_GLOBAL_AXIS]->GetFlags(), GMenuItem::FLAG_ON))
		m_gCamera.RotateAroundAxisAtPoint(thetaz, 0, 0, 1, p[0], p[1], p[2]);
	    else
		m_gCamera.RotateAroundForwardAxisAtPoint(thetaz, p[0], p[1], p[2]);
	    event = true;
	}
	return event;
    }
}
