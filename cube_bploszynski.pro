HEADERS += \
    cube.h \
    matma.h \
    window.h \
    glfunctions.h \
    vertices.h \
    indexmodel.h \
    baseprogram.h \
    cameraprogram.h \
    modelprogram.h \
    movablemodel.h

SOURCES += \
    main.cpp \
    matma.cpp \
    window.cpp \
    cube.cpp \
    indexmodel.cpp \
    baseprogram.cpp \
    cameraprogram.cpp \
    modelprogram.cpp

OTHER_FILES += \
    data/SimpleShader.fragment.glsl \
    data/SimpleShader.vertex.glsl

    
win32{
    copydata.commands = $(COPY_DIR) "$$shell_path("$$PWD/data")" "$$shell_path("$$OUT_PWD")"
}

unix{
    copydata.commands = $(COPY_DIR) $$PWD/data/* $$OUT_PWD
    CONFIG   += c++11
}

first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
