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

cd "/home/harsh/catkin_ws/src/image_pipeline/camera_calibration"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
/usr/bin/env \
    PYTHONPATH="/usr/local/lib/python2.7/dist-packages:/home/harsh/catkin_ws/src/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/harsh/catkin_ws/src/build" \
    "/usr/bin/python" \
    "/home/harsh/catkin_ws/src/image_pipeline/camera_calibration/setup.py" \
    build --build-base "/home/harsh/catkin_ws/src/build/image_pipeline/camera_calibration" \
    install \
    $DESTDIR_ARG \
    --install-layout=deb --prefix="/usr/local" --install-scripts="/usr/local/bin"
