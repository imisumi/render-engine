cmake_minimum_required(VERSION 3.10)
project(YourProjectName)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable
# add_executable(${PROJECT_NAME} src/main.cpp)
# file(GLOB SRC_FILES "src/*.cpp")
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

# add src/tests/*.h && src/tests/*.cpp
file(GLOB_RECURSE TESTS "src/tests/**/*.cpp")
file(GLOB_RECURSE TESTS_HEADERS "src/tests/**/*.h")




# add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${TESTS} ${TESTS_HEADERS})


# Include directories containing header files
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE dep/stb)
target_include_directories(${PROJECT_NAME} PRIVATE dep/glm)
target_include_directories(${PROJECT_NAME} PRIVATE dep)
# Add your executable
# add_executable(${PROJECT_NAME} ${SOURCES})

# Include Glad
target_sources(${PROJECT_NAME} PRIVATE dep/glad/src/glad.c)
# Set include directories
target_include_directories(${PROJECT_NAME} PRIVATE dep/glad/include)


# Add GLFW library
add_subdirectory(dep/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

# Set include directories
target_include_directories(${PROJECT_NAME} PRIVATE dep/glfw/include)




# find_package(imgui REQUIRED)
# # Add Dear ImGui source files to your project
# add_library(imgui
#     dep/imgui/imgui.cpp
#     dep/imgui/imgui_demo.cpp
#     dep/imgui/imgui_draw.cpp
#     dep/imgui/imgui_widgets.cpp
# )

# # Set include directories
# target_include_directories(imgui PUBLIC dep/imgui)

# # Link imgui to your project
# target_link_libraries(${PROJECT_NAME} PRIVATE imgui)


# Set where the ImGui files are stored
set(IMGUI_PATH dep/imgui)

file(GLOB IMGUI_GLOB 
	${IMGUI_PATH}/imgui.h
	${IMGUI_PATH}/imgui.cpp
	${IMGUI_PATH}/imconfig.h
	${IMGUI_PATH}/imgui_demo.cpp
	${IMGUI_PATH}/imgui_draw.cpp
	${IMGUI_PATH}/imgui_internal.h
	${IMGUI_PATH}/imstb_rectpack.h
	${IMGUI_PATH}/imstb_textedit.h
	${IMGUI_PATH}/imstb_truetype.h
	${IMGUI_PATH}/imgui_tables.cpp
	${IMGUI_PATH}/imgui_widgets.cpp
	
	${IMGUI_PATH}/backends/imgui_impl_glfw.h
	${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
	${IMGUI_PATH}/backends/imgui_impl_opengl3.h
	${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
	${IMGUI_PATH}/backends/imgui_impl_opengl3_loader.cpp)
add_library("imgui" STATIC ${IMGUI_GLOB})
target_include_directories("imgui" PUBLIC ${IMGUI_PATH} ${IMGUI_PATH}/backends)

target_link_libraries(${PROJECT_NAME} PRIVATE imgui)
# target_link_libraries(${PROJECT_NAME} PRIVATE imgui)


# Compile as static library 
# file(GLOB IMGUI_SOURCES ${IMGUI_PATH}/*.cpp) 
# add_library("ImGui" STATIC ${IMGUI_SOURCES}) target_include_directories("ImGui" PUBLIC ${IMGUI_PATH})

# target_link_libraries(${PROJECT_NAME} PUBLIC ImGui)


# Set where the ImGui files are stored
# set(IMGUI_PATH dep/imgui)
    
# # Compile as static library 
# file(GLOB IMGUI_SOURCES ${IMGUI_PATH}/*.cpp) 
# add_library("ImGui" STATIC ${IMGUI_SOURCES})
# target_include_directories("ImGui" PUBLIC ${IMGUI_PATH})

# target_link_libraries(${PROJECT_NAME} PUBLIC ImGui)



# Set OpenGL_GL_PREFERENCE to use GLVND
set(OpenGL_GL_PREFERENCE "GLVND")

# Find OpenGL package
find_package(OpenGL REQUIRED)

# Link OpenGL library to your target
target_link_libraries(YourProjectName PRIVATE OpenGL::GL)
