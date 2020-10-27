package figury;

public class Wektor {
   public final double dx;
   public final double dy;

   public Wektor(double dx, double dy) {
      this.dx = dx;
      this.dy = dy;
   }

   public static Wektor skladanie(Wektor v, Wektor w) {
      return new Wektor(v.dx + w.dx, v.dy + w.dy);
   }
}
