all:
	clang++-16 -std=c++20 -xc++-system-header --precompile iostream -o iostream.pcm
	clang++-16 -std=c++20 -fmodule-file=iostream.pcm HelloModule.cxx -o HelloModule