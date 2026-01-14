# cmake_minimum_required(VERSION 3.29)

# # 添加包含目录
# include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# # 查找所有的 .h 和 .cpp 文件
# file(GLOB_RECURSE KPROJECT_HPP_SOURCES
#     "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
#     "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
# )

# add_subdirectory(idevices)

# add_executable(kprojecthpp ${KPROJECT_HPP_SOURCES})

cmake_minimum_required(VERSION 3.29)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS *.cpp *.h *.hpp)
target_sources(${PROJECT_NAME} PUBLIC ${sources})

# 添加包含目录
#include_directories(${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_precompile_headers(${PROJECT_NAME} PRIVATE precompiled.h)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/opensourcelibrary/sourcecode/spdlog-1.x/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/opensourcelibrary/sourcecode/json/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/opensourcelibrary/sourcecode/asio-1.30.2/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/opensourcelibrary/bin/opencv/build/include)
target_link_libraries(${PROJECT_NAME} PRIVATE
    debug     ${CMAKE_SOURCE_DIR}/opensourcelibrary/bin/opencv/build/x64/vc16/lib/opencv_world4110d.lib
    optimized ${CMAKE_SOURCE_DIR}/opensourcelibrary/bin/opencv/build/x64/vc16/lib/opencv_world4110.lib
)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/opensourcelibrary/bin/NetworkSDK/include)
target_link_libraries(${PROJECT_NAME} PRIVATE
    debug     ${CMAKE_SOURCE_DIR}/opensourcelibrary/bin/NetworkSDK/lib/LibNetwork_x64_Debug.lib
    optimized ${CMAKE_SOURCE_DIR}/opensourcelibrary/bin/NetworkSDK/lib/LibNetwork_x64_Release.lib
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/thirdpartylibrary/Orbbec/OrbbecSDK_v1.10.22_win_x64/include)
target_link_libraries(${PROJECT_NAME} PRIVATE
    debug     ${CMAKE_SOURCE_DIR}/thirdpartylibrary/Orbbec/OrbbecSDK_v1.10.22_win_x64/lib/OrbbecSDK.lib
    optimized ${CMAKE_SOURCE_DIR}/thirdpartylibrary/Orbbec/OrbbecSDK_v1.10.22_win_x64/lib/OrbbecSDK.lib
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/thirdpartylibrary/XCore/xCoreSDK/include)
target_link_libraries(${PROJECT_NAME} PRIVATE
    debug     ${CMAKE_SOURCE_DIR}/thirdpartylibrary/XCore/xCoreSDK/lib/Windows/Debug/64bit/xCoreSDK.lib
    optimized ${CMAKE_SOURCE_DIR}/thirdpartylibrary/XCore/xCoreSDK/lib/Windows/Release/64bit/xCoreSDK.lib
)



# 安装库
install(DIRECTORY ${CMAKE_SOURCE_DIR}/opensourcelibrary/bin/opencv/build/x64/vc16/bin/
        DESTINATION bin
)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/opensourcelibrary/bin/NetworkSDK/bin/
        DESTINATION bin
)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/thirdpartylibrary/Orbbec/OrbbecSDK_v1.10.22_win_x64/lib/
        DESTINATION bin
)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/thirdpartylibrary/XCore/xCoreSDK/lib/Windows/Release/64bit/
        DESTINATION bin
)
