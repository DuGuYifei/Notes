# timer

```python
class timer:
	start_time = time.time()
	step = 0

	def elapsed(self, reset=true):
		self.step += 1
		print("%d. elapsed: %.1f sec %s"
			% (self.step, time.time() - self.start_time))
		if reset:
			self.reset()

	def reset(self):
		self.start_time = time.time()
		self.step = 0
```

```python
t = timer()
t.elapsed()
t.reset()
t.elapsed()
```

	1. elapsed: 0.0 sec
	1. elapsed: 0.0 sec