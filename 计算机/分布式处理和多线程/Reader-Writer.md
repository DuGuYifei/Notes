# Reader-Writer

## theory
处理访问共享资源的多个实体。

在此模式中，有两种类型的实体：只读取共享资源的读者和读取和修改共享资源的写入者。

目标是提供对共享资源的并发访问，同时保持数据一致性并避免读者和作者之间的冲突。

1. Multiple readers can access the shared resource simultaneously without causing data inconsistencies.
2. Writers must have exclusive access to the shared resource to maintain data integrity.
3. Readers and writers should not be allowed to starve （某个线程长时间阻塞） or be indefinitely blocked.

## ways to implement
1. Read-Write Lock
   1. 读写锁是同步原语，提供对共享资源的**并发读访问**和**独占写访问**。 多个读者可以同时获取读锁，允许并发读操作。 写者必须以独占方式获取写锁，确保以独占方式修改共享资源。 这种实现允许更高程度的并发，只要没有写入者持有写锁。
2. Semaphores
   1. 信号量可用于控制对共享资源的访问。 例如，信号量可以跟踪当前访问资源的读者数量。 **当读者想要访问资源时，如果当前没有作者正在访问它，它就会获取信号量。** 编写器以独占方式获取信号量，确保独占访问资源。 **如果总是有读者等待访问资源，此实现可能会导致写入者饥饿。**
3. Monitors
   1. 监视器，也称为条件变量，为实现读写器模式提供了更高级别的同步机制。 监视器通过为读者和作者提供获取和释放访问权限的方法来管理对共享资源的访问。 读者和写者在监视器上同步，并根据当前状态等待轮到他们访问资源。 此实现允许高效的调度和同步，但需要更高级的编程结构。