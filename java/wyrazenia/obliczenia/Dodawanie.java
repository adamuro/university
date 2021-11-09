package obliczenia;

public class Dodawanie extends OperatorDwuArg {
  public Dodawanie(Wyrazenie wl, Wyrazenie wp) {
    super(wl, wp);
  }

  @Override
  public int oblicz() {
    return this.wyrazenieLewe.oblicz() + this.wyrazeniePrawe.oblicz();
  }

  @Override
  public String toString() {
    return "(" + this.wyrazenieLewe.toString() + " + " + this.wyrazeniePrawe.toString() + ")";
  }
}