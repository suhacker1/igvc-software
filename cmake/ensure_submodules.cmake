find_package(Git QUIET)

set(EXTERNAL_PACKAGES rj-ros-common)
set(EXTERNAL_PACKAGES_FOUND True)

if(NOT WIN32)
    string(ASCII 27 Esc)
    set(ColourReset "${Esc}[m")
    set(ColourBold  "${Esc}[1m")
    set(Red         "${Esc}[31m")
    set(Green       "${Esc}[32m")
    set(Yellow      "${Esc}[33m")
    set(Blue        "${Esc}[34m")
    set(Magenta     "${Esc}[35m")
    set(Cyan        "${Esc}[36m")
    set(White       "${Esc}[37m")
    set(BoldRed     "${Esc}[1;31m")
    set(BoldGreen   "${Esc}[1;32m")
    set(BoldYellow  "${Esc}[1;33m")
    set(BoldBlue    "${Esc}[1;34m")
    set(BoldMagenta "${Esc}[1;35m")
    set(BoldCyan    "${Esc}[1;36m")
    set(BoldWhite   "${Esc}[1;37m")
endif()

if(NOT EXISTS ${GIT_REPO_DIR}/external)
    set(EXTERNAL_PACKAGES_FOUND False)
    message(WARNING "Couldn't find directory for external packages...")
endif()

foreach(EXTERNAL_PACKAGE ${EXTERNAL_PACKAGES})
    if(NOT EXISTS ${GIT_REPO_DIR}/external/${EXTERNAL_PACKAGE})
        set(EXTERNAL_PACKAGES_FOUND False)
        message(WARNING "Couldn't find external package external/${EXTERNAL_PACKAGE}...")
    endif()
endforeach()

if(NOT EXTERNAL_PACKAGES_FOUND)
    if(GIT_FOUND AND EXISTS "${GIT_REPO_DIR}/.git")
        message(STATUS "Running git submodule update --init --recursive...")
        # Update submodules as needed
        option(GIT_SUBMODULE "Check submodules during build" ON)
        if(GIT_SUBMODULE)
            message(STATUS "Submodule update")
            execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY ${GIT_REPO_DIR}
                RESULT_VARIABLE GIT_SUBMOD_RESULT)
            if(NOT GIT_SUBMOD_RESULT EQUAL "0")
                message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
            endif()
        endif()

        set(EXTERNAL_PACKAGES_FOUND True)
        foreach(EXTERNAL_PACKAGE ${EXTERNAL_PACKAGES})
            if(NOT EXISTS ${GIT_REPO_DIR}/external/${EXTERNAL_PACKAGE})
                set(EXTERNAL_PACKAGES_FOUND False)
            endif()
        endforeach()

        if(EXTERNAL_PACKAGES_FOUND)
            message(STATUS "Found all external packages after git submodule update --init --recursive!")
        endif()
        message(STATUS "${BoldRed}============================================================${ColourReset}")
        message(STATUS "${BoldRed}=                   RERUN CATKIN_MAKE                      =${ColourReset}")
        message(STATUS "${BoldRed}============================================================${ColourReset}")
        message(FATAL_ERROR "Read the above message.")
    endif()
endif()
