/*
Compile
 gcc -O2 -std=c11 pakgen_gpt5.c -o pakgen
 ./pakgen -e -s -q -o kernal.pak ./kernal
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#define HEADER_MAGIC "TOFUPAK!"
#define HEADER_MAGIC_LEN 8
#define HEADER_SIZE 16          // 8(magic) + 1(ver) + 1(flags) + 2(reserved) + 4(nfiles)
#define ENTRY_HEADER_SIZE 24      // 16(id) + 4(offset) + 4(size)

#define BLOCK_SIZE 8196

typedef struct {
    char* pathfile;   // 物理路径
    char* name;       // 相对路径名（如 "a.txt"、"subdir/b.bin"）
    unsigned char id[16]; // MD5(id) = MD5(name_norm)
    uint32_t offset;
    uint32_t size;
} FileEntry;

typedef struct {
    FileEntry* items;
    size_t count;
    size_t cap;
} FileList;

/* MD5 implementation (RFC 1321, minimal, self-contained) */
typedef struct {
    uint32_t h[4];
    uint64_t message_len; // in bytes
    uint32_t curlen;
    unsigned char buffer[64];
} MD5_CTX;

static const uint32_t MD5_K[64] = {
 0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,
 0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,0x6b901122,0xfd987193,0xa679438e,0x49b40821,
 0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
 0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,
 0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,
 0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
 0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,
 0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,0xf7537e82,0xbd3af235,0x2bd7b67f,0x90bfbc6c,
 0x3e07841c,0x14292967,0x3e9d7a6f,0x429b02d5,0x24a19947,0x4fefcfa7,0x5b5ac0a8,0x692d0c6b,
 0x788e7279,0x783e3f83,0x7a6d9c11,0x106aa070,0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,
 0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,
 0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

static const uint32_t MD5_S[64] = {
 7,12,17,22, 7,12,17,22, 7,12,17,22, 7,12,17,22,
 5,9,14,20, 5,9,14,20, 5,9,14,20, 5,9,14,20,
 4,11,16,23, 4,11,16,23, 4,11,16,23, 4,11,16,23,
 6,10,15,21, 6,10,15,21, 6,10,15,21, 6,10,15,21
};

static inline uint32_t F(uint32_t x, uint32_t y, uint32_t z) { return (x & y) | ((~x) & z); }
static inline uint32_t G(uint32_t x, uint32_t y, uint32_t z) { return (x & z) | (y & (~z)); }
static inline uint32_t H(uint32_t x, uint32_t y, uint32_t z) { return x ^ y ^ z; }
static inline uint32_t I(uint32_t x, uint32_t y, uint32_t z) { return y ^ (x | (~z)); }
static inline uint32_t LEFTROTATE(uint32_t x, uint32_t c) { return (x << c) | (x >> (32 - c)); }

static void MD5_Init(MD5_CTX* ctx) {
    ctx->h[0] = 0x67452301;
    ctx->h[1] = 0xefcdab89;
    ctx->h[2] = 0x98badcfe;
    ctx->h[3] = 0x10325476;
    ctx->message_len = 0;
    ctx->curlen = 0;
}

static void MD5_Process(MD5_CTX* ctx, const unsigned char* data) {
    uint32_t a = ctx->h[0];
    uint32_t b = ctx->h[1];
    uint32_t c = ctx->h[2];
    uint32_t d = ctx->h[3];

    uint32_t M[16];
    for (int i = 0; i < 16; ++i) {
        M[i] = (uint32_t)data[i*4] | ((uint32_t)data[i*4+1] << 8) | ((uint32_t)data[i*4+2] << 16) | ((uint32_t)data[i*4+3] << 24);
    }

    uint32_t AA = a, BB = b, CC = c, DD = d;

    for (int i = 0; i < 64; ++i) {
        uint32_t Fval, g;
        if (i < 16) {
            Fval = F(BB, CC, DD);
            g = i;
        } else if (i < 32) {
            Fval = G(BB, CC, DD);
            g = (5*i + 1) % 16;
        } else if (i < 48) {
            Fval = H(BB, CC, DD);
            g = (3*i + 5) % 16;
        } else {
            Fval = I(BB, CC, DD);
            g = (7*i) % 16;
        }
        Fval = Fval + AA + MD5_K[i] + M[g];
        AA = DD;
        DD = CC;
        CC = BB;
        BB = BB + LEFTROTATE(Fval, MD5_S[i]);
    }

    a += AA; b += BB; c += CC; d += DD;
    ctx->h[0] += a;
    ctx->h[1] += b;
    ctx->h[2] += c;
    ctx->h[3] += d;
}

static void MD5_Update(MD5_CTX* ctx, const unsigned char* data, size_t len) {
    ctx->message_len += len;
    if (ctx->curlen > 0) {
        size_t left = 64 - ctx->curlen;
        if (len < left) {
            memcpy(ctx->buffer + ctx->curlen, data, len);
            ctx->curlen += len;
            return;
        } else {
            memcpy(ctx->buffer + ctx->curlen, data, left);
            MD5_Process(ctx, ctx->buffer);
            data += left;
            len -= left;
            ctx->curlen = 0;
        }
    }
    while (len >= 64) {
        MD5_Process(ctx, data);
        data += 64;
        len -= 64;
    }
    if (len > 0) {
        memcpy(ctx->buffer, data, len);
        ctx->curlen = len;
    }
}

static void MD5_Final(unsigned char digest[16], MD5_CTX* ctx) {
    uint8_t padding[64] = {0x80};
    uint64_t bit_len = ctx->message_len * 8;
    int pad_len = (ctx->curlen < 56) ? (56 - ctx->curlen) : (64 + 56 - ctx->curlen);
    MD5_Update(ctx, padding, pad_len);

    // Append length in bits as little-endian 64-bit
    unsigned char len_bytes[8];
    for (int i = 0; i < 8; ++i) {
        len_bytes[i] = (unsigned char)((bit_len >> (8*i)) & 0xFF);
    }
    MD5_Update(ctx, len_bytes, 8);

    // Output digest
    for (int i = 0; i < 4; ++i) {
        digest[i*4+0] = (ctx->h[i]      ) & 0xff;
        digest[i*4+1] = (ctx->h[i] >> 8 ) & 0xff;
        digest[i*4+2] = (ctx->h[i] >> 16) & 0xff;
        digest[i*4+3] = (ctx->h[i] >> 24) & 0xff;
    }
}

static void md5(const unsigned char* data, size_t len, unsigned char out[16]) {
    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, data, len);
    MD5_Final(out, &ctx);
}

