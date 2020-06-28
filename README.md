# c-syntax-highlighter
This is a lightweight syntax highlighter for the C language. I wrote it while I was reading the book [Crafting interpreters](https://craftinginterpreters.com/). The book describes the complete implementation of a language with a C-like syntax. This project is more modest -- it only needs to scan the source code for tokens and identify their types to do the syntax highlighting.

The project is written in C. It takes in a C source file and produces an HTML file. The HTML file has the various tokens wrapped in spans of their respective classes. The provided CSS file defines styles for those classes that should look familiar to anyone who has used [Notepad++](https://notepad-plus-plus.org/). You can, of course, change the styles to your own taste.
