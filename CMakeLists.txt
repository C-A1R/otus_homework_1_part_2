cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VESRION})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(src/version/version.h.in version.h)

set(SOURCE_FILES 
    src/main.cpp     
)

add_executable(ip_filter_cli ${SOURCE_FILES})
add_library(ip_filter_lib src/version/versionLib.cpp src/IpFilter.cpp src/IpStruct.cpp)
add_executable(test_Version src/test_Version.cpp)
add_executable(test_IpStruct src/test_IpStruct.cpp)
add_executable(test_IpFilter src/test_IpFilter.cpp)

set_target_properties(ip_filter_cli ip_filter_lib test_Version test_IpStruct test_IpFilter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(ip_filter_lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)
set_target_properties(test_Version test_IpStruct test_IpFilter PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(ip_filter_cli PRIVATE
    ip_filter_lib
)
target_link_libraries(test_Version
    ${Boost_LIBRARIES}
    ip_filter_lib
)
target_link_libraries(test_IpStruct
    ${Boost_LIBRARIES}
    ip_filter_lib
)
target_link_libraries(test_IpFilter
    ${Boost_LIBRARIES}
    ip_filter_lib
)

if (MSVC)
    target_compile_options(ip_filter_cli PRIVATE
        /W4
    )
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(test_Version PRIVATE
        /W4
    )
    target_compile_options(test_IpStruct PRIVATE
        /W4
    )
    target_compile_options(test_IpFilter PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ip_filter_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_Version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_IpStruct PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_IpFilter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS ip_filter_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(test_Version test_Version)
add_test(test_IpStruct test_IpStruct)
add_test(test_IpFilter test_IpFilter)