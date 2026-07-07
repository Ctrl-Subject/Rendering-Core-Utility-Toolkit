#pragma once

//**************************************************
// DLL export handling
//**************************************************

#ifdef _WIN32

    #ifdef 
RCUTRenderer_EXPORTS
        #define 
RCUTRenderer_API __declspec(dllexport)
    #else
        #define 
RCUTRenderer_API __declspec(dllimport)
    #endif

#else

    #define 
RCUTRenderer_API
#endif