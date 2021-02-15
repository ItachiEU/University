import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collector;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

class Pierwsze {

   public static boolean isPrime(Integer number) {
      if (number == 1)
         return false;
      return IntStream.rangeClosed(2, number / 2).noneMatch(i -> number % i == 0);
   }

   public static void main(String[] args) {
      ArrayList<Integer> result = new ArrayList<Integer>();
      try (BufferedReader br = new BufferedReader(new FileReader("dane1.txt"))) {
         for (String ln = br.readLine(); ln != null; ln = br.readLine()) {
            assert ln.matches("^\\s*[1-9]*\\s*(//)*[a-zA-Z0-9]*");
            String intValue = ln.replaceAll("[^0-9]", "");
            result.add(Integer.parseInt(intValue));
         }
      } catch (Exception ex) {
         // System.out.print("tu" + ex);
      }
      for (Integer el : result) {
         System.out.print(el + " ");
      }
      List<Integer> sorted = result.stream().sorted().collect(Collectors.toList());
      System.out.println("\n a)");
      sorted.forEach(System.out::println);
      System.out.println("\n b)");
      List<Integer> primes = result.stream().filter(c -> isPrime(c)).collect(Collectors.toList());
      primes.forEach(System.out::println);
      System.out.println("\n c)");

      Integer sum = result.stream().filter(c -> c < 1000).mapToInt(Integer::intValue).sum();
      System.out.println("suma: " + sum);
      System.out.println("\n d)");

      Integer div13 = (int) result.stream().filter(c -> c % 13 == 0).mapToInt(Integer::intValue).count();

      System.out.println("count: " + div13);
   }
}