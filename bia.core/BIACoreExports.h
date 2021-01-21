#ifndef _BIA_CORE_EXPORTS_
#define _BIA_CORE_EXPORTS_

#ifdef BIACORE_EXPORTS
#define BIACORE_API __declspec(dllexport)
#else
#define BIACORE_API __declspec(dllimport)
#endif

#endif