/* Helpers */

static FileList g_list = {0};
static int g_encrypted = 0;
static int g_sorted = 0;
static int g_quiet = 0;
static int g_detailed = 0;
static const char* g_output = "aout.pak";

static void list_append(FileList* fl, FileEntry* fe) {
    if (fl->count == fl->cap) {
        size_t newcap = fl->cap ? fl->cap * 2 : 8;
        FileEntry* tmp = (FileEntry*)realloc(fl->items, newcap * sizeof(FileEntry));
        if (!tmp) {
            fprintf(stderr, "Out of memory\n");
            exit(1);
        }
        fl->items = tmp;
        fl->cap = newcap;
    }
    fl->items[fl->count++] = *fe;
}

static int is_dir(const char* p) {
    struct stat st;
    if (stat(p, &st) != 0) return 0;
    return S_ISDIR(st.st_mode);
}
static int is_regular_file(const char* p) {
    struct stat st;
    if (stat(p, &st) != 0) return 0;
    return S_ISREG(st.st_mode);
}

static char* join_path(const char* a, const char* b) {
    size_t la = strlen(a);
    size_t lb = strlen(b);
    int need_sep = (la > 0 && a[la-1] != '/');
    size_t len = la + (need_sep ? 1 : 0) + lb + 1;
    char* p = (char*)malloc(len);
    if (!p) { fprintf(stderr, "Out of memory\n"); exit(1); }
    strcpy(p, a);
    if (need_sep) strcat(p, "/");
    strcat(p, b);
    return p;
}

static void add_file_entry(const char* fullpath, const char* relname) {
    FileEntry fe;
    fe.pathfile = strdup(fullpath);
    fe.name = relname ? strdup(relname) : NULL;
    if (!fe.pathfile || (relname && !fe.name)) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    fe.offset = 0;
    fe.size = 0;
    memset(fe.id, 0, 16);
    list_append(&g_list, &fe);
}

static void scan_dir_recursive(const char* root, const char* rel, const char* dirpath) {
    // dirpath is current absolute path to directory
    DIR* d = opendir(dirpath);
    if (!d) {
        fprintf(stderr, "Cannot open directory: %s\n", dirpath);
        exit(1);
    }
    struct dirent* ent;
    while ((ent = readdir(d)) != NULL) {
        const char* name = ent->d_name;
        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) continue;
        char* full = join_path(dirpath, name);
        // compute new relative name
        char* newrel;
        if (rel == NULL) newrel = strdup(name);
        else {
            newrel = join_path(rel, name);
        }
        struct stat st;
        if (stat(full, &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
                scan_dir_recursive(root, newrel, full);
            } else if (S_ISREG(st.st_mode)) {
                add_file_entry(full, newrel);
            }
        }
        free(full);
        if (newrel) {
            free(newrel);
        }
    }
    closedir(d);
}

