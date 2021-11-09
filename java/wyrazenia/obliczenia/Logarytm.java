package obliczenia;

public class Logarytm extends OperatorDwuArg {
  public Logarytm(Wyrazenie wl, Wyrazenie wp) {
    super(wl, wp);
  }

  @Override
  public int oblicz() {
    return (int)(Math.log(this.wyrazeniePrawe.oblicz()) / Math.log(this.wyrazenieLewe.oblicz()));
  }

  @Override
  public String toString() {
    return "log" + this.wyrazenieLewe.toString() + "(" + this.wyrazeniePrawe.toString() + ")";
  }
}
