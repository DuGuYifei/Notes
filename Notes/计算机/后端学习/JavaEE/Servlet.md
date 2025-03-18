# Servlet

## 介绍

class used to extend the capabilities of servers that host applications accessed by means of a request-response model.

Servlets can respond to any type of request, however they are commonly used to extend the web applications, i.e. HTTP

## 转页面

```java
request.getRequestDispatcher("/users.jsp").forward(request, response);
response.sendRedirect(request.getContextPath() + "/users");
```

`getRequestDispatcher`和`sendRedirect`的区别在于前者是服务器内部转发，后者是客户端重定向。

getRequestDispatcher方法是将请求转发给另一个资源（如Servlet或JSP页面）进行处理。它是在服务器端内部完成的，客户端并不感知到请求的转发。该方法接收一个路径参数，指定要转发的目标资源的位置。可以是相对路径或绝对路径。转发后，目标资源将处理请求并生成响应，然后将响应返回给客户端。由于是服务器内部的转发，所以转发后的目标资源可以访问原始请求中的数据。

```java
RequestDispatcher dispatcher = request.getRequestDispatcher("/targetServlet");
dispatcher.forward(request, response);
```

sendRedirect方法是将请求重定向到另一个资源（如Servlet、JSP页面或其他网址）。它是在客户端完成的，服务器端发送一个特殊的响应状态码（302）和重定向目标的位置给客户端浏览器，然后浏览器会自动发送新的请求到重定向的目标位置。因此，客户端浏览器会显示新页面的URL，并且无法访问原始请求的数据。

```java
response.sendRedirect("/targetServlet");
```

## 案例

对应page见[JSP_JSTL](JSP_JSTL.md)

```java
package eeapp.servlets;

import eeapp.ApiClient;
import eeapp.dao.UserDao;
import eeapp.models.User;

import java.io.IOException;
import java.sql.SQLException;
import java.util.List;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;


/**
 * The UserServlet class implements a servlet that
 * response to the request of the user.
 */
@WebServlet(urlPatterns = {"/users", "/users/*"}, name = "UserServlet")
public class UserServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    /**
     * Get request to get all the users or add user page
     * @param request the request from the client
     * @param response the response from the server
     * @throws ServletException if the servlet encounters difficulty
     * @throws IOException if the servlet encounters difficulty
     */
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String path = request.getPathInfo();
        if (path == null) {
            try {
                List<User> users = UserDao.findAll();
                request.setAttribute("users", users);
                request.getRequestDispatcher("/users.jsp").forward(request, response);
            } catch (SQLException e) {
                e.printStackTrace();
            }
        } else if (path.equals("/add")) {
            request.getRequestDispatcher("/adduser.jsp").forward(request, response);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String path = request.getPathInfo();
        if (path == null) {
            try {
                updateUser(request);
            } catch (SQLException e) {
                e.printStackTrace();
            }
        } else if (path.equals("/add")) {
            addUser(request);
        } else if (path.equals("/del")){
            // Get the user ID from the request
            String id = request.getParameter("id");
            try {
                // Delete the user from the database
                UserDao.deleteUser(id);
            } catch (SQLException e) {
                throw new ServletException("Error deleting user", e);
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
        // Redirect the user back to the user list
        response.sendRedirect(request.getContextPath() + "/users");
    }

    private void addUser(HttpServletRequest request) throws IOException {
        // Get the user data from the request
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String email = request.getParameter("email");

        // Create a new use
        ApiClient.addUser(username, password, email);
    }

    private void updateUser(HttpServletRequest request) throws SQLException {
        // Get the user data from the request
        String id = request.getParameter("id");
        String username = request.getParameter("username");
        String email = request.getParameter("email");

        // Update the user
        UserDao.updateUser(id, username, email);
    }
}
```