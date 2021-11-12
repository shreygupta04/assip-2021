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
 
#ifndef Antipatrea__RndEngine_HPP_
#define Antipatrea__RndEngine_HPP_

#include "Utils/Definitions.hpp"
#include <random>

#include "Utils/Logger.hpp"

namespace Antipatrea
{
    class RndEngine
    {
    public:
	virtual void SetSeed(const unsigned int s)
	{
	    m_rnd.seed(s);

	    Logger::m_out << "RANDOM SEED = " << s << std::endl;
	    
	}
	
	virtual unsigned int UseRandomSeed(void);
	
	virtual double UniformReal(void)
	{
	    return m_uniform(m_rnd);
	}
	
	
	virtual double UniformReal(const double min, const double max)
	{
	    return min + (max - min) * UniformReal();
	}
	
	
	virtual long UniformInteger(const long min, const long max)
	{
	    return std::uniform_int_distribution<int>(min, max)(m_rnd);
	    
	}
	
	virtual bool UniformBoolean(void)
	{
	    return UniformInteger(0, 1);
	}
	
	virtual double NormalReal(const double mean, const double stddev)
	{
	    m_normal.param(std::normal_distribution<double>::param_type(mean, stddev));
	    return m_normal(m_rnd);
	}
	
	
	virtual void SamplePointInsideBox2D(const double min[2],
					    const double max[2],
					    double p[2]);
	
	virtual void SamplePointInsideTriangle2D(const double tA[2],
						 const double tB[2],
						 const double tC[2],
						 double p[2]);
	
	virtual void SamplePointInsideConvexPolygon2D(const int n,
						      const double poly[],
						      double p[2],
						      const double min[2] = NULL,
						      const double max[2] = NULL);
	
	virtual void SamplePointInsidePolygon2D(const int n,
						const double poly[],
						double p[2],
						const double min[2] = NULL,
						const double max[2] = NULL);
	
	virtual void SamplePointInsideCircle2D(const double center[2],
					       const double r,
					       double p[2]);
	
	virtual void SamplePointInsideBox3D(const double min[],
					    const double max[],
					    double p[]);
	
	virtual void SamplePointInsideBox(const int n,
					  const double min[],
					  const double max[],
					  double p[]);
	
    	
	virtual void SamplePointOnSphereSurface(const int    nrDims,
						const double center[],
						const double r,
						double       p[]);
	
	virtual void SamplePointInsideSphere(const int    nrDims,
					     const double center[],
					     const double r,
					     double       p[]);
	
	virtual void SamplePointOnEllipsoidSurface(const int    nrDims,
						   const double center[],
						   const double radii[],
						   double       p[]);
	
	virtual void SamplePointInsideEllipsoid(const int    nrDims,
						const double center[],
						const double radii[],
						double       p[]);
	
	
	static RndEngine* GetSingleton(void)
	{
	    return m_singleton;
	}
	
	
    protected:
        std::mt19937 m_rnd;
	std::uniform_real_distribution<double> m_uniform;
	std::normal_distribution<double> m_normal;
	
	static RndEngine *m_singleton;
    };
}

#endif











