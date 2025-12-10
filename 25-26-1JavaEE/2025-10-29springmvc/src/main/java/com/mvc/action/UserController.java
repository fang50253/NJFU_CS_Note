package com.mvc.action;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

import com.mvc.bean.User;

@Controller
@RequestMapping("/userjson")
public class UserController {
    public UserController() {
        System.out.println("user controntlll");
    }

    /* @RequestMapping(value="{name}", method = RequestMethod.GET)
       public @ResponseBody User getUser(@PathVariable String name) {

          User user = new User();

          user.setName(name);
          user.setId(1100);
          return user;
       }*/
    @RequestMapping(value = "/n", method = { RequestMethod.GET })  
    @ResponseBody  
    public Map testJson(HttpServletRequest request, HttpServletResponse arg1)  
            throws Exception {  
        // TODO Auto-generated method stub  
        Map map = new HashMap();  
        map.put("status", "n");  
        map.put("info", "failure");  
        return map;  
    }  
}