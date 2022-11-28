fn find_digit(num: i32, nth: i32) -> i32 {
    if nth < 1 {
        return -1;
    }

    num.abs()
        .to_string()
        .chars()
        .rev()
        .nth((nth - 1) as usize)
        .unwrap_or('0')
        .to_digit(10)
        .unwrap() as i32
}

#[cfg(test)]
mod tests {
    use crate::find_digit;

    #[test]
    fn test_negative_nth() {
        assert_eq!(find_digit(123, -3), -1)
    }

    #[test]
    fn test_test_nth_larger_than_number_length() {
        assert_eq!(find_digit(123, 5), 0)
    }

    #[test]
    fn test_nth_poiting_to_minus_sign() {
        assert_eq!(find_digit(-4912, 5), 0)
    }

    #[test]
    fn test_positive_number() {
        assert_eq!(find_digit(4321, 3), 3)
    }

    #[test]
    fn test_negative_number() {
        assert_eq!(find_digit(-123, 2), 2)
    }
}

#[test]
fn example_test() {
    assert_eq!(find_digit(5673, 4), 5);
    assert_eq!(find_digit(129, 2), 2);
    assert_eq!(find_digit(-2825, 3), 8);
    assert_eq!(find_digit(-456, 4), 0);
    assert_eq!(find_digit(0, 20), 0);
    assert_eq!(find_digit(65, 0), -1);
    assert_eq!(find_digit(24, -8), -1);
}
