#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    int num_physical_pages = numpp();
    printf(1, "Number of Physical Pages: %d\n", num_physical_pages);
    exit();
}
