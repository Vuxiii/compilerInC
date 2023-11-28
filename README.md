# compilerInC
This is my attempt at developing a compiler in high level assembly (AKA C)

# Syntax
This section aims to describe the syntax of the language including its keywords and operators.

It will be followed with an examples section

## Keywords

## Language Definition

## Examples

```
fn main() {
    let counter: int;
    
    
    
    if counter == 3 {
        ...
    } else {
        ...
    }
    
    // A new scope with shadowing
    {
        let counter: string;
    }
    
    // Call to another function
    let return_falue: int = another_function(1);
}

fn add_one(value: int) -> int {
    return value + 1;
}

fn add_numbers( left: int, right: int ) -> int {
    return left + right;
}


fn let_declarations() {
    // Demonstrate different let declarations
    
    let name: string;
    
    let my_name: string = "Adam";
    
    // Allocate 10 ints on the stack
    let int_array: [10] int;
    
    // Declare a user type ( struct )
    let Person :: struct {
        name: string,
        age: int
    };
    
    // Pointer
    let my_pointer: 
}

```