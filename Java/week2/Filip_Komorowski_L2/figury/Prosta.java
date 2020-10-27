package figury;

public class Prosta {
   public final double a, b, c;

   public Prosta(double a, double b, double c) {
      if (a == 0 && b == 0) {
         throw new IllegalArgumentException("A i B nie moga byc jednoczesnie zerami");
      } else {
         this.a = a;
         this.b = b;
         this.c = c;
      }
   }

   public static Prosta translacja(Prosta p, Wektor v) {
      return new Prosta(p.a + v.dy, p.b - v.dx, p.c);
   }

   public static boolean rownolegle(Prosta a, Prosta b) {
      return a.a * b.b == a.b * b.a;
   }

   public static boolean prostopadle(Prosta a, Prosta b) {
      return a.a * b.a == -a.b * b.b;
   }

   public static Punkt przeciecie(Prosta a, Prosta b) {
      if (rownolegle(a, b))
         throw new IllegalArgumentException("Brak punktu przeciecia");
      else {
         double W = a.a * b.b - a.b * b.a;
         double Wx = -a.c * b.b - (-b.c) * b.a;
         double Wy = a.a * (-b.c) - a.a * (-b.c);

         return new Punkt(Wx / W, Wy / W);
      }
   }
}
