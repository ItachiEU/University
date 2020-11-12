package obliczenia;

public class Maximum extends Operator2Arg {
   public Maximum(Wyrazenie w1, Wyrazenie w2) {
      super(w1, w2);
   }

   public int oblicz() {
      return Math.max(arg1.oblicz(), arg2.oblicz());
   }

   public String toString() {
      return "(Maximum z (" + arg1 + " , " + arg2 + ")";
   }
}