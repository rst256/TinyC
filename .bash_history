gcc
./configure --help
./configure  --enable-mingw32   --strip-binaries
mingw32-make
make
./configure 
make
./configure --help
./configure   --enable-cross  --extra-cflags=-Iwin32/include
make
./configure   --enable-cross  
make
win32/build-tcc.bat 
cd ..
patch i386-a
cd tcc-0.9.26/
patch i386-asm.c patch.diff 
patch i386-asm.c patch.diff 
