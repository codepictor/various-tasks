# Install script for directory: /home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/HelloWorld" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/HelloWorld")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/HelloWorld"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/HelloWorld")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/HelloWorld")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/HelloWorld" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/HelloWorld")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/HelloWorld")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/HelloWorld")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/HelloWorld.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/HelloWorld.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Window" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Window")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Window"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Window")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/Window")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Window" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Window")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Window")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Window")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Window.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Window.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Label" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Label")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Label"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Label")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/Label")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Label" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Label")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Label")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Label")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Label.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Label.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Box" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Box")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Box"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Box")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/Box")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Box" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Box")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Box")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Box")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Box.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Box.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Entry" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Entry")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Entry"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Entry")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/Entry")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Entry" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Entry")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Entry")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Entry")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Entry.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Entry.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Range" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Range")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Range"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Range")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/Range")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Range" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Range")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Range")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Range")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Range.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Range.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Desktop" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Desktop")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Desktop"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Desktop")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/Desktop")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Desktop" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Desktop")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Desktop")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Desktop")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Desktop.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Desktop.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Signals" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Signals")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Signals"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Signals")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/Signals")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Signals" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Signals")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Signals")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Signals")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Signals.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Signals.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/OpenGL" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/OpenGL")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/OpenGL"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/OpenGL")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/OpenGL")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/OpenGL" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/OpenGL")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/OpenGL")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/OpenGL")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/OpenGL.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/OpenGL.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/ComboBox" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/ComboBox")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/ComboBox"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/ComboBox")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/ComboBox")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/ComboBox" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/ComboBox")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/ComboBox")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/ComboBox")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/ComboBox.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/ComboBox.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Notebook" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Notebook")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Notebook"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Notebook")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/Notebook")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Notebook" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Notebook")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Notebook")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Notebook")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Notebook.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Notebook.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/GuessMyNumber" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/GuessMyNumber")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/GuessMyNumber"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/GuessMyNumber")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/GuessMyNumber")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/GuessMyNumber" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/GuessMyNumber")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/GuessMyNumber")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/GuessMyNumber")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/GuessMyNumber.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/GuessMyNumber.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Multiview" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Multiview")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Multiview"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Multiview")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/Multiview")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Multiview" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Multiview")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Multiview")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Multiview")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Multiview.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Multiview.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Image" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Image")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Image"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Image")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/Image")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Image" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Image")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Image")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Image")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Image.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Image.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Layout" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Layout")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Layout"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Layout")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/Layout")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Layout" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Layout")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Layout")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Layout")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Layout.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Layout.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/ScrolledWindowViewport" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/ScrolledWindowViewport")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/ScrolledWindowViewport"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/ScrolledWindowViewport")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/ScrolledWindowViewport")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/ScrolledWindowViewport" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/ScrolledWindowViewport")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/ScrolledWindowViewport")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/ScrolledWindowViewport")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/ScrolledWindowViewport.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/ScrolledWindowViewport.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Spinner" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Spinner")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Spinner"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Spinner")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/Spinner")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Spinner" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Spinner")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Spinner")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Spinner")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Spinner.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Spinner.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Table" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Table")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Table"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Table")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/Table")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Table" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Table")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Table")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Table")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Table.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Table.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Buttons" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Buttons")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Buttons"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Buttons")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/Buttons")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Buttons" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Buttons")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Buttons")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Buttons")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Buttons.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Buttons.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/ProgressBar" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/ProgressBar")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/ProgressBar"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/ProgressBar")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/ProgressBar")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/ProgressBar" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/ProgressBar")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/ProgressBar")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/ProgressBar")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/ProgressBar.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/ProgressBar.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/SpinButton" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/SpinButton")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/SpinButton"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/SpinButton")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/SpinButton")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/SpinButton" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/SpinButton")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/SpinButton")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/SpinButton")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/SpinButton.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/SpinButton.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Canvas" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Canvas")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Canvas"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Canvas")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/Canvas")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Canvas" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Canvas")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Canvas")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/Canvas")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Canvas.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Canvas.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/CustomWidget" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/CustomWidget")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/CustomWidget"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/CustomWidget")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/CustomWidget")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/CustomWidget" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/CustomWidget")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/CustomWidget")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/CustomWidget")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/CustomWidget.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/CustomWidget.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/SFGUI-Test" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/SFGUI-Test")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/SFGUI-Test"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/SFGUI-Test")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE EXECUTABLE FILES "/home/artem/artem/MIPT/infa/project/sfgui-build/examples/SFGUI-Test")
  if(EXISTS "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/SFGUI-Test" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/SFGUI-Test")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/SFGUI-Test")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/share/SFGUI/examples/SFGUI-Test")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/Test.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE FILE FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Test.cpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/SFGUI/examples/data")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/SFGUI/examples" TYPE DIRECTORY FILES "/home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/data")
endif()

