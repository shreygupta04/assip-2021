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
 
#include "Programs/GManagerSensor.hpp"
#include "Utils/GManager.hpp"

namespace Antipatrea
{
    
    bool GManagerSensor::HandleEventOnMouseLeftBtnDown(const int x, const int y)
    {
	
	auto items = GetManager()->GetMenuItems();
	
	if (GetSetup() && GetSetup()->GetSensor() && HasAllFlags( ( *items )[MENU_SENSOR_ACTIVATE]->GetFlags(), GMenuItem::FLAG_ON ) )
	{
	    auto cid = GetSetup()->GetScene()->GetGrid()->GetCellId(GetManager()->GetPositionClicked());
	    m_sensed = *(GetSetup()->GetSensor()->Sense(cid));
	    	    
	    return true;
	}
	
	return GManagerComponent::HandleEventOnMouseLeftBtnDown( x, y );
    }
    
	
    void GManagerSensor::HandleEventOnDisplay(void)
    {
	GManagerComponent::HandleEventOnDisplay();

	auto setup = GetSetup();

	if(setup == NULL)
	    return;
	
	auto sensor = setup->GetSensor();

	if(sensor == NULL)
	    return;
	
	auto items = GetManager()->GetMenuItems();
	
	if (items && HasAllFlags((*items)[MENU_SENSOR_ACTIVATE]->GetFlags(), GMenuItem::FLAG_ON))
	{
	    //sensor center
	    GDrawPushTransformation();
	    GDrawMultTrans(0.0, 0.0, setup->GetZOffset(Setup::ZOFF_SENSOR_CENTER));
	    GDrawColor(setup->GetColor(Setup::COLOR_SENSOR_CENTER));
	    GDrawSphere3D(GetManager()->GetPositionClicked(),  sensor->GetScene()->GetGrid()->GetMinUnit());
	    GDrawPopTransformation();
	    
	    auto grid = sensor->GetScene()->GetGrid();
	    std::vector<double> cmin(grid->GetNrDims());
	    std::vector<double> cmax(grid->GetNrDims());

	    void (*fnDraw)(const double[], const double []);

	    if(grid->GetNrDims())
		fnDraw = GDrawBox2D;
	    else
		fnDraw = GDrawBox3D;

	    //sensor cells free
	    GDrawPushTransformation();
	    GDrawMultTrans(0.0, 0.0, setup->GetZOffset(Setup::ZOFF_SENSOR_CELLS_FREE));
	    GDrawColor(setup->GetColor(Setup::COLOR_SENSOR_CELLS_FREE));	    
	    for(auto & cid : m_sensed.m_cellsFree)
	    {
		grid->GetCellFromId(cid, &cmin[0], &cmax[0]);
		fnDraw(&cmin[0], &cmax[0]);		
	    }
	    GDrawPopTransformation();

	    //sensor cells occupied
	    GDrawPushTransformation();
	    GDrawMultTrans(0.0, 0.0, setup->GetZOffset(Setup::ZOFF_SENSOR_CELLS_OCCUPIED));	 
	    GDrawColor(setup->GetColor(Setup::COLOR_SENSOR_CELLS_OCCUPIED));	    
	    for(auto & cid : m_sensed.m_cellsOccupied)
	    {
		grid->GetCellFromId(cid, &cmin[0], &cmax[0]);
		fnDraw(&cmin[0], &cmax[0]);		
	    }	    
	    GDrawPopTransformation();

	    //sensor cells free overall
	    GDrawPushTransformation();
	    GDrawMultTrans(0.0, 0.0, setup->GetZOffset(Setup::ZOFF_SENSOR_CELLS_FREE_OVERALL));	 
	    GDrawColor(setup->GetColor(Setup::COLOR_SENSOR_CELLS_FREE_OVERALL));
	    auto cells = setup->GetSensor()->GetSensedFreeCells();	    
	    for(auto & cid : *cells)
	    {
		grid->GetCellFromId(cid, &cmin[0], &cmax[0]);
		fnDraw(&cmin[0], &cmax[0]);		
	    }	    
	    GDrawPopTransformation();

	    //sensor cells occupied overall
	    GDrawPushTransformation();
	    GDrawMultTrans(0.0, 0.0, setup->GetZOffset(Setup::ZOFF_SENSOR_CELLS_OCCUPIED_OVERALL));	 
	    GDrawColor(setup->GetColor(Setup::COLOR_SENSOR_CELLS_OCCUPIED_OVERALL));	    
	    cells = setup->GetSensor()->GetSensedOccupiedCells();	    
	    for(auto & cid : *cells)
	    {
		grid->GetCellFromId(cid, &cmin[0], &cmax[0]);
		fnDraw(&cmin[0], &cmax[0]);		
	    }	    
	    GDrawPopTransformation();

	}	
    }
        
    int GManagerSensor::PrepareMenu(void)
    {
	GManagerComponent::PrepareMenu();
	
	auto items = GetManager()->GetMenuItems();
	
	MENU_SENSOR_ACTIVATE = items->size();
	items->push_back(new GMenuItem("activate", GMenuItem::FLAG_ON | GMenuItem::FLAG_TOGGLES));

	GetManager()->AddMenuEntry((*items)[MENU_SENSOR_ACTIVATE]->GetExtendedName(), MENU_SENSOR_ACTIVATE);
	
//	m_menuFirstItem = MENU_SENSOR_ACTIVATE;
	m_menuLastItem = MENU_SENSOR_ACTIVATE;
	
	return m_menu;
    }
}
