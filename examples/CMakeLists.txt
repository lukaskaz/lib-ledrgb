cmake_minimum_required(VERSION 3.10)

option(ADD_EXAMPLES "Creates examples" OFF)

if(POLICY CMP0002)
    cmake_policy(SET CMP0002 OLD)
    set_property(GLOBAL PROPERTY ALLOW_DUPLICATE_CUSTOM_TARGETS TRUE)
endif()

if(ADD_EXAMPLES)
    if(USE_RPI4)
        add_subdirectory(rpi4/ws281x)
    elseif(USE_RPI5)
        add_subdirectory(rpi5/ws281x)
    endif()
endif()
