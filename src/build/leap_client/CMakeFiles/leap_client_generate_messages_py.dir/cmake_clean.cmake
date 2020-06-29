FILE(REMOVE_RECURSE
  "CMakeFiles/leap_client_generate_messages_py"
  "../devel/lib/python2.7/dist-packages/leap_client/msg/_HandInfo.py"
  "../devel/lib/python2.7/dist-packages/leap_client/msg/_HandInfoList.py"
  "../devel/lib/python2.7/dist-packages/leap_client/msg/_BoneInfo.py"
  "../devel/lib/python2.7/dist-packages/leap_client/msg/_FingerInfo.py"
  "../devel/lib/python2.7/dist-packages/leap_client/msg/__init__.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/leap_client_generate_messages_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
