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

#include "Components/Scene2D.hpp"
#include "Components/Constants.hpp"
#include "External/ShewchukTriangle.hpp"
#include "Utils/Logger.hpp"
#include "Utils/GDraw.hpp"

namespace Antipatrea
{
    Scene2D::Scene2D(void)
    {
	m_grid.Setup(2, Constants::GRID_DIMS, Constants::GRID_MIN, Constants::GRID_MAX);
	m_allocatorPosition.SetDim(2);	
	m_heightObstacle = Constants::SCENE_OBSTACLE_HEIGHT;
    }
    
    void Scene2D::SetupFromParams(Params &params)
    {
	Polygon2D   *poly;
	std::string  str;
	
	const int n = params.GetValueAsInt(Constants::KW_NrObstacles, 0);
	m_heightObstacle = params.GetValueAsDouble(Constants::KW_ObstacleHeight, m_heightObstacle);
	
	Logger::m_out << " Scene should have " << n << " obstacles" << std::endl;
	
	for (int i = 0; i < n; ++i)
	{
	    str = ((std::string)Constants::KW_Obstacle) + std::to_string(i);
	    auto data = params.GetData(str.c_str());
	    if (data && data->m_params)
	    {
		if (data->m_params->HasParam(Constants::KW_Polygon2D))
		{
		    poly = new Polygon2D();
		    poly->SetupFromParams(*(data->m_params));
		    AddObstacle(poly);
		}
	    }
	}
	
	Scene::SetupFromParams(params);

	Logger::m_out << " scene has " << GetNrObstacles() << " obstacles " << std::endl;
	
	
    }
    
    
    void Scene2D::PrintObstacles(std::ostream & out) const
    {
	const int n = GetNrObstacles();
	
	out << Constants::KW_NrObstacles << " " << n << std::endl;
	for(int i = 0; i < n; ++i)
	{
	    out << Constants::KW_Obstacle << i << " { " << Constants::KW_Polygon2D << " [ ";
	    Writer::PrintValues<double>(out, *(GetObstacle(i)->GetVertices()));
	    out << " ] } " << std::endl;
	}
	
    }
    
    
    
    void Scene2D::AddObstacle(Polygon2D *const poly)
    {
	m_obstacles.push_back(poly);
	m_tmeshObstaclesCollision.AddPolygon(*poly);
	m_tmeshObstaclesDraw.AddExtrudedPolygon(*poly, 0, m_heightObstacle);
    }
    
    void Scene2D::AddBoundaries(const double thick, const double h)
    {
	m_tmeshObstaclesCollision.AddBoundaries2D(m_grid.GetMin()[0], m_grid.GetMin()[1], m_grid.GetMax()[0], m_grid.GetMax()[1], thick);
	m_tmeshObstaclesDraw.AddBoundaries(m_grid.GetMin()[0], m_grid.GetMin()[1], 0.0, m_grid.GetMax()[0], m_grid.GetMax()[1], h, thick);
    }
    
    void Scene2D::Triangulate(std::vector<double> &triVertices, std::vector<int> &triIndices, std::vector<int> &triNeighs, const double triAvgArea)
    {
	std::vector<double> vertices;
	std::vector<int> nrVerticesPerContour;
	std::vector<double> ptsInsideHoles;
	const int nrObsts = GetNrObstacles();
	Polygon2D *poly;
	
	const double *pmin = GetGrid()->GetMin();
	const double *pmax = GetGrid()->GetMax();
	
	// grid boundaries
	vertices.push_back(pmin[0]);
	vertices.push_back(pmin[1]);
	vertices.push_back(pmax[0]);
	vertices.push_back(pmin[1]);
	vertices.push_back(pmax[0]);
	vertices.push_back(pmax[1]);
	vertices.push_back(pmin[0]);
	vertices.push_back(pmax[1]);
	nrVerticesPerContour.push_back(4);
	
	// obstacles as holes
	ptsInsideHoles.resize(2 * nrObsts);
	for (int i = 0; i < nrObsts; ++i)
	{
	    poly = GetObstacle(i);
	    nrVerticesPerContour.push_back(poly->GetNrVertices());
	    poly->GetRepresentativePoint(&ptsInsideHoles[2 * i]);
	    
	    vertices.insert(vertices.end(), poly->GetVertices()->begin(), poly->GetVertices()->end());
	}
	
	Logger::m_out << "calling triangulation" << std::endl;
	
	TriangulatePolygonWithHoles2D(false, -1, triAvgArea, vertices.size() / 2, &vertices[0], &nrVerticesPerContour[0], ptsInsideHoles.size() / 2,
				      &ptsInsideHoles[0], &triVertices, &triIndices, &triNeighs);
	
	Logger::m_out << "done" << std::endl;
    }
    
    
    
    void Scene2D::DrawObstaclesPolygons(void)
    {
	for (int i = m_obstacles.size() - 1; i >= 0; --i)
	    GDrawPolygon2D(*(m_obstacles[i]));
    }
}
