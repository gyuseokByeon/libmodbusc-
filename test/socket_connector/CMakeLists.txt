
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(testSocketConnector test_socket_connector.cpp)
add_definitions(-Wall -Wextra -g -ggdb3 -O0)
target_link_libraries(testSocketConnector boost_system)

include_directories(
    ${PROJECT_SOURCE_DIR}/test
    ${PROJECT_SOURCE_DIR}/src/include
)
