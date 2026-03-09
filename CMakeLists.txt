cmake_minimum_required(VERSION 3.16)

# Название проекта
project(Lb3_FSM VERSION 1.0 LANGUAGES CXX)

# 1. Установка стандарта C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Автопоиск инструментов Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 3. Поиск пакетов Qt 6
find_package(Qt6 REQUIRED COMPONENTS Widgets Core)

# 4. Сбор списков файлов
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")
file(GLOB_RECURSE UI "ui/*.ui") # Исправлено название переменной

# 5. Настройка выходной папки для .exe
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/builds")

# 6. СОЗДАНИЕ ЦЕЛИ (обязательно ДО настройки инклудов и линковки)
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UI}
)

# Добавь эту настройку, чтобы AUTOUIC искал файлы в папке ui/
set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui"
)

# 7. Настройка путей для include (теперь цель существует, ошибки не будет)
target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_autogen/include"
)

# 8. Линковка библиотек
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    Qt6::Core
)
