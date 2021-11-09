package struktury;

public class Para implements Cloneable, Comparable<Para> {
    public final String klucz;
    private int wartosc;

    public Para(String k, int w) {
        this.klucz = k;
        this.wartosc = w;
    }

    public int getWartosc() {
        return this.wartosc;
    }

    public void setWartosc(int w) {
        this.wartosc = w;
    }

    @Override
    public String toString() {
        return String.format("%s = %d", this.klucz, this.wartosc);
    }

    @Override
    public boolean equals(Object obj) {
        if (obj.getClass() != Para.class) {
            return false;
        }

        Para p = (Para)obj;
        return this.klucz == p.klucz && this.wartosc == p.wartosc;
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        return super.clone();
    }

    @Override
    public int compareTo(Para p) {
        if (this.wartosc > p.wartosc) return  1;
        if (this.wartosc < p.wartosc) return -1;
        return 0;
    }
}
