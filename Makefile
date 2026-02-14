debug:
	@mkdir -p build
	@echo "Compiling Project"
	@clang++ -std=c++20 -Werror -fsanitize=address,undefined -fno-omit-frame-pointer -Wall -Wextra -Wshadow -Wconversion -Wsign-conversion -Wpedantic -O0 -g -o build/shell src/*.cpp
run:
	@exec build/shell
release:
	@mkdir -p build
	@echo "Compiling Project"
	@clang++ -std=c++20 -flto -march=native -O3 -o build/shell src/*.cpp
