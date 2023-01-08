use std::collections::BTreeMap;

fn letter_frequency(input: &str) -> BTreeMap<char, i32> {
    let mut map = BTreeMap::new();
    input.to_lowercase().chars().for_each(|c| {
        if c.is_alphabetic() {
            map.insert(c, map.get(&c).unwrap_or(&0) + 1);
        }
    });

    map
}

#[cfg(test)]
mod tests {
    use super::letter_frequency;
    use std::collections::BTreeMap;

    #[test]
    fn test_empty_string() {
        assert_eq!(letter_frequency(""), BTreeMap::new())
    }

    #[test]
    fn test_lowercase_letter() {
        assert_eq!(letter_frequency("o"), [('o', 1)].iter().cloned().collect())
    }

    #[test]
    fn test_uppercase_letter() {
        assert_eq!(letter_frequency("O"), [('o', 1)].iter().cloned().collect())
    }

    #[test]
    fn test_lowercase_word() {
        assert_eq!(
            letter_frequency("actual"),
            [('a', 2), ('c', 1), ('l', 1), ('t', 1), ('u', 1)]
                .iter()
                .cloned()
                .collect()
        );
    }

    #[test]
    fn test_uppercase_word() {
        assert_eq!(
            letter_frequency("WINDOW"),
            [('w', 2), ('i', 1), ('n', 1), ('d', 1), ('o', 1)]
                .iter()
                .cloned()
                .collect()
        );
    }

    #[test]
    fn test_non_alphabetic_characters() {
        assert_eq!(
            letter_frequency("Hello, I'm 22."),
            [('h', 1), ('e', 1), ('l', 2), ('o', 1), ('i', 1), ('m', 1)]
                .iter()
                .cloned()
                .collect()
        )
    }
}
