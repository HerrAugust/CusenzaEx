cmake_minimum_required(VERSION 3.13)
project(swatch4 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(swatch4
        code.c
        debug.c
        debug.h
        Event.c
        Event.h
        fonts.c
        fonts.h
        lcd_add.c
        lcd_add.h
        pictures.c
        pictures.h
        rtmodel.h
        rtwtypes.h
        STMPE811QTR.c
        STMPE811QTR.h
        SWatch2018.c
        SWatch2018.h
        Swatch2018.h
        SWatch2018_private.h
        Swatch2018_private.h
        SWatch2018_types.h
        Swatch2018_types.h
        Touch.c
        Touch.h
        Watch.c
        Watch.h
        Widget.c
        Widget.h
        WidgetConfig.c
        WidgetConfig.h
        zero_crossing_types.h)
