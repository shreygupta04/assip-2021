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
 
#include "Utils/Stats.hpp"
#include <string>
#include <iomanip>

namespace Antipatrea
{
    
    Stats* Stats::m_singleton = new Stats();

    double Stats::MeanStdSorted(const int n, const double vals[],  const double poff,  double &stddev) const
    {
	if(n == 0)
	{
	    stddev = 0.0;
	    return 0.0;
	}
	
	auto n1  = std::ceil(poff * n)  - 1;
	auto n2  = std::ceil((1 - poff) * n) - 1;
	
	double s = 0.0;
	for(int i = n1; i <= n2; ++i)
	    s += vals[i];
	auto u  = s / (n2 - n1 + 1);

	s = 0.0;	
	for(int i = n1; i <= n2; ++i)
	    s += (vals[i] - u) * (vals[i] - u);
	stddev  = sqrt(s / (n2 - n1));

	return u;
    }
    

    double Stats::GetValue(const char id[]) 
    {
	auto iter = m_values.find(id);
	if(iter != m_values.end())
	    return iter->second;
	return 0.0;
    }
    
    void Stats::SetValue(const char id[], const double t)
    {
	auto iter = m_values.find(id);
	if(iter != m_values.end())
	    iter->second = t;
	else
	    m_values.insert(std::make_pair(id, t));
    }
    
    double Stats::AddValue(const char id[], const double t)
    {
	auto iter = m_values.find(id);
	if(iter != m_values.end())
	{
	    iter->second += t;
	    return iter->second;
	}
	else
	{
	    m_values.insert(std::make_pair(id, t));
	    return t;
	}
    }
    
    void Stats::Print(std::ostream & out) const
    {
	for(auto iter = m_values.begin(); iter != m_values.end(); iter++)
	    out << std::setw(30) << std::left << iter->first.c_str() << " " << iter->second << std::endl;
    }
    
    Status Stats::Read(std::istream &in)
    {
	std::string id;
	double      val;
	
	while(in >> id >> val)
	    AddValue(id.c_str(), val);
	return STATUS_OK;
    }

    void Stats::AddToParams(Params &p) const
    {
	for(auto & iter : m_values)
	    p.SetValue(iter.first.c_str(), std::to_string(iter.second).c_str());
    }
    
    
}



