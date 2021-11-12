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

#ifndef Antipatrea__ProgramsConstants_HPP_
#define Antipatrea__ProgramsConstants_HPP_

#include <vector>

namespace Antipatrea
{
/**
 *@brief Keywords and default values.
 */
    namespace Constants
    {
	const char KW_TextureObstaclesFile[] = "TextureObstaclesFile";
	const char KW_TextureTerrainFile[] = "TextureTerrainFile";
	const char KW_TextureGoalsFile[] = "TextureGoalsFile";
	const char KW_TextureAbstractionFile[] = "TextureAbstractionFile";
	
	const char KW_UseScene[] = "UseScene";
	const char KW_UseSimulator[] = "UseSimulator";
	const char KW_UseAbstraction[] = "UseAbstraction";	
	const char KW_UseTourGenerator[] = "UseTourGenerator";
	
	
        const std::vector<const char*> KW_Colors = 
	    {
		"ColorObstacles",
		"ColorTerrain",

		"ColorSensorCenter",
		"ColorSensorCells",
			
		"ColorInspectRegion",
		"ColorChargeRegion",

		"ColorAbstractionCharge",
		"ColorAbstractionInspect",
		"ColorAbstractionInit",
		"ColorAbstractionOther",
		"ColorAbstractionEdges",

		"ColorFollow",
		"ColorTour"
	    };
	
	    
    }
}

#endif
