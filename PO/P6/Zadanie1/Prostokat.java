import java.io.Serializable;

public class Prostokat extends Figury implements Serializable {
   double a, b;

   public Prostokat(double a, double b) {
      this.a = a;
      this.b = b;
   }

   @Override
   public double pole() {
      return a * b;
   }

   @Override
   public String toString() {
      String str = "Prostokat o polu: " + pole();
      return str;
   }
}