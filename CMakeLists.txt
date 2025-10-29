cmake_minimum_required(VERSION 3.21)
project (Plugin.Core.SteamAudio)

if (PROJECT_IS_TOP_LEVEL)
    set (CMAKE_CXX_STANDARD 17)
    find_package (Urho3D REQUIRED)
endif ()

file (GLOB SOURCE_FILES *.h *.cpp)
add_plugin (${PROJECT_NAME} "${SOURCE_FILES}")

# Link to SteamAudio
list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake/Modules")
find_package (SteamAudio REQUIRED)
target_include_directories (${PROJECT_NAME} PRIVATE ${STEAMAUDIO_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} PRIVATE ${STEAMAUDIO_LIBRARIES})

# Copy .so and .dll files to the binary directory
foreach (lib ${STEAMAUDIO_LIBRARIES})
    string (REGEX REPLACE ".lib$" ".dll" lib "${lib}")
    if ("${lib}" MATCHES ".*\\.(so|dll)" AND EXISTS "${lib}")
        add_custom_command (TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${lib} $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    endif ()
endforeach ()

if (URHO3D_CSHARP)
    set (DEST_BIN_DIR_CONFIG bin)
    set (DEST_LIBRARY_DIR_CONFIG bin)
    target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    csharp_bind_target(
        TARGET ${PROJECT_NAME}
        SWIG ${CMAKE_CURRENT_SOURCE_DIR}/CSharp/Plugin.i
        CSPROJ ${CMAKE_CURRENT_SOURCE_DIR}/CSharp/Plugin.csproj
        NAMESPACE Urho3DNet
    )
endif ()

# Generate Visual Studio props file for csproj.
rbfx_configure_cmake_props()
