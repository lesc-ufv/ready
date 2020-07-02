#!/usr/bin/env bash

set -e

echo '----------------------------------------------------------------------------'
echo 'Welcome to READY Setup Wizard.'
echo ''
echo '----------------------------------------------------------------------------'

if echo "$SHELL" | grep 'bash' >/dev/null 2>&1 ; then
  MYPATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
else
  MYPATH="$( cd "$( dirname "$0" )" >/dev/null 2>&1 && pwd )"
fi

READY_ROOT=`cd $MYPATH/.. && pwd`


# read command line args
SUDO=''
INSTALL_DIR=$READY_ROOT/installation
N=3

for i in "$@"
do
case $i in
  -h|--help)
  echo ''
  echo 'Usage: sh install.sh [OPTION]'
  echo ''
  echo '-h  , --help         show arguments'
  echo '      --prefix=PATH  override default install location'
  echo '      --install-as-root  root user is necessary to install the applications'
  echo '-j=N, --jobs=N       specifies the number of jobs to run simultaneously'
  exit 0
  shift # past argument=value
  ;;
  --prefix=*)
  INSTALL_DIR="${i#*=}"
  shift # past argument=value
  ;;
  --install-as-root)
  SUDO='sudo '
  shift # past argument with no value
  ;;
  -j=*|--jobs=*)
  N=${i#*=}
  shift # past argument=value
  ;;
  *)
  # unknown option
  echo ''
  echo 'install.sh: invalid option!'
  echo ''
  echo "Try: 'bash install.sh --help' for more information."
  exit 1
  ;;
esac
done

JOBS="-j${N}"

$SUDO mkdir -p $INSTALL_DIR

cd $INSTALL_DIR
INSTALL_DIR=`pwd`
cd $CALLPATH

echo "cleaning up..."
echo ""
rm -rf $READY_ROOT/sw/mybuild
echo "end of cleaning up!"
echo ""

echo "installing fdam ..."

$SUDO $READY_ROOT/fdam/scripts/install.sh --prefix=$INSTALL_DIR --jobs=$N

echo "installing jsoncpp ..."
echo ""
mkdir $READY_ROOT/jsoncpp/mybuild
cd $READY_ROOT/jsoncpp/mybuild
cmake .. -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR -DCMAKE_PREFIX_PATH=$INSTALL_DIR
make $JOBS
$SUDO make install 
echo "end of installing jsoncpp"
echo ""

echo "installing ready ..."
echo ""
mkdir $READY_ROOT/sw/mybuild
cd $READY_ROOT/sw/mybuild
cmake .. -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR -DCMAKE_PREFIX_PATH=$INSTALL_DIR
make $JOBS
$SUDO make install 
echo "end of installing ready"
echo ""

echo "Installation completed successfully!"
echo ""

cd $CALLPATH
