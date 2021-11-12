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

#ifndef Antipatrea__Allocator_HPP_
#define Antipatrea__Allocator_HPP_

#include "Utils/Constants.hpp"
#include <algorithm>

namespace Antipatrea
{
    class Allocator 
    {
    public:
	Allocator(const int dim = 0) : m_dim(dim)
	{
	}
	
	virtual ~Allocator(void)
	{
	}
	
	virtual void SetupFromParams(Params &params)
	{
	    SetDim(params.GetValueAsInt(Constants::KW_Dim, GetDim()));
	}
	
	virtual void SetDim(const int dim)
	{
	    m_dim = dim;
	}
	
	virtual int GetDim(void) const
	{
	    return m_dim;
	}
	
	virtual double* New(void) const
	{
	    return new double[GetDim()];
	}
	
	virtual void Delete(double values[]) const
	{
	    if (values)
		delete[] values;
	}
	
	virtual void Copy(double dest[], const double src[]) const
	{
	    memcpy(dest, src, GetDim() * sizeof(double));
	}
	
	virtual double* Copy(const double values[]) const
	{
	    double *dest = New();
	    Copy(dest, values);
	    return dest;
	}
	
	virtual void Fill(double values[], const double val)
	{
	    std::fill(values, values + GetDim(), val);
	}

	virtual void Zero(double values[])
	{
	    Fill(values, 0);
	}
	
    protected:
	int m_dim;
    };
    
    ClassContainer(Allocator, m_allocator);
}

#endif
