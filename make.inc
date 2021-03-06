
#############################################################################
# configure.sh substitutions
#############################################################################

# Top directory
PROJECT_TOP = /work/02423/zst75/fresh_NEMO5

# ... or specify by hand:
# PROJECT_TOP = /home/mydir

# Platform build type
BUILD_TYPE = stampede-intel64


#############################################################################
# Should not need to edit below, unless adding new platform
#############################################################################


MAKE      = make
AR        = ar
ARFLAGS   = ruv
AR_FLAGS  = ruv
RANLIB    = ranlib
CD        = cd
ECHO      = echo
LN        = ln
LNFLAGS   = -s
RM        = rm
RMFLAGS   = -f
MV        = mv
MVFLAGS   = -f
SHELL     = sh
LIB       = -lm
LEX       = flex
YACC      = bison

USER = $(shell whoami)


#<ss> -axP instead of -msse3; use mpich-intel-10.1.013
ifeq ($(BUILD_TYPE),nanohub)
include $(PROJECT_TOP)/mkfiles/make.inc.nanohub
endif


ifeq ($(BUILD_TYPE),steele-intel64-mpich2)
include $(PROJECT_TOP)/mkfiles/make.inc.steele-intel64-mpich2
endif

ifeq ($(BUILD_TYPE),coates-intel64-mpich2)
include $(PROJECT_TOP)/mkfiles/make.inc.coates-intel64-mpich2
endif

ifeq ($(BUILD_TYPE),coates-intel64-mpich2-libs)
include $(PROJECT_TOP)/mkfiles/make.inc.coates-intel64-mpich2-libs
endif


ifeq ($(BUILD_TYPE),coates-intel64-mvapich-petsc33)
include $(PROJECT_TOP)/mkfiles/make.inc.coates-intel64-mvapich-petsc33
endif

ifeq ($(BUILD_TYPE),coates-intel64-mvapich-petsc33-libs)
include $(PROJECT_TOP)/mkfiles/make.inc.coates-intel64-mvapich-petsc33-libs
endif

ifeq ($(BUILD_TYPE),coates-debug-libs)
include $(PROJECT_TOP)/mkfiles/make.inc.coates-debug-libs
endif

ifeq ($(BUILD_TYPE),carter)
include $(PROJECT_TOP)/mkfiles/make.inc.carter
endif

ifeq ($(BUILD_TYPE),carter-impi-petsc33)
include $(PROJECT_TOP)/mkfiles/make.inc.carter-impi-petsc33
endif

ifeq ($(BUILD_TYPE),carter-impi-petscdev)
include $(PROJECT_TOP)/mkfiles/make.inc.carter-impi-petscdev
endif

ifeq ($(BUILD_TYPE),mac)
include $(PROJECT_TOP)/mkfiles/make.inc.mac
endif

ifeq ($(BUILD_TYPE),carter-libs)
include $(PROJECT_TOP)/mkfiles/make.inc.carter-libs
endif


ifeq ($(BUILD_TYPE),carter-debug-libs)
include $(PROJECT_TOP)/mkfiles/make.inc.carter-debug-libs
endif
# for Ubuntu/Kubuntu make sure you do NOT install the packages qhull, petsc, slepc, tetgen!!!
# packages needed: libmpich2-dev, g++, gfortran, gcc, libboost1.40-dev, libboost-iostreams1.40-dev, 
# libboost-test1.40-dev libboost-filesystems1.40-dev, liblapack-dev, m4, xutils-dev
# cd NEMO/; ./configure.sh sebuntu; cd libs/; make; cd ../MaterialDB; make; cd ../prototype; make;
ifeq ($(BUILD_TYPE),sebuntu)
include $(PROJECT_TOP)/mkfiles/make.inc.sebuntu
endif


ifeq ($(BUILD_TYPE),static-ubuntu)
include $(PROJECT_TOP)/mkfiles/make.inc.static-ubuntu
endif

ifeq ($(BUILD_TYPE),steele-gcc64-mpich2)
include $(PROJECT_TOP)/mkfiles/make.inc.steele-gcc64-mpich2
endif

ifeq ($(BUILD_TYPE),coates-gcc64-mpich2)
include $(PROJECT_TOP)/mkfiles/make.inc.coates-gcc64-mpich2
endif


# must load {visit,fftw}, and module swap PrgEnv-pgi PrgEnv-gnu; also set XTPE_INFO_MESSAGE_OFF=1
ifeq ($(BUILD_TYPE),jaguar-gcc64)
include $(PROJECT_TOP)/mkfiles/make.inc.jaguar-gcc64
endif

# for Ranger (TACC) load intel/10.1, mvapich2
ifeq ($(BUILD_TYPE),ranger-intel64)
include $(PROJECT_TOP)/mkfiles/make.inc.ranger-intel64
endif

# for Stampede (TACC) load intel/13.1, mvapich2
ifeq ($(BUILD_TYPE),stampede-intel64)
include $(PROJECT_TOP)/mkfiles/make.inc.stampede-intel64
endif

# for Kraken (NICS) load etc. 
ifeq ($(BUILD_TYPE),kraken-gcc64)
include $(PROJECT_TOP)/mkfiles/make.inc.kraken-gcc64
endif
# for blueweaters (NICS) load etc. 
ifeq ($(BUILD_TYPE),bluewaters)
include $(PROJECT_TOP)/mkfiles/make.inc.bluewaters
endif

