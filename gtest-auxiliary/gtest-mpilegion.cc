/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2014 Los Alamos National Security, LLC
 * All rights reserved.
 *~-------------------------------------------------------------------------~~*/

#include <gtest/gtest.h>
#include <mpi.h>

#define _UTIL_STRINGIFY(s) #s
#define EXPAND_AND_STRINGIFY(s) _UTIL_STRINGIFY(s)

#ifndef GTEST_INIT
  #include "gtest-init.h"
#else
  #include EXPAND_AND_STRINGIFY(GTEST_INIT)
#endif

#undef EXPAND_AND_STRINGIFY
#undef _UTIL_STRINGIFY

#include "listener.h"

int gtest_mpilegion_argc;
char** gtest_mpilegion_argv;

int main(int argc, char ** argv) {

  gtest_mpilegion_argc = argc;
  gtest_mpilegion_argv = argv;
  
  int version, subversion;
  MPI_Get_version(&version, &subversion);
  std::cout <<"MPI version = "<< version<< " , subversion =" <<
    subversion << std::endl;
//TOFIX:: add check for Gasnet conduit
  if(version==3 && subversion>0){
    int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
    // If you fail this assertion, then your version of MPI
    // does not support calls from multiple threads and you 
    // cannot use the GASNet MPI conduit
    if (provided < MPI_THREAD_MULTIPLE)
      printf("ERROR: Your implementation of MPI does not support "
           "MPI_THREAD_MULTIPLE which is required for use of the "
           "GASNet MPI conduit with the Legion-MPI Interop!\n");
    assert(provided == MPI_THREAD_MULTIPLE);
  }
  else{
    // Initialize the MPI runtime
    MPI_Init(&argc, &argv);
  }
  // Initialize the GTest runtime
  ::testing::InitGoogleTest(&argc, argv);

  ::testing::TestEventListeners& listeners =
    ::testing::UnitTest::GetInstance()->listeners();

  // Adds a listener to the end.  Google Test takes the ownership.
  listeners.Append(new cinch::listener);

  // Call the user-provided initialization function
  gtest_init(argc, argv);

  int result = RUN_ALL_TESTS();

  // Shutdown the MPI runtime
  // GMS: HACK as we are racing with Legion/GASNet 
  //MPI_Finalize();

  return result;

} // main

/*~------------------------------------------------------------------------~--*
 * vim: set tabstop=2 shiftwidth=2 expandtab :
 *~------------------------------------------------------------------------~--*/
