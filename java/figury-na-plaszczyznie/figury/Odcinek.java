package figury;

public class Odcinek {
  private Punkt a, b;

  public Odcinek(Punkt a, Punkt b) throws IllegalArgumentException{
    if (a.rowny(b)) {
      throw new IllegalArgumentException("Punkty są takie same");
    }

    // Kopiowanie punktów
    this.a = new Punkt(a);
    this.b = new Punkt(b);
  }

  public void przesun(Wektor v) {
    this.a.przesun(v);
    this.b.przesun(v);
  }

  public void obroc(Punkt p, double kat) {
    this.a.obroc(p, kat);
    this.b.obroc(p, kat);
  }

  public void odbij(Punkt p) {
    this.a.odbij(p);
    this.b.odbij(p);
  }
}
