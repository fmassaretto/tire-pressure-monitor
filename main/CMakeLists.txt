idf_component_register(SRCS 
"main.cpp"
"config/tire_pressure_monitor_config.c" 
"ui/ui.c" 
"utils/util.cpp" 
"ui/screens/ui_screen1.cpp" 
"ui/screens/ui_screen2.cpp" 
"domains/buttons/Button.cpp"
"domains/sensors/I2C.cpp"
"domains/sensors/pressure/Pressure.cpp"
"domains/sensors/temperature/Temperature.cpp"
INCLUDE_DIRS ".")
