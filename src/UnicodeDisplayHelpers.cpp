#include "UnicodeDisplayHelpers.h"

void use_unicode_borders(tabulate::Table& table)
{
    table.format()
        .border_top("─")
        .border_bottom("─")
        .border_left("│")
        .border_right("│")
        .corner("┼");
}
