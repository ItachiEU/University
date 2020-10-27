package figury;

public class Odcinek implements Figura {

   public Punkt start, koniec;

   public Odcinek(Punkt a, Punkt b) {
      start = a;
      koniec = b;
   }

   @Override
   public void translacja(Wektor v) {
      start.setX(start.getX() + v.dx);
      start.setY(start.getY() + v.dy);
      koniec.setX(koniec.getX() + v.dx);
      koniec.setY(koniec.getY() + v.dy);
   }

   @Override
   public void obrot(Punkt p, double kat) {
      start.setX((start.getX() - p.getX()) * Math.cos(kat) + (start.getY() - p.getY()) * Math.sin(kat) + p.getX());
      start.setY(
            Math.abs((start.getX() - p.getX()) * Math.sin(kat) - (start.getY() - p.getY()) * Math.cos(kat) - p.getY()));

      koniec.setX((koniec.getX() - p.getX()) * Math.cos(kat) + (koniec.getY() - p.getY()) * Math.sin(kat) + p.getX());
      koniec.setY(Math
            .abs((koniec.getX() - p.getX()) * Math.sin(kat) - (koniec.getY() - p.getY()) * Math.cos(kat) - p.getY()));

   }

   @Override
   public void odbij(Prosta l) {
      start.setX((start.getX() * (l.b * l.b - l.a * l.a) - 2.0 * l.a * (l.b * start.getY() + l.c))
            / (l.b * l.b + l.a * l.a));
      start.setY((start.getY() * (l.a * l.a - l.b * l.b) - 2.0 * l.b * (l.a * start.getX() + l.c))
            / (l.a * l.a + l.b * l.b));

      koniec.setX((koniec.getX() * (l.b * l.b - l.a * l.a) - 2.0 * l.a * (l.b * koniec.getY() + l.c))
            / (l.b * l.b + l.a * l.a));
      koniec.setY((koniec.getY() * (l.a * l.a - l.b * l.b) - 2.0 * l.b * (l.a * koniec.getX() + l.c))
            / (l.a * l.a + l.b * l.b));
   }
}