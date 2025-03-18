# attr()获取属性值配合data-

```html
<h4 class="chose" data-word="Github Repositories">Github Repositories</h4>
```

```css
.chose::before {
	padding-left: 16px;
    content: attr(data-word);
    position: absolute;
    top: 0;
    left: 0.5px;
    height: 0px;
    color: rgba(252, 171, 0, 0.9);
    overflow: hidden;
    z-index: 2;
    animation: redShadow 1s ease-in infinite;
    filter: contrast(200%);
    text-shadow: 1px 0 0 red;
}
```