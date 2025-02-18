cmake_minimum_required(VERSION 3.10)

include(ExternalProject)

set(source_dir "${CMAKE_BINARY_DIR}/libws2811-src")
set(build_dir "${CMAKE_BINARY_DIR}/libws2811-build")

EXTERNALPROJECT_ADD(
  libws2811
  GIT_REPOSITORY    https://github.com/jgarff/rpi_ws281x.git
  GIT_TAG           master
  PATCH_COMMAND     ""
  PREFIX            libws2811-workspace
  SOURCE_DIR        ${source_dir}
  BINARY_DIR        ${build_dir}
  CONFIGURE_COMMAND mkdir /${build_dir}/build &> /dev/null
  BUILD_COMMAND     cd ${build_dir}/build && cmake -D BUILD_SHARED_LIBS=ON
                      -D BUILD_TEST=OFF ${source_dir} && make -j 4
  UPDATE_COMMAND    ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

include_directories(${source_dir})
link_directories(${build_dir}/build)
