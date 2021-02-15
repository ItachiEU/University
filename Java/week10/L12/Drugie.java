import java.io.BufferedReader;
import java.io.FileReader;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Collector;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Drugie {
   static class Trojkat {
      Trojkat(Double a, Double b, Double c) throws Exception {
         if (a + b <= c || a + c <= b || b + c <= a)
            // throw new Exception("niepoprawny trojkąt");
            System.out.println("niepoprawny trojkat");
         this.a = a;
         this.b = b;
         this.c = c;
      }

      Double a;
      Double b;
      Double c;

      @Override
      public String toString() {
         return a.toString() + " " + b.toString() + " " + c.toString();
      }

      public boolean prostokatny() {
         Double[] temp = { this.a, this.b, this.c };
         Arrays.sort(temp);
         return temp[2] * temp[2] == temp[1] * temp[1] + temp[0] * temp[0];
      }

      public boolean rownoboczny() {
         return this.a.equals(this.b) && this.a.equals(this.c);
      }

      public double pole() {
         Double p = 0.5 * (this.a + this.b + this.c);
         return Math.sqrt(p * (p - this.a) * (p - this.b) * (p - this.c));
      }
   }

   static class ObwComparator implements Comparator<Trojkat> {
      @Override
      public int compare(Trojkat a, Trojkat b) {
         return a.a + a.b + a.c < b.a + b.b + b.c ? -1 : 1;
      }
   }

   static class PoleComparator implements Comparator<Trojkat> {
      @Override
      public int compare(Trojkat a, Trojkat b) {
         return a.pole() < b.pole() ? -1 : 1;
      }
   }

   public static void main(String[] args) {
      LinkedList<Trojkat> result = new LinkedList<Trojkat>();
      try (BufferedReader br = new BufferedReader(new FileReader("dane2.txt"))) {
         for (String ln = br.readLine(); ln != null; ln = br.readLine()) {
            assert ln.matches("^\\s*[0-9]+[.]*[0-9]*\\s*[0-9]+[.]*[0-9]\\s*[0-9]+[.]*[0-9]*\\s*(//)*[a-zA-Z0-9]*");
            Pattern p = Pattern.compile("[0-9]+[.]*[0-9]*");
            Matcher m = p.matcher(ln);
            Double[] temp = { 0.0, 0.0, 0.0 };
            int i = 0;
            while (m.find()) {
               temp[i++] = Double.parseDouble(m.group());
            }
            if (i == 0)
               continue;
            Trojkat t = new Trojkat(temp[0], temp[1], temp[2]);
            result.add(t);
            System.out.println(t.toString());
         }
      } catch (Exception ex) {
         System.out.print("tu" + ex);
      }
      System.out.print("a) \n");
      List<Trojkat> sorted = result.stream().sorted(new ObwComparator()).collect(Collectors.toList());
      sorted.forEach(System.out::println);
      System.out.print("b) \n");
      List<Trojkat> prostokatne = result.stream().filter(c -> c.prostokatny()).collect(Collectors.toList());
      prostokatne.forEach(System.out::println);
      System.out.println("\n c)");
      int ct = (int) result.stream().filter(c -> c.rownoboczny()).count();
      System.out.println("Równoboczne: " + ct);
      System.out.println("\n d)");
      Trojkat najmniejszy = result.stream().min(new PoleComparator()).orElseThrow(NoSuchElementException::new);
      System.out.println("min: " + najmniejszy);
      Trojkat najwiekszy = result.stream().max(new PoleComparator()).orElseThrow(NoSuchElementException::new);
      System.out.println("max: " + najwiekszy);
   }
}
