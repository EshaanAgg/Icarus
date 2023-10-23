#include <bits/stdc++.h>
#include "Icarus/Icarus.h"

int main()
{
    Icarus icarus;

    // Load the sample data
    icarus.loadCSV("data/students.csv");
    icarus.loadCSV("data/enrollments.csv");
    icarus.loadCSV("data/courses.csv");

    // Executing some sample queries on the data provided

    // Query to display student details along with courses they are enrolled in
    icarus.execute("NATURAL(students, NATURAL(enrollments, courses))");

    // Customise the field width and then start the REPL
    icarus.setFieldWidth(20);
    icarus.startREPL();
}