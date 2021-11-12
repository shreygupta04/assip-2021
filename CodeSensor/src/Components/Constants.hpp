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

#ifndef Antipatrea__ComponentsConstants_HPP_
#define Antipatrea__ComponentsConstants_HPP_

#include "Utils/Constants.hpp"

namespace Antipatrea
{
    namespace Constants
    {
// scene
	const char KW_Scene[]   = "Scene";
	const char KW_Scene2D[] = "Scene2D";
	const char KW_Scene3D[] = "Scene3D";
	const char KW_ObstaclesCollisionMeshFile[] = "ObstaclesCollisionMeshFile";
	const char KW_ObstaclesDrawMeshFile[]      = "ObstaclesDrawMeshFile";
	const char KW_ObstaclesPolygonsFile[]      = "ObstaclesPolygonsFile";
	const char KW_TerrainMeshFile[]            = "TerrainMeshFile";
	const char KW_ObstacleHeight[]             = "ObstacleHeight";
	const char KW_NrObstacles[]     = "NrObstacles";
	const char KW_Obstacle[]        = "Obstacle";
	const char KW_Boundaries[]      = "Boundaries";
	const char KW_Height[]          = "Height";
	const char KW_Thickness[]       = "Thickness";
	const char KW_AdjustGrid[]      = "AdjustGrid";
	
	const double SCENE_OBSTACLE_HEIGHT    = 2.0;
	const double SCENE_BOUNDARY_HEIGHT    = 3.0;
	const double SCENE_BOUNDARY_THICKNESS = 0.4;
	
//Sensor
	const char KW_Sensor[] = "Sensor";	
	const char KW_Radius[] = "Radius";
	const double SENSOR_RADIUS = 10.0;

	//Region
	const char KW_Region[] = "Region";
	const char KW_Penalty[] = "Penalty";
	const char KW_Time[] = "Time";
	const char KW_Energy[] = "Energy";
	const char KW_NrRegions[] = "NrRegions";
	const char KW_InspectRegions[]= "InspectRegions";
	const char KW_InspectRegion[] = "InspectRegion";	
	const char KW_ChargeRegions[] = "ChargeRegions";
	const char KW_ChargeRegion[] = "ChargeRegion";
	
//Problem
	const char KW_Problem[] = "Problem";
	const char KW_InitialPosition[] = "InitialPosition";
	
	
	
// PRM
	const char KW_PRM[]  = "PRM";
	const char KW_NrNeighbors[]     = "NrNeighbors";
	const char KW_BatchSize[]       = "BatchSize";
	const char KW_MaxNrVertices[]   = "MaxNrVertices";
	const char KW_SeparationPointObstacles[] = "SeparationPointObstacles";
	const char KW_SeparationSegmentObstacles[] = "SeparationSegmentObstacles";
	const char KW_SeparationSamples[] = "SeparationSamples";
	const char KW_SeparationSamplesReduceFactor[] = "SeparationSamplesReduceFactor";	
	const char KW_NrChargeVertices[] = "NrChargeVertices";
	const char KW_NrInspectVertices[] = "NrInspectVertices";
	const char KW_NrInspectRegions[] = "NrInspectRegions";
	const char KW_NrAttemptsToGeneratePointInsideRemainingCells[]  = "NrAttemptsToGeneratePointInsideRemainingCells";
	
       
	
	const int PRM_NR_NEIGHBORS      = 15;
	const int PRM_BATCH_SIZE        = 500;
	const int PRM_MAX_NR_VERTICES   = 5000;
	const double SEPARATION_POINT_OBSTACLES = 3.0;
	const double SEPARATION_SEGMENT_OBSTACLES = 3.0;
	const double PRM_DSEP_SAMPLES = 3.0;
	const double PRM_DSEP_SAMPLES_REDUCE_FACTOR = 0.95;
	const int PRM_NR_ATTEMPTS_TO_GENERATE_POINT_INSIDE_REMAINING_CELLS = 40;
	
// Follow
	const char KW_Follow[]              = "Follow";
	const char KW_WeightBase[]          = "WeightBase";
	const char KW_ReachDistance[]       = "ReachDistance";
	const char KW_ReachDistances[]      = "ReachDistances";
	const char KW_Ids[]                 = "Ids";
	const char KW_SeparationDistance[]  = "SeparationDistance";
	const char KW_Points[] = "Points";
	const char KW_Times[] = "Times";	
	const char KW_PointsCircle[] = "PointsCircle";    
	const char KW_PointsCircleCenter[]  = "PointsCircleCenter";
	const char KW_PointsCircleRadius[]  = "PointsCircleRadius";
	const char KW_PointsCircleNrSides[] = "PointsCircleNrSides";
	
	const char KW_PointsStar[] = "PointsStar";    
	const char KW_PointsStarCenter[] = "PointsStarCenter";
	const char KW_PointsStarLength[] = "PointsStarLength";
	const char KW_PointsStarHeight[] = "PointsStarHeight";
	
