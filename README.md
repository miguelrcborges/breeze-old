# breeze
An attempt to make a cross platform shell.


### Some uncommon code convections

- windows.h shouldn't be included. Required functions for certain file should be declared
at the top of the file (after includes).
    - Consquently, window's api types are replaced by standard C ones.
    - For fixed sized variables, should be used stdint.h
