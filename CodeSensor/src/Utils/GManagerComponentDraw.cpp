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

#include "Utils/GManagerComponentDraw.hpp"
#include "Utils/GManager.hpp"

namespace Antipatrea
{
    int GManagerComponentDraw::PrepareMenu(void)
    {
	GManagerComponent::PrepareMenu();
	
	auto items = GetManager()->GetMenuItems();

	MENU_DRAW_3D = items->size();
	items->push_back(new GMenuItem("3D", GMenuItem::FLAG_ON | GMenuItem::FLAG_TOGGLES));
	MENU_DRAW_TEXTURES = items->size();
	items->push_back(new GMenuItem("textures", GMenuItem::FLAG_ON | GMenuItem::FLAG_TOGGLES));
	MENU_DRAW_SAVE_FRAME = items->size();
	items->push_back(new GMenuItem("save frame", GMenuItem::FLAG_OFF));
	MENU_DRAW_SAVE_FRAMES = items->size();
	items->push_back(new GMenuItem("save frames", GMenuItem::FLAG_OFF | GMenuItem::FLAG_TOGGLES));

	m_menuLastItem = MENU_DRAW_SAVE_FRAMES;

	for(int i = MENU_DRAW_3D; i <= m_menuLastItem; ++i)
	    if(i == MENU_DRAW_SAVE_FRAME)
		GetManager()->AddMenuEntry((*items)[i]->GetName(), i);
	    else
		GetManager()->AddMenuEntry((*items)[i]->GetExtendedName(), i);
       
	
	return m_menu;	
    }
        
    
    void GManagerComponentDraw::SaveFrameAsImage(void)
    {
	char fname[50];
	sprintf(fname, "frames_%05d.ppm", m_nrFrames++);
	SaveFrameAsImage(fname);
	
	char cmd[300];
	sprintf(cmd, "convert -quality 100 %s %s.jpg", fname, fname);
	auto ignore = system(cmd);
	sprintf(cmd, "\\rm %s", fname);
	ignore = system(cmd);
    }
    
    void GManagerComponentDraw::SaveFrameAsImage(const char fname[])
    {
	auto width = glutGet(GLUT_WINDOW_WIDTH);
	auto height = glutGet(GLUT_WINDOW_HEIGHT);
	
	auto temp = new char[3 * width * height];
	auto image = new char[3 * width * height];
	
	FILE *fp = fopen(fname, "w");
	
	printf("Writing %s\n", fname);
	
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, temp);
	
	int a, b, row_sz = 3 * width;
	// Reverse rows
	for (int i = 0; i < height; i += 1)
	{
	    for (int j = 0; j < width; j += 1)
	    {
		a = i * row_sz + 3 * j;
		b = (height - i - 1) * row_sz + 3 * j;
		image[a] = temp[b];
		image[a + 1] = temp[b + 1];
		image[a + 2] = temp[b + 2];
	    }
	}
	fprintf(fp, "P6\n");
	fprintf(fp, "%i %i\n 255\n", width, height);
	fwrite(image, sizeof(char), 3 * width * height, fp);
	fclose(fp);
	delete[] temp;
	delete[] image;
    }
    
    
    bool GManagerComponentDraw::HandleEventOnMenu(const int item)
    {
	if (item == MENU_DRAW_SAVE_FRAME)
	    SaveFrameAsImage();
	return GManagerComponent::HandleEventOnMenu(item);
    }    
}
