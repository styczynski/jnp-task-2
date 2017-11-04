# JNP Task 2 (University of Warsaw)

Contributors: 

* @styczynski
* @wikzan

## Building

To compile run `make all`

To run example type `make run-<example_name>`
e.g. 

`make run-basic-usage` 

or `make run-example1`

## The task "Dictionaries"

The standard C ++ library provides very useful containers (eg.
unordered_map) that are not availabe in the C language.

We often need to combine the C++ code with the inherited code written in pure C. The purpose of this task
is to write two C++ modules that support key-value dictionaries
operating on strings so that they can be used inside C code.

### Modules

Each module consists of a header file (with extension h) and a file
with implementation (with cc extension).

The dict (dict.h and dict.cc files) should provide the following functions:

| Function           | Return type          | Parameters                                                                        | Description                                                                                                                                                                                                                                                                                                                                                  |
|--------------------|----------------------|-----------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| <b>dict_new</b>    | <i>unsigned long</i> |                                                                                   | Creates a new, empty dictionary and returns its id.                                                                                                                                                                                                                                                                                                          |
| <b>dict_delete</b> |                      | <i>unsigned long</i> id                                                           | If there exists a dictionary with the given id, removes it<br>and in the other case does nothing.                                                                                                                                                                                                                                                            |
| <b>dict_size</b>   | <i>size_t</i>        | <i>unsigned long</i> id                                                           | If there exists a dictionary with the given id, returns the number of its elements<br>in other case returns 0.                                                                                                                                                                                                                                               |
| <b>dict_insert</b> |                      | <i>unsigned long</i> id<br> <i>const char *</i> key<br> <i>const char *</i> value | If there exists a dictionary with the given id and value and key are not NULL c-style strings<br>then inserts value under key in the dictionary with the specified id<br>in other cases do nothing.<br>This function is guaranteed to have the same time complexity as<br>operations on STL unordered map plus<br>time to find the dictionary with given id. |
| <b>dict_remove</b> |                      | <i>unsigned long</i> id<br> <i>const char *</i> key                               | If there exists a dictionary with an id and contains the given key, removes that key and value associated with it<br>in other case does nothing.                                                                                                                                                                                                             |
| <b>dict_find</b>   | <i>const char *</i>  | <i>unsigned long</i> id<br> <i>const char *</i> key                               | If a dictionary with the given id exists and contains a value under the key, it returns a pointer to this value and<br>if there's no such key tries to find it in the global dictionary.<br>If there is no value in the global dictionary under the specifed key<br>the function call returns NULL.                                                          |
| <b>dict_clear</b>  |                      | <i>unsigned long</i> id                                                           | If a dictionary with the given id exists, it removes all its elements, in other case nothing happens.                                                                                                                                                                                                                                                        |
| <b>dict_copy</b>   |                      | <i>unsigned long</i> src_id<br> <i>unsigned long</i> dst_id                       | If dictionaries with src_id and dst_id exist, it copies the content of the dictionary src_id to the dictionary with the identifier dst_id.<br>In other cases this function does nothing.                                                                                                                                                                     |

The dictglobal (dictglobal.h and dictglobal.cc files) should provide the following functions: 

| Function           | Return type          | Parameters                                                                        | Description                                                                                                                                                                                                                                                                                                                                                  |
|--------------------|----------------------|-----------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| <b>dict_global</b> | <i>unsigned long</i> |                                                                                   | Returns a global dictionary identifier.<br>Global dictionary cannot be deleted and never contains more than MAX_GLOBAL_DICT_SIZE elements.                                                                                                                                                                                                                   |

And also a constant:

```

MAX_GLOBAL_DICT_SIZE

    The constant is equal to 42 and defines the maximum size of the global dictionary.
    The global dictionary never contains more than MAX_GLOBAL_DICT_SIZE elements.
    Insertion on filled global dict has got no effects.

```

The dict and dictglobal modules should verify the correctness of the parameters
passed to the given functions with assertions and 
output the diagnostic information to the standard error stream.
Compiling with the -DNDEBUG parameter should turn off any diagnostic output.

Also prepare the cdict and cdictglobal header files that they contain
dict and dictglobal module interfaces in the jnp1 namespace
(For C++ usage).

### Technical details

Expected solution should use containers and methods provided
by the standard C++ library. Do not define your own structures or
classes. Use a standard type to implement dictionaries
std::unordered_map <std::string, std::string>.

You must hide all global variables and functions from the outside world!
Do not overuse conditional builds!

### Formal requirements

The solution shall be placed
in the SVN repository in the directory

`grupaN/zadanie2ab123456+cd123456`

or

`grupaN/zadanie2ab123456+cd123456+ef123456`

where `N` is the group number, and `ab123456, cd123456, ef123456` are identifiers
of the members of the team submitting this solution.
Catalog with solution should contain no additional files to the source code,
but may contain a subdirectory `"private"` where you can place other files, such as your tests.
Files placed in subdirectories are not evaluated.
Do not place in the repository large, binary, temporary or any other way unnecessary files.

**English translation done by @styczynski (MIT license)**
