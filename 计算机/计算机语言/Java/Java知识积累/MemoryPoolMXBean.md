# MemoryPoolMXBean

获取各个内存区域的使用情况


```java
        var2 = ManagementFactory.getPlatformMXBeans(MemoryPoolMXBean.class).iterator();

        while(var2.hasNext()) {
            MemoryPoolMXBean memoryPoolBean = (MemoryPoolMXBean)var2.next();
            String area = MemoryType.HEAP.equals(memoryPoolBean.getType()) ? "heap" : "nonheap";
            Iterable<Tag> tagsWithId = Tags.concat(this.tags, new String[]{"id", memoryPoolBean.getName(), "area", area});
            Gauge.builder("jvm.memory.used", memoryPoolBean, (mem) -> {
                return JvmMemory.getUsageValue(mem, MemoryUsage::getUsed);
            }).tags(tagsWithId).description("The amount of used memory").baseUnit("bytes").register(registry);
            Gauge.builder("jvm.memory.committed", memoryPoolBean, (mem) -> {
                return JvmMemory.getUsageValue(mem, MemoryUsage::getCommitted);
            }).tags(tagsWithId).description("The amount of memory in bytes that is committed for the Java virtual machine to use").baseUnit("bytes").register(registry);
            Gauge.builder("jvm.memory.max", memoryPoolBean, (mem) -> {
                return JvmMemory.getUsageValue(mem, MemoryUsage::getMax);
            }).tags(tagsWithId).description("The maximum amount of memory in bytes that can be used for memory management").baseUnit("bytes").register(registry);
        }
```