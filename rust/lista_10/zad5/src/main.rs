fn print(n: i32) -> Option<String> {
    if n < 1 || n % 2 == 0 {
        return None;
    }

    Some(
        (0..n as usize)
            .map(|i| (n / 2 - i as i32).abs() as usize)
            .map(|dist| " ".repeat(dist) + &"*".repeat(n as usize - dist * 2) + "\n")
            .collect::<Vec<String>>()
            .join(""),
    )
}

#[cfg(test)]
mod tests {
    use crate::print;

    #[test]
    fn test_correct_size() {
        assert_eq!(print(1), Some("*\n".to_string()));
        assert_eq!(print(3), Some(" *\n***\n *\n".to_string()));
        assert_eq!(print(5), Some("  *\n ***\n*****\n ***\n  *\n".to_string()));
    }

    #[test]
    fn test_incorrect_size() {
        assert_eq!(print(-3), None);
        assert_eq!(print(2), None);
        assert_eq!(print(0), None);
    }
}
