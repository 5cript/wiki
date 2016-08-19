#pragma once

/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#elif defined(DYNAMIC_WIKI_CLIENT_LIBRARY)
    #define DLL_EXPORT __declspec(dllimport)
#else
    #define DLL_EXPORT
#endif
