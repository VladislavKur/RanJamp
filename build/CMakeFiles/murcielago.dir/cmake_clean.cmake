file(REMOVE_RECURSE
  "murcielago.pdb"
  "murcielago"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/murcielago.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
