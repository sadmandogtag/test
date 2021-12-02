#include <stdio.h>
#include <string.h>
#define READ_CHAR	1
#define SKIP_LINE 	2
#define GOT_TYPE	3
#define READ_ADDR 	4
#define READ_SIZE	5

int main(int argc, char **argv) {
unsigned int state = READ_CHAR;
unsigned int cache[128];
unsigned indexmask = (1<<7) - 1;
unsigned index;
unsigned tag;
unsigned address;
int transactions =0;
int hits = 0;
int misses = 0;
char addr[20];
int k = 0;
int c = 0;
while(1) {
c = getchar();
if(c == EOF){
break;
}
switch(state) {
case READ_CHAR:
if(c == '=' || c == '-'){
state = SKIP_LINE;}
else if(c == 'L' || c == 'M' || c == 'S'){
state = GOT_TYPE;
transactions++;
}
memset(addr, 0, sizeof(addr));
break;
case SKIP_LINE:
if(c == '\n'){
state = READ_CHAR;
}
break;
case GOT_TYPE:
if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')) {
state = READ_CHAR;
k =0;
addr[k] = c;
k++;
}
break;
case READ_ADDR:
if(c == ',') {
state = READ_SIZE;
sscanf(addr, "%x", &address);
index = (address >> 3) & indexmask;
tag = address >> 10;
} else {
addr[k] = c;
k++;
}
break;
case READ_SIZE:
if (cache[index] == tag) {
hits++;
} else{
cache[index] = tag;
misses++;
}
state = READ_CHAR;
break;
default:
state = READ_CHAR;
break;
}

}
double hitPercentage = (double)hits / (double)transactions * 100.0;
double missPercentage = (double)misses / (double)transactions * 100.0;

printf("Total Transactions: %d\n", transactions);
printf("Total Hits:	    %d (%f%%)\n", hits, hitPercentage);
printf("Total Misses: 	    %d (%f%%)\n", misses, missPercentage);

return 0;
}

