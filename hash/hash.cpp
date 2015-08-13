#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>

#define BUF 1024

int gethash(char *str)
{
	int i;
	int hash=0,total=0;
    
	int len=strlen(str);

	for(i=0;i<len;i++)
       total=total+str[i]-'0';
	hash=total;
    return hash;
}

unsigned long php_hash(char *arKey) 
{ 
    unsigned long h = 0, g;

	unsigned int nKeyLength=strlen(arKey);
    char *arEnd=arKey+nKeyLength;

    while(arKey<arEnd)
	{ 
        h = (h << 4) + *arKey++; 
        if((g = (h & 0xF0000000)))
	   { 
         h = h^(g>>24); 
         h = h^g; 
       } 
    } 
    return h; 
} 

unsigned long openssl1_strhash(char *str) 
{ 
     int i,l; 
     unsigned long ret=0; 
     unsigned short *s;

     if(str == NULL) 
		 return 0; 
     l=(strlen(str)+1)/2; 
     s=(unsigned short *)str; 
     for (i=0;i<l;i++) 
          ret^=(s[i]<<(i&0x0f)); 
     return ret; 
} 

unsigned long openssl2_strhash(const char *c)
{
    unsigned long ret = 0;
    long n;
    unsigned long v;
    int r;

    if ((c == NULL) || (*c == '\0'))
        return (ret);
/*-
    unsigned char b[16];
    MD5(c,strlen(c),b);
    return(b[0]|(b[1]<<8)|(b[2]<<16)|(b[3]<<24));
*/

    n = 0x100;
    while (*c) {
        v = n | (*c);
        n += 0x100;
        r = (int)((v >> 2) ^ v) & 0x0f;
        ret = (ret << r) | (ret >> (32 - r));
        ret &= 0xFFFFFFFFL;
        ret ^= v * v;
        c++;
    }
    return ((ret >> 16) ^ ret);
}

static unsigned int mysql_hash1(const char *key) 
{ 
	 unsigned int length=strlen(key);
     register unsigned int nr=1, nr2=4;

     while (length--) 
     { 
         nr^= (((nr & 63)+nr2)*((unsigned int) (unsigned char) *key++))+ (nr << 8); 
         nr2+=3; 
      } 
     return((unsigned int) nr); 
}

unsigned int mysql_hash2(const char *key) 
{ 
	unsigned int len=strlen(key);
    const char *end=key+len; 
    unsigned int hash; 
    for (hash = 0; key < end; key++)
	{ 
         hash *= 16777619; 
         hash ^= (unsigned int) (unsigned char) toupper(*key); 
    } 
    return hash; 
}

int openfile(char *str)
{
	int hash;
	int i;
	char buffer[BUF],data[BUF];
	FILE *fp;
	fp=fopen(str,"rb");
	while(fgets(buffer,sizeof(buffer),fp)!=NULL)
	{
		for(i=0;i<strlen(buffer);i++)
		{
			if(!isdigit(buffer[i]))
				   buffer[i]='\0';
		}
		hash=openssl1_strhash(buffer);
		printf("data:%s hash:%#x\n",buffer,hash);
	}
	fclose(fp);
	return 0;
}

int main()
{
	char *file="D:\\C_proj_code\\hashtable\\number.txt";
    openfile(file);
}