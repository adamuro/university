fn comp(a: Vec<i64>, b: Vec<i64>) -> bool {
    let mut a_clone = a.iter().map(|val| val.pow(2)).collect::<Vec<i64>>().clone();
    let mut b_clone = b.clone();
    a_clone.sort();
    b_clone.sort();
    a_clone == b_clone
}

#[cfg(test)]
mod tests {
    use crate::comp;

    #[test]
    fn test_empty_vecs() {
        assert_eq!(comp(vec![], vec![]), true);
    }

    #[test]
    fn test_one() {
        assert_eq!(comp(vec![1], vec![1]), true);
        assert_eq!(comp(vec![1, 1, 1], vec![1, 1, 1]), true);
    }

    #[test]
    fn test_matching_positive_numbers_in_order() {
        assert_eq!(
            comp(
                vec![2, 4, 7, 11, 123],
                vec![2 * 2, 4 * 4, 7 * 7, 11 * 11, 123 * 123]
            ),
            true
        );
    }

    #[test]
    fn test_not_matching_positive_numbers() {
        assert_eq!(
            comp(
                vec![3, 5, 13, 33, 99],
                vec![3 * 3, 5 * 4, 13 * 14, 33 * 33, 99 * 99]
            ),
            false
        );
    }

    #[test]
    fn test_negative_numbers() {
        assert_eq!(
            comp(
                vec![-1, -43, 23, -321],
                vec![1 * 1, 43 * 43, 23 * 23, 321 * 321]
            ),
            true
        );

        assert_eq!(
            comp(
                vec![-3, -54, 4, -345],
                vec![3 * 3, 54 * 45, 4 * 4, 345 * 333]
            ),
            false
        );
    }
}
