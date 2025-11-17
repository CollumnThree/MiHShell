all:
	mkdir -p build
	@clang++ -std=c++23 -o build/shell src/*.cpp

run:
	@exec build/shell
