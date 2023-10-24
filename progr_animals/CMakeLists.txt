# CMakeList.txt: проект CMake для progr_animals; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (progr_animals "progr_animals.cpp" "progr_animals.h" "Header1.h" "Header2.h" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET progr_animals PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
