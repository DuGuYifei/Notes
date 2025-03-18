# QMutex和QMutexLocker

QMutexLocker就是为了简化释放锁

```python
from PyQt5.QtCore import QMutex, QMutexLocker

mutex = QMutex()
mutex.lock()

# do something

mutex.unlock()
```

```python
from PyQt5.QtCore import QMutex, QMutexLocker

mutex = QMutex()

with QMutexLocker(mutex):
    # do something
```