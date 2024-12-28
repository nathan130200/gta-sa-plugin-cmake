cmake_minimum_required(VERSION 3.29)

project("GTA")

set(PLUGIN_NAME my_plugin)

# Add your source files.
add_library(${PLUGIN_NAME} SHARED
    src/DllMain.cpp
)

# Link your plugin with PluginSDK lib.
target_link_libraries(${PLUGIN_NAME}
    $<$<CONFIG:Release>:plugin.lib>
    $<$<CONFIG:Debug>:plugin_d.lib>
    "nethost.lib"
)

# PluginSDK include directories.
target_include_directories(${PLUGIN_NAME} 
    PRIVATE
        "$ENV{PLUGIN_SDK_DIR}/plugin_SA"
        "$ENV{PLUGIN_SDK_DIR}/plugin_SA/game_SA"
        "$ENV{PLUGIN_SDK_DIR}/shared"
        "$ENV{PLUGIN_SDK_DIR}/shared/game"
)

# PluginSDK library directories.
target_link_directories(${PLUGIN_NAME} 
    PRIVATE
        "$ENV{DXSDK_DIR}/Lib/x86"
        "$ENV{PLUGIN_SDK_DIR}/output/lib"
        "$ENV{PLUGIN_SDK_DIR}/shared/bass"
        "${PROJECT_SOURCE_DIR}/vendor/coreclr"
)

# Add target compile definitions.
target_compile_definitions(${PLUGIN_NAME} 
    PRIVATE
        _CRT_SECURE_NO_WARNINGS
        _CRT_NON_CONFORMING_SWPRINTFS
        _USE_MATH_DEFINES
        _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

        # Our game is GTASA
        GTASA
        GAMESA

        # Which GTA SA version we are targeting (check in Plugin SDK) - By default 1.0 US
        PLUGIN_SGV_10US

        # "RW" macro allow access to renderware functions.
        RW
)

# Do not touch here!
set_target_properties(${PLUGIN_NAME} PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS On
    SUFFIX ".asi"
)

# Do not touch here!
target_compile_options(${PLUGIN_NAME} PRIVATE
    /std:c++latest 
    /source-charset:windows-1252
    $<$<CONFIG:Debug>:/MTd>
    $<$<CONFIG:Release>:/MT>
)

# Comment everything below if you don't wanna cmake pre build task automatically close your gta_sa.exe (may sometimes gta_sa get stuck)
add_custom_command(TARGET ${PLUGIN_NAME} PRE_BUILD
    COMMAND "cmd.exe" ARGS /c taskkill /im gta_sa.exe /F /FI "STATUS eq RUNNING"
)

# Comment everything below if you don't wanna cmake post build task automatically install your plugin file in GTA directory.
add_custom_command(TARGET ${PLUGIN_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PLUGIN_NAME}> $ENV{GTA_SA_DIR}        
)
