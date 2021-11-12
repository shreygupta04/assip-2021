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
 
#ifndef Antipatrea__ContainerQueue_HPP_
#define Antipatrea__ContainerQueue_HPP_

#include "Utils/Container.hpp"
#include <queue>

namespace Antipatrea
{
    template <typename Key>
    class ContainerQueue : public Container<Key>
    {
    public:
	ContainerQueue(void) : Container<Key>()
	{
	}

	virtual ~ContainerQueue(void)
	{
	}
	
	virtual bool IsEmpty(void) const
	{
	    return m_queue.empty();
	}
	
	
	virtual Key  GetTop(void) const
	{
	    return m_queue.front();
	}
	
	
	virtual void Insert(const Key & key)
	{
	    m_queue.push(key);
	}
	

	virtual void RemoveOneElement(void)
	{
	    m_queue.pop();
	}

	virtual void Clear(void)
	{
	    m_queue = std::queue<Key>();
	}
	

    protected:
	std::queue<Key> m_queue;
    };
    
	
}

#endif
