# CSVSorter
Introduction

The input file will be a CSV or comma-separated value file, which is a simple way to represent a
database table. In a CSV file each line is one record (or row). Commas are separators that denote
different types of values per record (columns). Very often the first record (row) of a CSV is a list of
value types (column headings):
food,calories,fat
soup,200,12
pie,500,25
celery,-10,0

Your code will be given a CSV as well as a value type (column heading) to sort on. Your code will then
need to read in the CSV, sort it on the given value type and output the sorted version of the CSV.
Sorting the CSV above on the 'food' value type:
food,calories,fat
celery,-10,0
pie,500,25
soup,200,12

Sorting the CSV above on the 'calories' value type:
food,calories,fat
celery,-10,0
soup,200,12
pie,500,25

Methodology

a. Parameters
Your code will read the records through standard input (STDIN). Remember, the first record (line) is
the column headings and should not be sorted as data. Your code must take in a command-line
parameter to determine which value type (column) to sort on. If that parameter is not present be sure to
print out an informative error message on standard error (STDERR) and return without creating an
output file. The first argument to your program will be '-c' to indicate sorting by column and the second
will be the column name:
./simpleCSVsorter -c food
 Be sure to check the arguments are there and that they correspond to a listed value type
(column heading) in the CSV.

b. Operation
Your code will be reading the CSV to be sorted from STDIN. In order to run your code to test it, you
will need to open the CSV and read it in to the STDIN for your code:
cat input.file | ./simpleCSVsorter -c movie_title
The line above, if entered on the terminal, will open the file “input.file” and read it in to some
executing code named “simpleCSVsorter”, which was invoked with the parameters “-c” and
“movie_title”.
Your code's output will be a new CSV file outputted to STDOUT. You should output each record line
by line using printf.
For testing purposes you can redirect STDOUT to a file:
cat input.file | ./simpleCSVsorter -c movie_title > sortedmovies.csv

c. Structure
Your code should use Mergesort to do the actual sorting of records. It is a powerful algorithm with an
excellent average case. You should write your own Mergesort code.
It is strongly suggested that you use structs internally to represent each record in the CSV coming in as
input.
In order to help you do both of these, please use a user-defined header file named sorter.h. We have
attached one to the assignment description with some simple comments in it.

If you write any other definitions, typedefs, structs, unions or large helper functions (>~25 lines), be
sure to put them in your header file and document them.

Results

Submit your “simpleCSVsorter.c”, “simpleCSVsorter.h” and “mergesort.c” as well as any other source
files your header file references.
Document your design, assumptions, difficulties you had and testing procedure. Include any test CSV
files you used in your documentation. Be sure to also include a short description of how to use your
code.
