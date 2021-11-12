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

#include "Utils/GManagerComponent.hpp"
#include "Utils/GManager.hpp"

namespace Antipatrea
{
    bool GManagerComponent::HasMouseControl(void) const
    {
	return HasAllFlags(GetManager()->GetMenuItems()->operator[](MENU_MOUSE_CONTROL)->GetFlags(), GMenuItem::FLAG_ON);		    
    }

    bool GManagerComponent::HasKeyboardControl(void) const
    {
	return HasAllFlags(GetManager()->GetMenuItems()->operator[](MENU_KEYBOARD_CONTROL)->GetFlags(), GMenuItem::FLAG_ON);  	    
    }
    
    bool GManagerComponent::HandleEventOnMenu(const int item)
    {
	if (item >= m_menuFirstItem && item <= m_menuLastItem)
	{
	    auto items = GetManager()->GetMenuItems();
	    
	    if (HasAllFlags((*items)[item]->GetFlags(), GMenuItem::FLAG_TOGGLES))
	    {
		GetManager()->SetMenu(m_menu);
		(*items)[item]->SetFlags(FlipFlags((*items)[item]->GetFlags(), GMenuItem::FLAG_ON));
		GetManager()->ChangeToMenuEntry(item - m_menuFirstItem + 1, (*items)[item]->GetExtendedName(), item);
		return true;
	    }
	}
	
	return false;
    }
    
    int GManagerComponent::PrepareMenu(void)
    {
	m_menu = GetManager()->CreateMenu();
	
	auto items = GetManager()->GetMenuItems();
	
	MENU_MOUSE_CONTROL = items->size();
	items->push_back(new GMenuItem("mouse control", GMenuItem::FLAG_OFF| GMenuItem::FLAG_TOGGLES));
	
	MENU_KEYBOARD_CONTROL = items->size();
	items->push_back(new GMenuItem("keyboard control", GMenuItem::FLAG_OFF| GMenuItem::FLAG_TOGGLES));
	
	for(int i = MENU_MOUSE_CONTROL; i <= MENU_KEYBOARD_CONTROL; ++i)
	    GetManager()->AddMenuEntry((*items)[i]->GetExtendedName(), i);
	
	m_menuFirstItem = MENU_MOUSE_CONTROL;
	m_menuLastItem = MENU_KEYBOARD_CONTROL;
	
	return m_menu;
    }
}
