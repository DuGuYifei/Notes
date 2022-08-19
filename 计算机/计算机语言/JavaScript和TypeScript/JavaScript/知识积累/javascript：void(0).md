# javascript：void(0)

[What does "javascript:void(0)" mean?](https://stackoverflow.com/questions/1291942/what-does-javascriptvoid0-mean)


The void operator evaluates the given expression and then returns undefined.

The void operator is often used merely to obtain the **undefined** primitive value, usually using “void(0)” (which is equivalent to “void 0”). In these cases, the global variable undefined can be used instead (assuming it has not been assigned to a non-default value).

The reason you’d want to do this with the href of a link is that normally, a **javascript: URL** will redirect the browser to a plain text version of the result of evaluating that JavaScript. **But if the result is undefined, then the browser stays on the same page.** void(0) is just a short and simple script that evaluates to undefined.

An example of what phoenix is talking about is <a href="javascript: dosomething();">DO IT NOW! </a>. If dosomething returns false, then clicking the link will simply cause the browser to exit the page and display "false". However... <a href="javascript: dosomething(); void(0)">DO IT NOW! </a> avoids the problem. Go ahead and paste javascript: 1+1; into your browsers address bar. The browser should display "2"


也有 `<a href="javascript:;">`