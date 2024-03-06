# append和三个点和slice的取集合

```go
for i := range reg.registrations {
	if reg.registrations[i].ServiceURL == url {
		r.mutex.Lock()
		reg.registrations = append(reg.registrations[:i], reg.registrations[i+1:]...)
		r.mutex.Unlock()
		return nil
	}
}
```