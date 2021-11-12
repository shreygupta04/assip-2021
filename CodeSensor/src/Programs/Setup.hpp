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

#ifndef Antipatrea__ProgramsSetup_HPP_
#define Antipatrea__ProgramsSetup_HPP_

#include "Components/Scene.hpp"
#include "Components/Sensor.hpp"

namespace Antipatrea
{
    class Setup : public SceneContainer,
		  public SensorContainer,
		  public FlagsContainer
    {
    public:
	
	enum
	    {
		SETUP_SCENE     = 1 << 0,
		SETUP_SENSOR = 1 << 1,
		SETUP_GRAPHICS = 1 << 2
	    };
	
	Setup(void) : SceneContainer(),
		      SensorContainer(),
		      FlagsContainer()
	{
	    m_flags =
		SETUP_SCENE |
		SETUP_SENSOR |
		SETUP_GRAPHICS;
	    
	    std::fill( m_zoffsets, m_zoffsets + NR_Z_OFFSETS, 0.0 );
	    
	    SetColor(COLOR_OBSTACLES,   1.0, 0.3, 0.7);
	    SetColor(COLOR_OCCUPIED,   0.7, 0.7, 0.7);
	    SetColor(COLOR_TERRAIN, 0.7, 0.7, 0.1);

	    SetColor(COLOR_SENSOR_CENTER, 1.0, 0.0, 0.0);
	    SetColor(COLOR_SENSOR_CELLS_FREE, 0.7, 0.6, 0.9);
	    SetColor(COLOR_SENSOR_CELLS_OCCUPIED, 0.4, 0.4, 0.4);
	    SetColor(COLOR_SENSOR_CELLS_FREE_OVERALL, 0.9, 0.6, 0.9);
	    SetColor(COLOR_SENSOR_CELLS_OCCUPIED_OVERALL, 0.2, 0.2, 0.2);
	    
	}
		
	virtual ~Setup(void)
	{
	    if (GetScene())
		delete GetScene();
	    if(GetSensor())
		delete GetSensor();
	}
	
	enum
	    {
		COLOR_OBSTACLES = 0,
		COLOR_TERRAIN,
		COLOR_OCCUPIED,

		COLOR_SENSOR_CENTER,
		COLOR_SENSOR_CELLS_FREE,
		COLOR_SENSOR_CELLS_OCCUPIED,
		COLOR_SENSOR_CELLS_FREE_OVERALL,
		COLOR_SENSOR_CELLS_OCCUPIED_OVERALL,

		NR_COLORS,
		NR_COLOR_COMPONENTS = 3
	    };

	enum
	    {		
		ZOFF_SENSOR_CENTER = 0,
		ZOFF_SENSOR_CELLS_FREE,
		ZOFF_SENSOR_CELLS_OCCUPIED,
		ZOFF_SENSOR_CELLS_FREE_OVERALL,
		ZOFF_SENSOR_CELLS_OCCUPIED_OVERALL,
		NR_Z_OFFSETS
	    };
	
	
	
	virtual int GetNrColors(void) const
	{
	    return NR_COLORS;
	}
	
	virtual const double *GetColor(const int i) const
	{
	    return &m_colors[NR_COLOR_COMPONENTS * i];
	}
	
	virtual double *GetColor(const int i)
	{
	    return &m_colors[NR_COLOR_COMPONENTS * i];
	}

	virtual void SetColor(const int i, const double r, const double g, const double b)
	{
	    auto c = GetColor(i);
	    c[0] = r;
	    c[1] = g;
	    c[2] = b;	    
	}
	
	virtual const double GetZOffset(const int i) const
	{
	    return m_zoffsets[i];
	}

	virtual void SetZOffsets2D(void);

	virtual void SetZOffsets3D(void);
	
	virtual void SetZOffsets(void);
	
	virtual void SetupFromParams(Params &p);
	
	GTexture m_gTextureObstacles;
	GTexture m_gTextureTerrain;
	
    protected:
	virtual void SetupScene(Params &p);
	virtual void SetupSensor(Params &p);
	virtual void SetupGraphics(Params &p);
	virtual void SetupPointers(void);
       
	double m_colors[NR_COLOR_COMPONENTS * NR_COLORS];
	double m_zoffsets[NR_Z_OFFSETS];
	
    };
    
    ClassContainer(Setup, m_setup);
}

#endif
