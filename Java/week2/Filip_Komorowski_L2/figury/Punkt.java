package figury;

public class Punkt {
   private double x;
   private double y;

   public Punkt(double a, double b) {
      x = a;
      y = b;
   }

   public double getX() {
      return x;
   }

   public double getY() {
      return y;
   }

   public void setX(double x1) {
      x = x1;
   }

   public void setY(double y1) {
      y = y1;
   }
}