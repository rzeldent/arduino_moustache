#pragma once

#include <WString.h>

typedef struct moustache_variable
{
    const char *key;
    String value;
} moustache_variable_t;

template <size_t n>
inline String moustache_render(const String &format, moustache_variable_t (&values)[n])
{
    auto result = String(format);
    // Conditional sections
    for (size_t i = 0; i < n; i++)
    {
        // Include Section {{#expr}}
        auto match_section_begin = "{{#" + String(values[i].key) + "}}";
        // Inverted section {{^expr}}
        auto match_section_inverted_begin = "{{^" + String(values[i].key) + "}}";
        // End section {{/expr}}
        auto match_section_end = "{{/" + String(values[i].key) + "}}";
        while (true)
        {
            bool inverted = false;
            auto first = result.indexOf(match_section_begin);
            if (first < 0)
            {
                inverted = true;
                first = result.indexOf(match_section_inverted_begin);
                if (first < 0)
                    break;
            }

            auto second = result.indexOf(match_section_end, first + match_section_begin.length());
            if (second < 0)
                break;

            // Arduino returns 0 and 1 for bool.toString()
            if ((!inverted && (values[i].value == "1")) || (inverted && (values[i].value == "0")))
                result = result.substring(0, first) + result.substring(first + match_section_begin.length(), second) + result.substring(second + match_section_end.length());
            else
                result = result.substring(0, first) + result.substring(second + match_section_end.length());
        }
    }

    // Replace variables {{variable}}
    for (size_t i = 0; i < n; i++)
        result.replace("{{" + String(values[i].key) + "}}", values[i].value);

    return result;
}