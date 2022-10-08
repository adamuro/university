fn count_red_beads(n: u32) -> u32 {
    return if n < 2 { 0 } else { (n - 1) * 2 };
}

#[cfg(test)]
mod tests {
    use crate::count_red_beads;

    #[test]
    fn test_zero() {
        assert_eq!(count_red_beads(0), 0)
    }

    #[test]
    fn test_one() {
        assert_eq!(count_red_beads(1), 0)
    }

    #[test]
    fn test_two() {
        assert_eq!(count_red_beads(2), 2)
    }

    #[test]
    fn test_large_even_number() {
        assert_eq!(count_red_beads(384816), 769630)
    }

    #[test]
    fn test_large_odd_number() {
        assert_eq!(count_red_beads(947521), 1895040)
    }
}
