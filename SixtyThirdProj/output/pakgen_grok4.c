/*
Compile
gcc -o pakgen.exe pakgen_grok4.c
pakgen kernal -e -s -q -o kernal.pak
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>
#if defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
    #include <direct.h>
    #include <windows.h>
    #define mkdir(path, mode) _mkdir(path)
    #define stat _stat
    #define S_ISDIR(m) (((m) & _S_IFDIR) != 0)
#else
    #include <dirent.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <fnmatch.h>
#endif

// 常量定义
#define HEADER_SIZE 15  // 8+1+1+2+4-1 (调整为实际字节数)
#define ENTRY_HEADER_SIZE 24  // 16+4+4
#define VERSION 0x00
#define RESERVED_16B 0xFFFF
#define MAGIC_HEADER "TOFUPAK!"
#define BUFFER_SIZE 8196
// #define MAX_PATH 1024
#define MAX_FILES 10000
#define MD5_DIGEST_SIZE 16

// 文件条目结构
typedef struct {
    char name[MAX_PATH];
    char id[MD5_DIGEST_SIZE];
    char pathfile[MAX_PATH];
    uint32_t size;
    uint32_t offset;
} FileEntry;

// 全局变量
typedef struct {
    int quiet;
    int detailed;
    int encrypted;
    int sorted;
    char output[MAX_PATH];
} Flags;

static Flags flags = {0};
static FileEntry files[MAX_FILES];
static int file_count = 0;

// 简单的MD5实现 (简化版，基于RFC 1321)
typedef struct {
    uint32_t state[4];
    uint32_t count[2];
    unsigned char buffer[64];
} MD5_CTX;

#define F(x, y, z) ((x & y) | (~x & z))
#define G(x, y, z) ((x & z) | (y & ~z))
#define H(x, y, z) (x ^ y ^ z)
#define I(x, y, z) (y ^ (x | ~z))
#define ROTATE_LEFT(x, n) ((x << n) | (x >> (32 - n)))
#define FF(a, b, c, d, x, s, ac) { \
    a += F(b, c, d) + x + ac; \
    a = ROTATE_LEFT(a, s); \
    a += b; \
}
#define GG(a, b, c, d, x, s, ac) { \
    a += G(b, c, d) + x + ac; \
    a = ROTATE_LEFT(a, s); \
    a += b; \
}
#define HH(a, b, c, d, x, s, ac) { \
    a += H(b, c, d) + x + ac; \
    a = ROTATE_LEFT(a, s); \
    a += b; \
}
#define II(a, b, c, d, x, s, ac) { \
    a += I(b, c, d) + x + ac; \
    a = ROTATE_LEFT(a, s); \
    a += b; \
}

static void MD5_Init(MD5_CTX *context) {
    context->count[0] = context->count[1] = 0;
    context->state[0] = 0x67452301;
    context->state[1] = 0xefcdab89;
    context->state[2] = 0x98badcfe;
    context->state[3] = 0x10325476;
    memset(context->buffer, 0, sizeof(context->buffer));
}


static void MD5_Transform(uint32_t state[4], const unsigned char block[64]) {
    uint32_t a, b, c, d;
    unsigned char *input = (unsigned char *)block;
    uint32_t x[16];
    int i;
    for (i = 0; i < 16; i++) {
        x[i] = (uint32_t)input[4*i] | ((uint32_t)input[4*i+1] << 8) |
               ((uint32_t)input[4*i+2] << 16) | ((uint32_t)input[4*i+3] << 24);
    }
    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    FF(a, b, c, d, x[0], 7, 0xd76aa478);
    FF(d, a, b, c, x[1], 12, 0xe8c7b756);
    FF(c, d, a, b, x[2], 17, 0x242070db);
    FF(b, c, d, a, x[3], 22, 0xc1bdceee);
    FF(a, b, c, d, x[4], 7, 0xf57c0faf);
    FF(d, a, b, c, x[5], 12, 0x4787c62a);
    FF(c, d, a, b, x[6], 17, 0xa8304613);
    FF(b, c, d, a, x[7], 22, 0xfd469501);
    FF(a, b, c, d, x[8], 7, 0x698098d8);
    FF(d, a, b, c, x[9], 12, 0x8b44f7af);
    FF(c, d, a, b, x[10], 17, 0xffff5bb1);
    FF(b, c, d, a, x[11], 22, 0x895cd7be);
    FF(a, b, c, d, x[12], 7, 0x6b901122);
    FF(d, a, b, c, x[13], 12, 0xfd987193);
    FF(c, d, a, b, x[14], 17, 0xa679438e);
    FF(b, c, d, a, x[15], 22, 0x49b40821);
    GG(a, b, c, d, x[1], 5, 0xf61e2562);
    GG(d, a, b, c, x[6], 9, 0xc040b340);
    GG(c, d, a, b, x[11], 14, 0x265e5a51);
    GG(b, c, d, a, x[0], 20, 0xe9b6c7aa);
    GG(a, b, c, d, x[5], 5, 0xd62f105d);
    GG(d, a, b, c, x[10], 9, 0x02441453);
    GG(c, d, a, b, x[15], 14, 0xd8a1e681);
    GG(b, c, d, a, x[4], 20, 0xe7d3fbc8);
    GG(a, b, c, d, x[9], 5, 0x21e1cde6);
    GG(d, a, b, c, x[14], 9, 0xc33707d6);
    GG(c, d, a, b, x[3], 14, 0xf4d50d87);
    GG(b, c, d, a, x[8], 20, 0x455a14ed);
    GG(a, b, c, d, x[13], 5, 0xa9e3e905);
    GG(d, a, b, c, x[2], 9, 0xfcefa3f8);
    GG(c, d, a, b, x[7], 14, 0x676f02d9);
    GG(b, c, d, a, x[12], 20, 0x8d2a4c8a);
    HH(a, b, c, d, x[5], 4, 0xfffa3942);
    HH(d, a, b, c, x[8], 11, 0x8771f681);
    HH(c, d, a, b, x[11], 16, 0x6d9d6122);
    HH(b, c, d, a, x[14], 23, 0xfde5380c);
    HH(a, b, c, d, x[1], 4, 0xa4beea44);
    HH(d, a, b, c, x[4], 11, 0x4bdecfa9);
    HH(c, d, a, b, x[7], 16, 0xf6bb4b60);
    HH(b, c, d, a, x[10], 23, 0xbebfbc70);
    HH(a, b, c, d, x[13], 4, 0x289b7ec6);
    HH(d, a, b, c, x[0], 11, 0xeaa127fa);
    HH(c, d, a, b, x[3], 16, 0xd4ef3085);
    HH(b, c, d, a, x[6], 23, 0x04881d05);
    HH(a, b, c, d, x[9], 4, 0xd9d4d039);
    HH(d, a, b, c, x[12], 11, 0xe6db99e5);
    HH(c, d, a, b, x[15], 16, 0x1fa27cf8);
    HH(b, c, d, a, x[2], 23, 0xc4ac5665);
    II(a, b, c, d, x[0], 6, 0xf4292244);
    II(d, a, b, c, x[7], 10, 0x432aff97);
    II(c, d, a, b, x[14], 15, 0xab9423a7);
    II(b, c, d, a, x[5], 21, 0xfc93a039);
    II(a, b, c, d, x[12], 6, 0x655b59c3);
    II(d, a, b, c, x[3], 10, 0x8f0ccc92);
    II(c, d, a, b, x[10], 15, 0xffeff47d);
    II(b, c, d, a, x[1], 21, 0x85845dd1);
    II(a, b, c, d, x[8], 6, 0x6fa87e4f);
    II(d, a, b, c, x[15], 10, 0xfe2ce6e0);
    II(c, d, a, b, x[6], 15, 0xa3014314);
    II(b, c, d, a, x[13], 21, 0x4e0811a1);
    II(a, b, c, d, x[4], 6, 0xf7537e82);
    II(d, a, b, c, x[11], 10, 0xbd3af235);
    II(c, d, a, b, x[2], 15, 0x2ad7d2bb);
    II(b, c, d, a, x[9], 21, 0xeb86d391);
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}

static void MD5_Update(MD5_CTX *context, const unsigned char *input, unsigned int inputLen) {
    unsigned int i, index, partLen;
    index = (unsigned int)((context->count[0] >> 3) & 0x3F);
    if ((context->count[0] += (inputLen << 3)) < (inputLen << 3))
        context->count[1]++;
    context->count[1] += (inputLen >> 29);
    partLen = 64 - index;
    if (inputLen >= partLen) {
        memcpy(&context->buffer[index], input, partLen);
        MD5_Transform(context->state, context->buffer);
        for (i = partLen; i + 63 < inputLen; i += 64)
            MD5_Transform(context->state, &input[i]);
        index = 0;
    } else {
        i = 0;
    }
    memcpy(&context->buffer[index], &input[i], inputLen - i);
}

static void MD5_Final(unsigned char digest[16], MD5_CTX *context) {
    unsigned char bits[8];
    unsigned int index, padLen;
    static unsigned char PADDING[64] = {
        0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    index = (unsigned int)((context->count[0] >> 3) & 0x3f);
    padLen = (index < 56) ? (56 - index) : (120 - index);
    MD5_Update(context, PADDING, padLen);
    bits[0] = (unsigned char)(context->count[0]);
    bits[1] = (unsigned char)(context->count[0] >> 8);
    bits[2] = (unsigned char)(context->count[0] >> 16);
    bits[3] = (unsigned char)(context->count[0] >> 24);
    bits[4] = (unsigned char)(context->count[1]);
    bits[5] = (unsigned char)(context->count[1] >> 8);
    bits[6] = (unsigned char)(context->count[1] >> 16);
    bits[7] = (unsigned char)(context->count[1] >> 24);
    MD5_Update(context, bits, 8);
    digest[0] = (unsigned char)(context->state[0]);
    digest[1] = (unsigned char)(context->state[0] >> 8);
    digest[2] = (unsigned char)(context->state[0] >> 16);
    digest[3] = (unsigned char)(context->state[0] >> 24);
    digest[4] = (unsigned char)(context->state[1]);
    digest[5] = (unsigned char)(context->state[1] >> 8);
    digest[6] = (unsigned char)(context->state[1] >> 16);
    digest[7] = (unsigned char)(context->state[1] >> 24);
    digest[8] = (unsigned char)(context->state[2]);
    digest[9] = (unsigned char)(context->state[2] >> 8);
    digest[10] = (unsigned char)(context->state[2] >> 16);
    digest[11] = (unsigned char)(context->state[2] >> 24);
    digest[12] = (unsigned char)(context->state[3]);
    digest[13] = (unsigned char)(context->state[3] >> 8);
    digest[14] = (unsigned char)(context->state[3] >> 16);
    digest[15] = (unsigned char)(context->state[3] >> 24);
    memset(context, 0, sizeof(*context));
}

// 计算MD5
static void md5(const char *string, unsigned char output[16]) {
    MD5_CTX context;
    MD5_Init(&context);
    MD5_Update(&context, (const unsigned char *)string, strlen(string));
    MD5_Final(output, &context);
}

// 十六进制转换
static void bytes_to_hex(const unsigned char *bytes, int len, char *hex) {
    static const char hex_chars[] = "0123456789ABCDEF";
    for (int i = 0; i < len; i++) {
        hex[i*2] = hex_chars[(bytes[i] >> 4) & 0xF];
        hex[i*2+1] = hex_chars[bytes[i] & 0xF];
    }
    hex[len*2] = '\0';
}

// XOR加密/解密
static void xor_cipher(const unsigned char *key, int key_len, unsigned char *data, int data_len) {
    for (int i = 0; i < data_len; i++) {
        data[i] ^= key[i % key_len];
    }
}

// 规范化路径 (转换为小写，替换反斜杠)
static void normalize_path(const char *input, char *output) {
    int i;
    for (i = 0; input[i] && i < MAX_PATH - 1; i++) {
        if (input[i] == '\\') {
            output[i] = '/';
        } else {
            output[i] = tolower((unsigned char)input[i]);
        }
    }
    output[i] = '\0';
}

// 字符串比较 (用于排序)
static int compare_files(const void *a, const void *b) {
    const FileEntry *fa = (const FileEntry *)a;
    const FileEntry *fb = (const FileEntry *)b;
    return memcmp(fa->id, fb->id, MD5_DIGEST_SIZE);
}

// 递归扫描目录
#if defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
static int scan_directory(const char *path, const char *base_name) {
    char full_path[MAX_PATH];
    char search_path[MAX_PATH];
    WIN32_FIND_DATA find_data;
    HANDLE hFind;
    
    snprintf(search_path, sizeof(search_path), "%s\\*", path);
    hFind = FindFirstFile(search_path, &find_data);
    
    if (hFind == INVALID_HANDLE_VALUE) {
        return 0;
    }
    
    do {
        if (strcmp(find_data.cFileName, ".") == 0 || strcmp(find_data.cFileName, "..") == 0) {
       continue;
        }
        
        snprintf(full_path, sizeof(full_path), "%s\\%s", path, find_data.cFileName);
        
        if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            // 递归处理子目录
            scan_directory(full_path, base_name ? 
                (strlen(base_name) ? 
                    (snprintf(full_path, sizeof(full_path), "%s/%s", base_name, find_data.cFileName), full_path) : 
                    find_data.cFileName) : 
                NULL);
        } else {
            // 处理文件
            struct _stat st;
            if (_stat(full_path, &st) == 0 && S_ISDIR(st.st_mode) == 0) {
                char name[MAX_PATH];
                if (!base_name || !strlen(base_name)) {
                    strcpy(name, find_data.cFileName);
                } else {
                    snprintf(name, sizeof(name), "%s/%s", base_name, find_data.cFileName);
                }
                
                if (file_count < MAX_FILES) {
                    strcpy(files[file_count].pathfile, full_path);
                    strcpy(files[file_count].name, name);
                    files[file_count].size = (uint32_t)st.st_size;
                    
                    // 计算MD5
                    md5(name, (unsigned char *)files[file_count].id);
                    
                    file_count++;
                }
            }
        }
    } while (FindNextFile(hFind, &find_data));
    
    FindClose(hFind);
    return 1;
}
#else
static int scan_directory(const char *path, const char *base_name) {
    DIR *dir;
    struct dirent *entry;
    char full_path[MAX_PATH];
    struct stat st;
    
    dir = opendir(path);
    if (!dir) {
        return 0;
    }
    
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        
        if (stat(full_path, &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
                // 递归处理子目录
                char new_base[MAX_PATH];
                if (base_name && strlen(base_name)) {
                    snprintf(new_base, sizeof(new_base), "%s/%s", base_name, entry->d_name);
                    scan_directory(full_path, new_base);
                } else {
                    scan_directory(full_path, entry->d_name);
                }
            } else if (S_ISREG(st.st_mode)) {
                // 处理文件
                char name[MAX_PATH];
                if (!base_name || !strlen(base_name)) {
                    strncpy(name, entry->d_name, sizeof(name) - 1);
                    name[sizeof(name) - 1] = '\0';
                } else {
                    snprintf(name, sizeof(name), "%s/%s", base_name, entry->d_name);
                }
                
                if (file_count < MAX_FILES) {
                    strncpy(files[file_count].pathfile, full_path, sizeof(files[file_count].pathfile) - 1);
                    files[file_count].pathfile[sizeof(files[file_count].pathfile) - 1] = '\0';
                    strncpy(files[file_count].name, name, sizeof(files[file_count].name) - 1);
                    files[file_count].name[sizeof(files[file_count].name) - 1] = '\0';
                    files[file_count].size = (uint32_t)st.st_size;
                    
                    // 计算MD5
                    md5(name, (unsigned char *)files[file_count].id);
                    
                    file_count++;
                }
            }
        }
    }
    
    closedir(dir);
    return 1;
}
#endif

// 获取文件列表
static int fetch_files(const char **paths, int path_count) {
    file_count = 0;
    
    for (int i = 0; i < path_count && file_count < MAX_FILES; i++) {
        if (!flags.quiet) {
            printf("Fetching files from path `%s`\n", paths[i]);
        }
        
        struct stat st;
        if (stat(paths[i], &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
                scan_directory(paths[i], NULL);
            } else if (S_ISREG(st.st_mode)) {
                // 处理单个文件
                if (file_count < MAX_FILES) {
                    char name[MAX_PATH];
                    const char *filename = strrchr(paths[i], '/');
                    if (!filename) filename = strrchr(paths[i], '\\');
                    if (!filename) filename = paths[i];
                    else filename++;
                    
                    strcpy(files[file_count].pathfile, paths[i]);
                    strcpy(files[file_count].name, filename);
                    files[file_count].size = (uint32_t)st.st_size;
                    
                    // 计算MD5
                    md5(filename, (unsigned char *)files[file_count].id);
                    
                    file_count++;
                }
            }
        }
    }
    
    return file_count > 0;
}

// 优化文件列表 (检查重复)
static int optimize_files(void) {
    char normalized[MAX_PATH];
    unsigned char hash[MD5_DIGEST_SIZE];
    
    if (!flags.quiet) {
        printf("Optimizing...\n");
    }
    
    uint32_t offset = HEADER_SIZE + file_count * ENTRY_HEADER_SIZE;
    
    for (int i = 0; i < file_count; i++) {
        // 规范化文件名用于重复检查
        normalize_path(files[i].name, normalized);
        md5(normalized, hash);
        
        // 检查重复 (简化检查，使用文件名MD5)
        for (int j = 0; j < i; j++) {
            if (memcmp(hash, (unsigned char *)files[j].id, MD5_DIGEST_SIZE) == 0) {
                printf("*** entry w/ name `%s` is duplicated\n", files[i].name);
                return 0;
            }
        }
        
        files[i].offset = offset;
        offset += files[i].size;
    }
    
    return 1;
}

// 编译标志
static uint8_t compile_flags(void) {
    return (flags.encrypted ? 1 : 0) | (flags.sorted ? 2 : 0);
}

// 写入头信息
static int emit_header(FILE *fp) {
    // 写入魔数
    fwrite(MAGIC_HEADER, 1, 8, fp);
    
    // 写入版本
    fputc(VERSION, fp);
    
    // 写入标志
    fputc(compile_flags(), fp);
    
    // 写入保留字段
    uint16_t reserved = RESERVED_16B;
    fwrite(&reserved, 1, 2, fp);
    
    // 写入文件数量
    uint32_t count = (uint32_t)file_count;
    fwrite(&count, 1, 4, fp);
    
    return 1;
}

// 写入目录
static int emit_directory(FILE *fp) {
    FileEntry *sorted_files = malloc(file_count * sizeof(FileEntry));
    if (!sorted_files) {
        return 0;
    }
    
    // 复制文件列表
    memcpy(sorted_files, files, file_count * sizeof(FileEntry));
    
    if (flags.sorted) {
        if (!flags.quiet) {
            printf("Sorting...\n");
        }
        qsort(sorted_files, file_count, sizeof(FileEntry), compare_files);
    }
    
    for (int i = 0; i < file_count; i++) {
        if (!flags.quiet) {
            char hex_id[MD5_DIGEST_SIZE * 2 + 1];
            bytes_to_hex((unsigned char *)sorted_files[i].id, MD5_DIGEST_SIZE, hex_id);
            printf("[%04x] `%s` -> `%s`\n", i, hex_id, sorted_files[i].name);
        }
        
        // 写入ID (16字节)
        fwrite(sorted_files[i].id, 1, 16, fp);
        
        // 写入偏移量
        uint32_t offset = sorted_files[i].offset;
        fwrite(&offset, 1, 4, fp);
        
        // 写入大小
        uint32_t size = sorted_files[i].size;
        fwrite(&size, 1, 4, fp);
    }
    
    free(sorted_files);
    return 1;
}

// 写入单个文件
static int emit_entry(FILE *out_fp, const FileEntry *file) {
    FILE *in_fp = fopen(file->pathfile, "rb");
    if (!in_fp) {
        printf("*** can't access file `%s`\n", file->pathfile);
        return 0;
    }
    
    unsigned char key[MD5_DIGEST_SIZE];
    memcpy(key, file->id, MD5_DIGEST_SIZE);
    
    unsigned char buffer[BUFFER_SIZE];
    size_t bytes_read;
    
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, in_fp)) > 0) {
        if (flags.encrypted) {
            xor_cipher(key, MD5_DIGEST_SIZE, buffer, (int)bytes_read);
        }
        fwrite(buffer, 1, bytes_read, out_fp);
    }
    
    fclose(in_fp);
    return 1;
}

// 写入所有文件
static int emit_entries(FILE *fp) {
    if (!flags.quiet) {
        printf("Writing...\n");
    }
    
    for (int i = 0; i < file_count; i++) {
        uint32_t start_offset = (uint32_t)ftell(fp);
        
        if (!emit_entry(fp, &files[i])) {
            return 0;
        }
        
        if (!flags.quiet) {
            if (flags.detailed) {
                char hex_id[MD5_DIGEST_SIZE * 2 + 1];
                bytes_to_hex((unsigned char *)files[i].id, MD5_DIGEST_SIZE, hex_id);
                printf("> file `%s`\n  name: `%s`\n  id: `%s`\n  offset: %u\n  size: %u\n",
                    files[i].pathfile, files[i].name, hex_id, start_offset, files[i].size);
            } else {
                char hex_id[MD5_DIGEST_SIZE * 2 + 1];
                bytes_to_hex((unsigned char *)files[i].id, MD5_DIGEST_SIZE, hex_id);
                printf("[%04x] `%s` -> `%s`\n", i, hex_id, files[i].name);
            }
        }
    }
    
    return 1;
}

// 主打包函数
static int emit_package(void) {
    if (!optimize_files()) {
        return 0;
    }
    
    FILE *fp = fopen(flags.output, "wb");
    if (!fp) {
        printf("*** can't create file `%s`\n", flags.output);
        return 0;
    }
    
    if (!emit_header(fp)) {
        fclose(fp);
        remove(flags.output);
        return 0;
    }
    
    if (!emit_directory(fp)) {
        fclose(fp);
        remove(flags.output);
        return 0;
    }
    
    if (!emit_entries(fp)) {
        fclose(fp);
        remove(flags.output);
        return 0;
    }
    
    fclose(fp);
    return 1;
}

// 解析命令行参数
static int parse_arguments(int argc, char *argv[]) {
    int i;
    int input_count = 0;
    char *inputs[argc];
    
    strcpy(flags.output, "aout.pak");
    flags.quiet = 0;
    flags.detailed = 0;
    flags.encrypted = 0;
    flags.sorted = 0;
    
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            if (++i < argc) {
                strncpy(flags.output, argv[i], sizeof(flags.output) - 1);
                flags.output[sizeof(flags.output) - 1] = '\0';
            }
        } else if (strcmp(argv[i], "-q") == 0 || strcmp(argv[i], "--quiet") == 0) {
            flags.quiet = 1;
        } else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--detailed") == 0) {
            flags.detailed = 1;
        } else if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--encrypted") == 0) {
            flags.encrypted = 1;
        } else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--sorted") == 0) {
            flags.sorted = 1;
        } else {
            // 输入路径
            if (input_count < argc - 1) {
                inputs[input_count++] = argv[i];
            }
        }
    }
    
    if (input_count == 0) {
        printf("Error: No input paths specified\n");
        printf("Usage: %s [options] input_paths...\n", argv[0]);
        printf("Options:\n");
        printf("  -o, --output FILE     Output package file (default: aout.pak)\n");
        printf("  -q, --quiet           Quiet output\n");
        printf("  -d, --detailed        Detailed output\n");
        printf("  -e, --encrypted       Enable encryption\n");
        printf("  -s, --sorted          Sort entries\n");
        return 0;
    }
    
    if (!flags.quiet) {
        printf("PakGen v0.7.0\n");
        printf("=============\n");
    }
    
    int success = fetch_files((const char **)inputs, input_count);
    
    if (!success) {
        printf("Error: No files found\n");
        return 0;
    }
    
    if (!flags.quiet) {
        const char *sort_type = flags.sorted ? "sorted" : "unsorted";
        const char *enc_type = flags.encrypted ? "encrypted" : "plain";
        printf("Creating %s %s archive `%s` w/ %d entries\n", 
               sort_type, enc_type, flags.output, file_count);
    }
    
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [options] input_paths...\n", argv[0]);
        printf("Try `%s --help` for more information\n", argv[0]);
        return -1;
    }
    
    if (strcmp(argv[1], "--help") == 0) {
        printf("Usage: %s [options] input_paths...\n", argv[0]);
        printf("\nOptions:\n");
        printf("  -o, --output FILE     Output package file (default: aout.pak)\n");
        printf("  -q, --quiet           Quiet output\n");
        printf("  -d, --detailed        Detailed output\n");
        printf("  -e, --encrypted       Enable encryption\n");
        printf("  -s, --sorted          Sort entries\n");
        printf("\ninput_paths: Paths to files or directories to include in the package\n");
        return 0;
    }
    
    if (!parse_arguments(argc, argv)) {
        return -1;
    }
    
    int success = emit_package();
    
    if (!flags.quiet) {
        printf("%s!\n", success ? "Done" : "Failed");
    }
    
    return success ? 0 : -1;
}