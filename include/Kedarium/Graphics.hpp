#ifndef KDR_GRAPHICS_HPP
#define KDR_GRAPHICS_HPP

#include <GL/glew.h>

namespace kdr
{
  namespace gfx
  {
    /**
     * Sets the OpenGL polygon mode to render points.
     */
    void usePointMode()
    { glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); }
    /**
     * Sets the OpenGL polygon mode to render lines.
     */
    void useLineMode()
    { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
    /**
     * Sets the OpenGL polygon mode to filled polygons.
     */
    void useFillMode()
    { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
  };
}

#endif // KDR_GRAPHICS_HPP