#
# for blueweaters (NICS) load etc. 
ifeq ($(BUILD_TYPE),Tianhe-intel64-mpich2)
include $(PROJECT_TOP)/mkfiles/make.inc.make.inc.Tianhe-intel64-mpich2
endif
###########################################################################

# Top 3rd-party library directory
# set special LIB_TOP for group builds
LIB_TOP       = $(PROJECT_TOP)/libs
ifeq ($(BUILD_TYPE),coates-intel64-mpich2-libs)
LIB_TOP = /apps/group/ncn/NEMO5/libs
endif
ifeq ($(BUILD_TYPE),coates-intel64-mpich2-libs-petsc33)
LIB_TOP = /apps/group/ncn/rossmann/petsc33/libs
endif
ifeq ($(BUILD_TYPE),carter-libs)
LIB_TOP = /apps/group/ncn/carter/libs
endif
ifeq ($(BUILD_TYPE),carter-debug-libs)
#LIB_TOP = /apps/group/ncn/carter/libs
LIB_TOP = /apps/group/ncn/carter_debug/libs
endif
ifeq ($(BUILD_TYPE),coates-debug-libs)
LIB_TOP = /apps/group/ncn/NEMO5_rossmann_debug/libs
endif

# Common include paths
INCAMD        = -I $(LIB_TOP)/AMD/Include/
INCUFC        = -I $(LIB_TOP)/UFconfig/
INCUMF        = -I $(LIB_TOP)/UMFPACK/Include/
#INCNEMAT      = -I $(LIB_TOP)/../MaterialDB/GroupDB -I $(LIB_TOP)/../MaterialDB/NEMat -I $(LIB_TOP)/../MaterialDB/nml/include
INCQLL        = -I $(LIB_TOP)/qhull-2010.1/cpp -I$(LIB_TOP)/qhull-2010.1/src
INCTENSOR3D   = -I $(LIB_TOP)/tensor3D
INCTET        = -I $(LIB_TOP)/tetgen1.4.3


# libmesh directory
LIBMESH_LIBS  = -Wl,-rpath,$(LIBMESH_DIR)/lib/$(LIBMESH_ARCH) -L$(LIBMESH_DIR)/lib/$(LIBMESH_ARCH) -lmesh
LIBMESH_LIBS += -Wl,-rpath,$(LIBMESH_DIR)/contrib/lib/$(LIBMESH_ARCH) -L$(LIBMESH_DIR)/contrib/lib/$(LIBMESH_ARCH) $(LIBMESH_CONTRIBS) 
# parmetis, metis is in double petsc, and we use own version of tetgen
LIBMESH_LIBS += -Wl,-rpath,$(SLEPC_REAL_LIBDIR) -L$(SLEPC_REAL_LIBDIR) -lslepc -Wl,-rpath,$(PETSC_REAL_LIBDIR) -L$(PETSC_REAL_LIBDIR) $(PETSC_LIBS) $(PETSC_EXT_LIBS_REAL)
# even though all petsc/slepc symbols that nemo5 uses are mapped into libpetsc_nemo_*.{so,a}, we need to link the double version because libmesh might look for them
ifneq ($(LIBMESH_TECIO_ARCH),)
LIBMESH_LIBS += $(LIBMESH_DIR)/contrib/tecplot/lib/$(LIBMESH_TECIO_ARCH)/tecio.a
endif




# Common link options
#ARPACK        = -Wl,-rpath,$(LIB_TOP)/ARPACK/ -L$(LIB_TOP)/ARPACK/ -larpack
#ARPACK        = -Wl,-rpath,$(LIB_TOP)/ARPACK/ -L$(LIB_TOP)/ARPACK/ -lparpack -larpack
ARPACK        = -Wl,-rpath,$(ARPACK_DIR) -L$(ARPACK_DIR) $(ARPACK_LIBS)
AMD           = -Wl,-rpath,$(LIB_TOP)/AMD/Lib/ -L$(LIB_TOP)/AMD/Lib/ -lamd
#NEMAT         = -Wl,-rpath,$(LIB_TOP)/../MaterialDB/NEMat -L$(LIB_TOP)/../MaterialDB/NEMat -lNEMat-1.00 -Wl,-rpath,$(LIB_TOP)/../MaterialDB/nml/lib -L$(LIB_TOP)/../MaterialDB/nml/lib -lnml 
QHULL         = -Wl,-rpath,$(LIB_TOP)/qhull-2010.1/lib -L$(LIB_TOP)/qhull-2010.1/lib -lqhull++ -lqhull
TENSOR3D      = -Wl,-rpath,$(LIB_TOP)/tensor3D     -L$(LIB_TOP)/tensor3D -ltensor
TETGEN        = -Wl,-rpath,$(LIB_TOP)/tetgen1.4.3  -L$(LIB_TOP)/tetgen1.4.3 -ltet
UMFPACK       = -Wl,-rpath,$(LIB_TOP)/UMFPACK/Lib/ -L$(LIB_TOP)/UMFPACK/Lib/ -lumfpack
MPI           = -Wl,-rpath,$(MPIHOME)/lib -L$(MPIHOME)/lib

