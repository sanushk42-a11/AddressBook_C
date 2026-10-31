# Address Book in C

A menu-driven contact manager for the terminal, written in C. Create, edit, display and delete contacts, and save them to a file so nothing is lost when you close the program.

Built as part of my **Embedded Systems Training at Emertxe** (September 2026).

## Features

- **Create** a new contact
- **Edit** an existing contact
- **Display** all saved contacts
- **Delete** a contact
- **Save and Exit**, with contacts stored in a file and loaded again the next time you run the program

## Concepts used

- Structures and arrays to hold contact records
- String handling
- File I/O for persistent storage
- Modular code split across header and source files

## Project structure

````
Address-Book-C/
├── main.c         # Menu and program flow
├── contact.c/.h   # Create, edit, display, delete logic
├── file.c/.h      # Saving and loading contacts
├── populate.c/.h  # Loads saved data at startup
├── contacts.txt   # Saved contact data
└── README.md
````

## How to run

You need `gcc` installed.

````bash
git clone https://github.com/almishamsudheen-ops/Address-Book-C.git
cd Address-Book-C
gcc *.c -o addressbook
./addressbook
````

## Sample menu

````
Address Book
1. Create contact
2. Edit contact
3. Display contacts
4. Delete contact
5. Save and Exit
Enter your choice:
````

## What I learned

- Splitting a C program into multiple modules with header files
- Reading and writing records to files
- Designing a simple menu-driven program

## Author

**Sanush K Santhosh**, ECE graduate (B.Tech 2026), interested in embedded systems and IoT.

[LinkedIn](https://www.linkedin.com/in/sanush-k-santhosh-498432376) | [Portfolio](https://sanush.netlify.app) | [GitHub](https://github.com/sanushk42-a11)
