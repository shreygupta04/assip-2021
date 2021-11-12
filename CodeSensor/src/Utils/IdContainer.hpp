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

#ifndef Antipatrea__IdContainer_HPP_
#define Antipatrea__IdContainer_HPP_

#include "Utils/Constants.hpp"

namespace Antipatrea
{
    typedef int Id;

    class IdContainer
    {
    public:
	IdContainer(void) : m_id(Constants::ID_UNDEFINED)
	{
	}
	
	virtual ~IdContainer(void)
	{
	}
	
	virtual Id GetId(void) const
	{
	    return m_id;
	}
	
	virtual void SetId(const Id id)
	{
	    m_id = id;
	}
	
	
    protected:
	Id m_id;
	
    };    
}


#endif
