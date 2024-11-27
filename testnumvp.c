#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    // Get the number of virtual pages for the current process
    int num_pages = numvp();  
    printf(1, "Number of virtual pages: %d\n", num_pages);  
    exit();
}
