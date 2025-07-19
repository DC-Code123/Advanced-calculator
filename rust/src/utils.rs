use std::arch::x86_64;

use rand::Rng;
use rand::prelude::IndexedRandom;

pub fn gen_rand() -> f64 {
    let mut rng = rand::rng();
    return rng.random_range(1.0..=100.0);
}

pub fn hard_hint_chooser(secret_number: f64) {
    // Each tuple: (hint string, closure to compute value)
    let expressions: Vec<(&str, Box<dyn Fn(f64) -> f64>)> = vec![
        (
            "(x^2 - 3)×4 + (x^3÷2 - 7)",
            Box::new(|x| (x.powi(2) - 3.0) * 4.0 + (x.powi(3) / 2.0 - 7.0)),
        ),
        (
            "(2x^3 + 5)×3 - (x^2÷4 + 8)",
            Box::new(|x| (2.0 * x.powi(3) + 5.0) * 3.0 - (x.powi(2) / 4.0 + 8.0)),
        ),
        (
            "(x^4 - 2x)×2 + (3x÷5 - 12)",
            Box::new(|x| (x.powi(4) - 2.0 * x) * 2.0 + ((3.0 * x) / 5.0 - 12.0)),
        ),
        (
            "(5x^2 + 1)×6 - (x^3÷3 + 9)",
            Box::new(|x| (5.0 * x.powi(2) + 1.0) * 6.0 - (x.powi(3) / 3.0 + 9.0)),
        ),
        (
            "(x^3 - 4x^2)×5 + (2x÷7 - 11)",
            Box::new(|x| (x.powi(3) - 4.0 * x.powi(2)) * 5.0 + ((2.0 * x) / 7.0 - 11.0)),
        ),
        (
            "(3x^2 + 2x)×2 - (x^4÷6 + 10)",
            Box::new(|x| (3.0 * x.powi(2) + 2.0 * x) * 2.0 - (x.powi(4) / 6.0 + 10.0)),
        ),
        (
            "(x^5 - x^2)×4 + (5x÷3 - 13)",
            Box::new(|x| (x.powi(5) - x.powi(2)) * 4.0 + ((5.0 * x) / 3.0 - 13.0)),
        ),
        (
            "(2x^3 + 7)×3 - (x^2÷2 + 6)",
            Box::new(|x| (2.0 * x.powi(3) + 7.0) * 3.0 - (x.powi(2) / 2.0 + 6.0)),
        ),
        (
            "(x^4 - 5x)×2 + (4x÷5 - 8)",
            Box::new(|x| (x.powi(4) - 5.0 * x) * 2.0 + ((4.0 * x) / 5.0 - 8.0)),
        ),
        (
            "(4x^2 + 3x)×5 - (x^3÷4 + 7)",
            Box::new(|x| (4.0 * x.powi(2) + 3.0 * x) * 5.0 - (x.powi(3) / 4.0 + 7.0)),
        ),
        (
            "(x^3 - 2x^2)×6 + (3x÷2 - 9)",
            Box::new(|x| (x.powi(3) - 2.0 * x.powi(2)) * 6.0 + ((3.0 * x) / 2.0 - 9.0)),
        ),
        (
            "(2x^4 + x)×2 - (x^2÷3 + 12)",
            Box::new(|x| (2.0 * x.powi(4) + x) * 2.0 - (x.powi(2) / 3.0 + 12.0)),
        ),
        (
            "(x^2 + 6x)×3 + (2x^3÷5 - 14)",
            Box::new(|x| (x.powi(2) + 6.0 * x) * 3.0 + ((2.0 * x.powi(3)) / 5.0 - 14.0)),
        ),
        (
            "(5x^3 - x)×4 - (x^2÷6 + 11)",
            Box::new(|x| (5.0 * x.powi(3) - x) * 4.0 - (x.powi(2) / 6.0 + 11.0)),
        ),
        (
            "(x^4 + 2x^2)×2 + (3x÷7 - 10)",
            Box::new(|x| (x.powi(4) + 2.0 * x.powi(2)) * 2.0 + ((3.0 * x) / 7.0 - 10.0)),
        ),
        (
            "(3x^2 - 4x)×5 - (x^3÷2 + 13)",
            Box::new(|x| (3.0 * x.powi(2) - 4.0 * x) * 5.0 - (x.powi(3) / 2.0 + 13.0)),
        ),
        (
            "(x^5 + x^2)×3 + (4x÷4 - 15)",
            Box::new(|x| (x.powi(5) + x.powi(2)) * 3.0 + ((4.0 * x) / 4.0 - 15.0)),
        ),
        (
            "(2x^3 - 3x)×2 - (x^2÷5 + 8)",
            Box::new(|x| (2.0 * x.powi(3) - 3.0 * x) * 2.0 - (x.powi(2) / 5.0 + 8.0)),
        ),
        (
            "(x^4 + 5x)×4 + (2x^3÷3 - 7)",
            Box::new(|x| (x.powi(4) + 5.0 * x) * 4.0 + ((2.0 * x.powi(3)) / 3.0 - 7.0)),
        ),
        (
            "(4x^2 - x)×6 - (x^4÷2 + 9)",
            Box::new(|x| (4.0 * x.powi(2) - x) * 6.0 - (x.powi(4) / 2.0 + 9.0)),
        ),
        (
            "3(x^2 - 4) + 2x - (x^3÷5)",
            Box::new(|x| 3.0 * (x.powi(2) - 4.0) + 2.0 * x - x.powi(3) / 5.0),
        ),
        (
            "(2x^3 + 7x - 1)×2 - (x^2 - 3)",
            Box::new(|x| (2.0 * x.powi(3) + 7.0 * x - 1.0) * 2.0 - (x.powi(2) - 3.0)),
        ),
        (
            "(4x^4 - 2x^2)÷3 + 5x - 8",
            Box::new(|x| (4.0 * x.powi(4) - 2.0 * x.powi(2)) / 3.0 + 5.0 * x - 8.0),
        ),
        ("(x^2 + 2x)(x - 1) + 6", Box::new(|x| (x.powi(2) + 2.0 * x) * (x - 1.0) + 6.0)),
        (
            "7x^3 - 2(x^2 - 5x) + (x÷2)",
            Box::new(|x| 7.0 * x.powi(3) - 2.0 * (x.powi(2) - 5.0 * x) + x / 2.0),
        ),
        (
            "(x^4 - 3x^2 + 2)÷2 + 4x",
            Box::new(|x| (x.powi(4) - 3.0 * x.powi(2) + 2.0) / 2.0 + 4.0 * x),
        ),
        ("5(x^2 - x) - (2x^3 + 3)", Box::new(|x| 5.0 * (x.powi(2) - x) - (2.0 * x.powi(3) + 3.0))),
        ("(x^3 + 4x^2)(x - 2) + 9", Box::new(|x| (x.powi(3) + 4.0 * x.powi(2)) * (x - 2.0) + 9.0)),
        (
            "(3x^2 - 2x + 1)÷(x + 1) - 7",
            Box::new(|x| (3.0 * x.powi(2) - 2.0 * x + 1.0) / (x + 1.0) - 7.0),
        ),
        (
            "(2x^4 - x^2) + (3x - 5)^2",
            Box::new(|x| 2.0 * x.powi(4) - x.powi(2) + (3.0 * x - 5.0).powi(2)),
        ),
        (
            "6x^2 - 4x + (x^3 - 2x^2)",
            Box::new(|x| 6.0 * x.powi(2) - 4.0 * x + (x.powi(3) - 2.0 * x.powi(2))),
        ),
        (
            "(x^2 + 5x + 6)÷(x + 2) + 3x",
            Box::new(|x| (x.powi(2) + 5.0 * x + 6.0) / (x + 2.0) + 3.0 * x),
        ),
        (
            "2(x^3 - x^2) - (x^2 + 4x) + 10",
            Box::new(|x| 2.0 * (x.powi(3) - x.powi(2)) - (x.powi(2) + 4.0 * x) + 10.0),
        ),
        ("(x^4 - 2x^2 + x)×3 - 8", Box::new(|x| (x.powi(4) - 2.0 * x.powi(2) + x) * 3.0 - 8.0)),
        ("(x^2 - 3x + 2)^2 + x", Box::new(|x| (x.powi(2) - 3.0 * x + 2.0).powi(2) + x)),
        (
            "4x^3 - (x^2 + 2x - 1) + (x^4÷2)",
            Box::new(|x| 4.0 * x.powi(3) - (x.powi(2) + 2.0 * x - 1.0) + x.powi(4) / 2.0),
        ),
        ("(2x^2 - x + 5)(x - 3)", Box::new(|x| (2.0 * x.powi(2) - x + 5.0) * (x - 3.0))),
        ("(x^3 + 2x^2 - x)÷2 + 7", Box::new(|x| (x.powi(3) + 2.0 * x.powi(2) - x) / 2.0 + 7.0)),
        (
            "(x^2 - 4x + 4) + (3x^3 - x)",
            Box::new(|x| x.powi(2) - 4.0 * x + 4.0 + (3.0 * x.powi(3) - x)),
        ),
        (
            "(x^4 - x^2) - 2(x^3 + x) + 6",
            Box::new(|x| x.powi(4) - x.powi(2) - 2.0 * (x.powi(3) + x) + 6.0),
        ),
        (
            "2(x^3 - 2x^2 + 5) + 3x - 7",
            Box::new(|x| 2.0 * (x.powi(3) - 2.0 * x.powi(2) + 5.0) + 3.0 * x - 7.0),
        ),
        (
            "(x^2 + 4x + 4) - (2x^3 - x)",
            Box::new(|x| x.powi(2) + 4.0 * x + 4.0 - (2.0 * x.powi(3) - x)),
        ),
        (
            "(5x^4 - 3x^2)÷2 + x - 9",
            Box::new(|x| (5.0 * x.powi(4) - 3.0 * x.powi(2)) / 2.0 + x - 9.0),
        ),
        ("(3x^2 - x + 1)(x - 2) + 8", Box::new(|x| (3.0 * x.powi(2) - x + 1.0) * (x - 2.0) + 8.0)),
        (
            "4x^3 - 2(x^2 + 3x) + 5",
            Box::new(|x| 4.0 * x.powi(3) - 2.0 * (x.powi(2) + 3.0 * x) + 5.0),
        ),
        (
            "(x^4 + 2x^2 - 3)÷3 + 6x",
            Box::new(|x| (x.powi(4) + 2.0 * x.powi(2) - 3.0) / 3.0 + 6.0 * x),
        ),
        ("7(x^2 - 2x) - (x^3 + 4)", Box::new(|x| 7.0 * (x.powi(2) - 2.0 * x) - (x.powi(3) + 4.0))),
        (
            "(2x^3 + 5x^2)(x + 1) - 10",
            Box::new(|x| (2.0 * x.powi(3) + 5.0 * x.powi(2)) * (x + 1.0) - 10.0),
        ),
        ("(4x^2 - x + 2)÷(x + 2) + 3", Box::new(|x| (4.0 * x.powi(2) - x + 2.0) / (x + 2.0) + 3.0)),
        (
            "(x^4 - 2x^2) + (2x - 3)^2",
            Box::new(|x| x.powi(4) - 2.0 * x.powi(2) + (2.0 * x - 3.0).powi(2)),
        ),
        (
            "5x^2 - 3x + (2x^3 - x^2)",
            Box::new(|x| 5.0 * x.powi(2) - 3.0 * x + (2.0 * x.powi(3) - x.powi(2))),
        ),
        (
            "(x^2 + 3x + 2)÷(x + 1) + 4x",
            Box::new(|x| (x.powi(2) + 3.0 * x + 2.0) / (x + 1.0) + 4.0 * x),
        ),
        (
            "3(x^3 - 2x^2) - (x^2 + 5x) + 12",
            Box::new(|x| 3.0 * (x.powi(3) - 2.0 * x.powi(2)) - (x.powi(2) + 5.0 * x) + 12.0),
        ),
        ("(x^4 - x^2 + 2x)×2 - 7", Box::new(|x| (x.powi(4) - x.powi(2) + 2.0 * x) * 2.0 - 7.0)),
        ("(x^2 - 4x + 3)^2 + 2x", Box::new(|x| (x.powi(2) - 4.0 * x + 3.0).powi(2) + 2.0 * x)),
        (
            "6x^3 - (2x^2 + x - 2) + (x^4÷3)",
            Box::new(|x| 6.0 * x.powi(3) - (2.0 * x.powi(2) + x - 2.0) + x.powi(4) / 3.0),
        ),
        ("(3x^2 - 2x + 4)(x - 1)", Box::new(|x| (3.0 * x.powi(2) - 2.0 * x + 4.0) * (x - 1.0))),
        ("(x^3 + x^2 - 2x)÷3 + 9", Box::new(|x| (x.powi(3) + x.powi(2) - 2.0 * x) / 3.0 + 9.0)),
        (
            "(x^2 - 3x + 9) + (4x^3 - 2x)",
            Box::new(|x| x.powi(2) - 3.0 * x + 9.0 + (4.0 * x.powi(3) - 2.0 * x)),
        ),
        (
            "(x^4 - 2x^2) - 3(x^3 + 2x) + 8",
            Box::new(|x| x.powi(4) - 2.0 * x.powi(2) - 3.0 * (x.powi(3) + 2.0 * x) + 8.0),
        ),
        (
            "2(x^2 + 5x - 1) + x^3 - 6",
            Box::new(|x| 2.0 * (x.powi(2) + 5.0 * x - 1.0) + x.powi(3) - 6.0),
        ),
        (
            "(x^3 - 4x^2 + 2)×4 - (x^2 - 1)",
            Box::new(|x| (x.powi(3) - 4.0 * x.powi(2) + 2.0) * 4.0 - (x.powi(2) - 1.0)),
        ),
        (
            "(3x^4 - 2x^2)÷4 + 2x - 5",
            Box::new(|x| (3.0 * x.powi(4) - 2.0 * x.powi(2)) / 4.0 + 2.0 * x - 5.0),
        ),
        ("(2x^2 - x + 3)(x + 2) + 7", Box::new(|x| (2.0 * x.powi(2) - x + 3.0) * (x + 2.0) + 7.0)),
        ("5x^3 - (x^2 + 2x) + 4", Box::new(|x| 5.0 * x.powi(3) - (x.powi(2) + 2.0 * x) + 4.0)),
        (
            "(x^4 + 3x^2 - 2)÷2 + 5x",
            Box::new(|x| (x.powi(4) + 3.0 * x.powi(2) - 2.0) / 2.0 + 5.0 * x),
        ),
        ("8(x^2 - x) - (2x^3 + 6)", Box::new(|x| 8.0 * (x.powi(2) - x) - (2.0 * x.powi(3) + 6.0))),
        (
            "(3x^3 + 2x^2)(x - 1) - 11",
            Box::new(|x| (3.0 * x.powi(3) + 2.0 * x.powi(2)) * (x - 1.0) - 11.0),
        ),
        (
            "(2x^2 - 3x + 1)÷(x + 3) + 6",
            Box::new(|x| (2.0 * x.powi(2) - 3.0 * x + 1.0) / (x + 3.0) + 6.0),
        ),
        (
            "(x^4 - 3x^2) + (x - 4)^2",
            Box::new(|x: f64| x.powi(4) - 3.0 * x.powi(2) + (x - 4.0).powi(2)),
        )(
            "(x² - 3)×4 + (x³÷2 - 7)",
            Box::new(|x| (x.powi(2) - 3.0) * 4.0 + (x.powi(3) / 2.0 - 7.0))
        ),
        (
            "(2x³ + 5)×3 - (x²÷4 + 8)",
            Box::new(|x| (2.0 * x.powi(3) + 5.0) * 3.0 - (x.powi(2) / 4.0 + 8.0)),
        ),
        (
            "(5x² + 1)×6 - (x³÷3 + 9)",
            Box::new(|x| (5.0 * x.powi(2) + 1.0) * 6.0 - (x.powi(3) / 3.0 + 9.0)),
        ),
        (
            "(3x² + 2x)×2 - (x⁴÷6 + 10)",
            Box::new(|x| (3.0 * x.powi(2) + 2.0 * x) * 2.0 - (x.powi(4) / 6.0 + 10.0)),
        ),
        (
            "(x³ - 2x²)×6 + (3x÷2 - 9)",
            Box::new(|x| (x.powi(3) - 2.0 * x.powi(2)) * 6.0 + ((3.0 * x) / 2.0 - 9.0)),
        ),
        (
            "3(x² - 4) + 2x - (x³÷5)",
            Box::new(|x| 3.0 * (x.powi(2) - 4.0) + 2.0 * x - x.powi(3) / 5.0),
        ),
        ("(x² + 2x)(x - 1) + 6", Box::new(|x| (x.powi(2) + 2.0 * x) * (x - 1.0) + 6.0)),
        (
            "7x³ - 2(x² - 5x) + (x÷2)",
            Box::new(|x| 7.0 * x.powi(3) - 2.0 * (x.powi(2) - 5.0 * x) + x / 2.0),
        ),

        // Simplified polynomials (new additions)
        // Basic linear
        ("2x + 5", Box::new(|x| 2.0 * x + 5.0)),
        ("3x - 7", Box::new(|x| 3.0 * x - 7.0)),

        // Quadratic
        ("x² + 3x - 2", Box::new(|x| x.powi(2) + 3.0 * x - 2.0)),
        ("2x² - 5x + 1", Box::new(|x| 2.0 * x.powi(2) - 5.0 * x + 1.0)),

        // Cubic
        ("x³ + 2x - 1", Box::new(|x| x.powi(3) + 2.0 * x - 1.0)),
        ("2x³ - x² + 5", Box::new(|x| 2.0 * x.powi(3) - x.powi(2) + 5.0)),

        // Mixed operations
        ("x(x + 1)", Box::new(|x| x * (x + 1.0))),
        ("(x + 2)(x - 3)", Box::new(|x| (x + 2.0) * (x - 3.0))),
        ("2(x + 3)", Box::new(|x| 2.0 * (x + 3.0))),
        ("3(x² - 2x)", Box::new(|x| 3.0 * (x.powi(2) - 2.0 * x))),

        // Simple fractions
        ("x/2 + 3", Box::new(|x| x / 2.0 + 3.0)),
        ("(x + 1)/3", Box::new(|x| (x + 1.0) / 3.0)),

        // Practical forms
        ("Area: x²", Box::new(|x| x.powi(2))),
        ("Volume: x³", Box::new(|x| x.powi(3))),

        // Selected original complex ones
        (
            "(2x³ + 7x - 1)×2 - (x² - 3)",
            Box::new(|x| (2.0 * x.powi(3) + 7.0 * x - 1.0) * 2.0 - (x.powi(2) - 3.0)),
        ),
        (
            "(3x² - 2x + 1)÷(x + 1) - 7",
            Box::new(|x| (3.0 * x.powi(2) - 2.0 * x + 1.0) / (x + 1.0) - 7.0),
        ),
        (
            "2(x³ - x²) - (x² + 4x) + 10",
            Box::new(|x| 2.0 * (x.powi(3) - x.powi(2)) - (x.powi(2) + 4.0 * x) + 10.0),
        ),
        ("(3x² - x + 1)(x - 2) + 8", Box::new(|x| (3.0 * x.powi(2) - x + 1.0) * (x - 2.0) + 8.0))
    ];

    let mut rng = rand::rng();
    let (hint, expr) = expressions.choose(&mut rng).unwrap();

    print!("Hint chosen: ");
    println!("HINT: {} = {:.2}", hint, expr(secret_number));
}
