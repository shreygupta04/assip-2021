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
 
#ifndef Antipatrea__DLHandler_HPP_
#define Antipatrea__DLHandler_HPP_

namespace Antipatrea
{
    namespace DLHandler
    {
	void* GetSymbol(void *handle, const char name[]);

	void* GetSymbol(const char name[]);
    }
}

#endif
