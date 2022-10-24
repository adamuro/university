fn solution(num: i32) -> i32 {
    if num < 3 { return 0 }
    (3..num).filter(|n| n % 3 == 0 || n % 5 == 0).sum()
}

#[cfg(test)]
mod tests {
    use crate::solution;

    #[test]
    fn test_negative_number() {
        assert_eq!(solution(-112), 0);
    }

    #[test]
    fn test_zero() {
        assert_eq!(solution(0), 0);
    }

    #[test]
    fn test_positive_number_below_three() {
        assert_eq!(solution(1), 0);
        assert_eq!(solution(2), 0);
    }

    #[test]
    fn test_positive_number() {
        assert_eq!(solution(10), 23);
    }

    #[test]
    fn test_large_positive_number() {
        assert_eq!(solution(10500), 25719750)
    }
}