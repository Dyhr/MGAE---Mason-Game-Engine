
 
IF(WIN32) 
    FIND_PATH( LUABRIDGE_INCLUDE_DIR LuaBridge/LuaBridge.h
            $ENV{PROGRAMFILES}/LuaBridge 
            ${LuaBridge_ROOT_DIR}/include 
            $ENV{LuaBridge_ROOT_DIR}/include 
            $ENV{LuaBridge_ROOT_DIR} 
            DOC "The directory where LuaBridge/LuaBridge.h resides") 
ELSE(WIN32) 
    FIND_PATH( LUABRIDGE_INCLUDE_DIR LuaBridge/LuaBridge.h
            /usr/include 
            /usr/local/include 
            /sw/include 
            /opt/local/include 
            ${LuaBridge_ROOT_DIR}/include 
            $ENV{LuaBridge_ROOT_DIR}/include 
            $ENV{LuaBridge_ROOT_DIR} 
            DOC "The directory where LuaBridge/LuaBridge.h resides")
ENDIF(WIN32) 
 
IF(LUABRIDGE_INCLUDE_DIR) 
    SET(LUABRIDGE_FOUND "YES") 
    MESSAGE(STATUS "Found LuaBridge.") 
ENDIF(LUABRIDGE_INCLUDE_DIR)
