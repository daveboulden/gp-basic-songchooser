# CMakeLists.txt

# Always set the cmake min version.
cmake_minimum_required(VERSION 3.0)

# Change the PROJECT_VERSION and PROJECT_NAME values to suit your own project
set (PROJECT_VERSION "1.0")
set (PROJECT_NAME "BasicSongChooser")

# Set the appropriate GIT TAGS for the GigPerformer SDK and Saucer 
set (GP_SDK_GIT_TAG "main")    
set (SAUCER_GIT_TAG "experimental")     # master / dev / experimental     

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})

# To build shared libraries in Windows, we set CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS to TRUE.
# See https://cmake.org/cmake/help/v3.4/variable/CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS.html
# See https://blog.kitware.com/create-dlls-on-windows-without-declspec-using-new-cmake-export-all-feature/
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Create our library target
add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME}
  PUBLIC LibMain.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE "embedding")     # include embedded html + assets



# --------------------------------------------------------------------------------------------------------
# Link libraries - fetch the GP_SDK library from GitHub and make it available to the project
# --------------------------------------------------------------------------------------------------------

include(FetchContent)
FetchContent_Declare(
    gp-sdk  
    GIT_REPOSITORY https://github.com/gigperformer/gp-sdk.git
    GIT_TAG ${GP_SDK_GIT_TAG}
)
FetchContent_MakeAvailable(gp-sdk)

target_link_libraries(${PROJECT_NAME} PRIVATE gigperformer::sdk::cpp)


# --------------------------------------------------------------------------------------------------------
# Link libraries - fetch the Saucer library from GitHub and make it available to the project
# --------------------------------------------------------------------------------------------------------

include(FetchContent)
FetchContent_Declare(
    saucer 
    GIT_REPOSITORY "https://github.com/saucer/saucer" 
    GIT_TAG ${SAUCER_GIT_TAG}
) 
FetchContent_MakeAvailable(saucer)

target_link_libraries(${PROJECT_NAME} PRIVATE saucer)



include_directories(${CMAKE_CURRENT_SOURCE_DIR})    # So that the LibMain.h can be found

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Let's set compiler-specific flags
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    # G++
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    # MSVC
    target_compile_options(${PROJECT_NAME} PRIVATE /EHsc /W2 /c)
    # Set the DLLEXPORT variable to export symbols
    target_compile_definitions(${PROJECT_NAME} PRIVATE WIN_EXPORT)
endif()