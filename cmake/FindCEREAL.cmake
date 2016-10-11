# - Try to find CEREAL
#
find_package(PkgConfig)

pkg_check_modules(PC_CEREAL cereal)

set(CEREAL_ROOT "" CACHE PATH "Root directory of CEREAL installation")


find_path(CEREAL_INCLUDE_DIR cereal.hpp
  HINTS ENV CEREAL_ROOT
  PATHS ${CEREAL_ROOT}
  PATH_SUFFIXES include/cereal)

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LAPACKE_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(CEREAL REQUIRED_VARS CEREAL_INCLUDE_DIR)

mark_as_advanced(CEREAL_INCLUDE_DIR)


