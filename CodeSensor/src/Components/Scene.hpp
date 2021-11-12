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

#ifndef Antipatrea__Scene_HPP_
#define Antipatrea__Scene_HPP_

#include "Components/Constants.hpp"
#include "Utils/Component.hpp"
#include "Utils/Grid.hpp"
#include "Utils/Params.hpp"
#include "Utils/TriMeshDefault.hpp"
#include "Utils/Allocator.hpp"
#include "Utils/GDraw.hpp"
#include "Utils/IdContainer.hpp"
#include "Utils/HashFn.hpp"
#include <unordered_map>
#include <unordered_set>

namespace Antipatrea
{
    class Scene  : public Component
    {
    public:
	Scene( void ) :
	    Component(),
	    m_dsepPointObstacles(Constants::SEPARATION_POINT_OBSTACLES),
	    m_dsepSegmentObstacles(Constants::SEPARATION_SEGMENT_OBSTACLES)
	{
	}
	
	virtual ~Scene( void )
	{
	}

	virtual double GetSeparationPointObstacles(void) const
	{
	    return m_dsepPointObstacles;
	}

	virtual double GetSeparationSegmentObstacles(void) const
	{
	    return m_dsepSegmentObstacles;
	}
	
	virtual void SetupFromParams( Params &params );
	
	virtual const Grid* GetGrid(void) const
	{
	    return &m_grid;
	}
	
	virtual Grid *GetGrid( void )
	{
	    return &m_grid;
	}
	
	virtual TriMesh *GetObstaclesCollisionMesh( void )
	{
	    return &m_tmeshObstaclesCollision;
	}
	
	virtual TriMesh *GetObstaclesDrawMesh( void )
	{
	    return &m_tmeshObstaclesDraw;
	}
	
	virtual void AdjustGrid( const double eps );
	
	virtual void AddBoundaries( const double thick, const double h ) = 0;
	
	virtual void DrawObstacles( void )
	{
	    m_tmeshObstaclesDraw.Draw();
	}

	virtual void DrawTerrain(void)
	{
	    m_tmeshTerrain.Draw();
	}

	virtual void DrawOccupied(void);
	
	virtual double GetCellClearance(const Id cid);
	
	virtual bool IsCellInCollision(const Id cid);

	virtual bool IsCellSegmentInCollision(const Id cid1, const Id cid2);

	virtual bool IsPointInCollision(const double p[], const double dtol);
		    
	virtual bool IsPointInCollision(const double p[])
	{
	    return IsPointInCollision(p, m_dsepPointObstacles);
	}
	
	virtual bool IsSegmentInCollision(const double p1[], const double p2[], const double dtol);
	
	virtual bool IsSegmentInCollision(const double p1[], const double p2[])
	{
	    return IsSegmentInCollision(p1, p2, m_dsepSegmentObstacles);
	}
	

	virtual bool IsMeshInCollision(TriMesh &tmesh);

	virtual const Allocator* GetPositionAllocator(void) const
	{
	    return &m_allocatorPosition;
	}

	virtual Allocator* GetPositionAllocator(void)
	{
	    return &m_allocatorPosition;
	}

	virtual void DrawPoint(const double p[]) const = 0;
	
	virtual void DrawSegment(const double p1[], const double p2[]) const = 0;
	
	virtual double GetPointClearance(const double p[], const double dtol);
	virtual double GetPointClearance(const double p[])
	{
	    return GetPointClearance(p, m_dsepPointObstacles);
	}
	
	virtual double GetSegmentClearance(const double p1[], const double p2[], const double dtol);
	
	virtual double GetSegmentClearance(const double p1[], const double p2[])
	{
	    return GetSegmentClearance(p1, p2, m_dsepSegmentObstacles);
	}
		
	virtual double GetMeshClearance(TriMesh &tmesh);

	virtual void SamplePosition(double p[]) const
	{
	    return m_grid.SamplePoint(p);
	}
	
	virtual void SampleValidPosition(double p[]);

		
	virtual const std::unordered_set<Id>* GetAllOccupiedCells(void) const
	{
	    return &m_allCellsOccupied;
	}
	
	virtual std::unordered_set<Id>* GetAllOccupiedCells(void) 
	{
	    return &m_allCellsOccupied;
	}

	virtual void ComputeAllOccupiedCells(void);
	
	    
    protected:
	virtual void PointAsMesh(const double p[], const double dtol, TriMesh &tmesh);
	virtual void SegmentAsMesh(const double p1[], const double p2[], const double dtol, TriMesh &tmesh);

	Grid m_grid;
	TriMeshDefault m_tmeshObstaclesCollision;
	TriMesh m_tmeshObstaclesDraw;
	TriMeshDefault m_tmeshTerrain;
	Allocator m_allocatorPosition;

	std::unordered_map<Id, bool> m_cacheCollisionCells;
	std::unordered_map< std::pair<Id, Id>, bool > m_cacheSegmentCollisionCells;
	std::unordered_map<Id, double> m_cacheClearanceCells;

	double m_dsepPointObstacles;
	double m_dsepSegmentObstacles;

	std::unordered_set<Id> m_allCellsOccupied;
	
	
    };
    
    ClassContainer( Scene, m_scene );
}

#endif
