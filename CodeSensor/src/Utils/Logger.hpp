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
 
#ifndef Antipatrea__Logger_HPP_
#define Antipatrea__Logger_HPP_

#include <ostream>

namespace Antipatrea
{
    class Logger
    {
    public:
	Logger(void)
	{
	}
	
	virtual ~Logger(void)
	{
	}
	
	static std::ostream & m_out;
	
	static int GetVerbosity(void)
	{
	    return m_verbosity;
	}
	
	
	static void SetVerbosity(const int verbosity)
	{
	    m_verbosity = verbosity;
	}
	
    protected:
	static int   m_verbosity;
	
    };
}


#endif
