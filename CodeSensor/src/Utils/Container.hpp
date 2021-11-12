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
 
#ifndef Antipatrea__Container_HPP_
#define Antipatrea__Container_HPP_

namespace Antipatrea
{
    template <typename Key>
    class Container
    {
    public:
	Container(void)
	{
	}

	virtual ~Container(void)
	{
	}
	
	virtual bool IsEmpty(void) const = 0;
	
	virtual Key  GetTop(void) const = 0;
	
	virtual void Insert(const Key & key) = 0;

	virtual void RemoveOneElement(void) = 0;

	virtual void Clear(void) = 0;
	
	
    };
    
	
}

#endif
