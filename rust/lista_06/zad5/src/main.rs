fn descending_order(x: u64) -> u64 {
    let mut chars = x.to_string().chars().collect::<Vec<char>>();
    chars.sort_by(|a, b| b.cmp(a));
    String::from_iter(chars).parse::<u64>().unwrap()
}

#[cfg(test)]
mod tests {
    use crate::descending_order;

    #[test]
    fn test_zero() {
        assert_eq!(descending_order(0), 0);
    }

    #[test]
    fn test_one_digit() {
        assert_eq!(descending_order(3), 3);
    }

    #[test]
    fn test_all_different_digits() {
        assert_eq!(descending_order(52761), 76521);
    }

    #[test]
    fn test_multiple_repeating_digits() {
        assert_eq!(descending_order(5127763461), 7766543211);
    }

    #[test]
    fn test_one_repeating_digit() {
        assert_eq!(descending_order(44444), 44444);
    }
}
