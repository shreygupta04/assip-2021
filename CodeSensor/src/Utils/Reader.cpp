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
 
#include "Utils/Reader.hpp"
#include "Utils/Logger.hpp"
#include <fstream>
#include <string>

namespace Antipatrea
{
    Status Reader::ReadDouble(std::istream & in, double & val)
    {
	std::string s;

	if((in >> s))
	{
	    val = std::stod(s);
	    return STATUS_OK;
	}
	
	else
	{
	    Logger::m_out << "error Reader::ReadDouble : could not read double value" << std::endl;
	    return STATUS_ERROR;
	}
	
    }
 
    Status Reader::ReadDoubles(std::istream &in, const int n, double vals[])
    {
	for(int i = 0; i < n; ++i)
	    if(ReadDouble(in, vals[i]) == STATUS_ERROR)
		return STATUS_ERROR;
	return STATUS_OK;	
    }
    
	
    
    Status Reader::ReadFromFile(const char fname[],
				std::ios_base::openmode mode)
    {
	std::ifstream in(fname, mode);
	if(!in.is_open())
	    return STATUS_ERROR;
	
	
	auto status = Read(in);
	in.close();
	
	return status;
    }
}



