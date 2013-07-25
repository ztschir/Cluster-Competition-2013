#!/bin/bash

let nargs=$#
if [ $nargs != 1 ]; then
echo "Input parameter is missing. You have to execute:"
echo "./configure.sh BUILD_TYPE"
echo
echo "Available options for BUILD_TYPE:"
echo 
echo "carter                     (carter.rcac.purdue.edu)"
echo "carter-libs                (same as above but uses libs in group's shared application space)"
echo "carter-debug-libs          (same as above but with full (python/boost) debuggging)"
echo "carter-impi-petsc33        (same as 'carter' but with PETSc 3.3)"
echo "carter-impi-petscdev       (same as 'carter' but with PETSc developmental version)"
echo "carter-static              (same as carter but static build)"
echo "coates-intel64-mpich2      (Intel compiler on {coates,steele,rossmann}.rcac.purdue.edu with MKL)"
echo "coates-intel64-mpich2-libs         (same as above but uses libs in group's shared application space)"
echo "coates-intel64-mvapich-petsc33 (same as above but with PETSc 3.3)"
echo "coates-intel64-mvapich-petsc33-libs      (same as above but without group libraries)"
echo "coates-debug-libs          (same as above but with full (python/boost) debugging)"
echo "mac                        (for Macs)"
echo "nanohub                    (nanohub.org)"
echo "sebuntu                    (generic Kubuntu 10.04)"
echo "static-ubuntu              (static build on ubuntu)"
echo "ranger-intel64             (ranger.tacc.utexas.edu)"
echo "jaguar-gcc64               (Cray XT4 supercomputer jaguar.ccs.ornl.gov)"
echo "kraken-gcc64               (Cray XT5 supercomputer)"
echo "bluewaters                 (BlueWaters supercomputer with gcc)"
echo "bluewaters-cuda            (BlueWaters supercomputer with gcc and cuda)"
echo "Tianhe-intel64-mpich2      (Tianhe-1A supercomputer with intel)"
echo 
echo "configuration is NOT YET done!"
else
if  [ $1 != "coates-intel64-mpich2" \
	-a  $1 != "mac" \
	-a  $1 != "carter" \
	-a  $1 != "carter-libs" \
	-a  $1 != "carter-debug-libs" \
        -a  $1 != "carter-impi-petsc33" \
        -a  $1 != "carter-impi-petscdev" \
        -a  $1 != "carter-static" \
	-a  $1 != "coates-intel64-mpich2-libs" \
	-a  $1 != "coates-intel64-mvapich-petsc33" \
	-a  $1 != "coates-intel64-mvapich-petsc33-libs" \
	-a  $1 != "coates-debug-libs" \
 	-a $1 != "nanohub" \
 	-a $1 != "sebuntu" \
 	-a $1 != "ranger-intel64" \
 	-a $1 != "jaguar-gcc64" \
	-a $1 != "kraken-gcc64" \
	-a $1 != "bluewaters" \
        -a $1 != "bluewaters-cuda" \
   -a $1 != "static-ubuntu" \
   -a $1 != "Tianhe-intel64-mpich2" ]; then
	echo "Incorrect input parameter. Execute ./configure.sh for BUILD_TYPES"
 	echo
	echo "configuration is NOT YET done!"
else  	
top_directory=`pwd`
echo NEMO top directory is $top_directory
sed  "s+#PROJECT_TOP_INSERT+PROJECT_TOP = $top_directory+" make.inc.template > make.inc
echo Build type is $1
if [ $1 == "mac" ]; then
	sed  -i "" -e "s+#BUILD_TYPE_INSERT+BUILD_TYPE = $1+" make.inc
else
	sed  -i "s+#BUILD_TYPE_INSERT+BUILD_TYPE = $1+" make.inc
fi
if [ $1 == "sebuntu" ]; then
	gunzip $PWD/libs/libmesh/libmesh-0.7.2.tar.gz
	tar -xf $PWD/libs/libmesh/libmesh-0.7.2.tar
	gzip $PWD/libs/libmesh/libmesh-0.7.2.tar
	libmesh_architecture_opt=`ls $PWD/libs/libmesh/libmesh/lib`
	libmesh_architecture=${libmesh_architecture_opt/_opt/} 
	echo LIBMESH directory is $libmesh_architecture
	sed "s+#INSERT_LIBMESH_ARCH+LIBMESH_ARCH = $libmesh_architecture_opt+" mkfiles/make.inc.sebuntu.template > mkfiles/make.inc.sebuntu.temp
	sed "s+#INSERT_LIBMESH_TECIO_ARCH+LIBMESH_TECIO_ARCH = $libmesh_architecture+" mkfiles/make.inc.sebuntu.temp > mkfiles/make.inc.sebuntu
	rm mkfiles/make.inc.sebuntu.temp

elif [ $1 == "coates-intel64-mpich2-libs" ]; then
	libs_top=/apps/group/ncn/NEMO5/libs
	sed "s+#INSERT_LIB_TOP+$libs_top+g" mkfiles/make.inc.coates-intel64-mpich2-libs.template > mkfiles/make.inc.coates-intel64-mpich2-libs	
elif [ $1 == "coates-intel64-mvapich-petsc33-libs" ]; then
	libs_top=/apps/group/ncn/rossmann/NEMO5/petsc33/libs
	sed "s+#INSERT_LIB_TOP+$libs_top+g" mkfiles/make.inc.coates-intel64-mvapich-petsc33-libs.template > mkfiles/make.inc.coates-intel64-mvapich-petsc33-libs	
elif [ $1 == "carter-libs" ]; then
	libs_top=/apps/group/ncn/carter/libs
	sed "s+#INSERT_LIB_TOP+$libs_top+g" mkfiles/make.inc.carter-libs.template > mkfiles/make.inc.carter-libs	
elif [ $1 == "carter-debug-libs" ]; then
	libs_top=/apps/group/ncn/carter_debug/libs
	sed "s+#INSERT_LIB_TOP+$libs_top+g" mkfiles/make.inc.carter-debug-libs.template > mkfiles/make.inc.carter-debug-libs	
elif [ $1 == "coates-debug-libs" ]; then
	libs_top=/apps/group/ncn/NEMO5_rossmann_debug/libs
	sed "s+#INSERT_LIB_TOP+$libs_top+g" mkfiles/make.inc.coates-debug-libs.template > mkfiles/make.inc.coates-debug-libs	
fi

#if [ $1 == "coates-intel64-mpich2-libs" ]; then
#sed  "s+#NEMO_HOME_INSERT+nemo_home := $top_directory/prototype+" prototype/make.common.template > prototype/Make.common
#else
sed  "s+#NEMO_HOME_INSERT+nemo_home := $top_directory/prototype+" prototype/make.common.template > prototype/Make.common
#fi
echo configuration is done.
fi
fi
