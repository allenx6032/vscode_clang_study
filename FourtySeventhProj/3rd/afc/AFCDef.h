#ifndef AFCDEF_H
#define AFCDEF_H

#define AFC_STATIC
#ifdef AFC_STATIC
#define AFC_API
#else 
#ifdef AFC_EXPORTS
#define AFC_API __declspec(dllexport)
#else
#define AFC_API __declspec(dllimport)
#endif
#endif


#endif//AFCDEF_H