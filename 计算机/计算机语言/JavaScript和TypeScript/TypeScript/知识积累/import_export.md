# import, export
[TypeScript学习——模块的export与import_预立数据科技-CSDN博客_typescript的export](https://blog.csdn.net/sinat_16998945/article/details/101534031)

```typescript
/*-----export [test1.js]-----*/
let a = "aaaa";
export { a as b }
 
/*-----import [xxx.js]-----*/
import { b as c } from "./test1.js";
console.log(c); //aaaa
```