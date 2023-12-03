# Library
add_library(
  Kedarium
  Constants.cpp
  Core.cpp
  File.cpp
  Image.cpp
  Color.cpp
  Graphics.cpp
  Window.cpp
  Space.cpp
  Camera.cpp
  Solids.cpp
  Model.cpp
)

# Include Directory
target_include_directories(Kedarium PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
