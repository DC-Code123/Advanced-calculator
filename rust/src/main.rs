use std::io;
use std::cmp::Ordering;
use rand::Rng;
use colored::Colorize;

fn main() {
    println!("Welcome to my guessing game!");
    println!("Please enter the maximum number for the guessing range:1-100");
    loop {
        let secret_number = gen_rand();

        println!("A secret number has been generated between 1 and 100.");

        offer_hint(secret_number);

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

fn gen_rand() -> f64 {
    let mut rng = rand::rng();
    return rng.random_range(1.0..=100.0);
}

fn offer_hint(secret_number: f64) {
    println!("Do you want a hint? (yes=y/no=n)");

    let mut hint_choice = String::new();
    io::stdin().read_line(&mut hint_choice).expect("Failed to read line");
    let hint_choice = hint_choice.trim().to_lowercase();

    if hint_choice == "yes" || hint_choice == "y" {
        println!("input a random number between 1 and 7:");
        let mut hint_input = String::new();
        io::stdin().read_line(&mut hint_input).expect("Failed to read line");
        let hint_input: i32 = match hint_input.trim().parse() {
            Ok(num) => num,
            Err(_) => {
                println!("Invalid input, please enter a number.");
                return;
            }
        };
        if hint_input < 1 || hint_input > 7 {
            println!("Please enter a number between 1 and 7.");
            return;
        }
        match hint_input {
            1 =>
                println!(
                    "HINT:((x-2)*5)+((x/2)-23)= {:.2}",
                    (secret_number - 2.0) * 5.0 + (secret_number / 2.0 - 23.0)
                ),
            2 =>
                println!(
                    "HINT:x + (3×4) - (10÷2) + (7-1) = {:.2}",
                    secret_number + 3.0 * 4.0 - 10.0 / 2.0 + (7.0 - 1.0)
                ),
            3 =>
                println!(
                    "HINT:(x + (5×3)) ÷ (7-5) + (10-2×4) = {:.2}",
                    (secret_number + 5.0 * 3.0) / (7.0 - 5.0) + (10.0 - 2.0 * 4.0)
                ),
            4 =>
                println!(
                    "HINT:x + (100÷10÷2) - (3+2) + (4×5) - (21÷3) = {:.2}",
                    secret_number + 100.0 / 10.0 / 2.0 - (3.0 + 2.0) + 4.0 * 5.0 - 21.0 / 3.0
                ),
            5 =>
                println!(
                    "HINT:((x*3) + (24/(2+2))) - (5*(6-4)) + (10-(15/3)) = {:.2}",
                    secret_number * 3.0 +
                        24.0 / (2.0 + 2.0) -
                        5.0 * (6.0 - 4.0) +
                        (10.0 - 15.0 / 3.0)
                ),
            6 =>
                println!(
                    "HINT:(x + (5*(4-1))) * (10/(7-2)) - (3+(8/4)) = {:.2}",
                    (secret_number + 5.0 * (4.0 - 1.0)) * (10.0 / (7.0 - 2.0)) - (3.0 + 8.0 / 4.0)
                ),
            7 =>
                println!(
                    "HINT: x + ((15×2)÷5) - (9÷(3+0)) + (4×(5-2)) = {:.2}",
                    secret_number + (15.0 * 2.0) / 5.0 - 9.0 / (3.0 + 0.0) + 4.0 * (5.0 - 2.0)
                ),
            _ => println!("Invalid hint choice."),
        }
    } else {
        println!("Enjoy the game without hints!");
    }
}
