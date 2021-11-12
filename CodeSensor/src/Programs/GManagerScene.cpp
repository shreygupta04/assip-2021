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
 
#include "Programs/GManagerScene.hpp"
#include "Utils/GManager.hpp"

namespace Antipatrea
{
    void GManagerScene::HandleEventOnDisplay(void)
    {
	GManagerComponent::HandleEventOnDisplay();

	auto setup = GetSetup();

	if(setup == NULL)
	    return;
	
	auto scene = setup->GetScene();

	if(scene == NULL)
	    return;
	
	auto items = GetManager()->GetMenuItems();
	
	auto pmin = scene->GetGrid()->GetMin();
	auto pmax = scene->GetGrid()->GetMax();
	const double off = 0.002;
	
	GetManager()->SetValue(GManager::INDEX_MINX, pmin[0] - off * (pmax[0] - pmin[0]));
	GetManager()->SetValue(GManager::INDEX_MINY, pmin[1] - off * (pmax[1] - pmin[1]));
	GetManager()->SetValue(GManager::INDEX_MAXX, pmax[0] + off * (pmax[0] - pmin[0]));
	GetManager()->SetValue(GManager::INDEX_MAXY, pmax[1] + off * (pmax[1] - pmin[1]));
	
	if (items && HasAllFlags((*items)[MENU_DRAW_OBSTACLES]->GetFlags(), GMenuItem::FLAG_ON))
	{
	    GDrawColor(setup->GetColor(Setup::COLOR_OBSTACLES));
	    setup->m_gTextureObstacles.AutomaticCoords();
	    setup->m_gTextureObstacles.Use();
	    scene->DrawObstacles();
	}

	if (items && HasAllFlags((*items)[MENU_DRAW_OCCUPIED]->GetFlags(), GMenuItem::FLAG_ON))
	{
	    GDrawColor(setup->GetColor(Setup::COLOR_OCCUPIED));
	    setup->m_gTextureObstacles.AutomaticCoords();
	    setup->m_gTextureObstacles.Use();
	    scene->DrawOccupied();
	}
	
	if (items && HasAllFlags((*items)[MENU_DRAW_TERRAIN]->GetFlags(), GMenuItem::FLAG_ON))
	{
	    GDrawColor(setup->GetColor(Setup::COLOR_TERRAIN));
	    setup->m_gTextureTerrain.AutomaticCoords();
	    setup->m_gTextureTerrain.Use();
	    scene->DrawTerrain();
	}	
    }
        
    int GManagerScene::PrepareMenu(void)
    {
	GManagerComponent::PrepareMenu();
	
	auto items = GetManager()->GetMenuItems();
	
	MENU_DRAW_OBSTACLES = items->size();
	items->push_back(new GMenuItem("draw obstacles", GMenuItem::FLAG_ON | GMenuItem::FLAG_TOGGLES));

	MENU_DRAW_OCCUPIED = items->size();
	items->push_back(new GMenuItem("draw occupied cells", GMenuItem::FLAG_ON | GMenuItem::FLAG_TOGGLES));

	MENU_DRAW_TERRAIN = items->size();
	items->push_back(new GMenuItem("draw terrain", GMenuItem::FLAG_ON | GMenuItem::FLAG_TOGGLES));

	GetManager()->AddMenuEntry((*items)[MENU_DRAW_OBSTACLES]->GetExtendedName(), MENU_DRAW_OBSTACLES);
	GetManager()->AddMenuEntry((*items)[MENU_DRAW_OCCUPIED]->GetExtendedName(), MENU_DRAW_OCCUPIED);
	GetManager()->AddMenuEntry((*items)[MENU_DRAW_TERRAIN]->GetExtendedName(), MENU_DRAW_TERRAIN);
	
//	m_menuFirstItem = MENU_DRAW_OBSTACLES;
	m_menuLastItem = MENU_DRAW_TERRAIN;
	
	return m_menu;
    }
}