	const double FOLLOW_WEIGHT_BASE         = 4.0;
	const double FOLLOW_REACH_DISTANCE      = 1.0;
	const double FOLLOW_SEPARATION_DISTANCE = 8.0;

	
// simulator
const char KW_Simulator[]                    = "Simulator";
const char KW_SimulatorCarTrailers[]         = "SimulatorCarTrailers";
const char KW_TimeStep[]                     = "TimeStep";
const char KW_MinDistanceOneStep[]           = "MinDistanceOneStep";
const char KW_MaxDistanceOneStep[]           = "MaxDistanceOneStep";
const char KW_StopDistance[]                 = "StopDistance";
const char KW_StopExponent[]                 = "StopExponent";
const char KW_SteerDistanceReachDesired[]    = "SteerDistanceReachDesired";
const char KW_SteerDistanceReachAcceptable[] = "SteerDistanceReachAcceptable";
const char KW_SteerDistanceAbandon[]         = "SteerDistanceAbandon";
const char KW_SteerNrStepsAbandon[]          = "SteerNrStepsAbandon";
const char KW_DesiredVelocity[]              = "DesiredVelocity";
	const char KW_TimeToEnergyFactor[] = "TimeToEnergyFactor";	
const char KW_DrawPositionRadius[]           = "DrawPositionRadius";

const double SIMULATOR_TIME_STEP                       = 0.1;
const double SIMULATOR_MIN_DISTANCE_ONE_STEP           = 0.5;
const double SIMULATOR_MAX_DISTANCE_ONE_STEP           = 0.8;
const double SIMULATOR_STOP_DISTANCE                   = 6.0;
const double SIMULATOR_STOP_EXPONENT                   = 3.0;
const double SIMULATOR_STEER_DISTANCE_REACH_DESIRED    = 1.0;
const double SIMULATOR_STEER_DISTANCE_REACH_ACCEPTABLE = 2.0;
const double SIMULATOR_STEER_DISTANCE_ABANDON          = 3.0;
const int SIMULATOR_STEER_NR_STEPS_ABANDON          = 30;
const double SIMULATOR_DESIRED_VELOCITY                = 1.0;
	const double SIMULATOR_TIME_TO_ENERGY_FACTOR = 1.0;	
const double SIMULATOR_DRAW_POSITION_RADIUS            = 0.1;

const double SIMULATOR_SNAKE_SX = 1.75;
const double SIMULATOR_SNAKE_SY = 1.5;

const double SIMULATOR_CAR_SX = 1.5;
const double SIMULATOR_CAR_SY = 1.25;

	
// car
	const char CAR_CHASSIS_MESH_FILE[] = "gdata/models/porsche.obj";
	const char CAR_WHEEL_MESH_FILE[]   = "gdata/textures/wheel.mesh.xml";
	const char CAR_TIRE_TEXTURE_FILE[] = "gdata/textures/Tire_tex.png";
	const char BLIMP_MESH_FILE[]       = "gdata/models/blimp.off";
	const char AUV_MESH_FILE[]         = "gdata/models/model.obj";
	
// SimulatorCarTrailers
	const bool CAR_FRONT_WHEEL_DRIVING = true;
	const double CAR_BODY_LENGTH         = 1.75;
	const double CAR_BODY_WIDTH          = 1.0;
	const double CAR_MIN_STEER_ANGLE     = -85 * Constants::DEG2RAD;
	const double CAR_MAX_STEER_ANGLE     = 85 * Constants::DEG2RAD;
	const double CAR_MIN_VELOCITY        = -2.0;
	const double CAR_MAX_VELOCITY        = 2.0;
	const double CAR_MIN_ACCELERATION    = -1.0;
	const double CAR_MAX_ACCELERATION    = 1.0;
	const double CAR_MIN_STEER_VELOCITY  = -2.7;
	const double CAR_MAX_STEER_VELOCITY  = 2.7;
	const double CAR_NR_TRAILERS         = 5;
	const double CAR_ATTACH_DISTANCE     = 0.01;
	const double BLIMP_MIN_CONTROL_Z     = -2.7;
	const double BLIMP_MAX_CONTROL_Z     = 2.7;
	const double BLIMP_BODY_HEIGHT       = 1.0;
	const double AUV_BODY_HEIGHT       = 1.0;
	const double AUV_BODY_LENGTH         = 3.0;
	const double AUV_BODY_WIDTH          = 1.0;
	const double AUV_MIN_PITCH_ANGLE     = -13 * Constants::DEG2RAD;
	const double AUV_MAX_PITCH_ANGLE     = 13 * Constants::DEG2RAD;
	const double AUV_MIN_PITCH_VELOCITY  = -0.7;
	const double AUV_MAX_PITCH_VELOCITY  = 0.7;
	const double AUV_MIN_CONTROL_Z     = -2.7;
	const double AUV_MAX_CONTROL_Z     = 2.7;
	
	const char KW_CurrentState[]              = "CurrentState";
	const char KW_CarFrontWheelDriving[]      = "CarFrontWheelDriving";
	const char KW_CarBodyLength[]             = "CarBodyLength";
	const char KW_CarBodyWidth[]              = "CarBodyWidth";
	const char KW_BodyHeight[]                = "BodyHeight";
	const char KW_CarMinSteerAngleInDegrees[] = "CarMinSteerAngleInDegrees";
	const char KW_CarMaxSteerAngleInDegrees[] = "CarMaxSteerAngleInDegrees";
	const char KW_CarMinVelocity[]            = "CarMinVelocity";
	const char KW_CarMaxVelocity[]            = "CarMaxVelocity";
	const char KW_CarMinSteerVelocity[]       = "CarMinSteerVelocity";
	const char KW_CarMaxSteerVelocity[]       = "CarMaxSteerVelocity";
	const char KW_CarMinAcceleration[]        = "CarMinAcceleration";
	const char KW_CarMaxAcceleration[]        = "CarMaxAcceleration";
	const char KW_CarNrTrailers[]             = "CarNrTrailers";
	const char KW_CarAttachDistance[]         = "CarAttachDistance";
	const char KW_MinControlZ[]               = "MinControlZ";
	const char KW_MaxControlZ[]               = "MaxControlZ";

	//charge energy
	const double CHARGE_ENERGY = 300.0;
	
    }
}

#endif
