# - Try to find CEREAL
#
find_package(PkgConfig)

pkg_check_modules(PC_CEREAL cereal)

find_path(CEREAL_INCLUDE_DIR cereal.hpp HINTS ${PC_CEREAL_NCLUDE_DIRS} ${CMAKE_PREFIX_PATH})


set(CEREAL_INCLUDE_DIRS ${CEREAL_INCLUDE_DIR})

if (NOT CEREAL_INCLUDE_DIR)

set(CEREAL_ROOT "/usr" CACHE PATH "Root directory of CEREAL installation")

find_path(CEREAL_CHECK_DIR cereal.hpp HINTS ${CEREAL_ROOT} ${CEREAL_ROOT}/include/cereal)

if (NOT CEREAL_CHECK_DIR)

 message (WARNING " CEREAL package was not found in your system,
                   please set a correct  CEREAL_ROOT variable ")
else( NOT CEREAL_CHECK_DIR)

set(CEREAL_INCLUDE_DIRS ${CEREAL_CHECK_DIR}/../)
set (CEREAL_FOUND ON)

endif (NOT CEREAL_CHECK_DIR)

endif(NOT CEREAL_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LAPACKE_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(CEREAL DEFAULT_MSG  CEREAL_INCLUDE_DIRS )

mark_as_advanced(CEREAL_INCLUDE_DIR CEREAL_CHECK_DIR)


