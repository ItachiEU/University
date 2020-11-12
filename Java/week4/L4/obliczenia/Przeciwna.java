package obliczenia;

public class Przeciwna extends Operator1Arg {
   public Przeciwna(Wyrazenie w1) {
      super(w1);
   }

   public int oblicz() {
      return -(arg1.oblicz());
   }

   public String toString() {
      return "-(" + arg1 + ")";
   }
}
