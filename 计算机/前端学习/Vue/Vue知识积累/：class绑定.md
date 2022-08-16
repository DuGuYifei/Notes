# ：class绑定
```html
<img :src="imgSrc" alt="" :title="imgTitle+'!!!'" :class="{active:isActive}" @click="toggleActive">
```

active的存在会由isActive决定