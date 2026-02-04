cmake_minimum_required(VERSION 3.14)
project(StroustrupBookExercises LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Предупреждения
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	add_compile_options(-Wall -Wextra -Wpedantic)
	
	# GCC/Clang: обычно читают файлы в локальной кодировке,
	# но если файлы сохранены в UTF-8 (без BOM), этого достаточно.
	# Можно явно указать, хотя это редко нужно:
	add_compile_options(-finput-charset=UTF-8 -fpermissive)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	# MSVC: принудительно использовать UTF-8 (включая режим без BOM)
	add_compile_options(/EHs /W4 /utf-8 /permissive)
endif()

# Поддержка Matrix
option(ENABLE_MATRIX "Enable Stroustrup Matrix-based exercises" ON)

# ==========================================================================================
# Поддержка FLTK
# ==========================================================================================
option(ENABLE_FLTK "Enable FLTK-based GUI exercises" ON)
if(ENABLE_FLTK)
	# Подключаем UseFLTK.cmake напрямую (для FLTK 1.3.x)
	set(FLTK_ROOT ${CMAKE_SOURCE_DIR}/include/fltk/install)
	# include(${FLTK_ROOT}/CMake/UseFLTK.cmake)
	
	set(FLTK_INCLUDE_DIRS ${FLTK_ROOT}/include)
	if(WIN32)
		set(FLTK_LIBRARIES
			${FLTK_ROOT}/lib/fltk.lib
			${FLTK_ROOT}/lib/fltk_images.lib
			# ${FLTK_ROOT}/lib/fltk_png.lib
			${FLTK_ROOT}/lib/fltk_jpeg.lib
			# ${FLTK_ROOT}/lib/fltk_z.lib
		)
	else()
		# Linux / macOS
		find_package(X11 REQUIRED)
		find_package(Threads REQUIRED)
		
		# Проверяем доступность опциональных библиотек
		find_library(XFT_LIB Xft)
		find_library(XRANDR_LIB Xrandr)
		find_library(XDAMAGE_LIB Xdamage)
		find_library(XINERAMA_LIB Xinerama)
		find_library(XCURSOR_LIB Xcursor)
		find_library(XFIXES_LIB Xfixes)
		find_library(XRENDER_LIB Xrender)
		
		# Сначала проверяем, что FLTK библиотеки существуют
		if(NOT EXISTS "${FLTK_ROOT}/lib/libfltk.a")
			message(WARNING "FLTK library not found at ${FLTK_ROOT}/lib/libfltk.a")
			set(ENABLE_FLTK OFF)
		else()
			message(STATUS "FLTK found at: ${FLTK_ROOT}")
			
			set(FLTK_LIBRARIES
				${FLTK_ROOT}/lib/libfltk.a
				${FLTK_ROOT}/lib/libfltk_images.a
				
				# Основные библиотеки
				${X11_LIBRARIES}
				${X11_Xft_LIB}
				fontconfig
				
				# Системные библиотеки
				${CMAKE_THREAD_LIBS_INIT}
				jpeg
				dl
				m
			)
			
			# Пробуем добавить опциональные, но не падаем если их нет
			foreach(LIB Xinerama Xcursor Xfixes Xrender)
				find_library(FOUND_${LIB} ${LIB})
				if(FOUND_${LIB})
					list(APPEND FLTK_LIBRARIES ${FOUND_${LIB}})
				endif()
			endforeach()
		endif()
	endif()

	if(ENABLE_FLTK  AND  EXISTS "${FLTK_INCLUDE_DIRS}/FL/Fl.H")
		message(STATUS "FLTK ${FLTK_VERSION} found. GUI exercises will be built.")
	else()
		message(WARNING "FLTK not found. Skipping GUI exercises. Install FLTK to ${CMAKE_SOURCE_DIR}/include/fltk/CMake.")
		set(ENABLE_FLTK OFF)
	endif()
endif()


if(ENABLE_FLTK)
	set(GUI_LIBRARY_SOURCES
		${CMAKE_SOURCE_DIR}/include/addition.cpp
		${CMAKE_SOURCE_DIR}/include/Graph.cpp
		${CMAKE_SOURCE_DIR}/include/Window.cpp
		${CMAKE_SOURCE_DIR}/include/GUI.cpp
	)

	# Создаём статическую библиотеку один раз
	add_library(STROUSTRUP_GUI_LIB STATIC ${GUI_LIBRARY_SOURCES})

	# Настройка include-директорий и линковки с FLTK
	target_include_directories(STROUSTRUP_GUI_LIB
		PUBLIC
			${CMAKE_SOURCE_DIR}/include		# чтобы пользователи видели Graph.h и т.д.
			${FLTK_INCLUDE_DIRS}
	)
	
	# Добавляем X11 заголовки только на UNIX-системах
	if(UNIX AND NOT APPLE AND X11_INCLUDE_DIR)
		target_include_directories(STROUSTRUP_GUI_LIB PUBLIC ${X11_INCLUDE_DIR})
	endif()
	
	
	target_link_libraries(STROUSTRUP_GUI_LIB
		PUBLIC
			${FLTK_LIBRARIES}
	)

	# Указываем, что эта библиотека зависит от C++14
	set_target_properties(STROUSTRUP_GUI_LIB PROPERTIES
		CXX_STANDARD 14
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
	)
endif()
# ==========================================================================================
# Поддержка FLTK
# ==========================================================================================


# Шаг 1: найти все .cpp файлы
file(GLOB_RECURSE ALL_CPP_SOURCES
	CONFIGURE_DEPENDS
	${CMAKE_SOURCE_DIR}/chapter_*/*.cpp
)

# Шаг 2: собрать уникальные директории, содержащие .cpp
set(PROJECT_DIRS "")
foreach(SRC ${ALL_CPP_SOURCES})
	get_filename_component(DIR ${SRC} DIRECTORY)
	list(APPEND PROJECT_DIRS ${DIR})
endforeach()
list(REMOVE_DUPLICATES PROJECT_DIRS)

# Шаг 3: для каждой директории — своя цель
set(GLOBAL_INCLUDE
	${CMAKE_SOURCE_DIR}/include
)

set(ALL_EXECUTABLES "")



# Список шаблонов для исключения (примеры с намеренно допущенными ошибками,
#  либо отдельные функции без их использования и соотв. без main)
set(EXCLUDE_PATTERNS
	"chapter_3/0.try_this/3.7"
	"chapter_6/0.try_this/6.3.4"
	"chapter_6/1.drill/calculator02buggy"
	"chapter_7/1.drill/calculator08buggy"
	"chapter_8/2.exercises/2"
	"chapter_9/2.exercises/4"
	"chapter_14_GUI/2.exercises/2-3"
	"chapter_23/1.drill/boost"
)

# Список директорий с GUI-задачами (FLTK)
set(GUI_TASK_PATTERNS
	"chapter_12_GUI"
	"chapter_13_GUI"
	"chapter_14_GUI"
	"chapter_15_GUI"
	"chapter_16_GUI"
	"chapter_19_1GUI/2.exercises/14-15_GUI"
	"chapter_21_2GUI/2.exercises/11-12_GUI"
	"chapter_21_2GUI/2.exercises/13-15_GUI"
)


foreach(DIR ${PROJECT_DIRS})
	# Пропускаем, если путь совпадает с исключением
	set(SKIP_DIR FALSE)
	foreach(PAT IN LISTS EXCLUDE_PATTERNS)
		string(FIND "${DIR}" "${PAT}" POS)
		if(NOT POS EQUAL -1)
			set(SKIP_DIR TRUE)
			break()
		endif()
	endforeach()

	if(NOT ENABLE_MATRIX)
		if("${DIR}" MATCHES "chapter_24(/|$)")
			set(SKIP_DIR TRUE)
		endif()
	endif()

	if(SKIP_DIR)
		continue()
	endif()
	
	# Проверяем, является ли директория GUI-задачей
	set(IS_GUI_TASK FALSE)
	foreach(GUI_PAT IN LISTS GUI_TASK_PATTERNS)
		string(FIND "${DIR}" "${GUI_PAT}" POS)
		if(NOT POS EQUAL -1)
			set(IS_GUI_TASK TRUE)
			break()
		endif()
	endforeach()
	
	# Если это GUI-задача, но FLTK отключён — пропускаем
	if(IS_GUI_TASK AND NOT ENABLE_FLTK)
		continue()
	endif()


	# Получаем список всех .cpp в этой директории
	file(GLOB CPP_FILES ${DIR}/*.cpp)
	if(NOT CPP_FILES)
		continue()
	endif()

	# Формируем понятное имя: chapter_X__subdir__subsubdir
	file(RELATIVE_PATH REL_PATH ${CMAKE_SOURCE_DIR} ${DIR})
	
	# Заменяем слеши и точки на двойные подчёркивания для читаемости
	string(REGEX REPLACE "[/\\\\]" "__" TARGET_NAME "${REL_PATH}")
	string(REGEX REPLACE "\\." "_" TARGET_NAME "${TARGET_NAME}")
	
	# Убираем возможные дубли __
	string(REGEX REPLACE "__+" "__" TARGET_NAME "${TARGET_NAME}")
	string(REGEX REPLACE "^__+|__+$" "" TARGET_NAME "${TARGET_NAME}")
	
	# Ограничиваем длину (опционально, но полезно для Windows)
	if(${CMAKE_HOST_WIN32})
		string(SUBSTRING "${TARGET_NAME}" 0 80 TARGET_NAME_SHORT)
		set(TARGET_NAME ${TARGET_NAME_SHORT})
	endif()

	# Создаём исполняемый файл из всех .cpp в папке
	add_executable(${TARGET_NAME} ${CPP_FILES})
	
	list(APPEND ALL_EXECUTABLES ${TARGET_NAME})

	# Добавляем:
	# 1) саму директорию — чтобы локальные хедеры в одной директории с main.cpp попали в сборку
	# 2) глобальный include/ — для std_lib_facilities.h
	target_include_directories(${TARGET_NAME}
		PRIVATE
			${DIR}
			${GLOBAL_INCLUDE}
	)
	
	# FLTK-настройки
	if(IS_GUI_TASK AND ENABLE_FLTK)
		target_link_libraries(${TARGET_NAME} PRIVATE STROUSTRUP_GUI_LIB)
	endif()

	# Формируем подпапку внутри bin/, соответствующую структуре исходников
	file(RELATIVE_PATH REL_PATH ${CMAKE_SOURCE_DIR} ${DIR})
	string(REGEX REPLACE "[/\\\\]" "/" REL_PATH_SLASH "${REL_PATH}")
	set(OUTPUT_SUBDIR "bin/${REL_PATH_SLASH}")

	# Создаём директорию (если не существует - иначе упадет сборка)
	file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${OUTPUT_SUBDIR})

	# Устанавливаем выходную директорию для этой цели
	set_target_properties(${TARGET_NAME} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${OUTPUT_SUBDIR}
	)

	# Копирование .txt и .jpg файлов в выходную директорию
	file(GLOB DATA_FILES ${DIR}/*.txt ${DIR}/*.jpg)
	if(DATA_FILES)
		foreach(DATA_FILE ${DATA_FILES})
			get_filename_component(FILE_NAME ${DATA_FILE} NAME)
			add_custom_command(
				TARGET ${TARGET_NAME} POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy_if_different
					${DATA_FILE}
					${CMAKE_BINARY_DIR}/${OUTPUT_SUBDIR}/${FILE_NAME}
				COMMENT "Copying ${FILE_NAME} to ${OUTPUT_SUBDIR}"
			)
		endforeach()
	endif()
endforeach()

if(ALL_EXECUTABLES)
	list(LENGTH ALL_EXECUTABLES NUM_TARGETS_COUNT)

	add_custom_target(show_build_success ALL
		COMMAND ${CMAKE_COMMAND}
			-DNUM_TARGETS=${NUM_TARGETS_COUNT}
			-P "${CMAKE_SOURCE_DIR}/post_build_success.cmake"
		DEPENDS ${ALL_EXECUTABLES}
	)
endif()
