# Library
add_library(
  Kedarium
  Constants.cpp
  Core.cpp
  File.cpp
  Color.cpp
  Graphics.cpp
  Window.cpp
  Space.cpp
)

# Include Directory
target_include_directories(Kedarium PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
