# JSP_JSTL

## 介绍
JSP是一种Java服务器页面，它是一种基于文本的Web编程语言，它允许开发人员将动态内容嵌入HTML，XML或其他类型的文档中，JSP是一种服务器端技术，它允许开发人员将Java代码嵌入到HTML页面中。

JSTL是一种JSP标准标记库，它是一种JSP标签库，它提供了一组JSP标签，可以用来处理常见的任务，比如迭代和条件判断，JSTL是一种JSP标签库，它提供了一组JSP标签，可以用来处理常见的任务，比如迭代和条件判断。理解为vue的v-for和v-if对于原html标签的扩展。

## 案例
```jsp
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>User List</title>
</head>
<body>
<h1>User List</h1>
<a href="/users/add">Add User</a>
<form id="delete-form" method="post" action="<c:url value='/users/del'/>">
    <input type="text" name="id" size="0px"/>
    <button type="submit">Delete</button>
</form>
<table>
    <thead>
    <tr>
        <th>ID</th>
        <th>Username</th>
        <th>Password</th>
        <th>Created At</th>
        <th>Updated At</th>
        <th>Email</th>
        <th>Confirmation Code</th>
        <th>Confirmed At</th>
        <th>Global Permission</th>
        <th>Actions</th>
    </tr>
    </thead>
    <tbody>
    <c:forEach var="user" items="${users}">
        <tr>
            <form method="post" action="<c:url value='/users'/>">
                <input type="hidden" name="id" value="${user.id}"/>
                <td>${user.id}</td>
                <td><input type="text" name="username" value="${user.username}"/></td>
                <td>${user.password}</td>
                <td>${user.createdAt}</td>
                <td>${user.updatedAt}</td>
                <td><input type="text" name="email" value="${user.email}"/></td>
                <td>${user.confirmationCode}</td>
                <td>${user.confirmedAt}</td>
                <td>${user.globalPermission}</td>
                <td>
                    <button type="submit">Save</button>
                    <a href="/websites?userId=${user.id}">View Websites</a>
                </td>
            </form>
        </tr>
    </c:forEach>
    </tbody>
</table>
</body>
</html>
```