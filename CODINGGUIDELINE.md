
# Structure


### Structuring folders
- to be completed later

### Naming source files
- File names should begin with Uppercase and be suggestive for the file's content
(e.g. a file containing a class implementation should have that class name);
- No spaces in the file names are allowed.
- File extensions: .h for C++ header files, .cpp for source code files
	
### Headers
- All source files should contain a standard header containing useful 
information, as follows: File Description, Author, Creation Date


# Coding


### General rules

- Indents are tabs.
- Each line should be at most 80 characters long.
- Comments should be // and should precede commented code.
- Every new declared item should begin on a new line and should be commented.
- Code blocks should be between braces that are indented the same with the 
outer block, inner code block being indented one more tab.
- Multiple line declarations should contain one item per line.
- Multiple operations / conditions should be nested in parantheses
- Multiple line statements should be divided accordingly to nesting levels,
containing the same level of nesting on every line should break after 
the logical operator and align each line with the start of the first line
```
Example:
if((value1 == value2) &&
   (value2 == value3) &&
   (value3 == value4) ||
   (value4 == value5))
{
...	...   
}
```	

### Macros

- Name should use ALL_CAPS separated by underscore:
```
#define FLAG_FOO 0x0
```
- If a macro's replacement is not just a literal, enclose it in parentheses:
```
#define FLAG_BAZ (0x1 << 3)
```

### Constants / Variables

- Name should be a suggestive noun written in lower case, begining with lower 
case.
- If the name contains more than 'oneWord', every new word should begin with an 
upper case as word separator ('no_underscores_allowed')

### Enum 

- Type name should begin with "E_" followed by 'ClassNamingRules'.
- Values should look LIKE_MACROS

### Struct

- Type name should begin with "S_" followed by 'ClassNamingRules'.
- Names of members of structs should lookLikeVariables


### Functions / Methods

- Name should start with a verb, in mixed case with the first letter lowercase 
and the following internal word’s first letter capitalized.

```
Example:
*doSomething()*
```

- Function declarations or calls that span multiple lines should align 
subsequent lines with the first parameter
```
Example:
void doSomething(int firstParameter,
				 bool secondParameter,
				 long thirdParameter)
{
...	
}
```


### Classes

- Name should be a suggestive noun written in lower case, begining with upper 
case.
- If the name contains more than 'OneWord', every new word should begin with an 
upper case as word separator ('no_underscores_allowed')
- Access modifiers must always be specified. Also the variable respectively 
the methods should be grouped accourding to access modifiers.



