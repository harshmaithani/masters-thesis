FILE(REMOVE_RECURSE
  "CMakeFiles/ueye_cam_gencfg"
  "../devel/include/ueye_cam/UEyeCamConfig.h"
  "../devel/share/ueye_cam/docs/UEyeCamConfig.dox"
  "../devel/share/ueye_cam/docs/UEyeCamConfig-usage.dox"
  "../devel/lib/python2.7/dist-packages/ueye_cam/cfg/UEyeCamConfig.py"
  "../devel/share/ueye_cam/docs/UEyeCamConfig.wikidoc"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ueye_cam_gencfg.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
