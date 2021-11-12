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
#include <fstream>

using namespace Antipatrea;

extern "C" int ConvertSceneToCells( int argc, char **argv )
{
    
    Setup  setup;
    Params params;

    if ( argc < 1 )
        return 0;


    params.ReadFromFile( argv[1] );
    params.ProcessArgs( 2, argc - 1, argv );
    Logger::m_out << params << std::endl;


    setup.SetupFromParams( params );
    

    auto fname = params.GetValue("OutputFile", "data/cells.txt");    
    auto grid = setup.GetScene()->GetGrid();
    auto cells = setup.GetScene()->GetAllOccupiedCells();
    std::vector<int> coords(grid->GetNrDims());

    Logger::m_out << "..writing output to " << fname << std::endl;
    
    std::ofstream out(fname);

    out << "map:" << std::endl
	<< "  " << "dimensions:" << std::endl
	<< "  " << "- " << grid->GetDims()[0] << std::endl
	<< "  " << "- " << grid->GetDims()[1] << std::endl
	<< "  " << "obstacles:" << std::endl;

    for(auto cid : *cells)
    {
	grid->GetCoordsFromCellId(cid, &coords[0]);
	
	out << "  " << "- !!python/tuple" << std::endl
	    << "    " << "- " << coords[0] << std::endl
	    << "    " << "- " << coords[1] << std::endl;
	
    }
    
     
    out.close();
    
    return 0;
}
