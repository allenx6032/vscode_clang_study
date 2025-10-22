/*
Compile
gcc -o pakgen pakgen.c -lws2_32 -Wall -O2
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <getopt.h>
#include <ctype.h>
#include <assert.h>
#include <stdint.h> // 添加标准整数类型定义
// 字节序处理 (跨平台支持)
#if defined(__linux__)
#  include <endian.h>
#elif defined(__APPLE__)
#  include <libkern/OSByteOrder.h>
#  define htobe16(x) OSSwapHostToBigInt16(x)
#  define htole16(x) OSSwapHostToLittleInt16(x)
#  define be16toh(x) OSSwapBigToHostInt16(x)
#  define le16toh(x) OSSwapLittleToHostInt16(x)
#  define htobe32(x) OSSwapHostToBigInt32(x)
#  define htole32(x) OSSwapHostToLittleInt32(x)
#  define be32toh(x) OSSwapBigToHostInt32(x)
#  define le32toh(x) OSSwapLittleToHostInt32(x)
#elif defined(_WIN32)
#  include <winsock2.h>
#  define htobe16(x) htons(x)
#  define htole16(x) (x)
#  define be16toh(x) ntohs(x)
#  define le16toh(x) (x)
#  define htobe32(x) htonl(x)
#  define htole32(x) (x)
#  define be32toh(x) ntohl(x)
#  define le32toh(x) (x)
#endif

#define HEADER_SIZE 16
#define ENTRY_SIZE  24
#define VERSION     0x00
#define RESERVED    0xFFFF

typedef struct {
    char* path;
    char* name;
    uint8_t id[16];  // MD5结果固定16字节
    uint32_t size;
    uint32_t offset;
} FileEntry;

typedef struct {
    int quiet;
    int detailed;
    int encrypted;
    int sorted;
} Flags;

// ================== MD5实现开始 ==================
#define MD5_DIGEST_LENGTH 16 // MD5摘要长度为16字节
typedef struct {
    uint32_t state[4];
    uint32_t count[2];
    uint8_t buffer[64];
} MD5_CTX;

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ y ^ z)
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

// 补全md5_transform函数
// Round 1 - F function 
#define FF(a, b, c, d, x, s, ac) { \
    (a) += F((b), (c), (d)) + (x) + (uint32_t)(ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}
// Round 2 - G function 
#define GG(a, b, c, d, x, s, ac) { \
    (a) += G((b), (c), (d)) + (x) + (uint32_t)(ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}
// Round 3 - H function
#define HH(a, b, c, d, x, s, ac) { \
    (a) += H((b), (c), (d)) + (x) + (uint32_t)(ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
} 
// Round 4 - I function
#define II(a, b, c, d, x, s, ac) { \
    (a) += I((b), (c), (d)) + (x) + (uint32_t)(ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}

static const uint8_t PADDING[64] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


static void md5_init(MD5_CTX* context) {
    context->count[0] = context->count[1] = 0;
    context->state[0] = 0x67452301;
    context->state[1] = 0xefcdab89;
    context->state[2] = 0x98badcfe;
    context->state[3] = 0x10325476;
}

static void md5_transform(uint32_t state[4], const uint8_t block[64]) {
    uint32_t a = state[0], b = state[1], c = state[2], d = state[3];
    uint32_t x[16];

    for (int i = 0, j = 0; j < 64; i++, j += 4)
        x[i] = (block[j]) | (block[j+1] << 8) | (block[j+2] << 16) | (block[j+3] << 24);

    // Round 1 - F function
    FF(a, b, c, d, x[0],  7, 0xd76aa478);
    FF(d, a, b, c, x[1], 12, 0xe8c7b756);
    FF(c, d, a, b, x[2], 17, 0x242070db);
    FF(b, c, d, a, x[3], 22, 0xc1bdceee);
    FF(a, b, c, d, x[4],  7, 0xf57c0faf);
    FF(d, a, b, c, x[5], 12, 0x4787c62a);
    FF(c, d, a, b, x[6], 17, 0xa8304613);
    FF(b, c, d, a, x[7], 22, 0xfd469501);
    FF(a, b, c, d, x[8],  7, 0x698098d8);
    FF(d, a, b, c, x[9], 12, 0x8b44f7af);
    FF(c, d, a, b, x[10],17, 0xffff5bb1);
    FF(b, c, d, a, x[11],22, 0x895cd7be);
    FF(a, b, c, d, x[12], 7, 0x6b901122);
    FF(d, a, b, c, x[13],12, 0xfd987193);
    FF(c, d, a, b, x[14],17, 0xa679438e);
    FF(b, c, d, a, x[15],22, 0x49b40821);
    // Round 2 - G function
    GG(a, b, c, d, x[1],  5, 0xf61e2562);
    GG(d, a, b, c, x[6],  9, 0xc040b340);
    GG(c, d, a, b, x[11],14, 0x265e5a51);
    GG(b, c, d, a, x[0], 20, 0xe9b6c7aa);
    GG(a, b, c, d, x[5],  5, 0xd62f105d);
    GG(d, a, b, c, x[10], 9, 0x02441453);
    GG(c, d, a, b, x[15],14, 0xd8a1e681);
    GG(b, c, d, a, x[4], 20, 0xe7d3fbc8);
    GG(a, b, c, d, x[9],  5, 0x21e1cde6);
    GG(d, a, b, c, x[14], 9, 0xc33707d6);
    GG(c, d, a, b, x[3], 14, 0xf4d50d87);
    GG(b, c, d, a, x[8], 20, 0x455a14ed);
    GG(a, b, c, d, x[13], 5, 0xa9e3e905);
    GG(d, a, b, c, x[2],  9, 0xfcefa3f8);
    GG(c, d, a, b, x[7], 14, 0x676f02d9);
    GG(b, c, d, a, x[12],20, 0x8d2a4c8a);
    // Round 3 - H function
    HH(a, b, c, d, x[5],  4, 0xfffa3942);
    HH(d, a, b, c, x[8], 11, 0x8771f681);
    HH(c, d, a, b, x[11],16, 0x6d9d6122);
    HH(b, c, d, a, x[14],23, 0xfde5380c);
    HH(a, b, c, d, x[1],  4, 0xa4beea44);
    HH(d, a, b, c, x[4], 11, 0x4bdecfa9);
    HH(c, d, a, b, x[7], 16, 0xf6bb4b60);
    HH(b, c, d, a, x[10],23, 0xbebfbc70);
    HH(a, b, c, d, x[13], 4, 0x289b7ec6);
    HH(d, a, b, c, x[0], 11, 0xeaa127fa);
    HH(c, d, a, b, x[3], 16, 0xd4ef3085);
    HH(b, c, d, a, x[6], 23, 0x04881d05);
    HH(a, b, c, d, x[9],  4, 0xd9d4d039);
    HH(d, a, b, c, x[12],11, 0xe6db99e5);
    HH(c, d, a, b, x[15],16, 0x1fa27cf8);
    HH(b, c, d, a, x[2], 23, 0xc4ac5665);
    // Round 4 - I function
    II(a, b, c, d, x[0],  6, 0xf4292244);
    II(d, a, b, c, x[7], 10, 0x432aff97);
    II(c, d, a, b, x[14],15, 0xab9423a7);
    II(b, c, d, a, x[5], 21, 0xfc93a039);
    II(a, b, c, d, x[12], 6, 0x655b59c3);
    II(d, a, b, c, x[3], 10, 0x8f0ccc92);
    II(c, d, a, b, x[10],15, 0xffeff47d);
    II(b, c, d, a, x[1], 21, 0x85845dd1);
    II(a, b, c, d, x[8],  6, 0x6fa87e4f);
    II(d, a, b, c, x[15],10, 0xfe2ce6e0);
    II(c, d, a, b, x[6], 15, 0xa3014314);
    II(b, c, d, a, x[13],21, 0x4e0811a1);
    II(a, b, c, d, x[4],  6, 0xf7537e82);
    II(d, a, b, c, x[11],10, 0xbd3af235);
    II(c, d, a, b, x[2], 15, 0x2ad7d2bb);
    II(b, c, d, a, x[9], 21, 0xeb86d391);

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}


static void md5_update(MD5_CTX* context, const uint8_t* input, size_t length) {
    uint32_t i, index, partLen;

    index = (uint32_t)((context->count[0] >> 3) & 0x3F);
    context->count[0] += (uint32_t)(length << 3);
    if (context->count[0] < (uint32_t)(length << 3))
        context->count[1]++;
    context->count[1] += (uint32_t)(length >> 29);

    partLen = 64 - index;
    if (length >= partLen) {
        memcpy(&context->buffer[index], input, partLen);
        md5_transform(context->state, context->buffer);
        for (i = partLen; i + 63 < length; i += 64)
            md5_transform(context->state, &input[i]);
        index = 0;
    } else {
        i = 0;
    }
    memcpy(&context->buffer[index], &input[i], length - i);
}

static void md5_final(uint8_t digest[16], MD5_CTX* context) {
    uint8_t bits[8];
    uint32_t index, padLen;

    memcpy(bits, context->count, 8);
    
    index = (uint32_t)((context->count[0] >> 3) & 0x3F);
    padLen = (index < 56) ? (56 - index) : (120 - index);
    md5_update(context, PADDING, padLen);
    md5_update(context, bits, 8);
    
    memcpy(digest, context->state, 16);
}


void md5_hash(const uint8_t* input, size_t length, uint8_t digest[16]) {
    MD5_CTX context;
    md5_init(&context);
    md5_update(&context, input, length);
    md5_final(digest, &context);
}
// ================== MD5实现结束 ==================

// 目录遍历函数保持不变
static void process_dir(const char* path, const char* prefix, FileEntry** entries, int* count) {
    // 计算MD5部分修改为：
    // md5_hash((uint8_t*)fe->name, strlen(fe->name), fe->id);
    DIR* dir = opendir(path);
    if (!dir) return;

    struct dirent* entry;
    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(fullpath, &st) != 0) continue;

        // 构建规范化名称
        char* name = NULL;
        if (prefix) {
            name = malloc(strlen(prefix) + strlen(entry->d_name) + 2);
            sprintf(name, "%s/%s", prefix, entry->d_name);
        } else {
            name = strdup(entry->d_name);
        }

        // 转换为小写和统一路径分隔符
        for (char* p = name; *p; ++p) {
            *p = tolower(*p);
            if (*p == '\\') *p = '/';
        }

        if (S_ISDIR(st.st_mode)) {
            process_dir(fullpath, name, entries, count);
            free(name);
        } else {
            // 添加到条目列表
            *entries = realloc(*entries, (*count + 1) * sizeof(FileEntry));
            FileEntry* fe = &(*entries)[(*count)++];
            
            fe->path = strdup(fullpath);
            fe->name = name;
            fe->size = st.st_size;
            
            // 计算名称MD5
           md5_hash((uint8_t*)fe->name, strlen(fe->name), fe->id);
        }
    }
    closedir(dir);
}

// 检查重复项和排序函数保持不变
// 比较函数用于排序和查重
static int compare_entries(const void* a, const void* b) {
    return memcmp(((FileEntry*)a)->id, ((FileEntry*)b)->id, MD5_DIGEST_LENGTH);
}

// 检查重复ID
static int check_duplicates(FileEntry* entries, int count) {
    for (int i = 1; i < count; ++i) {
        if (memcmp(entries[i].id, entries[i-1].id, MD5_DIGEST_LENGTH) == 0) {
            fprintf(stderr, "Duplicate entries: %s and %s\n", 
                    entries[i-1].name, entries[i].name);
            return 0;
        }
    }
    return 1;
}

// 写入文件头
static int write_header(FILE* fp, const Flags* flags, int count) {
    uint8_t header[HEADER_SIZE] = {0};
    memcpy(header, "TOFUPAK!", 8);
    header[8] = VERSION;
    header[9] = (flags->encrypted << 0) | (flags->sorted << 1);
    *(uint16_t*)(header + 10) = htole16(RESERVED);
    *(uint32_t*)(header + 12) = htole32(count);
    return fwrite(header, 1, HEADER_SIZE, fp) == HEADER_SIZE;
}

// 写入目录条目
static int write_entries(FILE* fp, FileEntry* entries, int count) {
    for (int i = 0; i < count; ++i) {
        FileEntry* fe = &entries[i];
        uint32_t offset = htole32(fe->offset);
        uint32_t size = htole32(fe->size);
        
        if (fwrite(fe->id, 1, MD5_DIGEST_LENGTH, fp) != MD5_DIGEST_LENGTH ||
            fwrite(&offset, 1, 4, fp) != 4 ||
            fwrite(&size, 1, 4, fp) != 4) {
            return 0;
        }
    }
    return 1;
}

// 加密函数修改密钥生成方式
static int write_content(FILE* out, const FileEntry* fe, const Flags* flags) {
	FILE* in = fopen(fe->path, "rb");
    if (!in) return 0;
    
    uint8_t key[16];
    md5_hash(fe->id, 16, key);  // 使用自实现MD5
	int key_idx = 0;

    uint8_t buffer[8192];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), in)) > 0) {
        if (flags->encrypted) {
            for (size_t i = 0; i < bytes; ++i) {
                buffer[i] ^= key[key_idx];
                key_idx = (key_idx + 1) % MD5_DIGEST_LENGTH;
            }
        }
        if (fwrite(buffer, 1, bytes, out) != bytes) {
            fclose(in);
            return 0;
        }
    }
    
    fclose(in);
    return 1;
}

void print_hex(const uint8_t* data, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

// 测试用例
void test_md5() {
    uint8_t digest[16];
    
    // 测试空字符串
    md5_hash((uint8_t*)"", 0, digest);
    assert(memcmp(digest, "\xd4\x1d\x8c\xd9\x8f\x00\xb2\x04\xe9\x80\x09\x98\xec\xf8\x42\x7e", 16) == 0);
    // printf("Hex: 0x%02x\n", digest);
    print_hex(digest, 16);
    
    // 测试"abc"
    md5_hash((uint8_t*)"abc", 3, digest);
    assert(memcmp(digest, "\x90\x01\x50\x98\x3c\xd2\x4f\xb0\xd6\x96\x3f\x7d\x28\xe1\x7f\x72", 16) == 0);
    // printf("abc Hex: 0x%02x\n", digest);
    print_hex(digest, 16);
}

int main(int argc, char* argv[]) {
	
	test_md5();
    // 参数解析和主逻辑保持不变...
    // 编译时不再需要链接OpenSSL库
    // 解析命令行参数
    Flags flags = {0};
    char* output = "aout.pak";
    int opt;
    
    while ((opt = getopt(argc, argv, "o:qdes")) != -1) {
        switch (opt) {
            case 'o': output = optarg; break;
            case 'q': flags.quiet = 1; break;
            case 'd': flags.detailed = 1; break;
            case 'e': flags.encrypted = 1; break;
            case 's': flags.sorted = 1; break;
            default: return EXIT_FAILURE;
        }
    }
    
    if (optind >= argc) {
        fprintf(stderr, "No input paths specified\n");
        return EXIT_FAILURE;
    }

    // 收集输入文件
    FileEntry* entries = NULL;
    int count = 0;
    for (int i = optind; i < argc; ++i) {
        process_dir(argv[i], NULL, &entries, &count);
    }
    
    if (count == 0) {
        fprintf(stderr, "No files found\n");
        return EXIT_FAILURE;
    }

    // 处理排序和重复项
    if (flags.sorted) qsort(entries, count, sizeof(FileEntry), compare_entries);
    if (!check_duplicates(entries, count)) return EXIT_FAILURE;

    // 计算文件偏移
    uint32_t offset = HEADER_SIZE + count * ENTRY_SIZE;
    for (int i = 0; i < count; ++i) {
        entries[i].offset = offset;
        offset += entries[i].size;
    }

    // 创建输出文件
    FILE* fp = fopen(output, "wb");
    if (!fp) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    // 写入数据
    if (!write_header(fp, &flags, count) ||
        !write_entries(fp, entries, count)) {
        fclose(fp);
        remove(output);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < count; ++i) {
        if (!write_content(fp, &entries[i], &flags)) {
            fclose(fp);
            remove(output);
            return EXIT_FAILURE;
        }
    }

    // 清理资源
    fclose(fp);
    for (int i = 0; i < count; ++i) {
        free(entries[i].path);
        free(entries[i].name);
    }
    free(entries);

    if (!flags.quiet) printf("Archive created: %s\n", output);
    return EXIT_SUCCESS;
}