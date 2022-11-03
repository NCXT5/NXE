CXX = g++
RMDIR = rm -f
BUILD_DIR = build
SOURCE_DIR = src
CXX_ARGS = -std=c++23

default: debug

release:
	rm -rf $(BUILD_DIR)
	mkdir build
	mkdir build/release
	$(CXX) -o $(BUILD_DIR)/release/nxe $(SOURCE_DIR)/**/*.cxx -O3 -Isrc/**/*.hxx $(CXX_ARGS)

debug:
	rm -rf $(BUILD_DIR)
	mkdir build
	mkdir build/debug
	$(CXX) -o $(BUILD_DIR)/debug/nxe $(SOURCE_DIR)/**/*.cxx -g -Isrc/**/*.hxx $(CXX_ARGS)

debug-run:
	make debug
	$(BUILD_DIR)/debug/nxe

release-run:
	make release
	$(BUILD_DIR)/release/nxe
