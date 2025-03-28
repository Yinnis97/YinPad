cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set paths for SFML (adjust these paths according to your setup)
set(SFML_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/YinPad/External/SFML/include)
set(SFML_LIB_DIR ${CMAKE_SOURCE_DIR}/YinPad/External/SFML/lib)

# Add include directories (SFML headers)
include_directories(${SFML_INCLUDE_DIR})

# Add source files
file(GLOB SOURCES "YinPad/*.cpp")

# Create executable
add_executable(YinPad ${SOURCES})

# Link with SFML libraries
target_link_libraries(YinPad
    PRIVATE
    ${SFML_LIB_DIR}/sfml-graphics.lib
    ${SFML_LIB_DIR}/sfml-window.lib
    ${SFML_LIB_DIR}/sfml-system.lib
	${SFML_LIB_DIR}/openal32.lib
	${SFML_LIB_DIR}/flac.lib
	${SFML_LIB_DIR}/freetype.lib
	${SFML_LIB_DIR}/ogg.lib
	${SFML_LIB_DIR}/sfml-main.lib
	${SFML_LIB_DIR}/vorbis.lib
	${SFML_LIB_DIR}/vorbisenc.lib
	${SFML_LIB_DIR}/vorbisfile.lib
)

# Copy the required DLLs after build
add_custom_command(TARGET YinPad POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/YinPad/sfml-graphics-2.dll
    ${CMAKE_SOURCE_DIR}/YinPad/sfml-window-2.dll
	${CMAKE_SOURCE_DIR}/YinPad/openal32.dll
	${CMAKE_SOURCE_DIR}/YinPad/sfml-audio-2.dll 
	${CMAKE_SOURCE_DIR}/YinPad/sfml-system-2.dll 
    $<TARGET_FILE_DIR:YinPad>
)
# Copy the required shaders after build
add_custom_command(TARGET YinPad POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/YinPad/Shaders
    $<TARGET_FILE_DIR:YinPad>/Shaders
)

# Copy the required fonts after build
add_custom_command(TARGET YinPad POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/YinPad/Fonts
    $<TARGET_FILE_DIR:YinPad>/Fonts
)
