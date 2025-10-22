#ifdef CONFIG_H
#include CONFIG_H
#endif

#ifdef FILESYS_C
#pragma once
#define DIR_C
#define FILE_C
#define FOLDER_C
#define FTYPE_C
#define KVS_C
#define URI_C
#define VFS_C
#define PAK_C
#define FILE56_C
#endif

#include <stdio.h>

#include "filesys_kvs.c.h"
#include "filesys_folder.c.h"
#include "filesys_dir.c.h"
#include "filesys_file.c.h"
#include "filesys_type.c.h"
#include "filesys_uri.c.h"
#include "filesys_vfs.c.h"
#include "filesys_pak.c.h"
#include "filesys_file56.c.h"