static void normalize_for_id(const char* src, char* out, size_t max) {
    size_t i = 0;
    for (size_t j = 0; src[j] != '\0' && i + 1 < max; ++j) {
        char c = src[j];
        if (c == '\\') c = '/';
        c = (char)tolower((unsigned char)c);
        out[i++] = c;
    }
    out[i] = '\0';
}

static void compute_id_for_name(const char* name, unsigned char out[16]) {
    // normalize
    char tmp[4096];
    normalize_for_id(name, tmp, sizeof(tmp));
    md5((const unsigned char*)tmp, strlen(tmp), out);
}

/* Sorting by id (memcmp) */
static int cmp_by_id(const void* a, const void* b) {
    const FileEntry* fa = (const FileEntry*)a;
    const FileEntry* fb = (const FileEntry*)b;
    return memcmp(fa->id, fb->id, 16);
}

/* Little-endian helpers */
static void write_u8(FILE* f, uint8_t v) {
    fwrite(&v, 1, 1, f);
}
static void write_u32_le(FILE* f, uint32_t v) {
    uint8_t b[4];
    b[0] = (uint8_t)(v & 0xFF);
    b[1] = (uint8_t)((v >> 8) & 0xFF);
    b[2] = (uint8_t)((v >> 16) & 0xFF);
    b[3] = (uint8_t)((v >> 24) & 0xFF);
    fwrite(b, 1, 4, f);
}
static void write_bytes(FILE* f, const unsigned char* data, size_t len) {
    fwrite(data, 1, len, f);
}

/* XOR cipher with key (16-byte) */
static void xor_cipher_block(const unsigned char* key, size_t keylen, unsigned char* data, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        data[i] ^= key[i % keylen];
    }
}

static int emit_file_data(FILE* out, const char* inpath, int encrypted, const unsigned char key[16]) {
    FILE* in = fopen(inpath, "rb");
    if (!in) {
        fprintf(stderr, "*** can't access file `%s`\n", inpath);
        return 0;
    }

    unsigned char buf[BLOCK_SIZE];
    size_t nread;

    while ((nread = fread(buf, 1, BLOCK_SIZE, in)) > 0) {
        if (encrypted) {
            unsigned char tmp[BLOCK_SIZE];
            memcpy(tmp, buf, nread);
            xor_cipher_block((const unsigned char*)key, 16, tmp, nread);
            fwrite(tmp, 1, nread, out);
        } else {
            fwrite(buf, 1, nread, out);
        }
    }

    fclose(in);
    return 1;
}

static void print_hex_id(const unsigned char id[16]) {
    for (int i = 0; i < 16; ++i) {
        printf("%02X", id[i]);
    }
}

