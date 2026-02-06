/**
 * @file menus.c
 * @author Otajon 908553
 * @brief implementation of menu, building helper functions
 */

#include <stdio.h>
#include <stdlib.h>
#include "menus.h"
#include "utils/utils.h" // We use utils.h for clear_screen and colors

// Note: clear_screen() is implemented in src/utils/utils.c
// We do not re-implement it here to avoid "multiple definition" errors.

void print_divider() {
    // Swapped the dashes for a solid blue line. It frames the content better.
    printf(BOLD_BLUE "────────────────────────────────────────" COLOR_RESET "\n");
}

void print_header(const char *title) {
    // Instead of just text, I'm wrapping it in a Magenta bracket style.
    // This creates a clear visual hierarchy for the page title.
    printf("\n" BOLD_MAGENTA "═══ [ %s ] ═══" COLOR_RESET "\n", title);
}