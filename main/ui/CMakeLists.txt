SET(SOURCES screens/ui_Screen1.cpp
    screens/ui_Screen2.cpp
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c)

add_library(ui ${SOURCES})
