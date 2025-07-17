fn main() {
    let n = 9;
    println!("Hello, world!");

    /* 
    The {} are used to replace with the value of n(order-sensitive) 
    the {} only works for variables are clear on how they are represented 
    */
    
    println!("The value of n is: {}", &n);
    let n1 = n * n;
    println!("The square of n is: {}", &n1);
    let n2 = n1 * n;
    println!("The cube of n is: {}", &n2);

    /*
    for things like vectors, you can use the {:?} to print the value
    The & is used when you want to pass a reference to a value, rather than moving the value itself.
    For example, println!("{:?}", &vec) passes a reference to vec, which avoids moving ownership.
    */

    let vec = vec![n, n1, n2];
    println!("The vector is: {:?}", &vec);

    // This will split the string "hello world" by whitespace and collect the parts into a vector
    println!("Hello, world! ");
    let my_temporary_debug_variable = "hello world".split(' ').collect::<Vec<_>>();
    println!("Here is what we got are splitting using a whitespace: {:?}", my_temporary_debug_variable);
    my_temporary_debug_variable.join("-");

    /*
    This will split the string "hello world" by whitespace and collect the parts into a vector, then join them with a hyphen
    dbg! is a macro that prints the value of an expression to the console, along with the file and line number where it was called.
    It is useful for debugging purposes.
    */

    dbg!(
    "hello world".split(' ').collect::<Vec<_>>()
    ).join("-");
}
