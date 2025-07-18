use std::io;
use std::cmp::Ordering;
use rand::Rng;
use colored::Colorize;
fn main() {
    println!("Welcome to my guessing game!");
    println!("Please enter the maximum number for the guessing range:1-100");
    loop {
        let secret_number = secret_number();

        println!("A secret number has been generated between 1 and 100.");
        println!("Do you want a hint? (yes=y/no=n)");

        let mut hint_choice = String::new();
        io::stdin().read_line(&mut hint_choice).expect("Failed to read line");
        let hint_choice = hint_choice.trim().to_lowercase();

        if hint_choice == "yes" || hint_choice == "y" {
            println!("Hint: The secret number 5 digits positive from {}.", &secret_number - 5);
        } else {
            println!("Enjoy the game without hints!");
        }

        println!("Please enter your guess: ");

        let mut guess = String::new(); //(1)
        io::stdin().read_line(&mut guess).expect("Failed to read line");

        if guess.trim().is_empty() {
            println!("No input provided, please enter a number.");
            continue;
        }

        let guess: i32 = match guess.trim().parse() {
            //(2)&(1) are instances of shadowing where the variable `guess` is redefined
            // to hold the parsed integer value. and this allow us to use the same variable name with different types
            Ok(num) => num,
            Err(_) => {
                println!("Invalid input, please enter a number.");
                continue;
            }
        };

        if guess < 1 || guess > 100 {
            println!("Please enter a number between 1 and 100.");
            continue;
        }

        println!("You inputted: {}", guess);

        if guess == secret_number {
            println!("Congratulations! You guessed the number!");
        } else {
            println!("Sorry, the secret number was: {}", secret_number);
        }

        match guess.cmp(&secret_number) {
            Ordering::Less =>
                println!(
                    "{} {}",
                    "Too small!".red(),
                    format!("The number was: {}", secret_number).yellow()
                ),
            Ordering::Greater =>
                println!(
                    "{} {}",
                    "Too big!".red().bold(),
                    format!("The number was: {}", secret_number).yellow()
                ),
            Ordering::Equal => {
                println!("{}", "You guessed it!".green().bold());
                break;
            }
        }

        println!("Do you want to play again? (yes=y/no=n)");
        let mut play_again = String::new();
        io::stdin().read_line(&mut play_again).expect("Failed to read line");
        if play_again.trim().to_lowercase() != "yes" && play_again.trim().to_lowercase() != "y" {
            println!("Thank you for playing!");
            break;
        }
    }

    /*
    Data types
        Data types in Rust are categorized into two main types: scalar and compound.
        Scalar types represent a single value, while compound types can group multiple values together.
        Scalar types include integers, floating-point numbers, booleans, and characters.
        Compound types include tuples and arrays, which can hold multiple values of different or the same types.
    */

    /*
    //tuples
    let tuple = (42, 3.14, 'x'); // A tuple is a an array that can hold multiple values of different types
    //To access tuple elements, you can use pattern matching or indexing
    let (a, b, c) = tuple; // Pattern matching to extract values from the tuple
    println!("Tuple values: {}, {}, {}", a, b, c);
    let first_element = tuple.0; // Accessing the first element using indexing
    println!("First element of the tuple: {}", first_element);
    println!("Second element of the tuple: {}", tuple.1); // Accessing the second element using indexing
    println!("The element in the tuple has {:?}", tuple);

    //arrays
    let array = [1, 2, 3, 4, 5];

    // An array is a fixed-size collection of elements of the same type
    println!("Array values: {:?}", array); // Using {:?} to print the array
    println!("First element of the array: {}", array[0]); // Accessing the first
    println!("Second element of the array: {}", array[1]); // Accessing the second element
    println!("Third element of the array: {}", array[2]); // Accessing the third
    println!("Fourth element of the array: {}", array[3]); // Accessing the fourth element
    println!("Fifth element of the array: {}", array[4]); // Accessing the fifth element

    // Note: Arrays in Rust are immutable by default, meaning you cannot change their elements after creation.
    let mut array1 = [0; 5]; // An array with 5 elements, all initialized to 0
    array1[2] = 10;*/
}

/*
    By the way we know that variable are immutable(unable to be change) but they can sorta be changed 
    still through re-assignment and other way but consts are constant(can't be changed) at all
*/

fn secret_number() -> i32 {
    let mut rng = rand::rng();
    let num = rng.random_range(1..=100);
    num
}
