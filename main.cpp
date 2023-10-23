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

    // Display student details along with courses they are enrolled in
    // icarus.execute("NATURAL(students, NATURAL(enrollments, courses))");

    // Display details of students registered for all courses of CSE Department
    // icarus.execute("PROJECT(DIVIDE(NATURAL(students, NATURAL(enrollments, courses)), SELECT(courses, CourseDep = 'CSE')), RollNo, FirstName)")

    // Implement OR operator in SELECT operation
    // icarus.execute("SELECT(students, Department = 'CSE' || RollNo = '14085035')");

    // Display roll numbers of students studying CS301 but not CS302
    // icarus.execute("PROJECT(DIFF(SELECT(enrollments, CourseID = 'CS301'), SELECT(enrollments, CourseID = 'CS302')), RollNo)");

    // Display the roll numbers of students in Chemical Department or studying the course MA302
    icarus.execute("UNION(PROJECT(SELECT(students, Department = 'Chemical'), RollNo), PROJECT(SELECT(enrollments, CourseID = 'MA302'), RollNo))");

    // Customise the field width and then start the REPL
    icarus.setFieldWidth(15);
    icarus.startREPL();
}