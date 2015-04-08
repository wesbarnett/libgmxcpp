FILE(REMOVE_RECURSE
  "CMakeFiles/my_project_docs"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/my_project_docs.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
