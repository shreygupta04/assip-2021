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

#include "Utils/Misc.hpp"

namespace Antipatrea
{
    bool NextCounter(const int n, int vals[], const int max[])
    {
	int carry = 1;
	for(int i = n - 1; i >= 0; --i)
	{
	    vals[i] += carry;
	    carry = vals[i] >= max[i];
	    vals[i] = vals[i] % max[i];
	}
	
	return carry == 0;
    }
    

}

