// micro-moustache basic example
//
// Replace strings and conditional include / exclude text
//
// For examples can be found in the original documentation: http://mustache.github.io/mustache.5.html

#include <Arduino.h>
#include <moustache.h>

void setup()
{
    Serial.begin(115200);

    Serial.println("Moustache Example");

    const char *taxes =
        "Hello {{name}}\n" 
        "You have just won {{value}} dollars!\n"
        "{{#in_ca}}"
        "Well, {{taxed_value}} dollars, after taxes.\n"
        "{{/in_ca}}"
        "{{^in_ca}}"
        "And no taxes paid!\n"
        "{{/in_ca}}";

    const moustache_variable_t substitutions[] = {
        {"name", "Chris"},
        {"value", String(10000)},
        {"taxed_value", String(10000 - (10000 * 0.4))},
        {"in_ca", String(true)}};

    String result;
    // Default rendering
    result = moustache_render(taxes, substitutions);
    Serial.println(result);

    // Replace variable 'in_ca' at index 3 and render
    result = moustache_render(taxes, substitutions, 3, String(false));
    Serial.println(result);

    // Replace variable 'name' and render
    result = moustache_render(taxes, substitutions, "name", "John");
    Serial.println(result);

    // Replace variable value and taxed_value in one go. So start index = 1
    const String replace_1[] = {
        String(20000),
        String(20000 - (20000 * 0.4))
    };

    result = moustache_render(taxes, substitutions, 1, replace_1);
    Serial.println(result);

    // Replace variable name, value and taxed_value in one go. Start at "name"
    const String replace_name[] = {
        "Mike",
        String(30000),
        String(30000 - (30000 * 0.4))
    };

    result = moustache_render(taxes, substitutions, "name", replace_name);
    Serial.println(result);
}

void loop()
{
}