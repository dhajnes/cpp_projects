# c++ notes

### namespace is the set of names used in one scope (python takes care automatically)
`std::cout << "Lol.\n"` prints 'Lol.\n' into std (standard) namespace

### reference (using &)
Saves memory, e.g. for large data, it is possible to change value inside of a function that has been passed a reference (both pro and con  )
```
int a = 5;
int b = a;
b++;
```
out: 
```
a is 5
b is 6
```

Whereas if reference is used:
```
int a = 5;
int & b = a;
b++;
```

out: 
```
a is 6
b is 6
```

### C++ passes by value by default
- pass by value
```
int x = 10;
foo(x);

void foo(int a){
    a = 10;
}
```
Here, the function copies value from `x` to `a`, so `x` still has value 10 after the function executes.

- pass by reference
```
int x = 10;
foo(x);

void foo(int &a){
    a = 10;
}
```
Here, the function does not copy value, the `a` is the reference of `x`, so any change to `a` is directly applied to `x`.

- pass by pointer
```
int x = 10;
foo(&x);

void foo(int *a){
    *a = 10; //dereferenced pointer - now value, of `a`, which is the value of `x`, is changed
}
```

### using `new`

`int *x = new int(5);`
created on heap instead of stack, you need to manualy free the memory (`delete x;`), usually used with objects (`User *u = new User();`)

```
User *u = new User();
// now change some u data
(*u).name = "jano";
// or do it the c++ way:
u -> name = "jano";

// ... when youre done, delete
delete u;
```

### dynamic array for @RunTime allocation

```
#include <vector>
std::vector<int> data = {1,2,3};
//this is a dynamic array, called `vector` from the `<vector>`
data.push_back(10);
```

## Classes
Class is a user-defined data type, an object constructor - a blue print for the objects.
Concrete instances of classes are the objects.

```
class MyClass {       // The class
  public:             // Access specifier
    int myNum;        // Attribute (int variable)
    string myString;  // Attribute (string variable)
};
```

### Class Template