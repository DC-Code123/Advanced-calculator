use std::io;

fn main() {
    println!("Welcome to DCA's first rust project!");
    println!("This is a simple guessing game.");
    println!("Please enter a number between 1 and 100:");
    let mut guess = String::new();
    io::stdin()
        .read_line(&mut guess)
        .expect("Failed to read line");

    println!("You guessed: {}", guess);
}