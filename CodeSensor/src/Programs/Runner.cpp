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
 
#include "Utils/DLHandler.hpp"
#include "Utils/RndEngine.hpp"
#include "Utils/Logger.hpp"
#include "Utils/Misc.hpp"
#include "Utils/Writer.hpp"
#include <fstream>

using namespace Antipatrea;

/**
 *@brief Program to run other programs.
 *@remarks
 *  - First argument is the name of the program that should be run.
 *  - The other arguments are arguments to that program.
 *  - Runner looks for the name of the program in the list of the loaded symbols.
 *    - if it finds it, it runs the program passing along the arguments.
 *    - otherwise, it displays a warning message.
 *  - In order for Runner to be able to find the program, it should be of the form
 *   <center> <tt>extern "C" int ProgramName(int argc, char **argv)</tt></center>
 *   where <tt>ProgramName</tt> could be an valid function name.
 */
int main(int argc, char **argv)
{
    typedef int (*MainFcn) (int, char **);

    Writer::OutputFormat(Logger::m_out);

    auto seed = RndEngine::GetSingleton()->UseRandomSeed();
    //RndEngine::GetSingleton()->SetSeed(1288043937);//3252264742);//740687243);//4111786722);//3428875618);//4093986425);
    

    std::ofstream out("seed.txt");
    out << seed << std::endl;
    out.close();
    
    if(argc < 2)
	Logger::m_out << "usage: Runner <program_name> [list_of_program_args]" << std::endl;
    else
    {
	MainFcn fcn = (MainFcn) Antipatrea::DLHandler::GetSymbol(argv[1]);
	if(fcn)
	{
	    Logger::m_out << "Running program <" << argv[1] << ">" << std::endl << std::endl;
	    return fcn(argc - 1, &(argv[1]));
	}
	else
	    Logger::m_out << "Program <" << argv[1] << "> not found" << std::endl;
    }    

    return 0;
}
