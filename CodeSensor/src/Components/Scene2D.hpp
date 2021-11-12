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
 
#ifndef Antipatrea__Scene2D_HPP_
#define Antipatrea__Scene2D_HPP_

#include "Components/Scene.hpp"
#include "Utils/Misc.hpp"
#include "Utils/Polygon2D.hpp"
#include <ostream>

namespace Antipatrea
{
    class Scene2D : public Scene
    {
    public:
	Scene2D(void);
	
	virtual ~Scene2D(void)
	{
	    DeleteItems<Polygon2D *>(m_obstacles);
	}
	
	virtual void SetupFromParams(Params &params);
	
	virtual int GetNrObstacles(void) const
	{
	    return m_obstacles.size();
	}
	
	virtual const Polygon2D *GetObstacle(const int i) const
	{
	    return m_obstacles[i];
	}
	
	virtual Polygon2D *GetObstacle(const int i)
	{
	    return m_obstacles[i];
	}
	
	virtual void AddObstacle(Polygon2D *const obs);
	
	virtual void AddBoundaries(const double thick, const double h);
	
	virtual void Triangulate(std::vector<double> &triVertices, std::vector<int> &triIndices, std::vector<int> &triNeighs, const double triAvgArea);
	
	virtual void DrawObstaclesPolygons(void);
	
	virtual void PrintObstacles(std::ostream & out) const;

	virtual void DrawPoint(const double p[]) const
	{
	    GDrawSphere3D(p[0], p[1], 0.0, GDrawGetParam(GDRAW_POINT_SIZE));	    
	}
	
	virtual void DrawSegment(const double p1[], const double p2[]) const
	{
	    GDrawSegment2D(p1, p2);
	}
	
	
    protected:
	std::vector<Polygon2D *> m_obstacles;
	double m_heightObstacle;
    };
}

#endif
