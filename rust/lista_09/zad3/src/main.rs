fn part_list(arr: Vec<&str>) -> String {
    (1..arr.len())
        .map(|i| format!("({}, {})", arr[..i].join(" "), arr[i..].join(" ")))
        .collect::<Vec<String>>()
        .join("")
}

#[cfg(test)]
mod tests {
    use super::part_list;

    #[test]
    fn test_empty() {
        assert_eq!(part_list(vec![]), "");
    }

    #[test]
    fn test_one_word() {
        assert_eq!(part_list(vec!["jeden"]), "")
    }

    #[test]
    fn test_two_words() {
        assert_eq!(part_list(vec!["jeden", "dwa"]), "(jeden, dwa)")
    }

    #[test]
    fn test_words_with_commas() {
        assert_eq!(part_list(vec!["jeden,", ",dwa"]), "(jeden,, ,dwa)")
    }

    #[test]
    fn test_more_words() {
        assert_eq!(
            part_list(vec!["jeden", "dwa", "trzy", "cztery"]),
            "(jeden, dwa trzy cztery)(jeden dwa, trzy cztery)(jeden dwa trzy, cztery)"
        )
    }
}
