# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Users/jbali/OneDrive/Pulpit/PCC GIT/git/Gra2DCPP/cmake-build-debug/_deps/fmt-src")
  file(MAKE_DIRECTORY "C:/Users/jbali/OneDrive/Pulpit/PCC GIT/git/Gra2DCPP/cmake-build-debug/_deps/fmt-src")
endif()
file(MAKE_DIRECTORY
  "C:/Users/jbali/OneDrive/Pulpit/PCC GIT/git/Gra2DCPP/cmake-build-debug/_deps/fmt-build"
  "C:/Users/jbali/OneDrive/Pulpit/PCC GIT/git/Gra2DCPP/cmake-build-debug/_deps/fmt-subbuild/fmt-populate-prefix"
  "C:/Users/jbali/OneDrive/Pulpit/PCC GIT/git/Gra2DCPP/cmake-build-debug/_deps/fmt-subbuild/fmt-populate-prefix/tmp"
  "C:/Users/jbali/OneDrive/Pulpit/PCC GIT/git/Gra2DCPP/cmake-build-debug/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp"
  "C:/Users/jbali/OneDrive/Pulpit/PCC GIT/git/Gra2DCPP/cmake-build-debug/_deps/fmt-subbuild/fmt-populate-prefix/src"
  "C:/Users/jbali/OneDrive/Pulpit/PCC GIT/git/Gra2DCPP/cmake-build-debug/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/jbali/OneDrive/Pulpit/PCC GIT/git/Gra2DCPP/cmake-build-debug/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/jbali/OneDrive/Pulpit/PCC GIT/git/Gra2DCPP/cmake-build-debug/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
