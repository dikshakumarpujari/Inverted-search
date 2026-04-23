# Inverted Search

An inverted search system developed in C that efficiently indexes words from multiple files and enables fast retrieval of documents containing a given keyword using an inverted index data structure.

## Features
- Index words from multiple input files
- Fast keyword-based search
- Displays files in which the word is present
- Efficient data storage using inverted index
- Handles multiple occurrences of words

## Technologies Used
- C Programming
- File Handling
- Data Structures (Linked Lists / Hashing)
- Pointers
- Functions

## How It Works
The project builds an inverted index to map words to the files in which they appear.

- Each word is stored as a key
- Each key points to a list of files containing that word
- This allows quick lookup of files for a given keyword

Indexing:
- Reads multiple input files
- Extracts words from each file
- Stores words along with file references

Searching:
- User provides a keyword
- The program searches the index
- Displays all files where the word is found

## How to Run
1. Compile the code:
   gcc *.c -o inverted_search

2. Run the program:
   ./inverted_search file1.txt file2.txt file3.txt
