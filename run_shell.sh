#!/bin/sh

set -e # Exit early if any commands fail

export VCPKG_ROOT="$HOME/vcpkg"

(
  cd "$(dirname "$0")" # Ensure compile steps are run within the repository directory
  cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
  cmake --build ./build
)

exec ./build/shell "$@"
