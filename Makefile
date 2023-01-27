.PHONY: clean

TARGET = "Unix Makefiles"
ifeq ($(OS), Windows_NT)
TARGET = "Visual Studio 17 2022"
endif

build:
	cmake -B_build -G$(TARGET)

clean:
	rm -rf _build