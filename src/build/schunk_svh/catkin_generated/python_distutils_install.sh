#!/bin/sh -x

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
    DESTDIR_ARG="--root=$DESTDIR"
fi

cd "/home/harsh/catkin_ws/src/schunk_svh"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
/usr/bin/env \
    PYTHONPATH="/home/harsh/catkin_ws/src/export/lib/python2.7/dist-packages:/home/harsh/catkin_ws/src/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/harsh/catkin_ws/src/build" \
    "/usr/bin/python" \
    "/home/harsh/catkin_ws/src/schunk_svh/setup.py" \
    build --build-base "/home/harsh/catkin_ws/src/build/schunk_svh" \
    install \
    $DESTDIR_ARG \
    --install-layout=deb --prefix="/home/harsh/catkin_ws/src/export" --install-scripts="/home/harsh/catkin_ws/src/export/bin"
