CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12.1)

if(WIN32 AND NOT MINGW)
  if(NOT DEFINED CMAKE_DEBUG_POSTFIX)
    set(CMAKE_DEBUG_POSTFIX "d")
  endif()
endif()

IF(WIN32)
  # no permission for the default install prefix %ProgramFiles%
  SET(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE STRING "installation path")
ENDIF()

IF(NOT DEFINED CMAKE_BUILD_TYPE)
  # No effect for multi-configuration generators (e.g. for Visual Studio)
  SET(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose: RelWithDebInfo Release Debug MinSizeRel None")
ENDIF()

PROJECT(libfreenect2)

SET(MY_DIR ${libfreenect2_SOURCE_DIR})
SET(DEPENDS_DIR "${MY_DIR}/depends" CACHE STRING "dependency directory must be set to 'false' if external deps are used")

OPTION(BUILD_SHARED_LIBS "Build shared (ON) or static (OFF) libraries" ON)
OPTION(BUILD_EXAMPLES "Build examples" ON)
OPTION(ENABLE_CXX11 "Enable C++11 support" OFF)
OPTION(ENABLE_OPENCL "Enable OpenCL support" ON)
OPTION(ENABLE_OPENGL "Enable OpenGL support" ON)

IF(MSVC)
  # suppress several "possible loss of data" warnings, and
  # "zero-length array in struct" from libusb.h
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4267 /wd4244 /wd4200 /wd4305 /wd4146")
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS) # no warning for getenv()
ENDIF()

