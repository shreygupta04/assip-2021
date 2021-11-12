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

#include "Components/Scene.hpp"
#include "Components/Constants.hpp"
#include "Utils/TriMeshStreamer.hpp"
#include "Utils/Algebra3D.hpp"
#include "Utils/Misc.hpp"

namespace Antipatrea
{
    void Scene::SetupFromParams( Params &params )
    {
	Component::SetupFromParams(params);
	
	m_dsepPointObstacles = params.GetValueAsDouble(Constants::KW_SeparationPointObstacles, m_dsepPointObstacles);
	m_dsepSegmentObstacles = params.GetValueAsDouble(Constants::KW_SeparationSegmentObstacles, m_dsepSegmentObstacles);

	auto data = params.GetData( Constants::KW_Grid );
	if ( data && data->m_params )
	    m_grid.SetupFromParams( *( data->m_params ) );
	
	auto name = params.GetValue( Constants::KW_ObstaclesCollisionMeshFile );
	if ( name )
	    TriMeshReader( name, m_tmeshObstaclesCollision );
	name = params.GetValue( Constants::KW_ObstaclesDrawMeshFile );
	if ( name )
	    TriMeshReader( name, m_tmeshObstaclesDraw );
	name = params.GetValue( Constants::KW_TerrainMeshFile );
	if ( name )
	    TriMeshReader( name, m_tmeshTerrain );
	
	data = params.GetData( Constants::KW_Boundaries );
	if ( data && data->m_params )
	    AddBoundaries( data->m_params->GetValueAsDouble( Constants::KW_Thickness, Constants::SCENE_BOUNDARY_THICKNESS ),
			   data->m_params->GetValueAsDouble( Constants::KW_Height, Constants::SCENE_BOUNDARY_HEIGHT ) );
	
	
	const double eps = params.GetValueAsDouble( Constants::KW_AdjustGrid, INFINITY );
	if ( eps != INFINITY )
	    AdjustGrid( eps );

	if(m_tmeshTerrain.GetNrVertices() == 0)
	    m_tmeshTerrain.AddBox2D(m_grid.GetMin()[0], m_grid.GetMin()[1],  m_grid.GetMax()[0], m_grid.GetMax()[1]);

	ComputeAllOccupiedCells();
	
	
    }
    
    void Scene::AdjustGrid( const double eps )
    {
	const int           n = m_grid.GetNrDims();
	const int           nrDimsToAdjust = 2;
	const double        *gmin          = m_grid.GetMin();
	const double        *gmax          = m_grid.GetMax();
	const double        *omin          = m_tmeshObstaclesCollision.GetBoundingBoxMin();
	const double        *omax          = m_tmeshObstaclesCollision.GetBoundingBoxMax();
	
	std::vector<double> pmin;
	std::vector<double> pmax;
	
	pmin.resize( n );
	pmax.resize( n );
	
	for ( int i = 0; i < n && i < nrDimsToAdjust; ++i )
	{
	    pmin[i] = omin[i] - eps;
	    pmax[i] = omin[i] + eps;
	    if ( gmin[i] < pmin[i] )
		pmin[i] = gmin[i];
	    if ( gmax[i] > pmax[i] )
		pmax[i] = gmax[i];
	}
	for ( int i = nrDimsToAdjust; i < n; ++i )
	{
	    pmin[i] = gmin[i];
	    pmax[i] = gmax[i];
	}
	
	m_grid.Setup( n, m_grid.GetDims(), &pmin[0], &pmax[0] );
    }

    double Scene::GetCellClearance(const Id cid)
    {
	auto iter = m_cacheClearanceCells.find(cid);
	if(iter != m_cacheClearanceCells.end())
	    return iter->second;

	
	std::vector<double> bbox(2 * m_grid.GetNrDims());	
	TriMeshDefault tmesh;

	m_grid.GetCellFromId(cid, &bbox[0]);
	if(m_grid.GetNrDims() == 2)
	    tmesh.AddBox2D(bbox[0], bbox[1], bbox[2], bbox[3]);
	else
	    tmesh.AddBox(bbox[0], bbox[1], bbox[2], bbox[3], bbox[4], bbox[5]);
	auto res = tmesh.Distance(NULL, NULL, &m_tmeshObstaclesCollision, NULL, NULL);

	m_cacheClearanceCells.insert(std::make_pair(cid, res));

	return res;
	
    }
    
