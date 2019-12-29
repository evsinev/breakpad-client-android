
cmake_minimum_required(VERSION 3.4.1)

set(BREAKPAD_SRC_DIR ${CMAKE_SOURCE_DIR}/native_libs/breakpad/src/src)

include_directories(${BREAKPAD_SRC_DIR} ${BREAKPAD_SRC_DIR}/common/android/include)
set_property(SOURCE ${BREAKPAD_SRC_DIR}/common/android/breakpad_getcontext.S PROPERTY LANGUAGE C)

file(GLOB breakpad_source_files
        "${BREAKPAD_SRC_DIR}/client/linux/crash_generation/crash_generation_client.cc"
        "${BREAKPAD_SRC_DIR}/client/linux/dump_writer_common/thread_info.cc"
        "${BREAKPAD_SRC_DIR}/client/linux/dump_writer_common/ucontext_reader.cc"
        "${BREAKPAD_SRC_DIR}/client/linux/handler/exception_handler.cc"
        "${BREAKPAD_SRC_DIR}/client/linux/handler/minidump_descriptor.cc"
        "${BREAKPAD_SRC_DIR}/client/linux/log/log.cc"
        "${BREAKPAD_SRC_DIR}/client/linux/microdump_writer/microdump_writer.cc"
        "${BREAKPAD_SRC_DIR}/client/linux/minidump_writer/linux_dumper.cc"
        "${BREAKPAD_SRC_DIR}/client/linux/minidump_writer/linux_ptrace_dumper.cc"
        "${BREAKPAD_SRC_DIR}/client/linux/minidump_writer/minidump_writer.cc"
        "${BREAKPAD_SRC_DIR}/client/minidump_file_writer.cc"
        "${BREAKPAD_SRC_DIR}/common/android/breakpad_getcontext.S"
        "${BREAKPAD_SRC_DIR}/common/convert_UTF.cc"
        "${BREAKPAD_SRC_DIR}/common/md5.cc"
        "${BREAKPAD_SRC_DIR}/common/string_conversion.cc"
        "${BREAKPAD_SRC_DIR}/common/linux/elfutils.cc"
        "${BREAKPAD_SRC_DIR}/common/linux/file_id.cc"
        "${BREAKPAD_SRC_DIR}/common/linux/guid_creator.cc"
        "${BREAKPAD_SRC_DIR}/common/linux/linux_libc_support.cc"
        "${BREAKPAD_SRC_DIR}/common/linux/memory_mapped_file.cc"
        "${BREAKPAD_SRC_DIR}/common/linux/safe_readlink.cc"
)

add_library(
        breakpad-client
        SHARED
        ${breakpad_source_files}
        breakpad-client.cpp
)


find_library(log-lib log )

target_link_libraries(breakpad-client ${log-lib} )