#ifndef HELPERS_H
#define HELPERS_H

int validate_ext(const char *filename) {
        // const because this pointer isn't allowed to modify the filename, only read it
        while (*filename != '\0') {
                if (*filename != '.') {
                        filename++;
                        continue;
                }
                
                if (*(filename + 1) == '\0' ||
                    *(filename + 2) == '\0') return 0;
                
                else if (*(filename + 1) == 'b' &&
                         *(filename + 2) == 'f' &&
                         *(filename + 3) == '\0') return 1;

                else filename++;
        }
        
        return 0;
}

#endif