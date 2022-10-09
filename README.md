# hsC

Some convenient functions, that i used in Haskell and wanted to have in C.

Includes

```map``` - Map a function over a list

```filter``` - Filter a list with a bool function

```drop & dropWhile``` - Drop elements either by count or by bool function

```take & takeWhile``` - Take elements either by count or by bool function

```find``` - Find an element in an list. Returs a maybe struct

```chain``` - Chain functions with the same input and output over a list with the same type

```elem``` - Check if value is in a list

```isInfixOf``` - Check if a string is an infix of an string

```splitAt``` - Splits a string with a given splitter

everything is written in generic macros!
