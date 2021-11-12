PROJECT(Runner CXX C)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

IF(NOT CMAKE_BUILD_TYPE)
 set(CMAKE_BUILD_TYPE Release)
ENDIF()

#############################################################################
#Compiler flags for normal (debug) and optimized (release) builds
#
#
set(CMAKE_CXX_STANDARD 14) # <---- is this going to hurt things <jwm>

SET(CMAKE_CXX_FLAGS, "${CMAKE_CXX_FLAGS} -std=c++17" CACHE STRING "Flags" FORCE)

IF(NOT MSVC_IDE)

  SET(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -std=c++17" CACHE STRING
      "Flags used by the C++ compiler during debug builds." FORCE)
  SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -std=c++17"
      CACHE STRING "Flags used by the C++ compiler during release builds." FORCE)
  SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g -std=c++17" CACHE STRING
      "Flags used by the C++ compiler during release builds with debug information." FORCE)

  SET(CMAKE_C_FLAGS_DEBUG "-g -O0" CACHE STRING
      "Flags used by the C compiler during debug builds." FORCE)
  SET(CMAKE_C_FLAGS_RELEASE "-O3 -Wno-unused-result -DNDEBUG" CACHE STRING
      "Flags used by the C compiler during release builds." FORCE)
  SET(CMAKE_C_FLAGS_RELWITHDEBINFO "-O3 -g" CACHE STRING
      "Flags used by the C compiler during release builds with debug information." FORCE)
ENDIF(NOT MSVC_IDE)

IF(APPLE)
	LIST(APPEND CMAKE_SHARED_LINKER_FLAGS "-single_module")
ENDIF(APPLE)

ADD_DEFINITIONS(-D_USE_MATH_DEFINES)
add_definitions(
    -Wfatal-errors
    )
  
# added extra stuff for brew dependencies while using apple
IF(APPLE)
link_directories(
/lib
/usr/lib
/usr/local/lib
)
ENDIF(APPLE)


#############################################################################
INCLUDE_DIRECTORIES(src)
AUX_SOURCE_DIRECTORY(src/Utils      SRC_UTILS)
AUX_SOURCE_DIRECTORY(src/External   SRC_EXTERNAL)
AUX_SOURCE_DIRECTORY(src/External/PQP SRC_PQP)
AUX_SOURCE_DIRECTORY(src/Components SRC_COMPONENTS)
AUX_SOURCE_DIRECTORY(src/MP   SRC_MP)
AUX_SOURCE_DIRECTORY(src/Programs   SRC_PROGRAMS)
AUX_SOURCE_DIRECTORY(src/CreateScenes SRC_CREATE_SCENES)
AUX_SOURCE_DIRECTORY(src/MCTS SRC_MCTS)
AUX_SOURCE_DIRECTORY(src/MCTS/utils SRC_MCTS_UTILS)
AUX_SOURCE_DIRECTORY(src/MCTS/planner SRC_MCTS_PLANNER)

ADD_EXECUTABLE(Runner
  ${SRC_UTILS}
  ${SRC_EXTERNAL}
  ${SRC_PQP}
  ${SRC_COMPONENTS}
  ${SRC_MP}
  ${SRC_PROGRAMS}
  ${SRC_CREATE_SCENES}
  ${SRC_MCTS}
  ${SRC_MCTS_UTILS}
  ${SRC_MCTS_PLANNER}
  )



#############################################################################
#Find OpenGL and GLUT
#
INCLUDE(FindOpenGL)
IF(NOT OPENGL_INCLUDE_DIR)
  SET(OPENGL_INCLUDE_DIR GL CACHE STRING "OpenGL directory for header file" FORCE)
ENDIF(NOT OPENGL_INCLUDE_DIR)

INCLUDE(FindGLUT)
IF(NOT GLUT_INCLUDE_DIR)
  SET(GLUT_INCLUDE_DIR GL CACHE STRING "Glut header file" FORCE)
ENDIF(NOT GLUT_INCLUDE_DIR)
IF (NOT GLUT_glut_LIBRARY)
  IF (WIN32 AND NOT CYGWIN)
    SET(GLUT_glut_LIBRARY glut32 CACHE STRING "Glut library for win32" FORCE)
  ENDIF(WIN32 AND NOT CYGWIN)
ENDIF (NOT GLUT_glut_LIBRARY)

INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR} /usr/local/include/bullet /usr/local/include)


IF(GLUT_glut_LIBRARY)
  SET(INTERACTIVE_LIBS ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_glut_LIBRARY})
ELSE (GLUT_glut_LIBRARY)
  SET(INTERACTIVE_LIBS ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
ENDIF(GLUT_glut_LIBRARY)


FIND_LIBRARY(PNG_LIB png16 /usr/lib/ /usr/local/lib/ ./lib/ ${LIBRARY_OUTPUT_PATH})
FIND_LIBRARY(DL_LIB dl /usr/lib/ /usr/local/lib/ ./lib/ ${LIBRARY_OUTPUT_PATH})



TARGET_LINK_LIBRARIES(Runner 
  ${INTERACTIVE_LIBS} 
  ${PNG_LIB}
  ${DL_LIB}
  m
  pthread)
