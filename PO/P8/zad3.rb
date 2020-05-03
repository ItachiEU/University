class Jawna
   def initialize(text)
      @text = text
   end
   def to_s
      @text
   end
   def zaszyfruj(key)
      temp = ''
      for i in 0.. @text.length-1 do
         temp += key[@text[i]]
      end
      coded = Zaszyfrowane.new(temp)
   end
end
class Zaszyfrowane
   def initialize(text)
      @text = text
   end
   def to_s
      @text
   end
   def odszyfruj(key)
      temp = ''
      for i in 0.. @text.length - 1 do
            temp += key.invert[@text[i]]
      end
      decoded = Jawna.new(temp)
   end
 end

klucz ={
  'a' => 'c',
  'b' => 'd',
  'c' => 'e',
  'd' => 'f',
  'e' => 'g',
  'f' => 'h',
  'g' => 'i',
  'h' => 'j',
  'i' => 'k',
  'j' => 'l',
  'k' => 'm',
  'l' => 'n',
  'm' => 'o',
  'n' => 'p',
   #itd
}

test = Jawna.new("abcdefghi")
puts test.to_s

test = test.zaszyfruj(klucz)
puts test.to_s

test = test.odszyfruj(klucz)
puts test.to_s