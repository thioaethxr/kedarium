# Executable
add_executable(
  example
  Main.cpp
)

# Include Directory
target_include_directories(Kedarium PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Linking Libraries
target_link_libraries(example PRIVATE Kedarium GL GLEW glfw png)
