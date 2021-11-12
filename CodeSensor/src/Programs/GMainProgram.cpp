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
#include "Programs/GManagerScene.hpp"
#include "Programs/GManagerSensor.hpp"
#include "Utils/GManager.hpp"

using namespace Antipatrea;

extern "C" int GMainProgram( int argc, char **argv )
{
    GManager   gManager;
    GManagerScene   gScene;
    GManagerSensor gSensor;
   
    const std::vector<GManagerSetup*> scomps = 
	{
	    &gScene, &gSensor
	};
    
	
    
    Setup  setup;
    Params params;

    if ( argc < 1 )
        return 0;


    params.ReadFromFile( argv[1] );
    params.ProcessArgs( 2, argc - 1, argv );
    //Logger::m_out << params << std::endl;


    setup.SetupFromParams( params );
    
    for(auto & comp :  scomps)
    {
	comp->SetManager(&gManager);
	comp->SetSetup(&setup);
	gManager.GetComponents()->push_back(comp);	
    }
    
    auto data = params.GetData( Antipatrea::Constants::KW_Graphics );
    if ( data && data->m_params )
    {
        GDrawSetupFromParams( *( data->m_params ) );
	gManager.SetupFromParams( *( data->m_params ) );
	for(auto & comp :  scomps)
	    comp->SetupFromParams(*(data->m_params));
  } 


    gManager.MainLoop( "GMainProgram" );

    return 0;
}
