pub fn string_to_number(s: &str) -> i32 {
    return s.parse::<i32>().unwrap();
}

#[cfg(test)]
mod tests {
    use crate::string_to_number;

    #[test]
    fn test_zero() {
        assert_eq!(string_to_number("0"), 0);
    }

    #[test]
    fn test_positive_number() {
        assert_eq!(string_to_number("24"), 24);
    }
    #[test]
    fn test_negative_number() {
        assert_eq!(string_to_number("-777"), -777);
    }

    #[test]
    fn test_int_max() {
        assert_eq!(string_to_number("2147483647"), i32::MAX);
    }

    #[test]
    fn test_int_min() {
        assert_eq!(string_to_number("-2147483648"), i32::MIN);
    }

    #[test]
    #[should_panic]
    fn test_nan() {
        string_to_number("abc");
    }
}
