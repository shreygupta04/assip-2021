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
 
#include "Utils/RndEngine.hpp"
#include "Utils/Geometry.hpp"
#include <cstdio>
#include <ctime>
#include <vector>

namespace Antipatrea
{
    RndEngine *RndEngine::m_singleton = new RndEngine();
    
    unsigned int RndEngine::UseRandomSeed(void)
    {
	FILE        *fp = fopen("/dev/urandom", "r");    
	unsigned int s;
	int          size = 0;
	
	if(fp != NULL)
	{
	    size = fread(&s, sizeof(unsigned int), 1, fp);    
	    fclose(fp);    	        
	}
	else
	    s = (unsigned int) time(NULL);
	
	SetSeed(s);
	
	return s;
    }

    
    void RndEngine::SamplePointInsideBox2D(const double min[2], const double max[2], double p[2])
    {
	p[0] = UniformReal(min[0], max[0]);
	p[1] = UniformReal(min[1], max[1]);
    }
    
    void RndEngine::SamplePointInsideTriangle2D(const double tA[2], const double tB[2], const double tC[2], double p[2])
    {
	double a1 = UniformReal();
	double a2 = UniformReal();
	
	if (a1 + a2 > 1.0)
	{
	    a1 = 1 - a1;
	    a2 = 1 - a2;
	}
	
	p[0] = tA[0] + a1 * (tB[0] - tA[0]) + a2 * (tC[0] - tA[0]);
	p[1] = tA[1] + a1 * (tB[1] - tA[1]) + a2 * (tC[1] - tA[1]);
    }
    
    void RndEngine::SamplePointInsideConvexPolygon2D(const int n, const double poly[], double p[2], const double min[2], const double max[2])
    {
	double umin[2], umax[2];
	if (min == NULL || max == NULL)
	    BoundingBoxPolygon2D(n, poly, umin, umax);
	else
	{
	    umin[0] = min[0];
	    umin[1] = min[1];
	    umax[0] = max[0];
	    umax[1] = max[1];
	}
	
	do
	    SamplePointInsideBox2D(umin, umax, p);
	while (IsPointInsideConvexPolygon2D(p, n, poly) == false);
    }
    
    void RndEngine::SamplePointInsidePolygon2D(const int n, const double poly[], double p[2], const double min[2], const double max[2])
    {
	double umin[2], umax[2];
	if (min == NULL || max == NULL)
	    BoundingBoxPolygon2D(n, poly, umin, umax);
	else
	{
	    umin[0] = min[0];
	    umin[1] = min[1];
	    umax[0] = max[0];
	    umax[1] = max[1];
	}
	
	do
	   SamplePointInsideBox2D(umin, umax, p);
	while (IsPointInsidePolygon2D(p, n, poly) == false);
    }
    
    void RndEngine::SamplePointInsideCircle2D(const double center[2], const double r, double p[2])
    {
	const double s = r * sqrt(UniformReal());
	const double theta = UniformReal(0, 2 * M_PI);
	
	p[0] = s * cos(theta) + center[0];
	p[1] = s * sin(theta) + center[1];
    }

    
    void RndEngine::SamplePointInsideBox3D(const double min[],
					   const double max[],
					   double p[])
    {
	p[0] = UniformReal(min[0], max[0]);
	p[1] = UniformReal(min[1], max[1]);
	p[2] = UniformReal(min[2], max[2]);
    }
    
    
    void RndEngine::SamplePointInsideBox(const int n,
					 const double min[],
					 const double max[],
					 double p[])
    {
	for(int i = 0; i < n; ++i)
	    p[i] = UniformReal(min[i], max[i]);
    }
    
	
    void RndEngine::SamplePointOnSphereSurface(const int    nrDims,
					 const double center[],
					 const double r,
					 double       p[])
    {
	std::vector<double> radii;
	radii.resize(nrDims);
	std::fill(radii.begin(), radii.end(), r);
	SamplePointOnEllipsoidSurface(nrDims, center, &radii[0], p);
    }
    
    void RndEngine::SamplePointInsideSphere(const int nrDims,
				      const double center[],
				      const double r,
				      double       p[])
    {
	std::vector<double> radii;
	radii.resize(nrDims);
	std::fill(radii.begin(), radii.end(), r);
	SamplePointInsideEllipsoid(nrDims, center, &radii[0], p);
	
    }

    void RndEngine::SamplePointOnEllipsoidSurface(const int    nrDims,
					    const double center[],
					    const double radii[],
					    double       p[])
    {
	double s = 0.0;
	
	for(int i = 0; i < nrDims; i++)
	{
	    p[i] = NormalReal(0.0, 1.0);	
	    s   += p[i] * p[i];
	}    
	s = 1.0 / sqrt(s);    
	for(int i = 0; i < nrDims; ++i) 
	    p[i] = center[i] + p[i] * radii[i] * s;
    }

    void RndEngine::SamplePointInsideEllipsoid(const int    nrDims,
					 const double center[],
					 const double radii[],
					 double       p[])
    {
	double s = 0.0;
	
	for(int i = 0; i < nrDims; ++i)
	{
	    p[i] = NormalReal(0.0, 1.0);	
	    s   += p[i] * p[i];
	}    
	s = pow(UniformReal(), 1.0/nrDims) / sqrt(s);    
	for(int i = 0; i < nrDims; ++i) 
	    p[i] = center[i] + p[i] * radii[i] * s;
    }
    

}











