
public class Prostokat extends Figury {
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
      return pole;
   }
}