#!/bin/bash

ARCH="osx"
SOURCE_DIR="undef"

PARAMS=""
while (( "$#" )); do
  case "$1" in
    -a|--arch)
      ARCH=$2
      shift 2
      ;;
    -s|--source-dir)
      SOURCE_DIR=$2
      shift 2
      ;;
    --) # end argument parsing
      shift
      break
      ;;
    -*|--*=) # unsupported flags
      echo "Error: Unsupported flag $1" >&2
      exit 1
      ;;
    *) # preserve positional arguments
      PARAMS="$PARAMS $1"
      shift
      ;;
  esac
done
# set positional arguments in their proper place
eval set -- "$PARAMS"

if [[ "$SOURCE_DIR" == "undef" ]];then
    echo "Please provide the source directory."
    exit 1
fi

echo "Installing CRAVE libraries"
BUILD_DIR=${SOURCE_DIR}/build/root

if [[ "$ARCH" == "osx"]];then
    echo "Installing include headers..."
    cp -rf ${BUILD_DIR}/include/* /usr/local/include/
    cp -rf ${BUILD_DIR}/share/* /usr/local/share/
    echo "Installing library dependencies"
    cp -rf ${BUILD_DIR}/lib/* /usr/local/lib/

else
    echo "Installing include headers..."
    cp -rf ${BUILD_DIR}/include/* /usr/local/include/
    cp -rf ${BUILD_DIR}/share/* /usr/local/share/
    echo "Installing library dependencies"
    cp -rf ${BUILD_DIR}/lib/* /usr/local/lib/
    # crave/deps/glog-git-0.3.3/lib/libglog.so
    # crave/deps/systemc-2.3.1/lib-linux64/libsystemc.a
    # crave/deps/boost-1_55_0-fs/lib/libboost_filesystem.so
    # crave/deps/boost-1_55_0-fs/lib/libboost_system.so
    # crave/deps/boolector-2.2.0/lib/libboolector.so
    # crave/deps/cudd-3.0.0/lib/libCUDD_obj.so
    # crave/deps/cudd-3.0.0/lib/libCUDD_cudd.so
    # crave/deps/cudd-3.0.0/lib/libCUDD_dddmp.so
    # crave/deps/cudd-3.0.0/lib/libCUDD_epd.so
    # crave/deps/cudd-3.0.0/lib/libCUDD_mtr.so
    # crave/deps/cudd-3.0.0/lib/libCUDD_st.so
    # crave/deps/cudd-3.0.0/lib/libCUDD_util.so
    # crave/deps/minisat-git/lib/libminisat.so
    # crave/deps/lingeling-ayv-86bf266-140429/lib/liblingeling.so
fi

echo "CRAVE libraries installed."
exit 0

