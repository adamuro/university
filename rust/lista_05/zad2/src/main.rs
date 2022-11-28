fn even_numbers(array: &Vec<i32>, number: usize) -> Vec<i32> {
    let even = array
        .iter()
        .filter(|&n| n % 2 == 0)
        .cloned()
        .collect::<Vec<i32>>();
    even[(even.len() - number)..].to_vec()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_empty_array() {
        assert_eq!(even_numbers(&vec!(), 0), vec!());
    }

    #[test]
    fn test_only_even_numbers() {
        assert_eq!(even_numbers(&vec!(2, 4, 6, -8), 2), vec!(6, -8));
    }

    #[test]
    fn test_only_odd_numbers() {
        assert_eq!(even_numbers(&vec!(3, 5, 7, -7), 0), vec!());
    }

    #[test]
    fn test_take_all() {
        assert_eq!(
            even_numbers(&vec!(2, 4, 6, -8, 2132), 5),
            vec!(2, 4, 6, -8, 2132)
        );
    }

    #[test]
    fn test_even_and_odd_numbers() {
        assert_eq!(
            even_numbers(&vec!(-22, 5, 3, 11, 26, -6, -7, -8, -9, -8, 26), 2),
            vec!(-8, 26)
        );
    }
}
