# localStorage_IndexedDB

在浏览器清除浏览记录时，Local Storage 中的数据会被清除，而 IndexedDB 中的数据不会被清除。

Local Storage 是一个持久化存储区域，用于存储字符串类型的键值对，它的生命周期独立于浏览器的窗口或标签页。当用户清除浏览器缓存、cookie 和浏览记录时，Local Storage 中的数据也会被清除。

IndexedDB 是一个基于事件的 NoSQL 数据库，用于存储复杂的 JavaScript 对象。IndexedDB 存储的数据是异步存储的，其生命周期与 Local Storage 不同，即使浏览器关闭或清除了浏览记录，IndexedDB 中的数据也不会被清除。

需要注意的是，IndexedDB 存储的数据可以被用户手动清除或通过 JavaScript 代码清除。用户可以通过浏览器的开发者工具或清除浏览器数据来清除 IndexedDB 中的数据，而 JavaScript 代码可以通过调用 IndexedDB 的 deleteDatabase() 方法或使用特定的删除方法来删除 IndexedDB 中的数据。因此，如果需要确保数据不被清除，建议使用云存储等专门的文件存储服务。

## local Storage
```javascript
let jsonData = JSON.stringify(originData);
localStorage.setItem('data.json', jsonData);
```

## indexdb
[indexedDB介绍_hjb2722404的博客-CSDN博客_indexeddb](https://blog.csdn.net/hjb2722404/article/details/118789332)

```typescript
const request: IDBOpenDBRequest = indexedDB.open("myDatabase");
const db: IDBDatabase = request.result;
```

### 顺序
`transaction.onupgradeneeded`结束后还是会调用一次`onsuccess`的。


### 索引
创建了索引就像创建了view表，用新的方式做键去搜索
```
objectStore.createIndex(indexName, Path, options)
```

参数说明

* indexName: 索引名称
* Path:  索引在对象中的路径
* options: 可选参数对象
  * unique。如果为true，索引将不允许单个键的值重复。
  * multiEntry 。如果为 true，则当 Path 解析为数组时，索引将为每个数组元素在索引中添加一个条目。 如果为 false，它将添加一个包含数组的条目。
  * locale。目前只有Firefox（43+）支持，这允许您为索引指定区域设置


### 使用put还是add
当使用 IDBObjectStore.add() 方法向 IndexedDB 存储空间添加数据时，如果指定的主键（key）已经存在，则会抛出一个名为 ConstraintError 的异常。因此，添加数据时需要确保主键是唯一的，否则会抛出异常。

如果要修改已经存在的数据，可以使用 `IDBObjectStore.put()` 方法。当使用 put() 方法时，**如果指定的主键已经存在，则会覆盖原有数据。如果主键不存在，则会添加新数据。**