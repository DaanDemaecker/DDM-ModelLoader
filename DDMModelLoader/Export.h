#ifndef _DDMML_EXPORT_
#define _DDMML_EXPORT_

#if defined(_WIN32)
	#if defined(DDMMODELLOADER_BUILD)
		#define DDMML_API __declspec(dllexport)
	#else
		#define DDMML_API __declspec(dllimport)
	#endif
#else
	#define DDMML_API
#endif

#endif // !_DDMML_EXPORT_
