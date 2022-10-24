fn dont_give_me_five(start: isize, end: isize) -> isize {
    (start..=end)
        .map(|n| n.to_string())
        .filter(|s| !s.contains("5"))
        .count()
        .try_into()
        .unwrap()
}

#[cfg(test)]
mod tests {
    use crate::dont_give_me_five;

    #[test]
    fn test_zero() {
        assert_eq!(dont_give_me_five(1, 0), 0);
    }

    #[test]
    fn test_one_number() {
        assert_eq!(dont_give_me_five(0, 0), 1);
    }

    #[test]
    fn test_positive_numbers_without_five() {
        assert_eq!(dont_give_me_five(1, 4), 4);
    }

    #[test]
    fn test_positive_numbers_with_five() {
        assert_eq!(dont_give_me_five(1, 55), 44);
    }

    #[test]
    fn test_negative_numbers_without_five() {
        assert_eq!(dont_give_me_five(-4, -1), 4);
    }

    #[test]
    fn test_negative_numbers_with_five() {
        assert_eq!(dont_give_me_five(-55, -1), 44)
    }
    
    #[test]
    fn test_negative_and_positive_numbers() {
        assert_eq!(dont_give_me_five(-55, 55), 89)
    }
}