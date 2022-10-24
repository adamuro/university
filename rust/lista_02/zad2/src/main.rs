fn summy(strng: &str) -> i32 {
    strng
        .split_whitespace()
        .map(|n| n.parse::<i32>().unwrap())
        .into_iter()
        .sum()
}

#[cfg(test)]
mod tests {
    use super::summy;
    
    #[test]
    fn test_zero() {
        assert_eq!(summy("0"), 0);
        assert_eq!(summy("-0"), 0);
        assert_eq!(summy("0 0 0"), 0);
    }

    #[test]
    fn test_one_number() {
        assert_eq!(summy("23"), 23);
        assert_eq!(summy("-983484"), -983484);
    }

    #[test]
    fn test_multiple_positive_numbers() {
        assert_eq!(summy("1 2 3"), 6);
        assert_eq!(summy("2 5 2 1 11"), 21);
    }

    #[test]
    fn test_multiple_negative_numbers() {
        assert_eq!(summy("-2 -4 -6"), -12);
        assert_eq!(summy("-11 -3 -3 -1 -11"), -29);
    }

    #[test]
    fn test_multiple_negative_and_positive_numbers() {
        assert_eq!(summy("3 -5 0 2"), 0);
        assert_eq!(summy("-1 -7 4 1 5"), 2);
    }

    #[test]
    #[should_panic]
    fn test_nan() {
        summy("abc");
    }
}