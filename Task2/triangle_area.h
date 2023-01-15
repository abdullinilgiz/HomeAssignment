#include <math.h>
#if _WIN32
#define TRIANGLE_EXPORT __declspec(dllexport)
#else
#define TRIANGLE_EXPORT
#endif
/* Returns a triangle area specified via three sides.
 Returns 0. if the triangle cannot be created from input parameters.
*/
TRIANGLE_EXPORT double triangle_area (double a, double b, double c);
