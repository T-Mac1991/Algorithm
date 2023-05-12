#include <stdio.h>

//汉明重量，SWAR算法计算1的个数
unsigned int swar(unsigned int i)
{
    i = (i & 0x55555555) + ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    i = (i & 0x0F0F0F0F) + ((i >> 4) & 0x0F0F0F0F);
    i = (i * 0x01010101) >> 24;
    return i;
}