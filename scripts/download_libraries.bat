@echo off

REM  Download SDL2
if not exist libraries\SDL2-2.0.14 (
	curl	 -o SDL2.zip -OL https://www.libsdl.org/release/SDL2-2.0.14.tar.gz
	tar -xf SDL2.zip -C libraries
	del SDL2.zip
)

REM  Download GLM
if not exist libraries\glm-0.9.9.8 (
	curl	 -o glm.zip -OL https://github.com/g-truc/glm/archive/refs/tags/0.9.9.8.tar.gz
	tar -xf glm.zip -C libraries
	del glm.zip
)
