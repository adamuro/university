use std::cmp::min;

fn last_digit(str1: &str, str2: &str) -> i32 {
    if str2 == "0" { return 1 }

    let a = str1[(str1.len() - 1)..].parse::<i32>().unwrap();
    let b = str2[(str2.len() - min(str2.len(), 2))..].parse::<u32>().unwrap();
    a.pow(b % 4 + 4) % 10
}

#[cfg(test)]
mod tests {
    use crate::last_digit;

  #[test]
  fn test_zero_pow_zero() {
    assert_eq!(last_digit("0", "0"), 1);
  }
  #[test]
  fn test_zero_pow_non_zero() {
    assert_eq!(last_digit("0", "1"), 0);
    assert_eq!(last_digit("0", "5"), 0);
  }

  #[test]
  fn test_non_zero_to_zero() {
    assert_eq!(last_digit("1", "0"), 1);
    assert_eq!(last_digit("16", "0"), 1);
  }

  #[test]
  fn test_small_positive_numbers() {
    assert_eq!(last_digit("1", "6"), 1);
    assert_eq!(last_digit("16", "1"), 6);
    assert_eq!(last_digit("4", "13"), 4);
  }

  #[test]
  fn test_large_positive_numbers() {
    assert_eq!(last_digit("10000000","10000000000"), 0);
    assert_eq!(last_digit("1606938044258990275541962092341162602522202993782792835301376","2037035976334486086268445688409378161051468393665936250636140449354381299763336706183397376"), 6);
    assert_eq!(last_digit("3715290469715693021198967285016729344580685479654510946723", "68819615221552997273737174557165657483427362207517952651"), 7);
  }
}
