# DAO_DTO_Entity_Controller

* DAO(Data Access Object)是一个接口，它定义了访问数据库的方法，比如增删改查等。
* service由DAO组成，service是一个接口，它定义了业务逻辑的方法，比如登录，注册等。
* Entity 是一个类，它定义了数据库表的字段，比如id，name，age等。表示一行数据
* DTO(Data Transfer Object)
  * 在一些简单的应用场景中，直接将实体类作为Controller方法的返回值可能是可行的，
  * 但是在大多数情况下，建议在Controller方法中使用DTO（Data Transfer Object）来封装数据并作为返回值。这是因为DTO可以提供以下几个优点：
    * 保护实体类的隐私：实体类通常包含敏感信息，例如数据库表的主键、外键等，这些信息通常不应该暴露给客户端。使用DTO可以避免将这些信息暴露出去。
    * 精简返回结果：DTO可以根据实际需要来封装返回结果，过滤掉不需要返回给客户端的属性，从而精简返回结果。
    * 灵活性：DTO可以随时根据实际需要进行修改，而不会对实体类造成影响。
    * 解决循环依赖：当实体类之间存在循环依赖关系时，直接返回实体类可能会导致序列化异常。使用DTO可以避免这个问题。
