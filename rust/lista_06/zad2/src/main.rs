mod solution {
    pub fn range_extraction(a: &[i32]) -> String {
        if a.len() == 0 {
            return String::new();
        }

        let mut result = String::new();
        let mut range_start = 0;

        for i in 1..=a.len() {
            if i < a.len() && a[i] - 1 == a[i - 1] {
                continue;
            } else if range_start == i - 1 {
                result += &format!(",{}", a[i - 1]);
            } else if range_start == i - 2 {
                result += &format!(",{},{}", a[i - 2], a[i - 1]);
            } else {
                result += &format!(",{}-{}", a[range_start], a[i - 1]);
            }

            range_start = i;
        }

        result[1..].to_string()
    }
}

#[cfg(test)]
mod tests {
    use super::solution;

    #[test]
    fn test_empty() {
        assert_eq!(solution::range_extraction(&[]), "")
    }

    #[test]
    fn test_one_value() {
        assert_eq!(solution::range_extraction(&[3]), "3")
    }

    #[test]
    fn test_multiple_values() {
        assert_eq!(
            solution::range_extraction(&[-4, -2, 1, 5, 8]),
            "-4,-2,1,5,8"
        )
    }

    #[test]
    fn test_range() {
        assert_eq!(solution::range_extraction(&[-2, -1, 0, 1, 2, 3]), "-2-3")
    }

    #[test]
    fn test_single_values_and_ranges() {
        assert_eq!(
            solution::range_extraction(&[
                -6, -3, -2, -1, 0, 1, 3, 4, 5, 7, 8, 9, 10, 11, 14, 15, 17, 18, 19, 20
            ]),
            "-6,-3-1,3-5,7-11,14,15,17-20"
        );
    }
}
