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
 
#ifndef Antipatrea__Stats_HPP_
#define Antipatrea__Stats_HPP_

#include "Utils/Reader.hpp"
#include "Utils/Writer.hpp"
#include "Utils/Params.hpp"
#include <string>
#include <unordered_map>

namespace Antipatrea
{
    class Stats : public Reader,
		  public Writer
    {
    public:
	Stats(void) : Reader(),
		      Writer()
	{
	}
	
	virtual ~Stats(void)
	{
	}
	    

	virtual double MeanStdSorted(const int n, const double vals[],  const double poff,  double &stddev) const;
	
	virtual double GetValue(const char id[]);
	
	virtual void SetValue(const char id[], const double t);
	
	virtual double AddValue(const char id[], const double t);
	
	virtual void Print(std::ostream &out) const;
	
	virtual Status Read(std::istream &in);

	virtual void AddToParams(Params &p) const;
		
	static Stats *GetSingleton(void)
	{
	    return m_singleton;
	}
	
    protected:
	static Stats *m_singleton;
	
	std::unordered_map<std::string, double> m_values;
    };
}

#endif