    bool Scene::IsCellInCollision(const Id cid)
    {
	auto iter = m_cacheCollisionCells.find(cid);
	if(iter != m_cacheCollisionCells.end())
	    return iter->second;

	std::vector<double> bbox(2 * m_grid.GetNrDims());	
	TriMeshDefault tmesh;

	m_grid.GetCellFromId(cid, &bbox[0]);
	if(m_grid.GetNrDims() == 2)
	    tmesh.AddBox2D(bbox[0], bbox[1], bbox[2], bbox[3]);
	else
	    tmesh.AddBox(bbox[0], bbox[1], bbox[2], bbox[3], bbox[4], bbox[5]);
	auto res = IsMeshInCollision(tmesh);

	m_cacheCollisionCells.insert(std::make_pair(cid, res));
	
	return res;
    }
    
    bool Scene::IsCellSegmentInCollision(const Id cid1, const Id cid2)
    {
	if(cid1 == cid2)
	    return IsCellInCollision(cid1);
	
	Id cidMin;
	Id cidMax;
	MinMax<Id>(cid1, cid2, cidMin, cidMax);

	auto iter = m_cacheSegmentCollisionCells.find(std::make_pair(cidMin, cidMax));
	if(iter != m_cacheSegmentCollisionCells.end())
	    return iter->second;

	std::vector<double> p1(m_grid.GetNrDims());
	std::vector<double> p2(m_grid.GetNrDims());
	std::vector<double> p(m_grid.GetNrDims());
	

	m_grid.GetCellCenterFromId(cid1, &p1[0]);
	m_grid.GetCellCenterFromId(cid2, &p2[0]);

	auto d = Algebra::PointDistance(m_grid.GetNrDims(), &p1[0], &p2[0]);	
	auto step = m_grid.GetMinUnit();
	auto nrSteps = std::ceil(d / step);
	bool coll = false;
	
	for(int i = 0; i <= nrSteps && coll == false; ++i)
	{
	    auto t = (i + 0.0) / nrSteps;	    
	    Algebra::VecLinearInterpolation(m_grid.GetNrDims(), &p1[0], (1 - t), &p2[0], t, &p[0]);
	    coll = IsCellInCollision( m_grid.GetCellId(&p[0]));   
	}

	m_cacheSegmentCollisionCells.insert(std::make_pair(std::make_pair(cidMin, cidMax), coll));
		    
/*	for(int i = 0; i < cids.size() - 1; ++i)
	{
	    for(int j = i + 1; j < cids.size() - 1; ++j)
	    {
		MinMax<Id>(cids[i], cids[j], cidMin, cidMax);
		m_cacheSegmentCollisionCells.insert(std::make_pair(std::make_pair(cidMin, cidMax), false));		
	    }
	    MinMax<Id>(cids[i], cids.back(), cidMin, cidMax);
	    m_cacheSegmentCollisionCells.insert(std::make_pair(std::make_pair(cidMin, cidMax), coll));		
	}
*/	
	return coll;	
    }
    

    bool Scene::IsPointInCollision(const double p[], const double dtol)
    {
	TriMeshDefault tmesh;
	
	if(m_grid.GetNrDims() == 2)
	    tmesh.AddBox2D(p[0] - 0.5 * dtol, p[1] - 0.5 * dtol, p[0] + 0.5 * dtol, p[1] + 0.5 * dtol);
	else
	    tmesh.AddBox(p[0] - 0.5 * dtol, p[1] - 0.5 * dtol,  p[2]  - 0.5 * dtol, p[0] + 0.5 * dtol, p[1] + 0.5 * dtol, p[2] + 0.5 * dtol);

	return IsMeshInCollision(tmesh);	
    }

    bool Scene::IsSegmentInCollision(const double p1[], const double p2[], const double dtol)
    {
	TriMeshDefault tmesh;

	auto dim = GetGrid()->GetNrDims();
	auto d  = Algebra::PointDistance(dim, p1, p2);

	if(d <= Constants::EPSILON)
	    return false;
	
	auto dmax = 0.5 * dtol;
	auto z1  = dim == 2 ? 0.0 : p1[2];
	auto z2  = dim == 2 ? 0.0 : p2[2];
	const double xaxis[] = {1, 0, 0};
	const double other[] = {(p2[0] - p1[0]) / d, (p2[1] - p1[1]) / d, (z2 - z1) / d};
	
	double TR[Algebra3D::TransRot_NR_ENTRIES];
	
	if(dim == 3)
	    tmesh.AddBox(-0.5 * d - dmax, -dmax, -dmax,  0.5 * d + dmax,  dmax,  dmax);
	else
	    tmesh.AddBox2D(-0.5 * d - dmax, -dmax,   0.5 * d + dmax,  dmax);
		
	TR[0] = 0.5 * (p1[0] + p2[0]);
	TR[1] = 0.5 * (p1[1] + p2[1]);
	TR[2] = 0.5 * (z1 + z2);
	Algebra3D::FromToUnitAxisAsRot(xaxis, other, &TR[Algebra3D::Trans_NR_ENTRIES]);
	tmesh.ApplyTransRot(0, tmesh.GetNrVertices() - 1, TR);
	
	return IsMeshInCollision(tmesh);	
    }

    
    bool Scene::IsMeshInCollision(TriMesh &tmesh) 
    {
	return tmesh.Collision(NULL, NULL, &m_tmeshObstaclesCollision, NULL, NULL);
    }

