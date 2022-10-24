fn str_to_int(string: &str) -> i32 {
    string.parse::<i32>().unwrap()
}

fn worth_sum(count: &str, worths: &[i32]) -> i32 {
    count
        .split_whitespace()
        .enumerate()
        .map(|(i, s)| str_to_int(s) * worths[i])
        .sum()
}

fn good_vs_evil(good: &str, evil: &str) -> String {
    let good_worths = [1, 2, 3, 3, 4, 10];
    let evil_worths = [1, 2, 2, 2, 3, 5, 10];

    let good_sum = worth_sum(good, &good_worths);
    let evil_sum = worth_sum(evil, &evil_worths);

    if good_sum > evil_sum {
        "Battle Result: Good triumphs over Evil".to_string()
    } else if good_sum < evil_sum {
        "Battle Result: Evil eradicates all trace of Good".to_string()
    } else {
        "Battle Result: No victor on this battle field".to_string()
    }
}

#[cfg(test)]
mod tests {
    use crate::good_vs_evil;

    #[test]
    fn test_zeros() {
        assert_eq!(good_vs_evil("0 0 0 0 0 0", "0 0 0 0 0 0 0"), "Battle Result: No victor on this battle field");
    }

    #[test]
    fn test_good_win() {
        assert_eq!(good_vs_evil("0 0 0 0 0 10", "0 0 0 0 0 0 0"), "Battle Result: Good triumphs over Evil");
    }
    #[test]
    fn test_evil_win() {
        assert_eq!(good_vs_evil("0 0 0 0 0 0", "0 0 0 0 0 0 10"), "Battle Result: Evil eradicates all trace of Good");
    }
    #[test]
    fn test_draw() {
        assert_eq!(good_vs_evil("0 0 0 0 0 10", "0 0 0 0 0 0 10"), "Battle Result: No victor on this battle field");
    }

    #[test]
    fn test_every_race() {
        assert_eq!(good_vs_evil("1 1 1 1 1 1", "1 1 1 1 1 1 1"), "Battle Result: Evil eradicates all trace of Good");
    }
}
