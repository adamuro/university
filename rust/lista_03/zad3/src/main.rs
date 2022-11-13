fn zoom(n: i32) -> String {
    let size = n as usize;
    let mid = size / 2;
    let mut result_vec = vec![vec!['■'; size]; size];
    let mut result = String::new().to_owned();

    for i in (1..=mid).step_by(2) {
        for j in mid-i..=mid+i {
            result_vec[mid - i][j] = '□';
            result_vec[mid + i][j] = '□';
            result_vec[j][mid - i] = '□';
            result_vec[j][mid + i] = '□';
        }
    }

    for i in 0..size {
        result.push_str(&(result_vec[i].iter().collect::<String>() + if i != size - 1 {"\n"} else {""}));
    }

    result
}

#[cfg(test)]
mod tests {
    use crate::zoom;

    #[test]
    fn test_1() {
    assert_eq!(zoom(1), "■");
    }

    #[test]
    fn test_3() {
        assert_eq!(zoom(3), "\
□□□
□■□
□□□"
        );
    }

    #[test]
    fn test_5() {
        assert_eq!(zoom(5), "\
■■■■■
■□□□■
■□■□■
■□□□■
■■■■■"
        );
    }

    #[test]
    fn test_7() {
        assert_eq!(zoom(7), "\
□□□□□□□
□■■■■■□
□■□□□■□
□■□■□■□
□■□□□■□
□■■■■■□
□□□□□□□"
        );
    }

    #[test]
    fn test_9() {
        assert_eq!(zoom(9), "\
■■■■■■■■■
■□□□□□□□■
■□■■■■■□■
■□■□□□■□■
■□■□■□■□■
■□■□□□■□■
■□■■■■■□■
■□□□□□□□■
■■■■■■■■■"
        );
    }
}