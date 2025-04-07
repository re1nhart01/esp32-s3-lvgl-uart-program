set(PROJECT_ROOT "${CMAKE_SOURCE_DIR}")

file(GLOB_RECURSE SOURCES
        "${PROJECT_ROOT}/main/*.c"
        "${PROJECT_ROOT}/main/*.cc"
        "${PROJECT_ROOT}/main/core/*.c"
        "${PROJECT_ROOT}/main/core/*.cc"
        "${PROJECT_ROOT}/components/*.cc"
        "${PROJECT_ROOT}/components/base/*.cc"
        "${PROJECT_ROOT}/components/base/*.hh"
        "${PROJECT_ROOT}/main/ui/screens/*.cc"
        "${PROJECT_ROOT}/main/ui/*.cc"
)

idf_component_register(
        SRCS ${SOURCES}
        INCLUDE_DIRS
        "${PROJECT_ROOT}/main/core"
        "${PROJECT_ROOT}/components"
        "${PROJECT_ROOT}/components/base"
        "${PROJECT_ROOT}/main/ui"
        "${PROJECT_ROOT}/main/ui/screens"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options("-Wno-attributes")
