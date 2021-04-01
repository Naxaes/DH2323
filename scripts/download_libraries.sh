#!/bin/zsh

export LC_ALL=en_US.UTF-8
export LANG=en_EN.UTF-8

if [ ! -d "libraries/SDL2-2.0.14" ]; then
  curl -o SDL2.zip -OL https://www.libsdl.org/release/SDL2-2.0.14.tar.gz
  tar -xf SDL2.zip -C libraries
  rm SDL2.zip
fi

if [ ! -d "libraries/glm-0.9.9.8" ]; then
  curl -o glm.zip -OL https://github.com/g-truc/glm/archive/refs/tags/0.9.9.8.tar.gz
  tar -xf glm.zip -C libraries
  rm glm.zip
fi
