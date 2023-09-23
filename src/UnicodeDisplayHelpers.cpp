#include "UnicodeDisplayHelpers.h"

void use_unicode_borders(tabulate::Table& table)
{
    table.format()
        .border_top("─")
        .border_bottom("─")
        .border_left("│")
        .border_right("│")
        .corner("┼");

    auto no_rows = table.size();
    int  row_index = 0;

    for (auto& row : table)
    {
        auto no_columns = row.size();
        int  column_index = 0;
        for (auto& column : row)
        {
            if (column_index == 0)
            {
                column.format().corner_top_left("├").corner_bottom_left("├");
            }

            if (column_index == no_columns - 1)
            {
                column.format().corner_top_right("┤").corner_bottom_right("┤");
            }

            if (column_index > 0 && column_index < no_columns - 1)
            {
                column.format().border_left("│").border_right("│");
            }

            column_index++;
        }

        if (row_index == 0)
        {
            format_top_row(row);
        }

        if (row_index == no_rows - 1)
        {
            format_bottom_row(row);
        }

        row_index++;
    }
}

void format_top_row(tabulate::Row row)
{
    row.format().border_top("─").border_bottom("─");

    auto no_columns = row.size();
    int  column_index = 0;

    for (auto& column : row)
    {
        if (column_index == 0)
        {
            column.format().corner_top_left("┌").corner_top_right("┬");
        }

        if (column_index == no_columns - 1)
        {
            column.format().corner_top_left("┬").corner_top_right("┐");
        }

        if (column_index > 0 && column_index < no_columns - 1)
        {
            column.format().corner_top_left("┬").corner_top_right("┬");
        }

        column_index++;
    }
}

void format_bottom_row(tabulate::Row row)
{
    row.format().border_top("─").border_bottom("─");

    auto no_columns = row.size();
    int  column_index = 0;

    for (auto& column : row)
    {
        if (column_index == 0)
        {
            column.format().corner_bottom_left("└").corner_bottom_right("┴");
        }

        if (column_index == no_columns - 1)
        {
            column.format().corner_bottom_right("┘").corner_bottom_left("┴");
        }

        if (column_index > 0 && column_index < no_columns - 1)
        {
            column.format().corner_bottom_left("┴").corner_bottom_right("┴");
        }

        column_index++;
    }
}
