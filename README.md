# C++ Theater Backend

Problem: I have been hired by the owner of a very small movie theater to develop the backend for an online ticket reservation system. The program should display the current seating arrangement and allow the patron to select seats. A report should be generated at the end of the program to specify for each individual auditorium and overall for all auditoriums how many seats were sold/unsold and how much money was earned.

Details: The theater is stored as a static 2D array with a max size of 26 x 10, read in from a file in the project directory named "A1.txt". Displaying A1.txt would be as follows: 
         

      ABCDEFGHIJKLMNOPQRST
    1 ...##..#####........
    2 ########....####..##
    3 .........##.........
    4 #.#.#.#.#.#.#.#.#.#.
    5 ########.#####.#####
    

A sample of A1.txt is provided. A is an adult ticket ($10), C is a child ticket ($5), S is a senior ticket ($7.50), and "." represents an empty seat.
When displaying the theater to the user, all letters are replaced by a "#" because all the user needs to know is that the seat is reserved, not what type of seat it is.
