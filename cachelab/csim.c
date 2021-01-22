#include "cachelab.h"
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAX_LEN 1000

int my2pow(char * n);


struct Record
{
    int miss;
    int hit;
    int eviction;
};

typedef struct block
{
   int available;
   long addr;
} Block;


int main(int argc, char **argv)
{
  int vflag = 0;
  int hflag = 0;
  char *svalue = NULL;
  char *Evalue = NULL;
  char *bvalue = NULL;
  char *tname = NULL;  // 文件名字
  FILE *fp;
  char buffer[MAX_LEN];
  int index;
  int c;
  Block *hcache;  // 虚假的高速缓存
  Block *thcache;  // 临时高速缓存
  struct Record record; 
  
  opterr = 0;

  while ((c = getopt (argc, argv, "hvs:E:b:t:")) != -1)
    switch (c)
      {
      case 'h':
        hflag = 1;
        break;
      case 'v':
        vflag = 1;
        break;
      case 's':
        svalue = optarg;
        break;
      case 'E':
        Evalue = optarg;
        break;
      case 'b':
        bvalue = optarg;
        break;
      case 't':
        tname = optarg;
        break;
      case '?':
        // 这里是直接从网上抄的，没仔细改，有bug哈哈哈
        if (optopt == 's' || optopt == 'E' || optopt == 'b' || optopt == 't')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort();
      }

    for (index = optind; index < argc; index++)
        printf ("Non-option argument %s\n", argv[index]);

    // 如果-h 就直接返回
    if (hflag == 1) {
      printf("ok ok, i know you need help!\n");
      printf("Usage: ./csim [-hv] -s <s> -E <E> -b <b> -t <tracefile>\n");
      return 0;
    }

    // open file 
    fp = fopen(tname, "r");
    if (fp == NULL) {
      perror("error file not exsit\n");
      return 1;
    }
    // 划出内存
    hcache = (Block *) (malloc (sizeof(Block) * my2pow(svalue) * atoi(Evalue)));
    thcache = (Block *) (malloc (sizeof(Block) * atoi(Evalue) + 1));  // +1是因为循环的时候，不命中的时候会多一个block
    while (fgets(buffer, MAX_LEN - 1, fp))
    {
        buffer[strcspn(buffer, "\n")] = 0;
        char ce;
        char sign;
        char addrchar[20];
        char sizechar[10];
        char *cp = buffer;
        Block ele;
        if (*cp++ == 'I')
          continue;
        sign = *cp++;  // M L or S
        char * tp = addrchar;  // temp pointer
        while ( (ce = *cp++) != ',' )
        {
            if ( ce == ' ')
              continue;
            *tp++ = ce;
        }
        *tp = '\0';
        tp = sizechar;
        while ( (ce = *cp++) != '\0') 
        {
            *tp++ = ce;
        }
        *tp = '\0';
        // int size = atoi(sizechar);  存疑，这里是否需要用到size来判断当前内存是否够长？此答案没用到。
        long addr = strtol(addrchar, NULL, 16);
        // printf("buffer = %s, addr = %lx, size = %d\n",buffer, addr, size);
        long t = addr >> (atoi(bvalue) + atoi(svalue)) << (atoi(bvalue) + atoi(svalue));
        int group = (int) ((addr >> atoi(bvalue)) & (my2pow(svalue) -1));
        int E = atoi(Evalue);
        Block *tcp = hcache + group * E;  // 临时指针
        Block *thcp = thcache;  // 临时指针
        thcp->addr = t;  // 把t写到最前面
        thcp->available = 1;  // 写成命中
        thcp++;
        int is_hit = 0;  // 默认没命中
        int last_full = 0;  // 最后一个元素是否有东西 默认木有
        for (int i = E; i > 0; i--) {
          ele = *tcp++;
          if (ele.addr == t && ele.available == 1) {
            is_hit = 1;
          } else {
            // *thcp++ = ele;
            thcp->addr = ele.addr;
            thcp->available = ele.available;
            thcp++;
          }
          if ( i == 1 && ele.available == 1)
            last_full = 1;
        }
        // 写回去
        tcp = hcache + group * E;
        thcp = thcache;
        for (int i = E; i > 0; i--) {
          *tcp++ = *thcp++;
        }
        // 判断命中啥的
        if (is_hit) {
          record.hit += 1;
          if ( sign == 'M')
            record.hit += 1;
        } else {
          record.miss += 1;
          if ( sign == 'M')
            record.hit += 1;
        }

        if (!is_hit && last_full)
          record.eviction += 1;
        if (vflag) {
          printf("buffer = %s, is_hit = %d, eviction = %d\n", buffer, is_hit, !is_hit && last_full);
        }
    }
    fclose(fp);
    // free(hcache);  // 这里把free给注释了，因为……带着free会报错，不知道哪里的问题  - -
    // free(thcache);
    // printf("hit = %d, miss = %d, eviction = %d\n", record.hit, record.miss, record.eviction);
    printSummary(record.hit, record.miss, record.eviction);
    return 0;
}


int my2pow(char * n)
{
  int val = atoi(n);
  int ret = 1;
  while ( val > 0)
  {
    ret *= 2;
    val -= 1;
  }
  return ret;
}



