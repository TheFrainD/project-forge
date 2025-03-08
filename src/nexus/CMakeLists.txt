file(GLOB_RECURSE NEXUS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE NEXUS_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

add_library(nexus STATIC ${NEXUS_SOURCES} ${NEXUS_HEADERS})
target_include_directories(nexus PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(spdlog REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLAD REQUIRED)
find_package(glm REQUIRED)
find_package(EnTT REQUIRED)

target_link_libraries(nexus PUBLIC glfw glad::glad spdlog::spdlog glm::glm EnTT::EnTT)
target_compile_definitions(nexus PRIVATE GLFW_INCLUDE_NONE)
