.PHONY: clean

BUILD_DIRECTORY = "_build"

build:
	cmake -B$(BUILD_DIRECTORY) --preset default

clean:
	rm -rf $(BUILD_DIRECTORY)