package struktury;

public class ZbiorListowy implements Zbior, Cloneable {
  private class Wezel {
    private Para para;
    private Wezel nast;

    public Wezel(Para p, Wezel n) {
      this.para = p;
      this.nast = n;
    }

    public Wezel(Para p) {
      this(p, null);
    }
  }

  private Wezel lista;
  private int licznosc;

  @Override
  public Para szukaj(String k) {
    Wezel aktualnyWezel = this.lista;
    while (aktualnyWezel != null) {
      if (aktualnyWezel.para.klucz.equals(k)) {
        return aktualnyWezel.para;
      }

      aktualnyWezel = aktualnyWezel.nast;
    }

    return null;
  }

  @Override
  public void wstaw(Para p) {
    if (this.lista == null) {
      this.lista = new Wezel(p);
      this.licznosc += 1;
    } else if (this.lista.para.klucz.equals(p.klucz)) {
      this.lista = new Wezel(p, this.lista.nast);
    } else {
      Wezel aktualnyWezel = this.lista;
      while (aktualnyWezel.nast != null) {
        if (aktualnyWezel.nast.para.klucz.equals(p.klucz)) {
          aktualnyWezel.nast = new Wezel(p, aktualnyWezel.nast.nast);
          return;
        }

        aktualnyWezel = aktualnyWezel.nast;
      }

      this.lista = new Wezel(p, this.lista);
      this.licznosc += 1;
    }
  }

  @Override
  public void usun(String k) {
    if (this.lista == null) return;

    if (this.lista.para.klucz.equals(k)) {
      this.lista = this.lista.nast;
      this.licznosc -= 1;
    } else {
      Wezel aktualnyWezel = this.lista;
      while (aktualnyWezel.nast != null) {
        if (aktualnyWezel.nast.para.klucz.equals(k)) {
          aktualnyWezel.nast = aktualnyWezel.nast.nast;
          this.licznosc -= 1;
        }
      }
    }
  }

  @Override
  public void czysc() {
    this.lista = null;
  }

  @Override
  public int ile() {
    return this.licznosc;
  }

  @Override
  public Object clone() throws CloneNotSupportedException {
    return super.clone();
  }

  public void wypisz() {
    System.out.println("Liczba elementów: " + this.licznosc);
    Wezel aktualnyWezel = this.lista;
    while (aktualnyWezel != null) {
      System.out.println(aktualnyWezel.para.toString());
      aktualnyWezel = aktualnyWezel.nast;
    }
    System.out.println();
  }
}
