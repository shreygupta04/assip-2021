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

#ifndef Antipatrea__GManagerComponent_HPP_
#define Antipatrea__GManagerComponent_HPP_

#include "Utils/Params.hpp"
#include "Utils/Constants.hpp"
#include <string>
#include <cstdlib>

namespace Antipatrea
{
    
    class GManager;
    
    class GManagerComponent
    {
    public:
	GManagerComponent(void) : m_manager(NULL),
				  m_menu(Constants::ID_UNDEFINED),
				  MENU_MOUSE_CONTROL(Constants::ID_UNDEFINED),
				  MENU_KEYBOARD_CONTROL(Constants::ID_UNDEFINED),
				  m_menuFirstItem(Constants::ID_UNDEFINED),
				  m_menuLastItem(Constants::ID_UNDEFINED)
	{
	}
	
	virtual ~GManagerComponent(void)
	{
	}
	
	virtual const GManager *GetManager(void) const
	{
	    return m_manager;
	}
	
	virtual GManager *GetManager(void)
	{
	    return m_manager;
	}
	
	virtual void SetManager(GManager *const manager)
	{
	    m_manager = manager;
	}
	
	virtual void SetupFromParams(Params &params)
	{        
	}
	
	virtual void HandleEventOnTimer(void)
	{
	}
	
	virtual void HandleEventOnDisplay(void)
	{
	}
	
	virtual bool HandleEventOnMouseLeftBtnDown(const int x, const int y)
	{
	    return false;
	}
	
	virtual bool HandleEventOnMouseLeftBtnUp(const int x, const int y)
	{
	    return false;
	}
	
	virtual bool HandleEventOnActiveMouseMove(const int x, const int y)
	{
	    return false;
	}
	
	virtual bool HandleEventOnPassiveMouseMove(const int x, const int y)
	{
	    return false;
	}
	
	virtual bool HandleEventOnNormalKeyPress(const int key)
	{
	    return false;
	}
	
	virtual bool HandleEventOnSpecialKeyPress(const int key)
	{
	    return false;
	}
	
	virtual bool HandleEventOnNormalKeyUp(const int key)
	{
	    return false;
	}
	
	virtual bool HandleEventOnSpecialKeyUp(const int key)
	{
	    return false;
	}
	
	virtual bool HandleEventOnIdle(void)
	{
	    return false;
	}
	
	virtual bool HandleEventOnMenu(const int item);
	
	virtual int PrepareMenu(void);
	
	virtual const char *GetMenuName(void) const
	{
	    return m_menuName.c_str();
	}

	virtual bool HasMenuItem(const int item) const
	{
	    return item >= m_menuFirstItem && item <= m_menuLastItem;
	}

	virtual bool HasMouseControl(void) const;

	virtual bool HasKeyboardControl(void) const;
		
    protected:
	GManager *m_manager;
	int m_menu;
	int MENU_MOUSE_CONTROL;
	int MENU_KEYBOARD_CONTROL;	
	int m_menuFirstItem;
	int m_menuLastItem;
	std::string m_menuName;
    };
}

#endif
