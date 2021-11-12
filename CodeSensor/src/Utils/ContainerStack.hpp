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
 
#ifndef Antipatrea__ContainerStack_HPP_
#define Antipatrea__ContainerStack_HPP_

#include "Utils/Container.hpp"
#include <stack>

namespace Antipatrea
{
    template <typename Key>
    class ContainerStack : public Container<Key>
    {
    public:
	ContainerStack(void) : Container<Key>()
	{
	}

	virtual ~ContainerStack(void)
	{
	}
	
	virtual bool IsEmpty(void) const
	{
	    return m_stack.empty();
	}
	
	
	virtual Key  GetTop(void) const
	{
	    return m_stack.top();
	}
	
	
	virtual void Insert(const Key & key)
	{
	    m_stack.push(key);
	}
	

	virtual void RemoveOneElement(void)
	{
	    m_stack.pop();
	}

	virtual void Clear(void)
	{
	    m_stack = std::stack<Key>();
	    
	}
	

    protected:
	std::stack<Key> m_stack;
	
    };
    
	
}

#endif
