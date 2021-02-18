#if defined(_WIN32) && (BUILD_SHARED_LIBS==1)
#  if defined(EXPORTING_MYMATH)
#    define DECLSPEC __declspec(dllexport)
#  else
#    define DECLSPEC __declspec(dllimport)
#  endif
#else // non windows or static way
#  define DECLSPEC
#endif

namespace mathfunctions {
  
double DECLSPEC sqrt(double x);

}
