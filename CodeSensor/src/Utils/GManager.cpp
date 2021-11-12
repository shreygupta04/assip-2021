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

#include "Utils/GManager.hpp"
#include "Utils/Constants.hpp"
#include "Utils/Logger.hpp"
#include "Utils/Params.hpp"
#include "Utils/Stats.hpp"
#include <cmath>
#include <cstdlib>
#include <cstring>

namespace Antipatrea
{
    GManager *m_gManager = NULL;
    
    void GManager::CallbackEventOnActiveMouseMove(int x, int y)
    {
	if (m_gManager)
	{
	    if (m_gManager->HandleEventOnActiveMouseMove(x, y))
		glutPostRedisplay();
	    m_gManager->m_mousePrevX = x;
	    m_gManager->m_mousePrevY = y;
	}
    }
    
    void GManager::CallbackEventOnPassiveMouseMove(int x, int y)
    {
	if (m_gManager)
	{
	    if (m_gManager->HandleEventOnPassiveMouseMove(x, y))
		glutPostRedisplay();
	    m_gManager->m_mousePrevX = x;
	    m_gManager->m_mousePrevY = y;
	}
    }
    
    void GManager::CallbackEventOnMouse(int button, int state, int x, int y)
    {
	if (m_gManager)
	{
	    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && m_gManager->HandleEventOnMouseLeftBtnDown(x, y))
		glutPostRedisplay();
	    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && m_gManager->HandleEventOnMouseLeftBtnUp(x, y))
		glutPostRedisplay();
	    
