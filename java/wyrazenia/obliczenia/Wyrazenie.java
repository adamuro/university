package obliczenia;

public abstract class Wyrazenie implements Obliczalny {
  public static int suma (Wyrazenie... wyr) {
    int suma = 0;
    for (Wyrazenie wyrazenie : wyr) {
      suma += wyrazenie.oblicz();
    }

    return suma;
  }

  public static int iloczyn (Wyrazenie... wyr) {
    int suma = 0;
    for (Wyrazenie wyrazenie : wyr) {
      suma *= wyrazenie.oblicz();
    }

    return suma;
  }

  @Override
  public boolean equals(Object obj) {
    if (!(obj instanceof Obliczalny)) {
      return false;
    }

    Obliczalny o = (Obliczalny)obj;
    return o.oblicz() == this.oblicz();
  }
}