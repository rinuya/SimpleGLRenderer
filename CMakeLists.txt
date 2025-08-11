cmake_minimum_required(VERSION 3.28)
project(LearnOpenGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find system libs
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Find Assimp
find_package(assimp REQUIRED)

# Add GLAD
add_library(glad STATIC extern/glad/src/glad.c)
target_include_directories(glad PUBLIC extern/glad/include)

# Your sources
file(GLOB SRCS src/*.cpp)

add_executable(${PROJECT_NAME} ${SRCS})
target_include_directories(${PROJECT_NAME} 
    PRIVATE 
        extern/glad/include
        extern/stb_image
        ${ASSIMP_INCLUDE_DIRS}
)

# Link everything
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glad
        glfw
        OpenGL::GL
        assimp
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/src/shaders"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/src/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)