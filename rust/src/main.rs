use std::io;
use std::cmp::Ordering;
use colored::Colorize;
use crate::utils::gen_rand;
use crate::utils::hard_hint_chooser;
mod utils;

fn main() {
    println!("Welcome to my guessing game!");
    println!("Please enter the maximum number for the guessing range:1-100");
    loop {
        let secret_number = gen_rand();

        println!("A secret number has been generated between 1 and 100.");

        hard_hint_chooser(secret_number);

        println!("Please enter your guess: ");

        let mut guess = String::new();
        io::stdin().read_line(&mut guess).expect("Failed to read line");

        if guess.trim().is_empty() {
            println!("No input provided, please enter a number.");
            continue;
        }

        let guess: f64 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => {
                println!("Invalid input, please enter a number.");
                continue;
            }
        };

        if guess < 1.0 || guess > 100.0 {
            println!("Please enter a number between 1 and 100.");
            continue;
        }

        println!("You inputted: {}", guess);

        if (guess - secret_number).abs() < f64::EPSILON {
            println!("Congratulations! You guessed the number!");
        } else {
            println!("Sorry, the secret number was: {}", secret_number);
        }

        match guess.partial_cmp(&secret_number).unwrap() {
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
}
