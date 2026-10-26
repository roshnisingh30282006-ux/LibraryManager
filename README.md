# Library Manager (C++)

A beginner-friendly, menu-driven library management application demonstrating classes, encapsulation, vectors, searching, input validation, and file persistence.

## Features
- Add books and library members with unique positive IDs.
- List books and members.
- Search by book ID or title (case-insensitive title search).
- Issue a book to a member and return it.
- Save data automatically to local text files and reload it on startup.
- Reject invalid menu choices, malformed numbers, blank text, duplicate IDs, unavailable books, and unknown IDs.

## Requirements
A C++11-or-newer compiler (GCC, Clang, or a recent MSVC).

## Build and run

### Windows (MinGW g++)
Open PowerShell in this folder:

```powershell
g++ -std=c++11 -Wall -Wextra main.cpp Book.cpp Member.cpp Loan.cpp -o LibraryManager.exe
.\LibraryManager.exe
```

### Linux / macOS
```bash
g++ -std=c++11 -Wall -Wextra main.cpp Book.cpp Member.cpp Loan.cpp -o library_manager
./library_manager
```

In VS Code, open this folder, create/open the terminal in this directory, then run the command for your system.

## Data files
The application creates `books.txt`, `members.txt`, and `loans.txt` in the current working directory. Keep these files with your project if you want to preserve the sample records.

## Sample test flow
1. Select `1`, add book ID `101`, title `The Little Prince`, author `Antoine de Saint-Exupery`.
2. Select `2`, add member ID `1`, name `Aarav`.
3. Select `6`, issue book `101` to member `1`, and enter date `2026-10-26`.
4. Select `3` to confirm the book is marked `Issued`.
5. Select `7`, return book `101` for member `1`.
6. Select `3` again to confirm it is `Available`.
7. Select `0` to save and exit. Run the program again to verify records persist.

## Class responsibilities
- `Book`: stores book details and availability.
- `Member`: stores member details and borrowed book IDs.
- `Loan`: stores the book ID, member ID, and issue date for an active loan.
- `LibraryManager` (in `main.cpp`): coordinates menus, validation, searching, issue/return rules, and file storage.

## Class diagram
See `class-diagram.md` for the diagram source. You can paste its Mermaid diagram into a Mermaid renderer to export a PNG if your submission requires an image.

## Submission checklist
- [ ] Build succeeds on your machine.
- [ ] Test add, list, search, issue, return, invalid input, and restart persistence.
- [ ] Capture screenshots of the terminal output.
- [ ] Upload all source files, data files (if any), README, and class diagram to one repository.
