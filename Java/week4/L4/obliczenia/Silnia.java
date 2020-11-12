package obliczenia;

public class Silnia extends Operator1Arg {
   public Silnia(Wyrazenie w1) {
      super(w1);
   }

   public int oblicz() {
      int n = arg1.oblicz(), res = 1;
      while (n > 0) {
         res *= n;
      }
      return res;
   }

   public String toString() {
      return arg1 + "!";
   }
}