    double Scene::GetPointClearance(const double p[], const double dtol)
    {
	TriMeshDefault tmesh;
	PointAsMesh(p, dtol, tmesh);
	return GetMeshClearance(tmesh);	
    }

    double Scene::GetSegmentClearance(const double p1[], const double p2[], const double dtol)
    {
	TriMeshDefault tmesh;
	SegmentAsMesh(p1, p2, dtol, tmesh);
	return GetMeshClearance(tmesh);
    }
        
    double Scene::GetMeshClearance(TriMesh &tmesh) 
    {
	return tmesh.Distance(NULL, NULL, &m_tmeshObstaclesCollision, NULL, NULL);
    }

    void Scene::PointAsMesh(const double p[], const double dtol, TriMesh &tmesh)
    {
	if(m_grid.GetNrDims() == 2)
	    tmesh.AddBox2D(p[0] - 0.5 * dtol, p[1] - 0.5 * dtol, p[0] + 0.5 * dtol, p[1] + 0.5 * dtol);
	else
	    tmesh.AddBox(p[0] - 0.5 * dtol, p[1] - 0.5 * dtol,  p[2]  - 0.5 * dtol, p[0] + 0.5 * dtol, p[1] + 0.5 * dtol, p[2] + 0.5 * dtol);
    }

    void Scene::SegmentAsMesh(const double p1[], const double p2[], const double dtol, TriMesh &tmesh)
    {
	auto dim = GetGrid()->GetNrDims();
	auto d  = Algebra::PointDistance(dim, p1, p2);
	
	if(d <= Constants::EPSILON)
	{
	    PointAsMesh(p1, dtol, tmesh);	    
	    return;
	}
	
	auto dmax = 0.5 * dtol;
	auto z1  = dim == 2 ? 0.0 : p1[2];
	auto z2  = dim == 2 ? 0.0 : p2[2];
	const double xaxis[] = {1, 0, 0};
	const double other[] = {(p2[0] - p1[0]) / d, (p2[1] - p1[1]) / d, (z2 - z1) / d};
	
	double TR[Algebra3D::TransRot_NR_ENTRIES];
	
	if(dim == 3)
	    tmesh.AddBox(-0.5 * d - dmax, -dmax, -dmax,  0.5 * d + dmax,  dmax,  dmax);
	else
	    tmesh.AddBox2D(-0.5 * d - dmax, -dmax,   0.5 * d + dmax,  dmax);
	
	TR[0] = 0.5 * (p1[0] + p2[0]);
	TR[1] = 0.5 * (p1[1] + p2[1]);
	TR[2] = 0.5 * (z1 + z2);
	Algebra3D::FromToUnitAxisAsRot(xaxis, other, &TR[Algebra3D::Trans_NR_ENTRIES]);
	tmesh.ApplyTransRot(0, tmesh.GetNrVertices() - 1, TR);
    }

    void Scene::SampleValidPosition(double p[])
    {
	do
	    SamplePosition(p);
	while(IsPointInCollision(p));	
    }
    
    void Scene::ComputeAllOccupiedCells(void)
    {
	m_allCellsOccupied.clear();

	auto n = m_grid.GetNrCells();
	for(int i = 0; i < n; ++i)
	    if(IsCellInCollision(i))
		m_allCellsOccupied.insert(i);
	
    }

    void Scene::DrawOccupied(void)
    {
	std::vector<double> cmin(m_grid.GetNrDims());
	std::vector<double> cmax(m_grid.GetNrDims());

	void (*fnDraw)(const double[], const double []);
	
	if(m_grid.GetNrDims())
	    fnDraw = GDrawBox2D;
	else
	    fnDraw = GDrawBox3D;
	
	for(auto & cid : m_allCellsOccupied)
	{
	    m_grid.GetCellFromId(cid, &cmin[0], &cmax[0]);
	    fnDraw(&cmin[0], &cmax[0]);		
	}
    }
    
}
