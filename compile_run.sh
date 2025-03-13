rm -r build/
mkdir build
gcc src/*.c -o build/nook -lncurses && ./build/nook
