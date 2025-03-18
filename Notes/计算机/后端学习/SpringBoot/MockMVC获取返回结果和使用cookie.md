# MockMVC获取返回结果和使用cookie

```java
package lsea.controllers;


import lsea.LaboratoryApplication;
import org.junit.Test;
import org.junit.jupiter.api.DisplayName;
import org.junit.runner.RunWith;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.MvcResult;
import org.springframework.test.web.servlet.request.MockHttpServletRequestBuilder;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.result.MockMvcResultHandlers;
import org.springframework.test.web.servlet.result.MockMvcResultMatchers;

import javax.annotation.Resource;
import javax.servlet.http.Cookie;

/**
 * The LogControllerTests class contains unit tests for the LogController class.
 */
@RunWith(SpringRunner.class)
@SpringBootTest(classes = { LaboratoryApplication.class }, webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT)
@AutoConfigureMockMvc
public class LogControllerTests {

    /**
     * This is the MockMvc object that is used to send requests to the endpoints.
     */
    @Resource
    private MockMvc mockMvc;

    /**
     * This test method sends a Post request to the
     */
    @Test
    @DisplayName("Test of LogController")
    public void createOne() throws Exception {

        String userRequest = "{\n" +
                "    \"username\": \"test\",\n" +
                "    \"password\": \"12345678\",\n" +
                "    \"email\": \"123@11.com\"\n" +
                "}";

        String userAuthRequest = "{\n" +
                "    \"password\": \"12345678\",\n" +
                "    \"email\": \"123@11.com\"\n" +
                "}";

        String logRequest = "{\n" +
                "    \"data\": \"test data\",\n" +
                "    \"logType\": \"Success\"\n" +
                "}";

        mockMvc.perform(MockMvcRequestBuilders.post("/api/v1/users")
                .contentType("application/json;charset=UTF-8")
                .content(userRequest))
                .andReturn();

        MvcResult result = mockMvc.perform(MockMvcRequestBuilders.post("/api/v1/users/authorize")
                .contentType("application/json;charset=UTF-8")
                .content(userAuthRequest))
                .andReturn();

        Cookie cookie = result.getResponse().getCookie("token");

        MockHttpServletRequestBuilder requestBuilder = MockMvcRequestBuilders.post("/api/v1/logs")
                .cookie(cookie)
                .contentType("application/json;charset=UTF-8")
                .content(logRequest);

        mockMvc.perform(requestBuilder)
                .andExpect(MockMvcResultMatchers.status().isOk())
                .andDo(MockMvcResultHandlers.print())
                .andReturn();
    }

}
```