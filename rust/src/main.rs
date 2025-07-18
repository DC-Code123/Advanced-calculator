use std::io;
use std::cmp::Ordering;
use rand::Rng;
fn main() {
    println!("Welcome to my guessing game!");
    println!("Please enter the maximum number for the guessing range:1-100");
    loop {
        let mut rng = rand::rng();
        let secret_number = rng.random_range(1..=100);

        println!("A secret number has been generated between 1 and 100.");
        println!("Do you want a hint? (yes=y/no=n)");

        let mut hint_choice = String::new();
        io::stdin().read_line(&mut hint_choice).expect("Failed to read line");
        let hint_choice = hint_choice.trim().to_lowercase();

        if hint_choice == "yes" || hint_choice == "y" {
            println!("Hint: The secret number is between 1 and 100.");
        } else {
            println!("Enjoy the game without hints!");
            continue;
        }

        println!("Please enter your guess: ");

        let mut guess = String::new();
        io::stdin().read_line(&mut guess).expect("Failed to read line");

        let guess: i32 = guess.trim().parse().expect("Please type a valid integer!");
        println!("You inputted: {}", guess);

        if guess == secret_number {
            println!("Congratulations! You guessed the number!");
        } else {
            println!("Sorry, the secret number was: {}", secret_number);
        }

        match guess.cmp(&secret_number) {
            Ordering::Less => println!("Too small!, the number was: {}", secret_number),
            Ordering::Greater => println!("Too big!, the number was: {}", secret_number),
            Ordering::Equal => {
                println!("You guessed it!");
                break;
            }
        }
    }
}
