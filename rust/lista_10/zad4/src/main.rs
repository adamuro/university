fn encode(msg: String, n: i32) -> Vec<i32> {
    let key = n
        .to_string()
        .chars()
        .map(|c| c.to_digit(10).unwrap())
        .collect::<Vec<u32>>();

    msg.chars()
        .enumerate()
        .map(|(i, c)| (c as u32 + key[i % key.len()] - 96) as i32)
        .collect::<Vec<i32>>()
}

#[cfg(test)]
mod tests {
    use super::encode;

    #[test]
    fn test_empty() {
        assert_eq!(encode("".to_string(), 123), vec![]);
    }

    #[test]
    fn test_one_letter_msg_and_one_digit_key() {
        assert_eq!(encode("a".to_string(), 5), vec![6]);
        assert_eq!(encode("c".to_string(), 3), vec![6]);
        assert_eq!(encode("f".to_string(), 9), vec![15]);
    }

    #[test]
    fn test_one_letter_msg_and_multiple_digits_key() {
        assert_eq!(encode("a".to_string(), 5463), vec![6]);
        assert_eq!(encode("c".to_string(), 312165), vec![6]);
        assert_eq!(encode("f".to_string(), 99942), vec![15]);
    }

    #[test]
    fn test_multiple_letters_msg_and_one_digit_key() {
        assert_eq!(encode("abc".to_string(), 5), vec![6, 7, 8]);
        assert_eq!(encode("code".to_string(), 3), vec![6, 18, 7, 8]);
        assert_eq!(encode("fff".to_string(), 9), vec![15, 15, 15]);
    }

    #[test]
    fn test_multiple_letters_msg_and_same_length_key() {
        assert_eq!(encode("abc".to_string(), 517), vec![6, 3, 10]);
        assert_eq!(encode("code".to_string(), 3123), vec![6, 16, 6, 8]);
        assert_eq!(encode("fff".to_string(), 997), vec![15, 15, 13]);
    }

    #[test]
    fn test_multiple_letters_msg_and_different_length_key() {
        assert_eq!(encode("abc".to_string(), 517235), vec![6, 3, 10]);
        assert_eq!(encode("code".to_string(), 312), vec![6, 16, 6, 8]);
        assert_eq!(encode("fff".to_string(), 97), vec![15, 13, 15]);
    }
}
