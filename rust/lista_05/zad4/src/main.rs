fn add_zeros(c: char, n: usize) -> String {
    return c.to_string() + &"0".repeat(n);
}

fn expanded_form(n: u64) -> String {
    let len = n.to_string().len() - 1;
    n.to_string()
        .chars()
        .enumerate()
        .fold(String::new(), |acc, (i, c)| match (c, i) {
            ('0', _) => acc,
            (_, 0) => add_zeros(c, len - i),
            (_, _) => acc + " + " + &add_zeros(c, len - i),
        })
}

#[cfg(test)]
mod tests {
    use super::expanded_form;

    #[test]
    fn test_one_digit() {
        assert_eq!(expanded_form(3), "3")
    }

    #[test]
    fn test_multiple_positive_digits() {
        assert_eq!(expanded_form(123), "100 + 20 + 3");
        assert_eq!(expanded_form(99), "90 + 9");
    }

    #[test]
    fn test_number_with_zeros() {
        assert_eq!(expanded_form(70304), "70000 + 300 + 4");
    }

    #[test]
    fn test_number_with_one_positive_digit() {
        assert_eq!(expanded_form(5000000), "5000000")
    }
}
