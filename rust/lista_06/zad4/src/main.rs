fn accum(s: &str) -> String {
    s.chars()
        .enumerate()
        .map(|(i, c)| c.to_uppercase().to_string() + &c.to_lowercase().to_string().repeat(i))
        .collect::<Vec<String>>()
        .join("-")
}

#[cfg(test)]
mod tests {
    use crate::accum;

    #[test]
    fn test_empty_string() {
        assert_eq!(accum(""), "")
    }

    #[test]
    fn test_one_lowercase_char() {
        assert_eq!(accum("a"), "A")
    }

    #[test]
    fn test_one_uppercase_char() {
        assert_eq!(accum("A"), "A")
    }

    #[test]
    fn test_multiple_lowercase_chars() {
        assert_eq!(
            accum("zpglnrxqe"),
            "Z-Pp-Ggg-Llll-Nnnnn-Rrrrrr-Xxxxxxx-Qqqqqqqq-Eeeeeeeee"
        );
    }
    #[test]
    fn test_multiple_uppercase_chars() {
        assert_eq!(
            accum("NYFFSGEYYLB"),
            "N-Yy-Fff-Ffff-Sssss-Gggggg-Eeeeeee-Yyyyyyyy-Yyyyyyyyy-Llllllllll-Bbbbbbbbbbb"
        );
    }

    #[test]
    fn test_multiple_uppercase_and_lowercase_chars() {
        assert_eq!(
            accum("EvidjUnokmM"),
            "E-Vv-Iii-Dddd-Jjjjj-Uuuuuu-Nnnnnnn-Oooooooo-Kkkkkkkkk-Mmmmmmmmmm-Mmmmmmmmmmm"
        );
    }
}
