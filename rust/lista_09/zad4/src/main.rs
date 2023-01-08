fn both(n: i32) -> (Vec<i32>, Vec<i32>) {
    let mut ann: Vec<i32> = vec![1];
    let mut john: Vec<i32> = vec![0];

    for i in 1..n {
        john.push(i - ann[john[i as usize - 1] as usize]);
        ann.push(i - john[ann[i as usize - 1] as usize]);
    }

    (john, ann)
}

fn john(n: i32) -> Vec<i32> {
    both(n).0
}

fn ann(n: i32) -> Vec<i32> {
    both(n).1
}

fn sum_john(n: i32) -> i32 {
    john(n).iter().sum()
}

fn sum_ann(n: i32) -> i32 {
    ann(n).iter().sum()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_john() {
        assert_eq!(john(5), vec![0, 0, 1, 2, 2]);
        assert_eq!(john(10), vec![0, 0, 1, 2, 2, 3, 4, 4, 5, 6]);
    }
    #[test]
    fn test_ann() {
        assert_eq!(ann(5), vec![1, 1, 2, 2, 3]);
        assert_eq!(ann(10), vec![1, 1, 2, 2, 3, 3, 4, 5, 5, 6]);
    }
    #[test]
    fn test_sum_john() {
        assert_eq!(sum_john(5), 5);
        assert_eq!(sum_john(10), 27);
    }
    #[test]
    fn test_sum_ann() {
        assert_eq!(sum_ann(5), 9);
        assert_eq!(sum_ann(10), 32);
    }
}
