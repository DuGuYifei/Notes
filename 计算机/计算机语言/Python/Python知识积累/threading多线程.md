# threading多线程


```
        self.linkedin_mocker = LinkedInMocker(self.submitted_url)
        self.linkedin_mocker_thread = threading.Thread(target=lambda: self.linkedin_mocker.run())
        self.linkedin_mocker_thread = threading.Thread(target=self.linkedin_mocker.run())
        self.linkedin_mocker_thread.start()
```

注意一个是lamda，一个是将函数返回值给target，返回值会导致主线程阻塞等到返回，所以是错的。