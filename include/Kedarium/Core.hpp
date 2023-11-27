#ifndef KDR_CORE_HPP
#define KDR_CORE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

extern const std::string ENGINE_NAME;
extern const std::string ENGINE_VERSION;
extern const std::string ENGINE_AUTHOR;
extern const std::string ENGINE_LICENSE;

namespace kdr
{
  namespace core
  {
    /**
     * Prints information about the game engine.
     */
    void printEngineInfo();
    /**
     * Prints version information about OpenGL, GLEW, and GLFW.
     */
    void printVersionInfo();
    /**
     * Terminates the engine.
     */
    void terminate();
  }
}

#endif // KDR_CORE_HPP
