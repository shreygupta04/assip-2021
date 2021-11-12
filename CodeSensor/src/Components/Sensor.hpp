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

#ifndef Antipatrea__Sensor_HPP_
#define Antipatrea__Sensor_HPP_

#include "Utils/Component.hpp"
#include "Components/Scene.hpp"
#include "Utils/IdContainer.hpp"
#include "Components/Constants.hpp"
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace Antipatrea
{

    class Sensor : public Component,
		   public SceneContainer
    {
    public:
	Sensor( void ) : Component(),
			 SceneContainer(),
			 m_radius(Constants::SENSOR_RADIUS)
	{
	}
	
	virtual ~Sensor( void )
	{
	    Clear();	    
	}

	struct Data
	{
	    std::unordered_set<Id> m_cellsFree;
	    std::unordered_set<Id> m_cellsOccupied;		    
	};
	
	    

	virtual double GetRadius(void) const
	{
	    return m_radius;
	}

	virtual void SetRadius(const double r)
	{
	    m_radius = r;
	}
	
	virtual void SetupFromParams( Params &params )
	{
	    Component::SetupFromParams(params);	    
	    SetRadius(params.GetValueAsDouble(Constants::KW_Radius, GetRadius()));
	}

	virtual void Clear(void);
		
	virtual const Data* Sense(const Id cid);

	virtual const std::unordered_set<Id>* GetSensedFreeCells(void) const
	{
	    return &m_sensedCellsFree;
	}
	
	virtual std::unordered_set<Id>* GetSensedFreeCells(void) 
	{
	    return &m_sensedCellsFree;
	}

	virtual const std::unordered_set<Id>* GetSensedOccupiedCells(void) const
	{
	    return &m_sensedCellsOccupied;
	}
	
	virtual std::unordered_set<Id>* GetSensedOccupiedCells(void) 
	{
	    return &m_sensedCellsOccupied;
	}


    protected:
	double m_radius;	
	std::unordered_map<Id, Data*> m_sensorReadings;
	std::unordered_set<Id> m_sensedCellsFree;
	std::unordered_set<Id> m_sensedCellsOccupied;
    };
    
    ClassContainer( Sensor, m_sensor);
}

#endif
