all:
	@mkdir -p build
	@echo "Compiling"
	@clang++ -std=c++20 -Isec/headers -o build/shell src/*.cpp

run:
	@exec build/shell
