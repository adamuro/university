fn spin_words(words: &str) -> String {
    words
        .split_whitespace()
        .map(|word| {
            if word.len() < 5 {
                String::from(word)
            } else {
                word.chars().rev().collect::<String>()
            }
        })
        .fold(String::new(), |a, b| a + " " + &b)
        .trim()
        .to_string()
}

#[cfg(test)]
mod tests {
    use super::spin_words;

    #[test]
    fn test_one_short_word() {
        assert_eq!(spin_words("Hey"), "Hey");
    }

    #[test]
    fn test_multiple_short_words() {
        assert_eq!(spin_words("What is this"), "What is this");
    }

    #[test]
    fn test_one_long_word() {
        assert_eq!(spin_words("Welcome"), "emocleW");
    }

    #[test]
    fn test_multiple_long_words() {
        assert_eq!(spin_words("Three longer words"), "eerhT regnol sdrow");
    }

    #[test]
    fn test_multiple_short_and_long_words() {
        assert_eq!(
            spin_words("You are almost to the last test"),
            "You are tsomla to the last test"
        );
        assert_eq!(
            spin_words("Just kidding there is still one more"),
            "Just gniddik ereht is llits one more"
        );
        assert_eq!(
            spin_words("Seriously this is the last one"),
            "ylsuoireS this is the last one"
        );
    }
}
