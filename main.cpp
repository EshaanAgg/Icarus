#include <bits/stdc++.h>
#include "Icarus/Icarus.h"

int main()
{
    Icarus icarus;

    // Load the sample data
    icarus.loadCSV("data/students.csv");
    icarus.loadCSV("data/enrollmets.csv");
    icarus.loadCSV("data/courses.csv");

    // Customise the field width and then start the REPL
    icarus.setFieldWidth(30);
    icarus.startRELP();
}