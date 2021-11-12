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
 
#ifndef Antipatrea__DisjointSet_HPP_
#define Antipatrea__DisjointSet_HPP_

namespace Antipatrea
{
    class DisjointSet
    {
    public:
	DisjointSet(void) : m_nrComps(0)
	{
	}
	
	virtual ~DisjointSet(void)
	{
	}
	
	struct Elem
	{
	    int    m_rank;
	    Elem *m_parent;
	};
	
	virtual int GetNrComponents(void) const
	{
	    return m_nrComps;
	}
	
	virtual Elem* Make(void);
	
	virtual Elem* Find(Elem *elem);
	
	virtual void Join(Elem *x, Elem *y);
	
	virtual bool Same(Elem *x, Elem *y)
	{
	    return Find(x) == Find(y);
	}
	
    protected:
	int m_nrComps;
    };
}

#endif
