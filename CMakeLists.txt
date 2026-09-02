#-----------------------------------------------------------------------------
# Umicom Music Studio Module
# File: CMakeLists.txt
#
# PURPOSE:
#   Build a thin C23 product composition over Framework-owned application
#   experience, runtime and workbench contracts.
#
# AUTHOR AND ORGANISATION:
#   Sammy Hegab
#   Umicom Foundation
#
# LICENCE:
#   MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)

project(
    MusicStudioModule
    VERSION 0.1.0
    DESCRIPTION "Thin Umicom Music Studio composition over Umicom Framework"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(UMICOM_MUSIC_STUDIO_BUILD_CONSOLE
       "Build the native Umicom Music Studio verification console"
       ON)
option(UMICOM_MUSIC_STUDIO_BUILD_GTK4
       "Build the Framework-rendered native Umicom Music Studio workstation"
       ON)

include(CTest)
include(GNUInstallDirs)

# Load the dependency only when the parent build has not already provided its target.
if(NOT TARGET Umicom::Framework)
    find_package(UmicomFramework CONFIG REQUIRED)
endif()

# Load the dependency only when the parent build has not already provided its target.
if(NOT TARGET Umicom::application)
    message(FATAL_ERROR
        "Umicom Music Studio requires Framework target Umicom::application")
endif()

# Define the local fallback only when the parent build did not provide the shared helper.
if(NOT COMMAND umicom_apply_warnings)
    # Define the apply warnings build helper so parent and application projects apply one
    # consistent rule.
    function(umicom_apply_warnings target)
        # Select the warning options understood by the active compiler.
        if(MSVC)
            target_compile_options(${target} PRIVATE /W4)
        # Use this fallback path when the earlier condition does not apply.
        else()
            target_compile_options(${target} PRIVATE
                -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
        endif()
    endfunction()
endif()

# Define the local fallback only when the parent build did not provide the shared helper.
if(NOT COMMAND umicom_apply_sanitizers)
    # Define the apply sanitizers build helper so parent and application projects apply one
    # consistent rule.
    function(umicom_apply_sanitizers target)
    endfunction()
endif()

add_library(umicom_music_studio_module STATIC
    src/application_surface.c
    src/application_surface_controllers.c
    src/application.c
    src/workspace.c
)
add_library(Umicom::music_studio_module ALIAS umicom_music_studio_module)

target_include_directories(umicom_music_studio_module PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(umicom_music_studio_module PUBLIC
    Umicom::Framework
    Umicom::application
)
umicom_apply_warnings(umicom_music_studio_module)
umicom_apply_sanitizers(umicom_music_studio_module)

include(
    "${CMAKE_CURRENT_SOURCE_DIR}/../../framework/cmake/UmicomThinApplicationRuntime.cmake")
umicom_extend_thin_application_runtime(
    NAME "music"
    TARGET "umicom_music_studio_module")

# Create this optional product surface only when its build option is enabled.
if(UMICOM_MUSIC_STUDIO_BUILD_CONSOLE)
    add_executable(umicom-music-studio-console
        src/console/main.c)
    target_link_libraries(umicom-music-studio-console PRIVATE Umicom::music_studio_module)
    umicom_apply_warnings(umicom-music-studio-console)
    umicom_apply_sanitizers(umicom-music-studio-console)
endif()

# Music Studio supplies its safe creative controller and delegates the native
# workspace, rendering and customisation systems to Framework.
if(UMICOM_MUSIC_STUDIO_BUILD_GTK4 AND TARGET Umicom::ui_gtk4)
    add_library(umicom_music_studio_gtk STATIC src/gtk/workstation.c)
    add_library(Umicom::music_studio_gtk ALIAS umicom_music_studio_gtk)
    target_include_directories(umicom_music_studio_gtk PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
    target_link_libraries(umicom_music_studio_gtk PUBLIC
        Umicom::music_studio_module
        Umicom::ui_gtk4)
    umicom_apply_warnings(umicom_music_studio_gtk)
    umicom_apply_sanitizers(umicom_music_studio_gtk)

    add_executable(umicom-music-studio src/gtk/main.c)
    target_link_libraries(umicom-music-studio PRIVATE
        Umicom::music_studio_gtk)
    umicom_apply_warnings(umicom-music-studio)
    umicom_apply_sanitizers(umicom-music-studio)
    # Define the local fallback only when the parent build did not provide the shared helper.
    if(NOT COMMAND umicom_apply_application_branding)
        include(
            "${CMAKE_CURRENT_SOURCE_DIR}/../../framework/cmake/UmicomApplicationBranding.cmake")
    endif()
    umicom_apply_application_branding(
        TARGET umicom-music-studio
        PRODUCT_NAME "Umicom Music Studio"
        INTERNAL_NAME "umicom-music-studio"
        APPLICATION_ID "org.umicom.music-studio"
        VERSION_MAJOR ${PROJECT_VERSION_MAJOR}
        VERSION_MINOR ${PROJECT_VERSION_MINOR}
        VERSION_PATCH ${PROJECT_VERSION_PATCH}
        RESOURCE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../framework/resources"
        DESKTOP_ENTRY
        WINDOWS_GUI)
# Apply this branch only when its contract condition is satisfied.
elseif(UMICOM_MUSIC_STUDIO_BUILD_GTK4)
    message(STATUS
        "Umicom Music Studio native workstation disabled because Umicom::ui_gtk4 is unavailable")
endif()

# Register verification targets only when the developer has enabled testing.
if(BUILD_TESTING)
    add_executable(music-application-surface-test
        tests/test_application_surface.c)
    target_link_libraries(music-application-surface-test PRIVATE
        Umicom::music_studio_module)
    umicom_apply_warnings(music-application-surface-test)
    umicom_apply_sanitizers(music-application-surface-test)
    add_test(NAME music.module.application_surface
             COMMAND music-application-surface-test)

    add_executable(music-application-test
        tests/test_application.c)
    target_link_libraries(music-application-test PRIVATE Umicom::music_studio_module)
    umicom_apply_warnings(music-application-test)
    umicom_apply_sanitizers(music-application-test)
    add_test(NAME music.module.application
             COMMAND music-application-test)

    add_executable(music-workspace-test
        tests/test_workspace.c)
    target_link_libraries(music-workspace-test PRIVATE Umicom::music_studio_module)
    umicom_apply_warnings(music-workspace-test)
    umicom_apply_sanitizers(music-workspace-test)
    add_test(NAME music.module.workspace
             COMMAND music-workspace-test)
endif()

install(TARGETS umicom_music_studio_module
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
# Configure the optional target only when its feature has created it.
if(TARGET umicom-music-studio-console)
    install(TARGETS umicom-music-studio-console
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
# Configure the optional target only when its feature has created it.
if(TARGET umicom-music-studio)
    install(TARGETS umicom-music-studio
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES application.umicom.yaml README.md
    DESTINATION ${CMAKE_INSTALL_DATADIR}/umicom/applications/music)
# Use the optional file only when it is present in this checkout.
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
    install(FILES LICENSE
        DESTINATION ${CMAKE_INSTALL_DATADIR}/licenses/music)
endif()

message(STATUS "Umicom Music Studio Module version: ${PROJECT_VERSION}")
message(STATUS "Umicom Music Studio uses Framework-owned application experience")

include(
    "${CMAKE_CURRENT_SOURCE_DIR}/../../framework/cmake/UmicomApplicationProductisationContribution.cmake")
umicom_add_application_productisation_contribution(
    NAME "music"
    TARGET umicom_music_productisation
    SOURCE "src/productisation_contribution.c"
    TEST_SOURCE "tests/test_productisation_contribution.c")
