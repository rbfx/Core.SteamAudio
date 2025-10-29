cmake_minimum_required(VERSION 3.21)
project (Plugin.Core.SteamAudio)

# Top-level plugin build is not supported yet.
# If the plugin is only built as subdirectory, this snippet is not needed and may be discarded.
if (PROJECT_IS_TOP_LEVEL)
    set (CMAKE_CXX_STANDARD 17)
    find_package (Urho3D REQUIRED)
endif ()

file (GLOB SOURCE_FILES *.h *.cpp)
add_plugin (${PROJECT_NAME} "${SOURCE_FILES}")

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
