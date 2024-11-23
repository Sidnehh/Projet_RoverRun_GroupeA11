# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Sidne/OneDrive/Bureau/Projet_RoverRun_GroupeA11/cmake-build-debug/_deps/src/raylib"
  "C:/Users/Sidne/OneDrive/Bureau/Projet_RoverRun_GroupeA11/cmake-build-debug/_deps/src/raylib-build"
  "C:/Users/Sidne/OneDrive/Bureau/Projet_RoverRun_GroupeA11/cmake-build-debug/_deps"
  "C:/Users/Sidne/OneDrive/Bureau/Projet_RoverRun_GroupeA11/cmake-build-debug/_deps/tmp"
  "C:/Users/Sidne/OneDrive/Bureau/Projet_RoverRun_GroupeA11/cmake-build-debug/_deps/src/raylib-stamp"
  "C:/Users/Sidne/OneDrive/Bureau/Projet_RoverRun_GroupeA11/cmake-build-debug/_deps/src"
  "C:/Users/Sidne/OneDrive/Bureau/Projet_RoverRun_GroupeA11/cmake-build-debug/_deps/src/raylib-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Sidne/OneDrive/Bureau/Projet_RoverRun_GroupeA11/cmake-build-debug/_deps/src/raylib-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/Sidne/OneDrive/Bureau/Projet_RoverRun_GroupeA11/cmake-build-debug/_deps/src/raylib-stamp${cfgdir}") # cfgdir has leading slash
endif()
