fn dna_strand(dna: &str) -> String {
    let mut result = "".to_owned();

    for c in dna.chars() {
        result.push_str(
            match c {
                'A' => "T",
                'T' => "A",
                'C' => "G",
                'G' => "C",
                _ => ""
            }
        )
    }

    return result;
}

#[cfg(test)]
mod tests {
    use crate::dna_strand;

    #[test]
    fn test_one_letter() {
        assert_eq!(dna_strand("A"), "T");
        assert_eq!(dna_strand("T"), "A");
        assert_eq!(dna_strand("C"), "G");
        assert_eq!(dna_strand("G"), "C");
    }

    #[test]
    fn test_a_and_cg() {
        assert_eq!(dna_strand("ACAC"), "TGTG");
        assert_eq!(dna_strand("GGAGA"), "CCTCT");
    }

    #[test]
    fn test_t_and_cg() {
        assert_eq!(dna_strand("TTGG"), "AACC");
        assert_eq!(dna_strand("CTTTC"), "GAAAG");
    }

    #[test]
    fn test_c_and_at() {
        assert_eq!(dna_strand("ACAC"), "TGTG");
        assert_eq!(dna_strand("CTCCTT"), "GAGGAA");
    }

    #[test]
    fn test_g_and_at() {
        assert_eq!(dna_strand("GAAG"), "CTTC");
        assert_eq!(dna_strand("TGGTG"), "ACCAC");
    }

    #[test]
    fn test_a_and_t() {
        assert_eq!(dna_strand("AT"), "TA");
        assert_eq!(dna_strand("TA"), "AT");
        assert_eq!(dna_strand("TATAAT"), "ATATTA");
    }

    #[test]
    fn test_c_and_g() {
        assert_eq!(dna_strand("CG"), "GC");
        assert_eq!(dna_strand("GC"), "CG");
        assert_eq!(dna_strand("GCCCGG"), "CGGGCC");
    }

    #[test]
    fn test_all_letters() {
        assert_eq!(dna_strand("ACTG"), "TGAC");
        assert_eq!(dna_strand("TAGC"), "ATCG");
        assert_eq!(dna_strand("CCGATTTGGAAC"), "GGCTAAACCTTG");
    }
}
