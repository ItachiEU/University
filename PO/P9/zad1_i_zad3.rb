class Proc
   def value(x)
      self.call(x)
   end
   def zerowe(a, b, eps) #bin search
		  mid = (a+b)/2.0
        x = value(mid)
        if x.abs <= eps
            return mid
        else
            left = value(a)
            right = value(b)
            if left*x < 0
                return zerowe(a,mid,eps)
            elsif right * x < 0
                return zerowe(mid,b,eps)
            end
        end
    end
   def poch(x) #pochodna
		h = 0.00000000001
		return (0.0 + value(x + h) - value(x)) / h
   end
   def pole(a, b) #calka oznaczona
		sn = 0.0
		n = 10000
      h = (b-a)/n.to_f
      for i in 1..n
         #puts a+(i-1)*h
         yi = value(a + (i-1)*h)
         #puts yi
			sn += h*yi
      end
		return sn
   end
   def wykres(a, b, nazwa) #wykres

        file = File.open(nazwa, "w")
        file.puts "%!PS"
        x = 200
        y = 1000
        scale = (b - a) / x.to_f
        h = y / 2 # wysokosc
        file.puts "0 " + (value(a) + h).to_s + " moveto"
        for i in 1..x
            file.puts i.to_s + " " + (value(a+i*scale) + h).to_s + " lineto"
        end
        file.puts "stroke"
        file.puts "showpage"
        file.close
    end
end

f= proc {|x| x*x*x -3*x*x+2*x-6}
puts "F(2) -> #{f.value(2)}"
puts "F'(2) -> #{f.poch(3)}"
puts "Calka oznaczona od -1 do 3 -> #{f.pole(-1,3)}"
puts "Miejsce zerowe na przedziale (-1, 5) -> #{f.zerowe(-1, 5, 0.0000001)}"

f.wykres(-1, 3, "plik.PS")