import java.math.BigInteger;
import java.util.InputMismatchException;
import java.util.Scanner;

public class Silnia {
  private final static int N_MIN = 0;
  private final static int N_MAX = 100;

  private static BigInteger factorial(Integer n) {
    if (n == 0) {
      return BigInteger.valueOf(1);
    }

    return BigInteger.valueOf(n).multiply(factorial(n - 1));
  }

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    System.out.println("Wprowadź liczbę całkowitą z zakresu [0, 100]");
    try {
      Integer n = scanner.nextInt();
      if (n < N_MIN || n > N_MAX) {
        System.err.println("Wprowadzono liczbę spoza dozwolonego zakresu");
        scanner.close();
        return;
      }
      
      System.out.format("%d! = %s\n", n, factorial(n));
    } catch (InputMismatchException exception) {
      System.err.println("Wprowadzona wartość nie jest liczbą całkowitą");
    } finally {
      scanner.close();
    }
  }
}

