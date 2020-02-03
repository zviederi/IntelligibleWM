set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/src/Debug"
        CACHE STRING "Install path prefix, prepended onto install directories"
        FORCE)

#  Get full path to Qt libs
get_target_property(target_path Qt5::Core LOCATION)  

# Get folder path of library
get_filename_component(lib_path ${target_path} DIRECTORY) 

# Install single DLL to lib directory
install(FILES "${lib_path}/Qt5Cored.dll"
              "${lib_path}/Qt5Widgetsd.dll"
              "${lib_path}/Qt5Guid.dll" DESTINATION ${CMAKE_INSTALL_PREFIX})

# Install MongoDB DLL to lib directory
install(FILES "${MONGO_DRIVERS_DIR}/mongo-c-driver/bin/libbson-1.0.dll"
              "${MONGO_DRIVERS_DIR}/mongo-c-driver/bin/libmongoc-1.0.dll"
              "${MONGO_DRIVERS_DIR}/mongo-cxx-driver/bin/bsoncxx.dll"
              "${MONGO_DRIVERS_DIR}/mongo-cxx-driver/bin/mongocxx.dll" DESTINATION ${CMAKE_INSTALL_PREFIX})              