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
 
#ifndef Antipatrea__GTexture_HPP_
#define Antipatrea__GTexture_HPP_

#include "Utils/Definitions.hpp"
#include <cstdio>

namespace Antipatrea
{
    class GTexture
    {
    public:
	GTexture(void);	

	virtual ~GTexture(void);

	const char* GetFileName(void) const
	{
	    return m_fname;
	}
	
	
	unsigned int GetId(void) const
	{
	    return m_id;
	}
	
	unsigned char* GetImage(void) const
	{
	    return m_image;
	}
	void SetFileName(const char fname[]);
	void ReadBMP(FILE *in);
	void ReadPPM(FILE *in);
	void ReadPNG(FILE *in);


	static void ManualCoords(void);	
	static void AutomaticCoords(void);
	
	void Use(void);
	
    protected:    
	void ToRGBA(void);
	
	unsigned int   m_id;
	unsigned char *m_image;	
	int            m_sizeX;
	int            m_sizeY;
	char          *m_fname;
	bool           m_rgba;	
    };

    ClassContainer(GTexture, m_gTexture);
    
}

#endif









