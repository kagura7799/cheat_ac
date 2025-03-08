CC = cl
CFLAGS = /EHsc /std:c++17 /I ../include
LDFLAGS = /link User32.lib

SRC = \
    src/main.cpp \
    src/cheat.cpp \
    src/memory.cpp \
    src/offsets.cpp \
    src/esp/esp.cpp \
    src/esp/render.cpp \
    src/esp/vectors.cpp \
    src/aim/aimbot.cpp
TARGET = cheat.exe

all:
	$(CC) $(SRC) $(CFLAGS) /Fe$(TARGET) $(LDFLAGS)

clean:
	del /Q $(TARGET)
