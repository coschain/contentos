macro(add_library2)
  set(list_var "${ARGV}")
  if ( ENABLE_MAC_SHARED_LIB )
    list( INSERT list_var 1 SHARED )
  endif( ENABLE_MAC_SHARED_LIB )
  
  add_library(${list_var})
endmacro(add_library2)