IF(ENABLE_CXX11)
  INCLUDE(CheckCXXCompilerFlag)
  CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
  CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
  IF(COMPILER_SUPPORTS_CXX11)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    SET(LIBFREENECT2_WITH_CXX11_SUPPORT 1)
  ELSEIF(COMPILER_SUPPORTS_CXX0X)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
  ELSE()
    MESSAGE(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
  ENDIF()
ENDIF(ENABLE_CXX11)

# additional cmake modules
LIST(APPEND CMAKE_MODULE_PATH ${MY_DIR}/cmake_modules)

# setup threading
INCLUDE(SetupLibfreenect2Threading)

INCLUDE(GenerateResources)

#set the default path for built executables to the "bin" directory
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

#set the default path for built libraries to the "lib" directory
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# dependencies
FIND_PACKAGE(PkgConfig)    # try find PKGConfig as it will be used if found
FIND_PACKAGE(LibUSB REQUIRED)
FIND_PACKAGE(TurboJPEG REQUIRED) #does not provide a package-config file

# Add includes
INCLUDE_DIRECTORIES(
  "${MY_DIR}/include"
  "${MY_DIR}/include/internal"
  ${PROJECT_BINARY_DIR} # for generated headers
  ${LIBFREENECT2_THREADING_INCLUDE_DIR}
  ${LibUSB_INCLUDE_DIRS}
  ${TurboJPEG_INCLUDE_DIRS}
)

SET(RESOURCES_INC_FILE "${PROJECT_BINARY_DIR}/resources.inc.h")

SET(SOURCES
  include/internal/libfreenect2/protocol/command.h
  include/internal/libfreenect2/protocol/command_transaction.h
  include/internal/libfreenect2/protocol/response.h
  include/internal/libfreenect2/protocol/usb_control.h

  include/internal/libfreenect2/usb/event_loop.h
  include/internal/libfreenect2/usb/transfer_pool.h

  include/libfreenect2/logger.h
  include/internal/libfreenect2/logging.h

  include/internal/libfreenect2/async_packet_processor.h
  include/internal/libfreenect2/depth_packet_processor.h
  include/internal/libfreenect2/depth_packet_stream_parser.h
  include/internal/libfreenect2/double_buffer.h
  include/libfreenect2/frame_listener.hpp
  include/libfreenect2/frame_listener_impl.h
  include/libfreenect2/libfreenect2.hpp
  include/libfreenect2/packet_pipeline.h
  include/internal/libfreenect2/packet_processor.h
  include/libfreenect2/registration.h
  include/internal/libfreenect2/resource.h
  include/internal/libfreenect2/rgb_packet_processor.h
  include/internal/libfreenect2/rgb_packet_stream_parser.h
  include/internal/libfreenect2/threading.h

  src/transfer_pool.cpp
  src/event_loop.cpp
  src/usb_control.cpp
  src/double_buffer.cpp
  src/frame_listener_impl.cpp
  src/packet_pipeline.cpp
  src/rgb_packet_stream_parser.cpp
  src/rgb_packet_processor.cpp
  src/turbo_jpeg_rgb_packet_processor.cpp
  src/depth_packet_stream_parser.cpp
  src/depth_packet_processor.cpp
  src/cpu_depth_packet_processor.cpp
  src/resource.cpp
  src/command_transaction.cpp
  src/registration.cpp
  src/logging.cpp
  src/libfreenect2.cpp

  ${LIBFREENECT2_THREADING_SOURCE}
  ${RESOURCES_INC_FILE}
  "${PROJECT_BINARY_DIR}/libfreenect2/config.h"
  "${PROJECT_BINARY_DIR}/libfreenect2/export.h"
)

SET(LIBRARIES
  ${LibUSB_LIBRARIES}
  ${TurboJPEG_LIBRARIES}
  ${LIBFREENECT2_THREADING_LIBRARIES}
)

SET(LIBFREENECT2_DLLS
  ${LibUSB_DLL}
  ${TurboJPEG_DLL}
)

IF(ENABLE_OPENGL)
  FIND_PACKAGE(GLFW3)
  FIND_PACKAGE(OpenGL)
  IF(GLFW3_FOUND)
    INCLUDE_DIRECTORIES(${GLFW3_INCLUDE_DIRS})

    LIST(APPEND LIBFREENECT2_DLLS ${GLFW3_DLL})
    LIST(APPEND LIBRARIES
      ${GLFW3_LIBRARIES}
      ${OPENGL_gl_LIBRARY}
    )
  SET(LIBFREENECT2_WITH_OPENGL_SUPPORT 1)
  LIST(APPEND SOURCES
    src/flextGL.cpp
    src/opengl_depth_packet_processor.cpp
  )

  LIST(APPEND RESOURCES
    src/shader/debug.fs
    src/shader/default.vs
    src/shader/filter1.fs
    src/shader/filter2.fs
    src/shader/stage1.fs
    src/shader/stage2.fs
  )
  ENDIF()
ENDIF(ENABLE_OPENGL)

IF(ENABLE_OPENCL)
  FIND_PACKAGE(OpenCL)

  IF(OpenCL_FOUND)
    IF(UNIX AND NOT APPLE)
      INCLUDE(CheckOpenCLICDLoader)
      IF(OpenCL_C_WORKS AND NOT OpenCL_CXX_WORKS)
        SET(LIBFREENECT2_OPENCL_ICD_LOADER_IS_OLD 1)
        MESSAGE(WARNING "Your libOpenCL.so is incompatible with CL/cl.h. Install ocl-icd-opencl-dev to update libOpenCL.so?")
      ENDIF()
    ENDIF()
    SET(LIBFREENECT2_WITH_OPENCL_SUPPORT 1)
    INCLUDE_DIRECTORIES(${OpenCL_INCLUDE_DIRS})

    LIST(APPEND SOURCES
      src/opencl_depth_packet_processor.cpp
    )

    LIST(APPEND LIBRARIES
      ${OpenCL_LIBRARIES}
    )

    LIST(APPEND RESOURCES
      src/opencl_depth_packet_processor.cl
    )

    # Major Linux distro stable releases have buggy OpenCL ICD loader.
    # The workaround of disabling exceptions can only be set up during compile time.
    # Diabling it for all should be harmless. The flag is the same for GCC/Clang/ICC.
    IF(UNIX AND NOT APPLE)
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
    ENDIF()
  ENDIF(OpenCL_FOUND)
ENDIF(ENABLE_OPENCL)

# RPATH handling for private libusb copies
# Users have two options:
# 1. Build libusb in depends/ and leave it there:
#      Do NOT set CMAKE_INSTALL_RPATH. It works by default.
# 2. Build libusb and install it somewhere:
#      Set CMAKE_INSTALL_RPATH to the libusb.so installation directory before compiling.
# Both command line -DCMAKE_INSTALL_RPATH=... and CMake GUI settings are accepted.
#
# Anyway if wrong versions of libusb is used, errors will be reported explicitly.
IF(NOT DEFINED CMAKE_INSTALL_RPATH)
  SET(CMAKE_INSTALL_RPATH ${LibUSB_LIBDIR} CACHE STRING "Set RPATH for a private libusb")
ELSE()
  SET(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_RPATH} CACHE STRING "Set RPATH for a private libusb")
