# Validation

[教程](https://blog.csdn.net/liudachu/article/details/131418503)

## 其他要点
1. groups 时候，或者validated() 时候多个组，用`{}`
2. [全局异常处理](https://blog.csdn.net/HD243608836/article/details/116239908)
   1. BindException（@Validated @Valid仅对于表单提交有效，对于以json格式提交将会失效）
        ```
        @ResponseStatus(HttpStatus.BAD_REQUEST)
        @ExceptionHandler(BindException.class)
        public ResultVO bindExceptionHandler(BindException e) {
            List<FieldError> fieldErrors = e.getBindingResult().getFieldErrors();
            List<String> msgList = fieldErrors.stream()
                    .map(o -> o.getDefaultMessage())
                    .collect(Collectors.toList());
            String messages = StringUtils.join(msgList.toArray(), ";");
            log.error("Validation格式校验异常:-------------->{}",messages);
            return ResultVO.builder().errorcode(HttpStatus.BAD_REQUEST.value()).errormessage(messages).build();
        }
        ```
    2. MethodArgumentNotValidException（@Validated @Valid 前端提交的方式为json格式有效，出现异常时会被该异常类处理）：
        ```
        /**
         * @Validated 校验错误异常处理
         */
        @ResponseStatus(HttpStatus.BAD_REQUEST)
        @ExceptionHandler(value = MethodArgumentNotValidException.class)
        public ResultVO handler(MethodArgumentNotValidException e) throws IOException {
            BindingResult bindingResult = e.getBindingResult();
            ObjectError objectError = bindingResult.getAllErrors().stream().findFirst().get();
            String messages = objectError.getDefaultMessage();
            log.error("MethodArgumentNotValidException异常:-------------->{}", messages);
            return ResultVO.builder().errorcode(400).errormessage(messages).build();
        }
        ```
    3.  ConstraintViolationException（@NotBlank @NotNull @NotEmpty etc. constraint package 下的）：
        ```
        @ResponseStatus(HttpStatus.BAD_REQUEST)
        @ExceptionHandler(value = ConstraintViolationException.class)
        public ResultVO handler(ConstraintViolationException e) throws IOException {
            List<String> msgList = new ArrayList<>();
            for (ConstraintViolation<?> constraintViolation : e.getConstraintViolations()) {
                msgList.add(constraintViolation.getMessage());
            }
            String messages = StringUtils.join(msgList.toArray(), ";");
            log.error("entity格式校验异常:-------------->{}",messages);
            return ResultVO.builder().errorcode(400).errormessage(messages).build();
        }
        ```