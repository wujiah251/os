#define T_DIR     1   // Directory
#define T_FILE    2   // File
#define T_DEVICE  3   // Device

struct stat {
  int dev;     // File system's disk device
  uint ino;    // Inode number
  // inode的节点号
  short type;  // Type of file
  // 文件类型，目录/文件/设备
  short nlink; // Number of links to file
  // 文件的连接数
  uint64 size; // Size of file in bytes
  // 文件的字节
};
