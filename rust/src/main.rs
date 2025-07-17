use std::io;
fn main() {
    println!("Welcome to my guessing game!");
    println!("Please enter your guess: ");
    let mut guess = String::new();
    io::stdin()
        .read_line(&mut guess)
        .expect("Failed to read line");
    let guess: i32 = guess.trim().parse().expect("Please type a valid integer!");
    println!("You guessed: {}", guess);
}