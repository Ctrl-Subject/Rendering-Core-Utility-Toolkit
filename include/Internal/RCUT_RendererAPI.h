#ifdef _WIN32

#ifdef RENDERER_EXPORTS
#define Renderer_API __declspec(dllexport)
#else
#define Renderer_API __declspec(dllimport)
#endif

#else

#define Renderer_API

#endif