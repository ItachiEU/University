package figury;

public class Trojkat implements Figura {
   public Punkt a, b, c;

   public Trojkat(Punkt a, Punkt b, Punkt c) {
      double pole = Math
            .abs((b.getX() - a.getX()) * (c.getX() - a.getY()) - (b.getY() - a.getY()) * (c.getX() - a.getX())) / 2.0;
      if (pole <= 0.0)
         throw new IllegalArgumentException("Niepoprawny trojkat");
      else {
         this.a = a;
         this.b = b;
         this.c = c;
      }
   }

   @Override
   public void translacja(Wektor v) {
      a.setX(a.getX() + v.dx);
      a.setY(a.getY() + v.dy);
      b.setX(b.getX() + v.dx);
      b.setY(b.getY() + v.dy);
      c.setX(c.getX() + v.dx);
      c.setY(c.getY() + v.dy);
   }

   @Override
   public void obrot(Punkt p, double kat) {
      a.setX((a.getX() - p.getX()) * Math.cos(kat) + (a.getY() - p.getY()) * Math.sin(kat) + p.getX());
      a.setY(Math.abs((a.getX() - p.getX()) * Math.sin(kat) - (a.getY() - p.getY()) * Math.cos(kat) - p.getY()));

      b.setX((b.getX() - p.getX()) * Math.cos(kat) + (b.getY() - p.getY()) * Math.sin(kat) + p.getX());
      b.setY(Math.abs((b.getX() - p.getX()) * Math.sin(kat) - (b.getY() - p.getY()) * Math.cos(kat) - p.getY()));

      c.setX((c.getX() - p.getX()) * Math.cos(kat) + (c.getY() - p.getY()) * Math.sin(kat) + p.getX());
      c.setY(Math.abs((c.getX() - p.getX()) * Math.sin(kat) - (c.getY() - p.getY()) * Math.cos(kat) - p.getY()));
   }

   @Override
   public void odbij(Prosta l) {
      a.setX((a.getX() * (l.b * l.b - l.a * l.a) - 2.0 * l.a * (l.b * a.getY() + l.c)) / (l.b * l.b + l.a * l.a));
      a.setY((a.getY() * (l.a * l.a - l.b * l.b) - 2.0 * l.b * (l.a * a.getX() + l.c)) / (l.a * l.a + l.b * l.b));

      b.setX((b.getX() * (l.b * l.b - l.a * l.a) - 2.0 * l.a * (l.b * b.getY() + l.c)) / (l.b * l.b + l.a * l.a));
      b.setY((b.getY() * (l.a * l.a - l.b * l.b) - 2.0 * l.b * (l.a * b.getX() + l.c)) / (l.a * l.a + l.b * l.b));

      c.setX((c.getX() * (l.b * l.b - l.a * l.a) - 2.0 * l.a * (l.b * c.getY() + l.c)) / (l.b * l.b + l.a * l.a));
      c.setY((c.getY() * (l.a * l.a - l.b * l.b) - 2.0 * l.b * (l.a * c.getX() + l.c)) / (l.a * l.a + l.b * l.b));
   }

}
