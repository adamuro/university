fn number(bus_stops:&[(i32,i32)]) -> i32 {
    bus_stops.iter().fold(0, |acc, (come_in, come_out)| acc + come_in - come_out)
}

#[cfg(test)]
mod tests {
    use crate::number;

    #[test]
    fn test_no_stops() {
        assert_eq!(number(&[]), 0);
    }

    #[test]
    fn test_no_people_come_in() {
        assert_eq!(number(&[(0, 0)]), 0);
        assert_eq!(number(&[(0, 0), (0, 0), (0, 0)]), 0);
    }

    #[test]
    fn test_one_stop() {
        assert_eq!(number(&[(5, 0)]), 5);
    }

    #[test]
    fn test_multiple_stops() {
        assert_eq!(number(&[(3,0),(9,1),(4,10),(12,2),(6,1),(7,10)]), 17);
    }

    #[test]
    fn test_no_people_left_after_multiple_stops() {
        assert_eq!(number(&[(2,0),(6,3),(7,6),(5,6),(6,8),(7,10)]), 0);
    }
}