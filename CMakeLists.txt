cmake_minimum_required(VERSION 3.16)

project(Lb3_FSM VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")
file(GLOB_RECURSE UI "ui/*.ui")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/builds")

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UI}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui"
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_autogen/include"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    Qt6::Core
)

if(WIN32)
    # Ищем путь к windeployqt
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "C:/Qt/6.10.2/mingw_64/bin")

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        # Запускаем только в режиме Release
        COMMAND $<$<CONFIG:Release>:${WINDEPLOYQT_EXECUTABLE}>
        $<$<CONFIG:Release>:"--no-translations"> # Опционально: убираем лишние переводы
        $<$<CONFIG:Release>:"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.exe">
        COMMENT "Running windeployqt for Release deployment..."
    )
endif()
