# tuple

  tuple是一个固定大小的不同类型值的集合，是泛化的std::pair。我们也可以把他当做一个通用的结构体来用，不需要创建结构体又获取结构体的特征，在某些情况下可以取代结构体使程序更简洁，直观。s**td::tuple理论上可以有无数个任意类型的成员变量，而std::pair只能是2个成员，因此在需要保存3个及以上的数据时就需要使用tuple元组了。**

```cpp
std::tuple<T1, T2, TN> t1;  //创建一个空的tuple对象（使用默认构造），它对应的元素分别是T1和T2...Tn类型，采用值初始化。
std::tuple<T1, T2, TN> t2(v1, v2, ... TN); //创建一个tuple对象，它的两个元素分别是T1和T2 ...Tn类型; 要获取元素的值需要通过tuple的成员get<Ith>(obj)进行获取(Ith是指获取在tuple中的第几个元素，请看后面具体实例)。
std::tuple<T1&> t3(ref&); // tuple的元素类型可以是一个引用
std::make_tuple(v1, v2); // 像pair一样也可以通过make_tuple进行创建一个tuple对象
```

## get<>()

要么返回的是: &引用, 要么返回的是: const &常量引用;

即, std::get<0>( t), 他返回的, 一定是 t这个tuple的 第一个元素的 **引用**, **不会产生 临时对象**!!!

至于是不是const 引用, 自然**取决于: t对象本身, 是不是const**

## auuto &&

auto&& [_, idx, diff] = sweep[k];