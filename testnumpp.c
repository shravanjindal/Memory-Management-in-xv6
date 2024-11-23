#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    int num_physical_pages = numpp();
    printf(1, "Initial Number of Physical Pages: %d\n", num_physical_pages);

    // Allocate memory and check again
    printf(1, "Allocating 1 page of memory...\n");
    char *mem = sbrk(4096);  // Allocate one page
    if (mem == (char *)-1) {
        printf(1, "sbrk failed!\n");
        exit();
    }

    num_physical_pages = numpp();
    printf(1, "Number of Physical Pages after allocation: %d\n", num_physical_pages);

    // Allocate more memory
    printf(1, "Allocating 3 more pages of memory...\n");
    sbrk(4096 * 3);  // Allocate three more pages
    num_physical_pages = numpp();
    printf(1, "Number of Physical Pages after allocating 3 more pages: %d\n", num_physical_pages);

    exit();
}
