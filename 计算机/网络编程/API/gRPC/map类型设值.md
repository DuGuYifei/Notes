# map类型设值
```text-x-java
message RedisHashKeyValueDto {
  string key = 1 [(buf.validate.field).string.min_len = 1];
  map <string, string> value = 2 [(buf.validate.field).map.min_pairs = 1];
  optional int64 timeout = 3 [(buf.validate.field).cel = {
    id: "redis.timeout",
    message: "Value timeout must be between 1 and 2592000 seconds (30 days).",
    expression: "this >= 1 && this <= 2592000"
  }];
  optional string prefix = 4 [(buf.validate.field).string.max_len = 64];
}
```

`put`方法

```text-x-java
public RedisHashKeyValueDto hGetByDto(RedisHashKeyValueGetRequestDto redisHashKeyValueGetRequestDto) {
        String key = redisHashKeyValueGetRequestDto.getPrefix() + redisHashKeyValueGetRequestDto.getKey();
        Long remainTime = redisTemplate.getExpire(key);
        if (remainTime != null) {
            if (remainTime == -2L) {
                throw new RpcException("Key not found.");
            }
        }
        Map<Object, Object> value = redisTemplate.opsForHash().entries(key);
        Map<String, String> valueMap = new HashMap<>();
        for (Map.Entry<Object, Object> entry : value.entrySet()) {
            valueMap.put((String) entry.getKey(), (String) entry.getValue());
        }
        return RedisHashKeyValueDto.newBuilder()
                .setKey(redisHashKeyValueGetRequestDto.getKey())
                .putAllValue(valueMap)
                .setTimeout(remainTime == null ? -2L : remainTime)
                .setPrefix(redisHashKeyValueGetRequestDto.getPrefix())
                .build();
    }
```