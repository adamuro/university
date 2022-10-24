fn camel_case(str: &str) -> String {
    str.split_whitespace()
        .map(|s| s[..1].to_owned() + &s[1..])
        .fold(String::new(), |a, b| a + &b)
}

#[cfg(test)]
mod tests {
    use crate::camel_case;

    #[test]
    fn test_empty_string() {
        assert_eq!(camel_case(""), "");
    }

    #[test]
    fn test_one_lowercase_word() {
        assert_eq!(camel_case("capybara"), "Capybara");
    }

    #[test]
    fn test_multiple_lowercase_words() {
        assert_eq!(camel_case("some happy capybaras"), "SomeHappyCapybaras");
    }

    #[test]
    fn test_camelcase_word() {
        assert_eq!(camel_case("Capybara"), "Capybara");
    }

    #[test]
    fn test_multiple_camelcase_words() {
        assert_eq!(camel_case("SomeHappyCapybaras"),"SomeHappyCapybaras");
    }

    #[test]
    fn test_different_cases_words() {
        assert_eq!(camel_case("some HappyCapybaras"), "SomeHappyCapybaras");
    }
}