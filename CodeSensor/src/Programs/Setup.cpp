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

#include "Programs/Setup.hpp"
#include "Components/Scene2D.hpp"
#include "Components/Scene3D.hpp"
#include "Programs/Constants.hpp"
#include "Components/Constants.hpp"

namespace Antipatrea
{
 
    void Setup::SetZOffsets( void )
    {
	if ( dynamic_cast<Scene3D*>(GetScene()))
	    SetZOffsets3D();
	else
	    SetZOffsets2D();
    }
    
    void Setup::SetZOffsets3D( void )
    {
	std::fill( m_zoffsets, m_zoffsets + NR_Z_OFFSETS, 0.0 );
    }
    
    void Setup::SetZOffsets2D( void )
    {
	Logger::m_out << "...using 2D zoffsets" << std::endl;
	
	const double zoff = 0.01;
	for(int i = 0; i < NR_Z_OFFSETS; ++i)
	    m_zoffsets[i] = zoff * (i + 1);
    }

    void Setup::SetupScene(Params &p)
    {
	Params::Data *data;
	
	auto sceneParams = p.GetValue(Constants::KW_UseScene);
	
	if (sceneParams)
	{
	    if (StrSameContent(sceneParams, "Scene2D"))
		SetScene( new Scene2D() );
	    else if (StrSameContent(sceneParams, "Scene3D"))
		SetScene( new Scene3D() );
	    else
		Logger::m_out << "Setup::SetupFromParams...warning unknown <" << Constants::KW_UseScene << " " << sceneParams << std::endl;
	}
	
	if (GetScene() && sceneParams && (data = p.GetData(sceneParams)) && data->m_params)
	    GetScene()->SetupFromParams(*(data->m_params));
    }

    void Setup::SetupSensor(Params &p)
    {
	SetSensor(new Sensor());
	
	Params::Data *data;
	
	if ((data = p.GetData(Constants::KW_Sensor)) && data->m_params)
	    GetSensor()->SetupFromParams(*(data->m_params));
    }

    
    
    void Setup::SetupGraphics(Params &p)
    {
	auto data = p.GetData( Constants::KW_Graphics );
	if ( data && data->m_params )
	{
	    auto n = std::min<int>(Constants::KW_Colors.size(), GetNrColors());
	    
	    for(int i  = 0; i < n; ++i)
	  	data->m_params->GetValuesAsDoubles(Constants::KW_Colors[i], GetColor(i), NR_COLOR_COMPONENTS);
	  
	    
	    m_gTextureObstacles.SetFileName(data->m_params->GetValue(Constants::KW_TextureObstaclesFile));
	    m_gTextureTerrain.SetFileName(data->m_params->GetValue(Constants::KW_TextureTerrainFile));
	}
    }
    
    void Setup::SetupPointers(void)
    {
	if(GetSensor())
	    GetSensor()->SetScene(GetScene());
    }
        
    void Setup::SetupFromParams( Params &p )
    {
	if(HasAllFlags(GetFlags(), SETUP_SCENE))
	    SetupScene(p);	
	if(HasAllFlags(GetFlags(), SETUP_SENSOR))
	    SetupSensor(p);
	if(HasAllFlags(GetFlags(), SETUP_GRAPHICS))
	    SetupGraphics(p);	
	
	SetupPointers();
	
	SetZOffsets();
	
    }


}
