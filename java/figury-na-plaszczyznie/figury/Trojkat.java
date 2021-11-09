package figury;

public class Trojkat {
  private Punkt a, b, c;
    
  public Trojkat(Punkt a, Punkt b, Punkt c) throws IllegalArgumentException {
    if (a.rowny(b) || b.rowny(c) || c.rowny(a)) {
      throw new IllegalArgumentException("Przynajmniej dwa z podanych punktów są sobie równe");
    }

    if (b.nachylenieWzgledem(a) == c.nachylenieWzgledem(b)) {
      throw new IllegalArgumentException("Punkty leżą na jednej prostej");
    }
      
    // Kopiowanie punktów
    this.a = new Punkt(a);
    this.b = new Punkt(b);
    this.c = new Punkt(c);
  }

  public void przesun(Wektor v) {
    this.a.przesun(v);
    this.b.przesun(v);
    this.c.przesun(v);
  }

  public void obroc(Punkt p, double kat) {
    this.a.obroc(p, kat);
    this.b.obroc(p, kat);
    this.c.obroc(p, kat);
  }

  public void odbij(Punkt p) {
    this.a.odbij(p);
    this.b.odbij(p);
    this.c.odbij(p);
  }

  @Override
  public String toString() {
    return "(" + this.a.toString() + ", " + this.b.toString() + ", " + this.c.toString() + ")";
  }
}
