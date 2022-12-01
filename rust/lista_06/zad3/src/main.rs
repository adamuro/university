use std::cmp::max;

fn longest_slide_down(pyramid: &[Vec<u16>]) -> u16 {
    let mut max_pyramid = pyramid.to_owned();

    for (level, values) in pyramid.iter().enumerate().skip(1) {
        for (i, value) in values.iter().enumerate() {
            let prev_level = &max_pyramid[level - 1];
            max_pyramid[level][i] = match i {
                0 => prev_level.first().unwrap().to_owned(),
                _ if i == level => prev_level.last().unwrap().to_owned(),
                _ => max(prev_level[i - 1], prev_level[i]),
            } + value;
        }
    }

    max_pyramid.last().unwrap().iter().max().unwrap().to_owned()
}

#[cfg(test)]
mod tests {
    use super::longest_slide_down;

    #[test]
    fn test_one_level_pyramid() {
        let pyramid = vec![vec![5]];
        assert_eq!(longest_slide_down(&pyramid), 5)
    }

    #[test]
    fn test_max_value_on_left_edge() {
        let pyramid = vec![vec![3], vec![7, 4], vec![6, 4, 6], vec![11, 5, 9, 3]];
        assert_eq!(longest_slide_down(&pyramid), 27);
    }

    #[test]
    fn test_max_value_on_right_edge() {
        let pyramid = vec![vec![3], vec![7, 8], vec![6, 4, 7], vec![7, 5, 9, 13]];
        assert_eq!(longest_slide_down(&pyramid), 31);
    }

    #[test]
    fn test_small_pyramid() {
        let pyramid = vec![vec![3], vec![7, 4], vec![2, 4, 6], vec![8, 5, 9, 3]];
        assert_eq!(longest_slide_down(&pyramid), 23);
    }

    #[test]
    fn test_large_pyramid() {
        let pyramid = vec![
            vec![75],
            vec![95, 64],
            vec![17, 47, 82],
            vec![18, 35, 87, 10],
            vec![20, 4, 82, 47, 65],
            vec![19, 1, 23, 75, 3, 34],
            vec![88, 2, 77, 73, 7, 63, 67],
            vec![99, 65, 4, 28, 6, 16, 70, 92],
            vec![41, 41, 26, 56, 83, 40, 80, 70, 33],
            vec![41, 48, 72, 33, 47, 32, 37, 16, 94, 29],
            vec![53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14],
            vec![70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57],
            vec![91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48],
            vec![63, 66, 4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31],
            vec![4, 62, 98, 27, 23, 9, 70, 98, 73, 93, 38, 53, 60, 4, 23],
        ];
        assert_eq!(longest_slide_down(&pyramid), 1074);
    }
}
