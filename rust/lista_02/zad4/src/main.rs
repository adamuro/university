fn longest(a1: &str, a2: &str) -> String {
    ('a'..='z').filter(|&c| a1.contains(c) || a2.contains(c)).collect()
}

#[cfg(test)]
mod tests {
    use crate::longest;

    #[test]
    fn test_empty_strings() {
        assert_eq!(longest("", ""), "");
    }

    #[test]
    fn test_one_sorted_string() {
        assert_eq!(longest("abcd", ""), "abcd");
    }

    #[test]
    fn test_two_sorted_strings() {
        assert_eq!(longest("aefg", "bcd"), "abcdefg");
    }

    #[test]
    fn test_one_unsorted_string() {
        assert_eq!(longest("bead", ""), "abde");
    }

    #[test]
    fn test_two_unsorted_strings() {
        assert_eq!(longest("dae", "cbf"), "abcdef");
    }

    #[test]
    fn test_repeating_characters() {
        assert_eq!(longest("baadb", "fcccad"), "abcdf");
    }
}