int main(int argc, char** argv) {
    // Simple argument parsing
    const char* input_paths[128];
    int input_cnt = 0;
    const char* output_path = "aout.pak";
    int i;
    int opt_encrypted = 0;
    int opt_sorted = 0;
    int opt_quiet = 0;
    int opt_detailed = 0;

    const char* program = argv[0];

    for (i = 1; i < argc; ++i) {
        char* arg = argv[i];
        if (strcmp(arg, "-o") == 0 || strcmp(arg, "--output") == 0) {
            if (i + 1 < argc) {
                output_path = argv[++i];
            } else {
                fprintf(stderr, "Missing output path after %s\n", arg);
                return 1;
            }
        } else if (strncmp(arg, "--output=", 9) == 0) {
            output_path = arg + 9;
        } else if (strncmp(arg, "-o=", 3) == 0) {
            output_path = arg + 3;
        } else if (strcmp(arg, "-q") == 0 || strcmp(arg, "--quiet") == 0) {
            opt_quiet = 1;
        } else if (strcmp(arg, "-d") == 0 || strcmp(arg, "--detailed") == 0) {
            opt_detailed = 1;
        } else if (strcmp(arg, "-e") == 0 || strcmp(arg, "--encrypted") == 0) {
            opt_encrypted = 1;
        } else if (strcmp(arg, "-s") == 0 || strcmp(arg, "--sorted") == 0) {
            opt_sorted = 1;
        } else {
            input_paths[input_cnt++] = arg;
            if (input_cnt >= 128) break;
        }
    }

    if (input_cnt == 0) {
        fprintf(stderr, "Usage: %s [options] <input_path>...\n", program);
        return 1;
    }

    g_encrypted = opt_encrypted;
    g_sorted = opt_sorted;
    g_quiet = opt_quiet;
    g_detailed = opt_detailed;
    g_output = output_path;

    // Collect files
    g_list.items = NULL;
    g_list.count = 0;
    g_list.cap = 0;

    for (int k = 0; k < input_cnt; ++k) {
        const char* root = input_paths[k];
        if (!g_quiet) {
            printf("Fetching files from path `%s`\n", root);
        }
        if (is_dir(root)) {
            // Scan directory, name starts with entries inside root
            scan_dir_recursive(NULL, NULL, root);
        } else if (is_regular_file(root)) {
            // Direct file
            add_file_entry(root, NULL);
        } else {
            // Try to treat as file path; if not, skip
            fprintf(stderr, "*** can't access path `%s`\n", root);
        }
    }

    // If no files
    if (g_list.count == 0) {
        fprintf(stderr, "No files found to pack.\n");
        return 1;
    }

    // Compute IDs and detect duplicates
    for (size_t idx = 0; idx < g_list.count; ++idx) {
        unsigned char id[16];
        compute_id_for_name(g_list.items[idx].name ? g_list.items[idx].name : "", id);
        memcpy(g_list.items[idx].id, id, 16);
    }

    // Check duplicates
    for (size_t i1 = 0; i1 < g_list.count; ++i1) {
        for (size_t i2 = i1 + 1; i2 < g_list.count; ++i2) {
            if (memcmp(g_list.items[i1].id, g_list.items[i2].id, 16) == 0) {
                fprintf(stderr, "*** entry w/ name `%s` is duplicated (id `%02X`...`%02X` already used for `%s`)\n",
                        g_list.items[i1].name ? g_list.items[i1].name : "",
                        g_list.items[i1].id[0], g_list.items[i1].id[15] /* rough display */, g_list.items[i2].name ? g_list.items[i2].name : "");
                return 1;
            }
        }
    }

    // If sorted flag, sort by id
    if (g_sorted) {
        qsort(g_list.items, g_list.count, sizeof(FileEntry), cmp_by_id);
    }

    // Compute offsets
    const uint32_t base_header = HEADER_SIZE;
    const uint32_t per_entry = ENTRY_HEADER_SIZE;
    uint32_t offset = base_header + g_list.count * per_entry;
    for (size_t idx = 0; idx < g_list.count; ++idx) {
        g_list.items[idx].offset = offset;
        g_list.items[idx].size = (uint32_t) ( (size_t)0 /* will fill after we know file sizes */ );
        // We need to read file size now
    }

    // Determine sizes
    for (size_t idx = 0; idx < g_list.count; ++idx) {
        struct stat st;
        if (stat(g_list.items[idx].pathfile, &st) == 0 && S_ISREG(st.st_mode)) {
            g_list.items[idx].size = (uint32_t)st.st_size;
        } else {
            fprintf(stderr, "*** can't access file `%s`\n", g_list.items[idx].pathfile);
            return 1;
        }
        // offset was set earlier; now advance
        offset += g_list.items[idx].size;
    }

    // Write pak
    FILE* out = fopen(g_output, "wb");
    if (!out) {
        fprintf(stderr, "*** can't create file `%s`\n", g_output);
        return 1;
    }

    // Header
    fwrite(HEADER_MAGIC, 1, HEADER_MAGIC_LEN, out);
    uint8_t ver = 0x00;
    write_u8(out, ver);
    uint8_t flags = (g_encrypted ? 1 : 0) | ((g_sorted ? 1 : 0) << 1);
    write_u8(out, flags);
    uint16_t reserved = 0xFFFF;
    fwrite(&reserved, 2, 1, out);
    write_u32_le(out, (uint32_t)g_list.count);

    // Directory entries
    for (size_t idx = 0; idx < g_list.count; ++idx) {
        fwrite(g_list.items[idx].id, 1, 16, out);
        write_u32_le(out, g_list.items[idx].offset);
        write_u32_le(out, g_list.items[idx].size);
    }

    // Prepare encryption key for each file and write data
    for (size_t idx = 0; idx < g_list.count; ++idx) {
        // Compute key: MD5(file.id)
        unsigned char key[16];
        md5(g_list.items[idx].id, 16, key);

        // Encrypt/write file data
        if (!emit_file_data(out, g_list.items[idx].pathfile, g_encrypted, key)) {
            fclose(out);
            return 1;
        }

        if (!g_quiet) {
            if (g_detailed) {
                printf("> file `%s`\n  name: `%s`\n  id: `", g_list.items[idx].pathfile,
                       g_list.items[idx].name ? g_list.items[idx].name : "");
                print_hex_id(g_list.items[idx].id);
                printf("`\n  offset: %u\n  size: %u\n",
                       g_list.items[idx].offset, g_list.items[idx].size);
            } else {
                printf("[%04zu] `%02X%02X...` -> `%s`\n",
                       idx, g_list.items[idx].id[0], g_list.items[idx].id[15], g_list.items[idx].name ? g_list.items[idx].name : "");
            }
        }
    }

    fclose(out);

    // Cleanup
    for (size_t i1 = 0; i1 < g_list.count; ++i1) {
        free(g_list.items[i1].pathfile);
        if (g_list.items[i1].name) free(g_list.items[i1].name);
    }
    free(g_list.items);

    return 0;
}