ENDIF()
IF(DEFINED CMAKE_INSTALL_RPATH)
  MESSAGE(STATUS "RPATH set to ${CMAKE_INSTALL_RPATH}")
ENDIF()

CONFIGURE_FILE("${MY_DIR}/include/libfreenect2/config.h.in" "${PROJECT_BINARY_DIR}/libfreenect2/config.h" @ONLY)
GENERATE_RESOURCES(${RESOURCES_INC_FILE} ${MY_DIR} ${RESOURCES})

ADD_DEFINITIONS(-DRESOURCES_INC)
ADD_LIBRARY(freenect2 ${SOURCES})
SET_TARGET_PROPERTIES(freenect2 PROPERTIES
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN 1
)
INCLUDE(GenerateExportHeader)
GENERATE_EXPORT_HEADER(freenect2
  BASE_NAME libfreenect2
  EXPORT_FILE_NAME libfreenect2/export.h
)

IF(MSVC AND NOT BUILD_SHARED_LIBS)
  # MSVC creates freenect2.lib for both dynamic and static by default
  set_target_properties(freenect2 PROPERTIES SUFFIX "static.lib")
ENDIF()
STRING(REPLACE ";" "\n " LIBRARIES_STRING "${LIBRARIES}")
MESSAGE(STATUS "Linking with these libraries: \n ${LIBRARIES_STRING}")
TARGET_LINK_LIBRARIES(freenect2 ${LIBRARIES})

CONFIGURE_FILE(freenect2.cmake.in "${PROJECT_BINARY_DIR}/freenect2Config.cmake" @ONLY)
CONFIGURE_FILE(freenect2.pc.in "${PROJECT_BINARY_DIR}/freenect2.pc" @ONLY)

INSTALL(TARGETS freenect2 DESTINATION lib RUNTIME DESTINATION bin)
INSTALL(DIRECTORY "${MY_DIR}/include/${PROJECT_NAME}" DESTINATION include PATTERN "*.in" EXCLUDE)
INSTALL(DIRECTORY "${PROJECT_BINARY_DIR}/${PROJECT_NAME}" DESTINATION include)
INSTALL(FILES "${PROJECT_BINARY_DIR}/freenect2Config.cmake" DESTINATION lib/cmake/freenect2/)
INSTALL(FILES "${PROJECT_BINARY_DIR}/freenect2.pc" DESTINATION lib/pkgconfig/)

find_package(Doxygen)
IF(DOXYGEN_FOUND)
  CONFIGURE_FILE(Doxyfile.in "${PROJECT_BINARY_DIR}/Doxyfile" @ONLY)
  add_custom_target(
    doc
    COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
  )
ENDIF()

IF(BUILD_EXAMPLES)
  MESSAGE(STATUS "Configurating examples")
  ADD_SUBDIRECTORY(${MY_DIR}/examples)
ENDIF()