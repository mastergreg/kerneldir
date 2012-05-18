#!/bin/bash
#
# utopia.sh
#
#       Sets up User-mode Linux and launches it.
#
# Copyright (C) 2010, Computing Systems Lab., ECE, NTUA.
#
# Modification history
#
# Date          Name            Description
# 2010-03-10    bkk             Initial real script.
# 2010-03-09    gtsouk          Initial utopic script.
#

UTOPIA_CONFIG="utopia.config"

VERBOSE=1
PF=\*\*\*

if [ -n "$VERBOSE" ]; then
    echo " "
    echo " $PF Reading configuration"
    echo " "
fi

# Check for the configuration file
if [ -n "$VERBOSE" ]; then
    echo "UTOPIA_CONFIG="$UTOPIA_CONFIG
fi

if [ ! -e "$UTOPIA_CONFIG" ]; then
    echo "$0: cannot find '$UTOPIA_CONFIG'." 1>&2
    echo "Please provide a configuration file and rerun." 1>&2
    exit 1
fi

# Source the configuration file
# FIXME: some parsing here might be better.
. $UTOPIA_CONFIG

if [ -n "$VERBOSE" ]; then
    echo " "
    echo " $PF Checking configuration"
    echo " "
fi

# Check for root filesystem
if [ -n "$VERBOSE" ]; then
    echo "UML_ROOT_FS_IMAGE="$UML_ROOT_FS_IMAGE
fi

if [ -z "$UML_ROOT_FS_IMAGE" ]; then
    echo "$0: Configuration variable UML_ROOT_FS_IMAGE is empty." 1>&2
    echo "Please specify a root filesystem." 1>&2
    exit 1
fi

if [ ! -e "$UML_ROOT_FS_IMAGE" ]; then
    echo "$0: '$UML_ROOT_FS_IMAGE' does not exist." 1>&2
    echo "Please supply an existing root filesystem image." 1>&2
    exit 1
fi

# Check if UML_ROOT_FS_IMAGE is actually a filesystem image
is_fs_image=$(file -L $UML_ROOT_FS_IMAGE | grep "filesystem")

if [ -z "$is_fs_image" ]; then
    echo -n "$0: '$UML_ROOT_FS_IMAGE' doesn't seem to be a filesystem image. "
    while [ 1 ]; do
        echo -n "Do you want to continue? (y/n) " && read ans
        case $ans in
            "y" | "Y" | "yes" | "Yes" | "YES")
                break ;;
            "n" | "N" | "no" | "No" | "NO")
                exit 1 ;;
            *)
                echo "Please type 'yes' or 'no'." ;;
        esac
    done
fi

if [ -n "$VERBOSE" ]; then
    echo "KERNEL_SRCDIR="$KERNEL_SRCDIR
fi

if [ -z "$KERNEL_SRCDIR" ]; then
    echo "$0: Configuration variable KERNEL_SRCDIR is empty." 1>&2
    echo "Please specify a directory to search for UML kernels." 1>&2
    exit 1
fi

if [ ! -e "$KERNEL_SRCDIR" ]; then
    echo "$0: '$KERNEL_SRCDIR' does not exist." 1>&2
    echo "Make sure you supplied a valid directory." 1>&2
    exit 1
fi

if [ ! -d "$KERNEL_SRCDIR" ]; then
    echo "$0: '$KERNEL_SRCDIR' is not a directory." 1>&2
    echo "Make sure you supplied a valid directory." 1>&2
    exit 1
fi

uml_kernel="$KERNEL_SRCDIR/linux"
if [ ! -e "$uml_kernel" ]; then
    echo "$0: cannot find a UML kernel '$KERNEL_SRCDIR/linux'." 1>&2
    echo "Please make sure you have properly compiled your kernel or you supplied the correct source directory." 1>&2
    exit 1
fi

if [ -n "$VERBOSE" ]; then
    echo "PRIVATE_COW="$PRIVATE_COW
fi

if [ -z "$PRIVATE_COW" ]; then
    echo "$0: Configuration variable PRIVATE_COW is empty." 1>&2
    echo "Please specify a private COW filesystem image." 1>&2
    exit 1
fi

if [ -e "$PRIVATE_COW" ] && [ ! -f "$PRIVATE_COW" ]; then
    echo "$0: '$PRIVATE_COW' is not a regular file." 1>&2
    echo "Please specify a valid private COW filesystem image." 1>&2
    exit 1
fi


export TMPDIR=/tmp/uml/$(whoami)
mkdir -p $TMPDIR
chmod 777 $TMPDIR

echo " "
echo " $PF Transfering to Utopia ..."
echo " "

if [ x"$OVER_SSH" = x"yes" ]; then
    # Launch UML over ssh
    exec $uml_kernel ubd0="$PRIVATE_COW","$UML_ROOT_FS_IMAGE" mem=54MB \
        eth0=slirp,,slirp-fullbolt con0=fd:0,fd:1 con1=pts con2=pts con3=pts con=null $*
else
    # Launch UML normally
    exec $uml_kernel ubd0="$PRIVATE_COW","$UML_ROOT_FS_IMAGE" mem=256MB \
        con0=xterm con1=fd:0,fd:1 con2=xterm con3=xterm con=null eth0=tuntap,utopia $*
fi
