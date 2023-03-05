# 模拟enum

Go语言没有enum，但是可以这样
```go
const (
	GradeQuiz = GradeType("Quiz")
	GradeTest = GradeType("Test")
	GradeExam = GradeType("Exam")
)
```