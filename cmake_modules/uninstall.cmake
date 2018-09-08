function(add_uninstall)
    if(NOT TARGET uninstall)
        add_custom_target(uninstall
                          COMMAND sudo xargs rm < install_manifest.txt
                          COMMENT "Uninstalling")
        message("-- Adding uninstall instructions...")
        endif(NOT TARGET uninstall)
endfunction()
