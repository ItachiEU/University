class Fixnum
   def czynniki
      res = []
      for i in 1..self do
         if self % i == 0
            res.append(i)
         end
      end
      res
   end
   def doskonala
      temp = 0
      for i in self.czynniki
         if i != self
            temp += i
         end
      end
      temp == self
   end
   def ack(m)
      if self == 0
         m + 1
      elsif m == 0
         (self - 1).ack(1)
      else
         (self-1).ack(self.ack(m-1))
      end
   end
   def slownie
      res = ''
      s = self.to_s
      for i in 0.. s.length do
         case s[i]
         when '0'
            res.concat('zero ')
         when '1'
            res.concat('jeden ')
         when '2'
            res.concat('dwa ')
         when '3'
            res.concat('trzy ')
         when '4'
            res.concat('cztery ')
         when '5'
            res.concat('pięć ')
         when '6'
            res.concat('sześć ')
         when '7'
            res.concat('siedem ')
         when '8'
            res.concat('osiem ')
         when '9'
            res.concat('dziewięć ')
         end
      end
      res
   end
end
 

puts "Ackermann #{2.ack(1)}"
puts "Dzielniki 12 #{12.czynniki}"
puts "6 doskonala? #{6.doskonala}"
puts "Slownie 123 #{123.slownie}"