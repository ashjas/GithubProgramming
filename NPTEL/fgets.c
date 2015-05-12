#include<stdio.h>
int main()
{
    char line[1024], *p, *e;
    long v;
    while (fgets(line, sizeof(line), stdin)) {
        p = line;
        printf("%s",p);
        for (p = line; ; p = e) {
            v = strtol(p, &e, 10);
            if (p == e)
                break;
            // process v here
        }
    }
}
