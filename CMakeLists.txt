cmake_minimum_required(VERSION 3.2)
if($ENV{TRAVIS_BUILD_NUMBER})
    project(print_ip VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(print_ip VERSION 0.0.42)
endif()

configure_file(description.json.in description.json)

find_package(GTest REQUIRED)
set(INCLUDE ${CMAKE_BINARY_DIR}/../include)
include_directories(${INCLUDE} ${GTEST_INCLUDE_DIRS})


set(SOURCE ${CMAKE_BINARY_DIR}/../source)
add_executable(print_ip ${SOURCE}/main.cpp)


set(TESTS_DIR ${CMAKE_BINARY_DIR}/../tests)
add_executable(sfinae_tests ${TESTS_DIR}/sfinae_tests.cpp)
target_link_libraries(sfinae_tests gtest gtest_main pthread)

set_target_properties(print_ip sfinae_tests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if(MSVC)
    target_compile_options(print_ip PRIVATE
        /W4
    )
    target_compile_options(sfinae_tests PRIVATE
        /W4
    )
else()
    target_compile_options(print_ip PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(sfinae_tests PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

#doxygen
find_package(Doxygen REQUIRED)
set(DOXYGEN_OUTPUT_DIRECTORY)
set(DOXYGEN_PROJECT_NUMBER ${VERSION})
set(DOXYGEN_HAVE_DOT YES)
set(DOXYGEN_EXTRACT_ALL YES)
doxygen_add_docs(print_ip_doc 
    ${INCLUDE} ${SOURCE} 
)

#Pack
install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
# Tests
enable_testing()
add_test(sfinae_tests sfinae_tests)