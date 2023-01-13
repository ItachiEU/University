IFS=$'\n'

png=$(find . -type f -name '*.png')

for IMG in $png
do
   echo $IMG
   convert $IMG $(basename $IMG .png).jpg
done