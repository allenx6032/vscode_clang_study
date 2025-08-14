#ifndef __tools__
#define __tools__
#include "public.h"

//ID3D11Device* g_pd3dDevice;


ImVec4 RGBAtoIV4(int r, int g, int b, int a);
double evaluate(std::string tokens);
bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
std::string WideCharToMultiByte(const std::wstring& wstr);
#endif