	    m_gManager->m_mousePrevX = x;
	    m_gManager->m_mousePrevY = y;
	}
    }
    
    void GManager::CallbackEventOnTimer(int id)
    {
	if (m_gManager)
	{
	    m_gManager->HandleEventOnTimer();
	    glutTimerFunc(m_gManager->m_timer, CallbackEventOnTimer, id);
	    glutPostRedisplay();
	}
    }
    
    void GManager::CallbackEventOnIdle(void)
    {
	if (m_gManager && m_gManager->HandleEventOnIdle())
	    glutPostRedisplay();
    }
    
    void GManager::CallbackEventOnSpecialKeyPress(int key, int x, int y)
    {
	if (m_gManager && m_gManager->HandleEventOnSpecialKeyPress(key))
	    glutPostRedisplay();
    }
    
    void GManager::CallbackEventOnNormalKeyPress(unsigned char key, int x, int y)
    {
	if (m_gManager && m_gManager->HandleEventOnNormalKeyPress(key))
	    glutPostRedisplay();
    }
    
    void GManager::CallbackEventOnSpecialKeyUp(int key, int x, int y)
    {
	if (m_gManager && m_gManager->HandleEventOnSpecialKeyUp(key))
	    glutPostRedisplay();
    }
    
    void GManager::CallbackEventOnNormalKeyUp(unsigned char key, int x, int y)
    {
	if (m_gManager && m_gManager->HandleEventOnNormalKeyUp(key))
	    glutPostRedisplay();
    }
    
    void GManager::CallbackEventOnDisplay(void)
    {
	if (m_gManager)
	{
	    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	    glClearDepth(1.0);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	    
	    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	    glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();

	    const bool is3D = HasAllFlags(m_gManager->m_menuItems[m_gManager->m_gCompDraw.MENU_DRAW_3D]->GetFlags(), GMenuItem::FLAG_ON);
	    
	    if (is3D)
		gluPerspective(m_gManager->m_values[INDEX_PERSPECTIVE_ANGLE], (double)glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT),
			       m_gManager->m_values[INDEX_PERSPECTIVE_NEAR_PLANE], m_gManager->m_values[INDEX_PERSPECTIVE_FAR_PLANE]);
	    else
		glOrtho(m_gManager->m_values[INDEX_MINX], m_gManager->m_values[INDEX_MAXX], m_gManager->m_values[INDEX_MINY], m_gManager->m_values[INDEX_MAXY],
			m_gManager->m_values[INDEX_ORTHO_NEAR_PLANE], m_gManager->m_values[INDEX_ORTHO_FAR_PLANE]);
	    
	    glMatrixMode(GL_MODELVIEW);
	    glLoadIdentity();
	    
	    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	    
	    if (HasAllFlags(m_gManager->m_menuItems[m_gManager->m_gCompDraw.MENU_DRAW_TEXTURES]->GetFlags(), GMenuItem::FLAG_ON))
		glEnable(GL_TEXTURE_2D);
	    else
		glDisable(GL_TEXTURE_2D);
	    
	    glEnable(GL_DEPTH_TEST);
	    glShadeModel(GL_SMOOTH);
	    
	    if (is3D)
	    {
		double m[16];
		m_gManager->m_gCompCamera.GetCamera()->GetModelViewMatrixOpenGL(m);
		glMultMatrixd(m);
		GDraw3D();
		GDrawIllumination(m_gManager->m_gIllumination);
	    }
	    else
		GDraw2D();
	    
	    m_gManager->HandleEventOnDisplay();
	    
	    if (HasAllFlags(m_gManager->m_menuItems[m_gManager->m_gCompDraw.MENU_DRAW_SAVE_FRAMES]->GetFlags(), GMenuItem::FLAG_ON))
		m_gManager->m_gCompDraw.SaveFrameAsImage();
	    
	    glutSwapBuffers();
	}
    }
    
    GManager::GManager(void)
    {
	
	m_idWindow = -1;
	m_timer = Constants::GRAPHICS_TIMER_INTERVAL;
	m_mousePrevX = 0;
	m_mousePrevY = 0;
	
	m_values.resize(NR_INDICES);
	m_values[INDEX_MINX] = Constants::GRID_MIN[0];
	m_values[INDEX_MINY] = Constants::GRID_MIN[1];
	m_values[INDEX_MAXX] = Constants::GRID_MAX[0];
	m_values[INDEX_MAXY] = Constants::GRID_MAX[1];
	m_values[INDEX_ORTHO_NEAR_PLANE] = Constants::GRAPHICS_ORTHO_NEAR_PLANE;
	m_values[INDEX_ORTHO_FAR_PLANE] = Constants::GRAPHICS_ORTHO_FAR_PLANE;
	m_values[INDEX_PERSPECTIVE_ANGLE] = Constants::GRAPHICS_PERSPECTIVE_ANGLE_IN_DEGREES;
	m_values[INDEX_PERSPECTIVE_NEAR_PLANE] = Constants::GRAPHICS_PERSPECTIVE_NEAR_PLANE;
	m_values[INDEX_PERSPECTIVE_FAR_PLANE] = Constants::GRAPHICS_PERSPECTIVE_FAR_PLANE;
	
	m_menuMain = Constants::ID_UNDEFINED;
	m_menuSelectedItem = Constants::ID_UNDEFINED;

	m_posClicked[0] = m_posClicked[1] = m_posClicked[2] = 0.0;

	m_gCompDraw.SetManager(this);	
	m_gCompCamera.SetManager(this);
	m_components.push_back(&m_gCompDraw);	
	m_components.push_back(&m_gCompCamera);	
    }
    
    
    GManager::~GManager(void)
    {
	if (m_idWindow >= 0)
	    glutDestroyWindow(m_idWindow);
    }
    
    void GManager::SetupFromParams(Params &p)
    {
	m_values[INDEX_ORTHO_NEAR_PLANE] = p.GetValueAsDouble(Constants::KW_OrthoNearPlane, m_values[INDEX_ORTHO_NEAR_PLANE]);
	m_values[INDEX_ORTHO_FAR_PLANE] = p.GetValueAsDouble(Constants::KW_OrthoFarPlane, m_values[INDEX_ORTHO_FAR_PLANE]);
	m_values[INDEX_PERSPECTIVE_ANGLE] = p.GetValueAsDouble(Constants::KW_PerspectiveAngleInDegrees, m_values[INDEX_PERSPECTIVE_ANGLE]);
	m_values[INDEX_PERSPECTIVE_NEAR_PLANE] = p.GetValueAsDouble(Constants::KW_PerspectiveNearPlane, m_values[INDEX_PERSPECTIVE_NEAR_PLANE]);
	m_values[INDEX_PERSPECTIVE_FAR_PLANE] = p.GetValueAsDouble(Constants::KW_PerspectiveFarPlane, m_values[INDEX_PERSPECTIVE_FAR_PLANE]);
	m_timer = p.GetValueAsInt(Constants::KW_OnTimerInterval, m_timer);
	
	auto data = p.GetData(Constants::KW_Min);
	if (data)
	{
	    if (data->m_values.size() > 0)
		m_values[INDEX_MINX] = StrToDouble(data->m_values[0]->c_str());
	    if (data->m_values.size() > 1)
		m_values[INDEX_MINY] = StrToDouble(data->m_values[0]->c_str());
	}
	
	data = p.GetData(Constants::KW_Max);
	if (data)
	{
	    if (data->m_values.size() > 0)
		m_values[INDEX_MAXX] = StrToDouble(data->m_values[0]->c_str());
	    if (data->m_values.size() > 1)
		m_values[INDEX_MAXY] = StrToDouble(data->m_values[0]->c_str());
	}

	m_gCompDraw.SetupFromParams(p);	
	m_gCompCamera.SetupFromParams(p);
	data = p.GetData(Constants::KW_Illumination);
	if (data && data->m_params)
	    m_gIllumination.SetupFromParams(*(data->m_params));
    }
    
    void GManager::MainLoop(const char *const title, const int width, const int height)
    {
	m_gManager = this;
	
	static int argc = 1;
	static char *args = (char *)"args";
	
	glutInit(&argc, &args);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	m_idWindow = glutCreateWindow(title);
	
	PrepareMenuMain();
	
	glutDisplayFunc(CallbackEventOnDisplay);
	glutMouseFunc(CallbackEventOnMouse);
	glutMotionFunc(CallbackEventOnActiveMouseMove);
	glutPassiveMotionFunc(CallbackEventOnPassiveMouseMove);
	glutIdleFunc(CallbackEventOnIdle);
	glutTimerFunc(0, CallbackEventOnTimer, 0);
	glutKeyboardFunc(CallbackEventOnNormalKeyPress);
	glutSpecialFunc(CallbackEventOnSpecialKeyPress);
	glutKeyboardUpFunc(CallbackEventOnNormalKeyUp);
	glutSpecialUpFunc(CallbackEventOnSpecialKeyUp);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	
	GDrawLineWidth(4);
	
	glutMainLoop();
    }
    
    void GManager::Help(void)
    {
    }
    
    void GManager::MousePosFromScreenToWorld(const int x, const int y, double *const wx, double *const wy, double *const wz)
    {
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ = 0;
	double px = 0, py = 0, pz = 0;
	
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);
	
	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &px, &py, &pz);
	
	if (wx)
	    *wx = px;
	if (wy)
	    *wy = py;
	if (wz)
	    *wz = pz;
    }
    
    
    void GManager::CallbackEventOnMenu(int item)
    {
	if (m_gManager)
	    m_gManager->m_menuSelectedItem = item;
    }
    
    int GManager::CreateMenu(void)
    {
	return glutCreateMenu(CallbackEventOnMenu);
    }
    
    void GManager::SetMenu(const int menu)
    {
	glutSetMenu(menu);
    }
    
    void GManager::AddSubMenu(const char name[], const int menu)
    {
	glutAddSubMenu(name, menu);
    }
    
    void GManager::AddMenuEntry(const char name[], const int item)
    {
	glutAddMenuEntry(name, item);
    }
    
    void GManager::ChangeToMenuEntry(const int pos, const char name[], const int item)
    {
	glutChangeToMenuEntry(pos, name, item);
    }
    
    void GManager::PrepareMenuMain(void)
    {
	m_menuMain = CreateMenu();
	
	auto items = GetMenuItems();
	MENU_PAUSE = items->size();
	items->push_back(new GMenuItem("pause", GMenuItem::FLAG_OFF | GMenuItem::FLAG_TOGGLES));
	AddMenuEntry((*items)[MENU_PAUSE]->GetExtendedName(), MENU_PAUSE);
	
	for (auto &comp : m_components)
	{
	    auto id = comp->PrepareMenu();
	    SetMenu(m_menuMain);
	    AddSubMenu(comp->GetMenuName(), id);
	}
    }
    
    
    void GManager::HandleEventOnTimer(void)
    {
	if (m_menuSelectedItem >= 0)
	{
	    HandleEventOnMenu(m_menuSelectedItem);
	    m_menuSelectedItem = Constants::ID_UNDEFINED;
	}
	
	if (HasAllFlags(m_menuItems[MENU_PAUSE]->GetFlags(), GMenuItem::FLAG_ON) == false)
	    for (auto &comp : m_components)
		comp->HandleEventOnTimer();
    }
    
    void GManager::HandleEventOnDisplay(void)
    {
	for (auto &comp : m_components)
	    comp->HandleEventOnDisplay();
    }
    
    bool GManager::HandleEventOnMouseLeftBtnDown(const int x, const int y)
    {
	MousePosFromScreenToWorld( x, y, &m_posClicked[0], &m_posClicked[1], &m_posClicked[2]);

	bool res = false;
	for (auto &comp : m_components)
	    if(comp->HasMouseControl())
		res = comp->HandleEventOnMouseLeftBtnDown(x, y);
	return res;
    }
    
    bool GManager::HandleEventOnMouseLeftBtnUp(const int x, const int y)
    {
	bool res = false;	
	for (auto &comp : m_components)
	    if(comp->HasMouseControl())
		res = res || comp->HandleEventOnMouseLeftBtnUp(x, y);
	return res;
    }
    
    bool GManager::HandleEventOnActiveMouseMove(const int x, const int y)
    {
	bool res = false;	
	for (auto &comp : m_components)
	    if(comp->HasMouseControl())
		res = res || comp->HandleEventOnActiveMouseMove(x, y);
	return res;
    }
    
    bool GManager::HandleEventOnPassiveMouseMove(const int x, const int y)
    {
	bool res = false;	
	for (auto &comp : m_components)
	    if(comp->HasMouseControl())
		res = res || comp->HandleEventOnPassiveMouseMove(x, y);
	return res;
    }
    
    bool GManager::HandleEventOnNormalKeyPress(const int key)
    {
	if (key == 27) // escape key
	{
	    exit(0);
	    return true;
	}
	else if (glutGetModifiers() & GLUT_ACTIVE_ALT)
	{
	    switch (key)
	    {
	    case Constants::KEY_PRINT_STATS:
		Logger::m_out << *(Stats::GetSingleton()) << std::endl;
		return true;
	    };
	    
	    auto cur = m_mapKeysToMenuItems.find(key);
	    if (cur != m_mapKeysToMenuItems.end())
		return HandleEventOnMenu(cur->second);
	}

	bool res = false;	
	for (auto &comp : m_components)
	    if(comp->HasKeyboardControl())
		res = res || comp->HandleEventOnNormalKeyPress(key);
	return res;
    }
    
    bool GManager::HandleEventOnSpecialKeyPress(const int key)
    {
	if (key == GLUT_KEY_F1)
	{
	    Help();
	    return true;
	}
	
	bool res = false;
	for (auto &comp : m_components)
	    if(comp->HasKeyboardControl())
		res = res || comp->HandleEventOnSpecialKeyPress(key);
	return res;
    }
    
    bool GManager::HandleEventOnNormalKeyUp(const int key)
    {
	
	bool res = false;	
	for (auto &comp : m_components)
	    if(comp->HasKeyboardControl())
		res = res || comp->HandleEventOnNormalKeyUp(key);
	return res;
    }
    
    bool GManager::HandleEventOnSpecialKeyUp(const int key)
    {
	bool res = false;	
	for (auto &comp : m_components)
	    if(comp->HasKeyboardControl())
		res = res || comp->HandleEventOnSpecialKeyUp(key);
	return res;
    }
    
    bool GManager::HandleEventOnIdle(void)
    {
	bool res = false;
	
	for (auto &comp : m_components)
	    res = res || comp->HandleEventOnIdle();
	return res;
    }
    
    bool GManager::HandleEventOnMenu(const int item)
    {
	if (item == MENU_PAUSE)
	{
	    if (HasAllFlags(m_menuItems[item]->GetFlags(), GMenuItem::FLAG_TOGGLES))
	    {
		SetMenu(m_menuMain);
		m_menuItems[item]->SetFlags(FlipFlags(m_menuItems[item]->GetFlags(), GMenuItem::FLAG_ON));
		ChangeToMenuEntry(item - item + 1, m_menuItems[item]->GetExtendedName(), item);
		return true;
	    }
	}
	else
	{
	    for (auto &comp : m_components)
		if (comp->HandleEventOnMenu(item))
		    return true;
	}
	
	return false;
    }    
}
