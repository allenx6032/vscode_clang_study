#ifndef CHAR_CONVERT_H
#define CHAR_CONVERT_H

#include <cstdint>
#include <vector>
#include <stdexcept>
namespace agg
{
  // 手动将 UTF-8 转为 wchar_t*（兼容 Windows/Linux/macOS）
  static wchar_t* utf8_to_wchar(const char* utf8_str) {
      if (!utf8_str) return nullptr;
      std::vector<wchar_t> wchars;
      uint32_t codepoint = 0;
      int remaining = 0;
      // 遍历 UTF-8 字符串
      for (; *utf8_str != '\0'; ++utf8_str) {
          uint8_t byte = static_cast<uint8_t>(*utf8_str);
          if (remaining == 0) {
              if (byte <= 0x7F) {          // 1字节字符
                  codepoint = byte;
                  remaining = 0;
              } else if ((byte & 0xE0) == 0xC0) { // 2字节
                  codepoint = byte & 0x1F;
                  remaining = 1;
              } else if ((byte & 0xF0) == 0xE0) { // 3字节
                  codepoint = byte & 0x0F;
                  remaining = 2;
              } else if ((byte & 0xF8) == 0xF0) { // 4字节
                  codepoint = byte & 0x07;
                  remaining = 3;
              } else {
                  throw std::runtime_error("Invalid UTF-8");
              }
          } else {
              if ((byte & 0xC0) != 0x80) {
                  throw std::runtime_error("Invalid UTF-8 continuation byte");
              }
              codepoint = (codepoint << 6) | (byte & 0x3F);
              remaining--;
          }
          if (remaining == 0) {
              // 根据平台转换为 UTF-16 或 UTF-32
  #if defined(_WIN32)
              // Windows: 处理 UTF-16 代理对
              if (codepoint >= 0x10000) {
                  codepoint -= 0x10000;
                  wchars.push_back(0xD800 | ((codepoint >> 10) & 0x3FF)); // 高代理
                  wchars.push_back(0xDC00 | (codepoint & 0x3FF));          // 低代理
              } else {
                  wchars.push_back(static_cast<wchar_t>(codepoint));
              }
  #else
              // Linux/macOS: 直接存储 UTF-32
              wchars.push_back(static_cast<wchar_t>(codepoint));
  #endif
          }
      }
      if (remaining != 0) {
          throw std::runtime_error("Truncated UTF-8 sequence");
      }
      wchars.push_back(L'\0'); // 添加终止符
      wchar_t* result = new wchar_t[wchars.size()];
      std::copy(wchars.begin(), wchars.end(), result);
      return result;
  }
  // 手动将 wchar_t* 转为 UTF-8
  static char* wchar_to_utf8(const wchar_t* wstr) {
      if (!wstr) return nullptr;
      std::vector<char> utf8;
      size_t i = 0;
      while (wstr[i] != L'\0') {
          uint32_t codepoint = 0;
  #if defined(_WIN32)
          // Windows: 处理 UTF-16 代理对
          if (wstr[i] >= 0xD800 && wstr[i] <= 0xDBFF) { // 高代理
              if (wstr[i+1] < 0xDC00 || wstr[i+1] > 0xDFFF) {
                  throw std::runtime_error("Invalid UTF-16 surrogate pair");
              }
              codepoint = 0x10000 + ((wstr[i] & 0x3FF) << 10 | (wstr[i+1] & 0x3FF));
              i += 2;
          } else {
              codepoint = static_cast<uint32_t>(wstr[i]);
              i += 1;
          }
  #else
          // Linux/macOS: 直接读取 UTF-32 码点
          codepoint = static_cast<uint32_t>(wstr[i]);
          i += 1;
  #endif
          // 转换为 UTF-8
          if (codepoint <= 0x7F) {
              utf8.push_back(static_cast<char>(codepoint));
          } else if (codepoint <= 0x7FF) {
              utf8.push_back(0xC0 | ((codepoint >> 6) & 0x1F));
              utf8.push_back(0x80 | (codepoint & 0x3F));
          } else if (codepoint <= 0xFFFF) {
              utf8.push_back(0xE0 | ((codepoint >> 12) & 0x0F));
              utf8.push_back(0x80 | ((codepoint >> 6) & 0x3F));
              utf8.push_back(0x80 | (codepoint & 0x3F));
          } else if (codepoint <= 0x10FFFF) {
              utf8.push_back(0xF0 | ((codepoint >> 18) & 0x07));
              utf8.push_back(0x80 | ((codepoint >> 12) & 0x3F));
              utf8.push_back(0x80 | ((codepoint >> 6) & 0x3F));
              utf8.push_back(0x80 | (codepoint & 0x3F));
          } else {
              throw std::runtime_error("Invalid Unicode code point");
          }
      }
      utf8.push_back('\0'); // 添加终止符
      char* result = new char[utf8.size()];
      std::copy(utf8.begin(), utf8.end(), result);
      return result;
  }
}
#endif // CHAR_TRAITS_FIX_H