#!/usr/bin/env python
# creates a relay to a python script source file, acting as that file.
# The purpose is that of a symlink
with open("/home/harsh/catkin_ws/src/image_pipeline/camera_calibration/nodes/cameracalibrator.py", 'r') as fh:
    exec(fh.read())
