use std::f64::consts::PI;

fn square_area_to_circle(size: f64) -> f64 {
    return size / 4.0 * PI;
}

#[cfg(test)]
mod tests {
    use std::f64::consts::PI;

    use crate::square_area_to_circle;

    #[test]
    fn test_zero() {
        assert_eq!(square_area_to_circle(0.0), 0.0)
    }

    #[test]
    fn test_small_divisible_by_four_number() {
        assert_eq!(square_area_to_circle(4.0), PI)
    }

    #[test]
    fn test_small_indivisible_by_four_number() {
        assert_eq!(square_area_to_circle(8.633241), 2.15831025 * PI)
    }

    #[test]
    fn test_large_divisible_by_four_number() {
        assert_eq!(square_area_to_circle(7243528104.0), 1810882026.0 * PI)
    }

    #[test]
    fn test_large_indivisible_by_four_number() {
        assert_eq!(square_area_to_circle(92340341.4353), 23085085.358825 * PI)
    }
}
