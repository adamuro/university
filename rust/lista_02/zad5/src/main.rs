fn get_count(string: &str) -> usize {
    let vowels = "aeiou";
    string.chars().filter(|c| vowels.contains(&c.to_string())).count()
}

#[cfg(test)]
mod tests {
    use crate::get_count;


    #[test]
    fn test_empty_string() {
        assert_eq!(get_count(""), 0);
    }

    #[test]
    fn test_only_consonants() {
        assert_eq!(get_count("jbfdrl"), 0);
    }

    #[test]
    fn test_only_vowels() {
        assert_eq!(get_count("aeiou"), 5);
    }

    #[test]
    fn test_repeating_vowels() {
        assert_eq!(get_count("eeeiauuoooo"), 11);
    }

    #[test]
    fn test_vowels_and_consonants() {
        assert_eq!(get_count("sfuisfpewiuralpo"), 7);
    }
}
