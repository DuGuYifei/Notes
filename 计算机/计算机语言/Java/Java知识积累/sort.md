# sort

Arrays.sort(obj[])

Collections.sort(list)

默认升序，多维要自写排序
```Java
// int[][] cuboids
Arrays.sort(cuboids, (a,b)->{int s = (a[2] - b[2]); return s == 0? (a[1] - b[1] == 0? a[0] - b [0] : a[1] - b[1]): s;});
```