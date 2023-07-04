#########################
# Dependencies download #
#########################

set(DOWNLOAD_DIR "${PROJECT_BINARY_DIR}/test_downloads")
file(MAKE_DIRECTORY "${DOWNLOAD_DIR}")

set(GREATEST_SHA256 "b3f89ecad2301c64c580f328cc03a74d92f4cd4bf42ab18d3d4bfb7b8be5b948")
if (NOT CMAKE_SYSTEM_NAME STREQUAL "SunOS")
    file(DOWNLOAD "https://raw.githubusercontent.com/SamuelMarks/greatest/cmake-and-msvc/greatest.h"
            "${DOWNLOAD_DIR}/greatest.h")
    file(SHA256 "${DOWNLOAD_DIR}/greatest.h" GREATEST_SHA256_FOUND)
    if (NOT GREATEST_SHA256_FOUND STREQUAL GREATEST_SHA256)
        message(FATAL_ERROR "SHA256 hash verification failed for \"${DOWNLOAD_DIR}/greatest.h\"
                             \n\"${GREATEST_SHA256_FOUND}\" != \"${GREATEST_SHA256}\"")
    endif (NOT GREATEST_SHA256_FOUND STREQUAL GREATEST_SHA256)
endif (NOT CMAKE_SYSTEM_NAME STREQUAL "SunOS")

##################
# Top-level test #
##################

set(EXEC_NAME "test_ll")

set(Source_Files "${EXEC_NAME}_suites.c")
source_group("${EXEC_NAME} Source Files" FILES "${Source_Files}")

add_executable("${EXEC_NAME}" "${Source_Files}")

target_include_directories(
        "${EXEC_NAME}"
        PRIVATE
        "$<BUILD_INTERFACE:${DOWNLOAD_DIR}>"
)
set_target_properties(
        "${EXEC_NAME}"
        PROPERTIES
        LINKER_LANGUAGE
        C
)
target_link_libraries("${EXEC_NAME}" PUBLIC "${PROJECT_NAME}")

find_package(c_str_span CONFIG REQUIRED)
target_link_libraries(
        "${EXEC_NAME}"
        PRIVATE
        c_str_span c_str_span_compiler_flags
)

add_test(NAME "${EXEC_NAME}" COMMAND "${EXEC_NAME}")
