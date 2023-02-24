cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project("SHADOW")
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenMP)
add_subdirectory(ext/glm)

add_executable(SHADOW)

include("cmake/BuildGlad.cmake")
include("cmake/BuildImgui.cmake")

set_target_properties(SHADOW
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

target_sources(SHADOW PRIVATE
    "src/main.cpp"
    "src/world.cpp"
    "src/matrixStack.cpp"
    "src/Drawmodel.cpp"
    "src/stb_image.cpp"
    "src/textureMap.cpp"
    "src/logger.c"
    "src/RAWmodel.cpp"
)
target_sources(glad PRIVATE
    "ext/glad/src/glad.c"
)

target_include_directories(SHADOW PRIVATE
    "include/"
)
target_include_directories(glad PUBLIC
    "ext/glad/include"
)

target_link_libraries(SHADOW PRIVATE 
    glad # include(BuildGlad.cmake)
    imgui # include(BuildImgui.cmake)
    glm::glm # add_subdirectory(ext/glm)
    glfw  # find_package(glfw3 REQUIRED)
    OpenGL::GL # find_package(OpenGL REQUIRED)
)

if(OpenMP_CXX_FOUND)
    target_link_libraries(SHADOW PRIVATE OpenMP::OpenMP_CXX)
endif()

add_custom_command(TARGET SHADOW POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${CMAKE_CURRENT_SOURCE_DIR}/shader"
        "$<TARGET_FILE_DIR:SHADOW>/shader"
    VERBATIM
)

add_custom_command(TARGET SHADOW POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${CMAKE_CURRENT_SOURCE_DIR}/texture"
        "$<TARGET_FILE_DIR:SHADOW>/texture"
    VERBATIM
)

add_custom_command(TARGET SHADOW POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${CMAKE_CURRENT_SOURCE_DIR}/stl"
        "$<TARGET_FILE_DIR:SHADOW>/stl"
    VERBATIM
)

add_custom_command(TARGET SHADOW POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${CMAKE_CURRENT_SOURCE_DIR}/raw"
        "$<TARGET_FILE_DIR:SHADOW>/raw"
    VERBATIM
)