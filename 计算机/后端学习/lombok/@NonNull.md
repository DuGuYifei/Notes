# @NonNull

不能为空，为空在运行时遇到会报 

和[Spring validation](../SpringBoot/Validation.md)`@NotNull`一起使用时，先触发NonNull，validation会无效，所以别一起使用。