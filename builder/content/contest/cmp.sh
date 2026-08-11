for ((i=1;;i+=1)); do
  echo $i
  ./gen $i > int
  diff -w <(./bf < int) <(./A < int) || break;
done
