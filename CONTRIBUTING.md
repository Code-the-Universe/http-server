# Contribution standards
These are our contribution guides. In order to be accepted, pull requests need to follow them.
## Formatting
### Casing
Class names are to be written in PascalCase, methods in camelCase and local variables in snake_case
### Object initialization
Primitives are to be initialized with the `=` operator, classes using bracket `{}` construction.
### Newlines
Every {bracket} is to be placed on a newline, long function parameters are to be broken up in newlines too. (Use common sense)
### Namespaces
Every class goes into the `http` namespace
### Macros
Macros are not allowed, the only exception is HEADER_GUARDS

## Dependencies
The only dependency allowed is SFML's networking module, where the classes `sf::Http` and `sf::Ftp` are disallowed.
(And of course the C++ Standard Template Library)
## Exceptions
Avoid throwing exceptions, and try to deal with the underlying problem.
All standard and / or SFML functionality which could throw  exceptions are to be dealt with by the caller directly.
## Dynamic memory
Avoid allocating dynamic memory if possible. If need be, use smart pointers and structures 
like std::vector to manage memory for you

## General guidelines
Try writing efficient code. Use C++'s abstractions. Try avoiding pointers, and prefer references.