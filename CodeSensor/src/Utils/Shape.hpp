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
 
#ifndef Antipatrea__Shape_HPP_
#define Antipatrea__Shape_HPP_

#include "Utils/Component.hpp"
#include "Utils/Grid.hpp"
#include "Utils/IdContainer.hpp"

namespace Antipatrea
{
    class TriMesh;

    class Shape : public Component
    {
    public:
	Shape(void) : Component()
	{
	}
	
	virtual ~Shape(void)
	{
	}

	virtual void Info(std::ostream & out) const
	{
	    Component::Info(out);
	    out << "Dim = " << GetDim() << std::endl;
	}
	

	virtual int GetDim(void) const = 0;
	
	virtual void GetRepresentativePoint(double p[]) = 0;
	
	virtual bool IsPointInside(const double p[]) = 0;
	
	virtual void SamplePointInside(double p[]) = 0;
	
	virtual void AddToTriMesh(TriMesh &tmesh) = 0;

	virtual void OccupiedGridCells(const Grid &grid, std::vector<Id> &cids) = 0;
		
	virtual void GetDrawTextPos(double p[])
	{
	    GetRepresentativePoint(p);
	}

	virtual void Draw(void)
	{
	}	
    };

    ClassContainer(Shape, m_shape);

}
#endif
